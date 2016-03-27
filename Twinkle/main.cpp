//=============================================================================================
// Szamitogepes grafika hazi feladat keret. Ervenyes 2016-tol.
// A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sorokon beluli reszben celszeru garazdalkodni, mert a tobbit ugyis toroljuk.
// A beadott program csak ebben a fajlban lehet, a fajl 1 byte-os ASCII karaktereket tartalmazhat.
// Tilos:
// - mast "beincludolni", illetve mas konyvtarat hasznalni
// - faljmuveleteket vegezni a printf-et kivéve
// - new operatort hivni a lefoglalt adat korrekt felszabaditasa nelkul
// - felesleges programsorokat a beadott programban hagyni
// - felesleges kommenteket a beadott programba irni a forrasmegjelolest kommentjeit kiveve
// ---------------------------------------------------------------------------------------------
// A feladatot ANSI C++ nyelvu forditoprogrammal ellenorizzuk, a Visual Studio-hoz kepesti elteresekrol
// es a leggyakoribb hibakrol (pl. ideiglenes objektumot nem lehet referencia tipusnak ertekul adni)
// a hazibeado portal ad egy osszefoglalot.
// ---------------------------------------------------------------------------------------------
// A feladatmegoldasokban csak olyan OpenGL fuggvenyek hasznalhatok, amelyek az oran a feladatkiadasig elhangzottak
//
// NYILATKOZAT
// ---------------------------------------------------------------------------------------------
// Nev    : Bajorics Bence
// Neptun : CG7L3O
// ---------------------------------------------------------------------------------------------
// ezennel kijelentem, hogy a feladatot magam keszitettem, es ha barmilyen segitseget igenybe vettem vagy
// mas szellemi termeket felhasznaltam, akkor a forrast es az atvett reszt kommentekben egyertelmuen jeloltem.
// A forrasmegjeloles kotelme vonatkozik az eloadas foliakat es a targy oktatoi, illetve a
// grafhazi doktor tanacsait kiveve barmilyen csatornan (szoban, irasban, Interneten, stb.) erkezo minden egyeb
// informaciora (keplet, program, algoritmus, stb.). Kijelentem, hogy a forrasmegjelolessel atvett reszeket is ertem,
// azok helyessegere matematikai bizonyitast tudok adni. Tisztaban vagyok azzal, hogy az atvett reszek nem szamitanak
// a sajat kontribucioba, igy a feladat elfogadasarol a tobbi resz mennyisege es minosege alapjan szuletik dontes.
// Tudomasul veszem, hogy a forrasmegjeloles kotelmenek megsertese eseten a hazifeladatra adhato pontokat
// negativ elojellel szamoljak el es ezzel parhuzamosan eljaras is indul velem szemben.
//=============================================================================================

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <vector>

//=============================================================================================
#include <iostream>
#include <fstream>
using namespace std;
//=============================================================================================

#if defined(__APPLE__)
#include <GLUT/GLUT.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/glew.h>		// must be downloaded
#include <GL/freeglut.h>	// must be downloaded unless you have an Apple
#endif

const unsigned int windowWidth = 600, windowHeight = 600;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Innentol modosithatod...

// OpenGL major and minor versions
int majorVersion = 3, minorVersion = 0;

void getErrorInfo(unsigned int handle) {
    int logLen;
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0) {
        char * log = new char[logLen];
        int written;
        glGetShaderInfoLog(handle, logLen, &written, log);
        printf("Shader log:\n%s", log);
        delete log;
    }
}

// check if shader could be compiled
void checkShader(unsigned int shader, char * message) {
    int OK;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &OK);
    if (!OK) {
        printf("%s!\n", message);
        getErrorInfo(shader);
    }
}

// check if shader could be linked
void checkLinking(unsigned int program) {
    int OK;
    glGetProgramiv(program, GL_LINK_STATUS, &OK);
    if (!OK) {
        printf("Failed to link shader program!\n");
        getErrorInfo(program);
    }
}

// vertex shader in GLSL
const char *vertexSource = R"(
#version 140
precision highp float;

uniform mat4 MVP;			// Model-View-Projection matrix in row-major format

in vec2 vertexPosition;		// variable input from Attrib Array selected by glBindAttribLocation
in vec3 vertexColor;	    // variable input from Attrib Array selected by glBindAttribLocation
out vec3 color;				// output attribute

void main() {
    color = vertexColor;														// copy color from input to output
    gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0, 1) * MVP; 		// transform to clipping space
}
)";

// fragment shader in GLSL
const char *fragmentSource = R"(
#version 140
precision highp float;

in vec3 color;				// variable input: interpolated color of vertex shader
out vec4 fragmentColor;		// output that goes to the raster memory as told by glBindFragDataLocation

void main() {
    fragmentColor = vec4(color, 1); // extend RGB to RGBA
}
)";

// row-major matrix 4x4
struct mat4 {
    float m[4][4];
public:
    mat4() {}
    mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
        m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }
    
    mat4 operator*(const mat4& right) {
        mat4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = 0;
                for (int k = 0; k < 4; k++) result.m[i][j] += m[i][k] * right.m[k][j];
            }
        }
        return result;
    }
    operator float*() { return &m[0][0]; }
};


// 3D point in homogeneous coordinates
struct vec4 {
    float v[4];
    
    vec4(float x = 0, float y = 0, float z = 0, float w = 1) {
        v[0] = x; v[1] = y; v[2] = z; v[3] = w;
    }
    
    vec4 operator*(const mat4& mat) {
        vec4 result;
        for (int j = 0; j < 4; j++) {
            result.v[j] = 0;
            for (int i = 0; i < 4; i++) result.v[j] += v[i] * mat.m[i][j];
        }
        return result;
    }
    
    vec4 operator*(float f) {
        return vec4(v[0] * f, v[1] * f, v[2] * f);
    }
    
    vec4 operator/(float f) {
        return vec4(v[0] / f, v[1] / f, v[2] / f);
    }
    
    vec4 operator+(const vec4& vec) {
        return vec4(v[0] + vec.v[0], v[1] + vec.v[1], v[2] + vec.v[2]);
    }
    vec4 operator-(const vec4& vec) {
        return vec4(v[0] - vec.v[0], v[1] - vec.v[1], v[2] - vec.v[2]);
    }
};

// 2D camera
struct Camera {
    float wCx, wCy;	// center in world coordinates
    float wWx, wWy;	// width and height in world coordinates
public:
    Camera() {
        Animate(0);
    }
    
    mat4 V() { // view matrix: translates the center to the origin
        return mat4(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    -wCx, -wCy, 0, 1);
    }
    
    mat4 P() { // projection matrix: scales it to be a square of edge length 2
        return mat4(2 / wWx, 0, 0, 0,
                    0, 2 / wWy, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
    }
    
    mat4 Vinv() { // inverse view matrix
        return mat4(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    wCx, wCy, 0, 1);
    }
    
    mat4 Pinv() { // inverse projection matrix
        return mat4(wWx / 2, 0, 0, 0,
                    0, wWy / 2, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
    }
    
    void Animate(float t) {
        //wCx = 0; // 10 * cosf(t);
        //wCy = 0;
        wWx = 20;
        wWy = 20;
    }
};

// 2D camera
Camera camera;
bool spacePressed = false;
// handle of the shader program
unsigned int shaderProgram;

class Triangle {
    unsigned int vao;	// vertex array object id
    float wTx, wTy;		// translation
    float sx, sy;
public:
    
    vec4 color;
    
    Triangle() {
        Animate(0);
    }
    
    void Create() {
        glGenVertexArrays(1, &vao);	// create 1 vertex array object
        glBindVertexArray(vao);		// make it active
        
        unsigned int vbo[2];		// vertex buffer objects
        glGenBuffers(2, &vbo[0]);	// Generate 2 vertex buffer objects
        
        // vertex coordinates: vbo[0] -> Attrib Array 0 -> vertexPosition of the vertex shader
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // make it active, it is an array
        static float vertexCoords[] = { -1.0f, -sqrtf(3.0f) / 3.0f, 1.0f, -sqrtf(3.0f) / 3.0f, -0.0f, 2 * sqrtf(3.0f) / 3.0f };	// vertex data on the CPU
        glBufferData(GL_ARRAY_BUFFER,      // copy to the GPU
                     sizeof(vertexCoords),  // number of the vbo in bytes
                     vertexCoords,		   // address of the data array on the CPU
                     GL_STATIC_DRAW);	   // copy to that part of the memory which is not modified
        // Map Attribute Array 0 to the current bound vertex buffer (vbo[0])
        glEnableVertexAttribArray(0);
        // Data organization of Attribute Array 0
        glVertexAttribPointer(0,			// Attribute Array 0
                              2, GL_FLOAT,  // components/attribute, component type
                              GL_FALSE,		// not in fixed point format, do not normalized
                              0, NULL);     // stride and offset: it is tightly packed
        
						  // vertex colors: vbo[1] -> Attrib Array 1 -> vertexColor of the vertex shader
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // make it active, it is an array
        float vertexColors[] = { color.v[0], color.v[1], color.v[2], color.v[0], color.v[1], color.v[2], color.v[0], color.v[1], color.v[2] };	// vertex data on the CPU
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);	// copy to the GPU
        
        // Map Attribute Array 1 to the current bound vertex buffer (vbo[1])
        glEnableVertexAttribArray(1);  // Vertex position
        // Data organization of Attribute Array 1
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL); // Attribute Array 1, components/attribute, component type, normalize?, tightly packed
    }
    
    void Animate(float a) {
        a = a * M_PI / 180.0f;
        sx = sinf(a);
        sy = cosf(a);
        wTx = 0; // 4 * cosf(t / 2);
        wTy = 0; // 4 * sinf(t / 2);
    }
    
    void Draw(float size, mat4 Rp, mat4 Ms) {
        
        size = size / 60.0f;
        
        mat4 S(size, 0, 0, 0,
               0, size, 0, 0,
               0, 0, 0, 0,
               0, 0, 0, 1); // scale matrix
        
        mat4 R(sy, -sx, 0, 0,
               sx, sy, 0, 0,
               0, 0, 0, 0,
               0, 0, 0, 1); // rotate matrix
        
        mat4 M(1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 0, 0,
               wTx, wTy, 0, 1); // M matrix
        
        mat4 MVPTransform = S * R * Rp * M * Ms * camera.V() * camera.P();
        
        // set GPU uniform matrix variable MVP with the content of CPU variable MVPTransform
        int location = glGetUniformLocation(shaderProgram, "MVP");
        if (location >= 0) glUniformMatrix4fv(location, 1, GL_TRUE, MVPTransform); // set uniform variable MVP to the MVPTransform
        else printf("uniform MVP cannot be set\n");
        
        glBindVertexArray(vao);	// make the vao and its vbos active playing the role of the data source
        glDrawArrays(GL_TRIANGLES, 0, 3);	// draw a single triangle with vertices defined in vao
    }
};

class LineStrip {
    GLuint vao, vbo;        // vertex array object, vertex buffer object
    int    nVertices;       // number of vertices
public:
    float  vertexData[27500];
    LineStrip() {
        nVertices = 0;
    }
    void Create() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glGenBuffers(1, &vbo); // Generate 1 vertex buffer object
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // Enable the vertex attribute arrays
        glEnableVertexAttribArray(0);  // attribute array 0
        glEnableVertexAttribArray(1);  // attribute array 1
        // Map attribute array 0 to the vertex data of the interleaved vbo
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0)); // attribute array, components/attribute, component type, normalize?, stride, offset
        // Map attribute array 1 to the color data of the interleaved vbo
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
    }
    
    void AddPoint(float cX, float cY) {
        //printf("%f,    %f\n", cX, cY);
        if (nVertices >= 5500) return;
        
        vec4 wVertex = vec4(cX, cY, 0, 1) * camera.Pinv() * camera.Vinv();
        // fill interleaved data
        vertexData[5 * nVertices] = wVertex.v[0];
        vertexData[5 * nVertices + 1] = wVertex.v[1];
        vertexData[5 * nVertices + 2] = 0.4; // red
        vertexData[5 * nVertices + 3] = 0.2; // green
        vertexData[5 * nVertices + 4] = 0.0; // blue
        nVertices++;
        // copy data to the GPU
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, nVertices * 5 * sizeof(float), vertexData, GL_DYNAMIC_DRAW);
    }
    
    void Clear_data() {
        
        for (int i = 0; i < 27500; i++) {
            vertexData[i] = 0;
        }
        nVertices = 0;
    }
    
    void Draw() {
        if (nVertices > 0) {
            mat4 VPTransform = camera.V() * camera.P();
            
            int location = glGetUniformLocation(shaderProgram, "MVP");
            if (location >= 0) glUniformMatrix4fv(location, 1, GL_TRUE, VPTransform);
            else printf("uniform MVP cannot be set\n");
            
            glBindVertexArray(vao);
            glDrawArrays(GL_LINE_STRIP, 0, nVertices);
        }
    }
};

class Star {
    Triangle triangles[3];
    float sx, sy;
    int caught;
public:
    float wTx, wTy;
    float mass;
    
    Star() {
    }
    
    void Create(float r, float g, float b, float mass, float pos) {
        
        this->mass = mass;
        caught = 0;
        
        Triangle triangle1;
        Triangle triangle2;
        Triangle triangle3;
        
        vec4 color(r, g, b, 0);
        triangle1.color = color;
        triangle2.color = color;
        triangle3.color = color;
        
        triangle1.Create();
        triangle2.Create();
        triangle3.Create();
        
        triangles[0] = triangle1;
        triangles[1] = triangle2;
        triangles[2] = triangle3;
        
        wTx = pos;
        wTy = pos;
    }
    
    void Animate(float t) {
        sx = 0.5f * sinf(t);
        sy = cosf(t);
    }
    
    void AnimateTriangles() {
        
        for (int i = 0; i < 3; i++) {
            triangles[i].Animate(i * 40);
        }
    }
    
    void NGravity(Star big, float t) {
        float F, G, Rsqr;
        G = 0.005f;
        
        Rsqr = pow((big.wTx - wTx), 2) + pow((big.wTy - wTy), 2);
        
        if (Rsqr == 0) {
            Rsqr = 0.00001;
        }
        F = G * mass * big.mass / Rsqr;
        
        vec4 velocity;
        
        float mu = ((F - (0.00001f * mass)) / F);
        if(mu > 1.0f) mu = 1.0f;
        
        printf("mu %f\n", mu);
        velocity = vec4((big.wTx - wTx) / sqrt(Rsqr), (big.wTy - wTy) / sqrt(Rsqr), 0.0, 1.0) * (F + ((-1.0)*mu   * F )) * t;
        
        //printf("wTx:%f, wTx:%f\n", wTx, wTy);
        //if(firstTime == 0) {
//            float d0 = sqrt(pow((wTx - 0.0f), 2) + pow((wTy - 0.0f), 2));
//            wTx = wTx/d0;
//            wTy = wTy/d0;
//            firstTime++;
        //}
                     
        wTx = wTx + velocity.v[0] * t;
        wTy = wTy + velocity.v[1] * t;
    }
    
    void Draw(float pos) {
        mat4 R(sy, -sx, 0, 0,
               sx, sy, 0, 0,
               0, 0, 0, 0,
               0, 0, 0, 1); // rotate matrix
        
        mat4 M(1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 0, 0,
               wTx, wTy, 0, 1); // M matrix
        
        
        for (int i = 0; i < 3; i++) {
            triangles[i].Draw(mass * 10.0f, R, M);
        }
    }
    
};

class ControllPoint {
    
public:
    vec4 center;
    vec4 speed;
    float time;
    
    ControllPoint() {}
    
    ControllPoint(vec4 center, float t) : center(center), time(t) {
        speed = vec4(0.0, 0.0, 0.0, 0.0);
    }
    
    ~ControllPoint() {}
    
};

class Spline {
public:
    int cpNum;
    ControllPoint cp_array[11];
    LineStrip line;
    
    
    Spline(int num) {
        cpNum = num;
    }
    
    vec4& p(int i) {
        return cp_array[i].center;
    }
    
    vec4 a0(int i) {
        return p(i);
    }
    
    vec4 a1(int i) {
        return v(i);
    }
    
    vec4 a2(int i) {
        vec4 a2 = (((p(i + 1) * 3.0f) - (p(i) * 3.0f)) / pow(t(i + 1) - t(i), 2)) -
        ((v(i + 1) + v(i) * 2.0f) / (t(i + 1) - t(i)));
        
        return a2;
    }
    
    vec4 a3(int i) {
        vec4 a3 = (((p(i) * 2.0f) - (p(i + 1) * 2.0f)) / pow(t(i + 1) - t(i), 3)) +
        ((v(i + 1) + v(i)) / pow(t(i + 1) - t(i), 2));
        
        return a3;
    }
    
    
    
    float t(int i) {
        return cp_array[i].time;
    }
    
    vec4 v(int i) {
        return cp_array[i].speed;
    }
    
    void setSpeeds() {
        //vec4 n(100.21f, 234.0f ,0.0f, 1.0f);
        //vec4 n(-0.1529f, 0.3207f ,0.0f, 1.0f);
        //	cp_array[0].speed = n;
        //	cp_array[cpNum + 1].speed = n;
        
        for (int i = 0; i < cpNum + 1; i++) {
            
            vec4 first = (p(i + 1) - p(i)) / (t(i + 1) - t(i));
            vec4 next = (p(i) - p(i - 1)) / (t(i) - t(i - 1));
            cp_array[i].speed = ((first + next) / 2.0f);
        }
    }
    
    vec4 f(int i, float t) {
        
        vec4 r = a3(i) * pow(t - cp_array[i].time, 3)
        + a2(i) * pow(t - cp_array[i].time, 2)
        + a1(i) * (t - cp_array[i].time) + a0(i);
        
        //r = r /10.0f;
        //printf("vector: x: %f, y: %f\n", r.v[0], r.v[1]);
        
        return r;
    }
    
    vec4 d(int i, float t) {
        
        vec4 r = a3(i) * 3.0f * pow(t - cp_array[i].time, 2)
        + a2(i) * 2.0f *  (t - cp_array[i].time) + a1(i);
        
        return r;
    }
    
    void createLine() {
        
        float step = 0.0f;
        
        cp_array[cpNum + 1] = ControllPoint(cp_array[0].center, cp_array[cpNum].time+500.0f);
        setSpeeds();
        
        line.Clear_data();
        for (int j = 0; j < cpNum+1; j++) {
            step = (cp_array[j+1].time - cp_array[j].time) / 500.0f;
            
            
            for (int i = 0; i < 500; i++) {
                
                vec4 v = f(j, cp_array[j].time + i * step);
                line.AddPoint(v.v[0] + camera.wCx, v.v[1] + camera.wCy);
                
            }
            
        }        
    }
    
};

// The virtual world: collection of two objects
ControllPoint cp;
Spline spline(0);
LineStrip lineStrip;

Star starBig;
Star starMiddle;
Star starSmall;

// Initialization, create an OpenGL context
void onInitialization() {
    glViewport(0, 0, windowWidth, windowHeight);
    
    // Create objects by setting up their vertex data on the GPU
    lineStrip.Create();
    starBig.Create(1.0f, 1.0f, 0.0f, 6.0f, 0.0f);
    starMiddle.Create(0.6f, 0.6f, 0.1f, 4.0f, 2.0f);
    starSmall.Create(0.5f, 0.4f, 0.2f, 3.0f, -3.0f);
    spline.line.Create();
    
    // Create vertex shader from string
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!vertexShader) {
        printf("Error in vertex shader creation\n");
        exit(1);
    }
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    checkShader(vertexShader, "Vertex shader error");
    
    // Create fragment shader from string
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragmentShader) {
        printf("Error in fragment shader creation\n");
        exit(1);
    }
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader, "Fragment shader error");
    
    // Attach shaders to a single program
    shaderProgram = glCreateProgram();
    if (!shaderProgram) {
        printf("Error in shader program creation\n");
        exit(1);
    }
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    // Connect Attrib Arrays to input variables of the vertex shader
    glBindAttribLocation(shaderProgram, 0, "vertexPosition"); // vertexPosition gets values from Attrib Array 0
    glBindAttribLocation(shaderProgram, 1, "vertexColor");    // vertexColor gets values from Attrib Array 1
    
    // Connect the fragmentColor to the frame buffer memory
    glBindFragDataLocation(shaderProgram, 0, "fragmentColor");	// fragmentColor goes to the frame buffer memory
    
    // program packaging
    glLinkProgram(shaderProgram);
    checkLinking(shaderProgram);
    // make this program run
    glUseProgram(shaderProgram);
}

void onExit() {
    glDeleteProgram(shaderProgram);
    printf("exit");
}

// Window has become invalid: Redraw
void onDisplay() {
    glClearColor(0, 0, 0, 0);							// background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

    //lineStrip.Draw();
    spline.line.Draw();
    starBig.Draw(0.0f);
    starMiddle.Draw(2.0f);
    starSmall.Draw(-3.0f);
    
    glutSwapBuffers();									// exchange the two buffers
}

// Key of ASCII code pressed
void onKeyboard(unsigned char key, int pX, int pY) {
    if (key == 'd') glutPostRedisplay();         // if d, invalidate display, i.e. redraw
    if (key == 's') {
        for (int i = 0; i < spline.cpNum + 1; i++) {
            printf("cp:  x:%f, y:%f time:%f\n", spline.cp_array[i].center.v[0], spline.cp_array[i].center.v[1], spline.cp_array[i].time);
        }
    }
    if (key == ' ') {
        if (spacePressed == false)
            spacePressed = true;
    }
}

// Key of ASCII code released
void onKeyboardUp(unsigned char key, int pX, int pY) {
    
}

// Mouse click event
void onMouse(int button, int state, int pX, int pY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  // GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON and GLUT_DOWN / GLUT_UP
        
        float cX = 2.0f * pX / windowWidth - 1;	// flip y axis
        float cY = 1.0f - 2.0f * pY / windowHeight;
        
        if (spline.cpNum <= 10) {
            
            //lineStrip.AddPoint(cX, cY);
            
            long t = glutGet(GLUT_ELAPSED_TIME);
            
            vec4 center(cX, cY, 0.0f, 1.0f);
            
            spline.cp_array[spline.cpNum] = ControllPoint(center, t);
            
            if (spline.cpNum > 0) {
                spline.createLine();
            }
            spline.cpNum = spline.cpNum + 1;
        }
        
        glutPostRedisplay();     // redraw
    }
}

// Move mouse with key pressed
void onMouseMotion(int pX, int pY) {
}

int splinePosition = 0;
float lastTime = 0;

// Idle event indicating that some time elapsed: do animation here
void onIdle() {
    long time = glutGet(GLUT_ELAPSED_TIME); // elapsed time since the start of the program
    float sec = time / 1000.0f;				// convert msec to sec
    camera.Animate(sec);					// animate the camera
    
    starBig.AnimateTriangles();
    starMiddle.AnimateTriangles();
    starSmall.AnimateTriangles();
    
    if (spline.cpNum > 1) {
        
        starBig.wTx = spline.line.vertexData[splinePosition * 5];
        starBig.wTy = spline.line.vertexData[splinePosition * 5 + 1];
        
        if (splinePosition == (spline.cpNum) * 500 -1 ) splinePosition = 0;
        splinePosition++;
        
        float dTime = 0.005;
        for (float t = lastTime; t <= sec; t += dTime) {
            starMiddle.NGravity(starBig, t);
            starSmall.NGravity(starBig, t);
            lastTime = sec;
        }
    }
    
    if (spacePressed) {
        camera.wCx = starBig.wTx;
        camera.wCy = starBig.wTy;
        //printf("small.x: %f, small.y: %f", starSmall.wTx, starSmall.wTy);
    }
    
    starBig.Animate(sec);
    starMiddle.Animate(sec);
    starSmall.Animate(sec);
    
    glutPostRedisplay();					// redraw the scene
}

// Idaig modosithatod...
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
#if !defined(__APPLE__)
    glutInitContextVersion(majorVersion, minorVersion);
#endif
    glutInitWindowSize(windowWidth, windowHeight);				// Application window is initially of resolution 600x600
    glutInitWindowPosition(100, 100);							// Relative location of the application window
#if defined(__APPLE__)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);  // 8 bit R,G,B,A + double buffer + depth buffer
#else
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif
    glutCreateWindow(argv[0]);
    
#if !defined(__APPLE__)
    glewExperimental = true;	// magic
    glewInit();
#endif
    
    printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
    printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
    printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    printf("GL Version (integer) : %d.%d\n", majorVersion, minorVersion);
    printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    onInitialization();
    
    glutDisplayFunc(onDisplay);                // Register event handlers
    glutMouseFunc(onMouse);
    glutIdleFunc(onIdle);
    glutKeyboardFunc(onKeyboard);
    glutKeyboardUpFunc(onKeyboardUp);
    glutMotionFunc(onMouseMotion);
    
    glutMainLoop();
    onExit();
    return 1;
}
