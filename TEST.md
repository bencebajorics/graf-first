# Site Engine Model Service


<a name="overview"></a>
## Overview
Service for site-engine collection


### Version information
*Version* : 0.2.0




<a name="paths"></a>
## Paths

<a name="healthy-get"></a>
### Returns 'OK' to show that the service is working
```
GET /__healthy
```


#### Description
The /__healthy endpoint gives back 'OK' with code 200, to enable the user to check whether the service is working or not.


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|An OK answer.|string|


#### Tags

* Get


<a name="count-get"></a>
### Counts the model elements in the database
```
GET /count
```


#### Description
The /count endpoint gives back the number of service model elements in the database. The object's schema is described at the end in the Definitions section.


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|The number of elements.|integer|
|**400**|Validation error by MongoDB.|[MongoDB_Error](#mongodb_error)|


#### Tags

* Get


<a name="rest-post"></a>
### Creates a new model element with the data object given as body parameter
```
POST /rest
```


#### Description
The /rest post endpoint creates and adds a new element to the database, in form of a SiteEngineSchema. The object's schema is described at the end in the Definitions section.


#### Parameters

|Type|Name|Description|Schema|Default|
|---|---|---|---|---|
|**Body**|**Object**  <br>*required*|The expected object with one required parameters.|[SiteEngineSchema](#siteengineschema)||


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**201**|The response is 'ok', if everything went well.|string|
|**400**|Validation error by MongoDB.|[MongoDB_Error](#mongodb_error)|


#### Tags

* Post


<a name="rest-get"></a>
### Search database for all the service model elements
```
GET /rest
```


#### Description
The /rest get endpoint gives back the service model elements from the database. The object's schema is described at the end in the Definitions section.


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|The returned model elements.|< [SiteEngineSchema](#siteengineschema) > array|
|**400**|Validation error by MongoDB.|[MongoDB_Error](#mongodb_error)|


#### Tags

* Get


<a name="rest-patch"></a>
### Search in database and update one service model element
```
PATCH /rest
```


#### Description
The /rest patch endpoint find and update one service model element from the database. The element is determined by an array's first object. In the second object of the array you give the parameters you want to change. The object's schema is described at the end in the Definitions section.


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|The updated model elements.|< [SiteEngineSchema](#siteengineschema) > array|
|**400**|Validation error by MongoDB.|[MongoDB_Error](#mongodb_error)|


#### Tags

* Patch


<a name="rest-id-get"></a>
### Search database for a particular service model element
```
GET /rest/{id}
```


#### Description
The /rest/:id get endpoint gives back the service model element with matching ID from the database. The object's schema is described at the end in the Definitions section.

  Example call:
  ```
  SiteEngine.get('/rest/12312312313')
  ```


#### Parameters

|Type|Name|Description|Schema|Default|
|---|---|---|---|---|
|**Path**|**id**  <br>*required*|The ID of the element you want to get|string||


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|The returned model element.|[SiteEngineSchema](#siteengineschema)|
|**400**|Validation error by MongoDB.|[MongoDB_Error](#mongodb_error)|


#### Tags

* Get


<a name="rest-id-put"></a>
### Find and update an element
```
PUT /rest/{id}
```


#### Description
The /rest/:id put endpoint search and then update a model element with the ID matching the path parameter. The updated object's schema is described at the end in the Definitions section.


#### Parameters

|Type|Name|Description|Schema|Default|
|---|---|---|---|---|
|**Path**|**id**  <br>*required*|The ID of the element you want to delete|string||
|**Body**|**Object**  <br>*required*|The expected object with all required parameters.|[SiteEngineSchema](#siteengineschema)||


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|The updated model element.|[SiteEngineSchema](#siteengineschema)|
|**400**|Validation error by MongoDB.|[MongoDB_Error](#mongodb_error)|


#### Tags

* Put


<a name="rest-id-delete"></a>
### Delete a particular service model element
```
DELETE /rest/{id}
```


#### Description
The /rest/:id delete endpoint search and then delete a model element with the ID matching the path parameter. The deleted object's schema is described at the end in the Definitions section.

  Example call:
  ```
  SiteEngine.delete('/rest/12312312313')
  ```


#### Parameters

|Type|Name|Description|Schema|Default|
|---|---|---|---|---|
|**Path**|**id**  <br>*required*|The ID of the element you want to delete|string||


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|The deleted model element.|[SiteEngineSchema](#siteengineschema)|
|**400**|Validation error by MongoDB.|[MongoDB_Error](#mongodb_error)|


#### Tags

* Delete


<a name="version-get"></a>
### Shows the version number
```
GET /version
```


#### Description
The /version endpoint gives back version number of the current service.


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|The version number of the service.|integer|


#### Tags

* Get




<a name="definitions"></a>
## Definitions

<a name="mongodb_error"></a>
### MongoDB_Error

|Name|Description|Schema|
|---|---|---|
|**message**  <br>*optional*|Error object by MongoDB|object|


<a name="siteengineschema"></a>
### SiteEngineSchema

|Name|Description|Schema|
|---|---|---|
|**atcSelectors**  <br>*optional*||< string > array|
|**name**  <br>*required*||string|
|**pluginPageUrl**  <br>*optional*||string|
|**pluginUrl**  <br>*optional*||string|
|**slug**  <br>*required*||string|





