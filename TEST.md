# Sass Service


<a name="overview"></a>
## Overview
Service to render sass


### Version information
*Version* : 0.1.0

<a name="paths"></a>
## Paths

<a name="render-post"></a>
### Renders scss to css
```
POST /render
```


#### Description
The /render post endpoint render the given scss parameter into css elements using node-sass, and returns them if everything went well.

  Example call:
  ```
  SassService.post('/render', {
    '$font-stack:    Helvetica, sans-serif;
     $primary-color: #333;
     body {
      font: 100% $font-stack;
      color: $primary-color;
    }'
  })
  ```


#### Parameters

|Type|Name|Description|Schema|Default|
|---|---|---|---|---|
|**Body**|**scss**  <br>*required*|The scss object you want to turn into css.|[Scss](#scss)||


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|The response is the rendered object.|object|


#### Tags

* Post




<a name="definitions"></a>
## Definitions

<a name="scss"></a>
### Scss

|Name|Description|Schema|
|---|---|---|
|**scss**  <br>*optional*|Some scss code.|string|
