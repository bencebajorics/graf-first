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
// Nev    :
// Neptun :
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
        wCx = 0; // 10 * cosf(t);
        wCy = 0;
        wWx = 20;
        wWy = 20;
    }
};

// 2D camera
Camera camera;

// handle of the shader program
unsigned int shaderProgram;

class Triangle {
    unsigned int vao;	// vertex array object id
    float sx, sy;		// scaling
    float wTx, wTy;		// translation
    float coords[6];
    public:
    Triangle() {
        Animate(0);
    }
    
    float* rotateCoords(vec4 center, float a) {
        a = a * M_PI / 180;
        
        float x1 = ((center.v[0]-1.0f - center.v[0]) * cos(a)) - ((center.v[1]-1.0f - center.v[1]) * sin(a)) + center.v[0];
        float y1 = ((center.v[0]-1.0f - center.v[0]) * sin(a)) + ((center.v[1]-1.0f - center.v[1]) * cos(a)) + center.v[1];
        
        float x2 = ((center.v[0]+1.0f - center.v[0]) * cos(a)) - ((center.v[1]-1.0f - center.v[1]) * sin(a)) + center.v[0];
        float y2 = ((center.v[0]+1.0f - center.v[0]) * sin(a)) + ((center.v[1]-1.0f - center.v[1]) * cos(a)) + center.v[1];
        
        float x3 = ((center.v[0] - center.v[0]) * cos(a)) - ((center.v[1]+1.0f - center.v[1]) * sin(a)) + center.v[0];
        float y3 = ((center.v[0] - center.v[0]) * sin(a)) + ((center.v[1]+1.0f - center.v[1]) * cos(a)) + center.v[1];
        
        coords[0] = x1;
        coords[1] = y1;
        coords[2] = x2;
        coords[3] = y2;
        coords[4] = x3;
        coords[5] = y3;
        return coords;
    }
    
    void Create(vec4 center, float a) {
        glGenVertexArrays(1, &vao);	// create 1 vertex array object
        glBindVertexArray(vao);		// make it active
        
        unsigned int vbo[2];		// vertex buffer objects
        glGenBuffers(2, &vbo[0]);	// Generate 2 vertex buffer objects
        float c[18];
        
        for(int i = 0; i < 3; i++) {
            float* temp;
            temp = rotateCoords(center, i * a);
            for(int j = 0; j < 6; j++){
                c[i*6+j] = temp[j];
                printf("coord: %f\n", c[i*6+j]);
            }
        }
        
        // vertex coordinates: vbo[0] -> Attrib Array 0 -> vertexPosition of the vertex shader
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // make it active, it is an array
        static float vertexCoords[] = { c[6], c[7], c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15], c[16], c[17] };	// vertex data on the CPU
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
        static float vertexColors[] = { 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 };	// vertex data on the CPU
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);	// copy to the GPU
        
        // Map Attribute Array 1 to the current bound vertex buffer (vbo[1])
        glEnableVertexAttribArray(1);  // Vertex position
        // Data organization of Attribute Array 1
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL); // Attribute Array 1, components/attribute, component type, normalize?, tightly packed
    }
    
    void Animate(float t) {
        sx = -0.5 * sinf(t);
        sy = cosf(t);
        wTx = 0;
        wTy = 0;
        printf("anima\n");
    }
    
    void Draw() {
        
        mat4 M(1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 0, 0,
               wTx, wTy, 0, 1); // model matrix
        
        mat4 rotate(sy, sx, 0, 0,
               sx, sy, 0, 0,
               0, 0, 0, 0,
               0, 0, 0, 1); // rotate matrix
        
        
        mat4 MVPTransform = rotate * M * camera.V() * camera.P();
        
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
    float  vertexData[100]; // interleaved data of coordinates and colors
    int    nVertices;       // number of vertices
    public:
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
        if (nVertices >= 20) return;
        
        vec4 wVertex = vec4(cX, cY, 0, 1) * camera.Pinv() * camera.Vinv();
        // fill interleaved data
        vertexData[5 * nVertices] = wVertex.v[0];
        vertexData[5 * nVertices + 1] = wVertex.v[1];
        vertexData[5 * nVertices + 2] = 1; // red
        vertexData[5 * nVertices + 3] = 1; // green
        vertexData[5 * nVertices + 4] = 0; // blue
        nVertices++;
        // copy data to the GPU
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, nVertices * 5 * sizeof(float), vertexData, GL_DYNAMIC_DRAW);
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

public:
    Triangle star_triangles[3];
    
    void Create(vec4 center) {
        star_triangles[0].Create(center, 0);
        star_triangles[1].Create(center, 40);
        star_triangles[2].Create(center, 80);
    }
    
    void Draw() {
        
        star_triangles[0].Draw();
        star_triangles[1].Draw();
        star_triangles[2].Draw();
    }
};
//
//class Spline {
//    
//public:
//    int pointNum;
//    ControllPoint cp_array[100];
//    
//    
//    Spline(int num){
//        pointNum = num;
//    }
//    
//    vec4& p(int i) {
//        return cp_array[i].center;
//    }
//    
//    vec4 a0(int i){
//        return p(i);
//    }
//    
//    vec4 a1(int i){
//        return v(i);
//    }
//    
//    vec4 a2(int i){
//        vec4 a2 = (((p(i+1) * 3.0f) - (p(i) * 3.0f)) / pow(t(i+1) - t(i), 2)) -
//        ((v(i+1) + v(i) * 2.0f)  /  (t(i+1) - t(i)));
//        
//        return a2;
//    }
//    
//    vec4 a3(int i){
//        vec4 a3 = (((p(i) * 2.0f) - (p(i+1) * 2.0f)) / pow(t(i+1) - t(i), 3)) +
//        ((v(i+1) + v(i))  /  pow(t(i+1) - t(i), 2));
//        
//        return a3;
//    }
//    
//    
//    
//    float t(int i){
//        return cp_array[i].time;
//    }
//    
//    vec4 v(int i){
//        return cp_array[i].speed;
//    }
//    
//    void setSpeeds() {
//        vec4 n(100.21f, 234.0f);
//        cp_array[0].speed = n;
//        cp_array[pointNum].speed = n;
//        
//        for(int i = 1; i < pointNum; i++){
//            
//            vec4 first = (p(i+1) - p(i)) / (t(i+1) - t(i));
//            vec4 next = (p(i) - p(i-1)) / (t(i) - t(i-1));
//            cp_array[i].speed = ((first + next) / 2.0f);
//        }
//    }
//    
//    vec4 f(int i, float t){
//        
//        vec4 r = a3(i) * pow(t - cp_array[i].time, 3)
//        + a2(i) * pow(t - cp_array[i].time, 2)
//        + a1(i) * (t - cp_array[i].time) + a0(i);
//        
//        return r;
//    }
//    
//    vec4 d(int i, float t){
//        
//        vec4 r = a3(i) * 3.0f * pow(t - cp_array[i].time, 2)
//        + a2(i) * 2.0f *  (t - cp_array[i].time) + a1(i);
//        
//        return r;
//    }
//    
//    vec4 drawTangent(vec4 ip){
//        vec4 n = dir.norm();
//        
//        glColor3f(0.0f, 1.0f, 0.0f);
//        glBegin(GL_LINE_STRIP); {
//            
//            for(int x = 0; x < 1000; x++) {
//                float y = ((n.x * ip.x) + (n.y * ip.y) - (n.x * x)) / n.y;
//                glVertex2f(x, y);
//            }
//        }
//        glEnd();
//    }
//    
//    void drawSpline(){
//        
//        float end_time = 0.0;
//        
//        for(int i = 0; i < pointNum; i++){
//            end_time += cp_array[i].time;
//        }
//        
//        end_time = ( end_time / pointNum ) + cp_array[ pointNum - 1 ].time;
//        cp_array[pointNum] = ControllPoint(cp_array[0].center, end_time);
//        setSpeeds();
//        
//        glColor3f(1.0f, 1.0f, 1.0f);
//        glBegin(GL_LINE_STRIP); {
//            
//            for(int i = 0; i < pointNum; i++) {
//                float step = (cp_array[i+1].time - cp_array[i].time) / 1000.0f;
//                for(float t = cp_array[i].time; t < cp_array[i+1].time; t += step) {
//                    
//                    vec4 v = f(i, t);
//                    glVertex2f(v.x, v.y);
//                }
//            }
//        }
//        glEnd();
//        
//    }
//    
//};

// The virtual world: collection of two objects
Triangle tr1, tr2;

LineStrip lineStrip;
Star star;

// Initialization, create an OpenGL context
void onInitialization() {
    glViewport(0, 0, windowWidth, windowHeight);
    
    vec4 star_center(0.0, 0.0, 0.0, 1.0);
    
    // Create objects by setting up their vertex data on the GPU
    lineStrip.Create();
    star.Create(star_center);
    
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
    
    //triangle.Draw();
    lineStrip.Draw();
    star.Draw();
    glutSwapBuffers();									// exchange the two buffers
}

// Key of ASCII code pressed
void onKeyboard(unsigned char key, int pX, int pY) {
    if (key == 'd') glutPostRedisplay();         // if d, invalidate display, i.e. redraw
}

// Key of ASCII code released
void onKeyboardUp(unsigned char key, int pX, int pY) {
    
}

// Mouse click event
void onMouse(int button, int state, int pX, int pY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  // GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON and GLUT_DOWN / GLUT_UP
        float cX = 2.0f * pX / windowWidth - 1;	// flip y axis
        float cY = 1.0f - 2.0f * pY / windowHeight;
        lineStrip.AddPoint(cX, cY);
        glutPostRedisplay();     // redraw
    }
}

// Move mouse with key pressed
void onMouseMotion(int pX, int pY) {
}

// Idle event indicating that some time elapsed: do animation here
void onIdle() {
    long time = glutGet(GLUT_ELAPSED_TIME); // elapsed time since the start of the program
    float sec = time / 1000.0f;				// convert msec to sec
    camera.Animate(sec);                    // animate the camera
    //star.star_triangles[0].Animate(sec);	// animate the triangle object
    //star.star_triangles[1].Animate(sec);
    //star.star_triangles[2].Animate(sec);
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
