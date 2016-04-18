# Country Model Service

## Overview
Service for country collection

### Version information
Version: 0.1.7

## Paths

### GET /__healthy
##### Returns 'OK' to show that the service is working

#### Description

The /__healthy endpoint gives back 'OK' with code 200, to enable the user to check whether the service is working or not.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|An OK answer.|string|


#### Tags

* Get

### GET /count
##### Counts the model elements in the database

#### Description

The /count endpoint gives back the number of service model elements in the database. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The number of elements.|integer|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### POST /rest
##### Creates a new model element with the data object given as body parameter

#### Description

The /rest post endpoint creates and adds a new element to the database, in form of a CountrySchema. The object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||The expected object with two required parameters.|true|CountrySchema||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|201|The response is 'ok', if everything went well.|string|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Post

### GET /rest
##### Search database for all the service model elements

#### Description

The /rest get endpoint gives back the service model elements from the database. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned model elements.|CountrySchema array|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### PATCH /rest
##### Search in database and update one service model element

#### Description

The /rest patch endpoint find and update one service model element from the database. The element is determined by an array's first object. In the secound object of the array you give the parameters you want to change. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The updated model elements.|CountrySchema array|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Patch

### DELETE /rest/{id}
##### Delete a particular service model element

#### Description

The /rest/:id delete endpoint search and then delete a model element with the ID matching the path parameter. The deleted object's schema is described at the end in the Definitions section.

  Example call:
  ```
  Country.delete('/rest/12312312313')
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to delete|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The deleted model element.|CountrySchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Delete

### GET /rest/{id}
##### Search database for a particular service model element

#### Description

The /rest/:id get endpoint gives back the service model element with matching ID from the database. The object's schema is described at the end in the Definitions section.

  Example call:
  ```
  Country.get('/rest/12312312313')
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to get|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned model element.|CountrySchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### PUT /rest/{id}
##### Find and update an element

#### Description

The /rest/:id put endpoint search and then update a model element with the ID matching the path parameter. The updated object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to delete|true|string||
|BodyParameter||The expected object with all required parameters.|true|CountrySchema||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The updated model element.|CountrySchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Put

### GET /version
##### Shows the version number

#### Description

The /version endpoint gives back version number of the current service.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The version number of the service.|integer|


#### Tags

* Get

## Definitions
### CountrySchema
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|country||true|string||
|states||false|string array||


### MongoDB_Error
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|message|Error object by MongoDB|false|object||


