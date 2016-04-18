# Message Log Model Service

## Overview
Service for message-log collection

### Version information
Version: 0.1.4

## Paths

### GET /__healthy
##### Returns 'OK' to show that the service is working

#### Description

The /__healthy endpoint gives back 'OK' with code 200, to enable the user to check whether the service is working or not.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|An 'OK' answer.|string|


#### Tags

* Get

### POST /bulkUpdate
##### Push informations about a cart item

#### Description

The /bulkUpdate endpoint updates the message log elements. The new data is given as a body parameter. The object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||The expected update data.|true|MessageLogSchema||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well.|string|


#### Tags

* Post

### GET /count
### Counts the model elements in the database

#### Description

The /count endpoint gives back the number of service model elements in the database. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The number of elements.|integer|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### GET /diagram
##### Gives the daily number of sent emaials data to fill a diagram

#### Description

The /diagram endpoint gives back an array filled with dates given as timestamps, and number of emails paired up. These pairs are used as data of a diagram. The object's schema is described at the end in the Definitions section.
Example call:
```
MessageLog.get('/diagram', {
  site_id: '12312312313',
  end:  'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)'
  start: 'Thu Feb 18 2016 12:25:45 GMT+0100 (CET)'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|site_id|The ID of the site you want to get informations about.|true|string||
|QueryParameter|end|The end date of the interval of time.|true|string||
|QueryParameter|start|The start date of the interval of time.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned statistic elements in a Json object.|Response_diagram|
|400|Returned error message if a parameter is required.|Response_400|


#### Tags

* Get

### PATCH /rest
##### Search in database and update one service model element

#### Description

The /rest patch endpoint find and update one service model element from the database. The element is determined by an array's first object. In the secound object of the array, you give the parameters you want to change. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The updated model elements.|MessageLogSchema array|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Patch

### POST /rest
###### Creates a new model element with the data object given as body parameter

#### Description

The /rest post endpoint creates and adds a new element to the database, in form of a MessageLogSchema. The object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||The expected object.|true|MessageLogSchema||


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
|200|The returned model elements.|MessageLogSchema array|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### GET /rest/{id}
##### Search database for a particular service model element

#### Description

The /rest/:id get endpoint gives back the service model element with matching ID from the database. The object's schema is described at the end in the Definitions section.

  Example call:
  ```
  MessageLog.get('/rest/12312312313')
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to get|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned model element.|MessageLogSchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### DELETE /rest/{id}
##### Delete a particular service model element

#### Description

The /rest/:id delete endpoint search and then delete a model element with the ID matching the path parameter. The deleted object's schema is described at the end in the Definitions section.

  Example call:
  ```
  MessageLog.delete('/rest/12312312313')
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to delete|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The deleted model element.|MessageLogSchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Delete

### PUT /rest/{id}
##### Find and update an element

#### Description

The /rest/:id put endpoint search and then update a model element with the ID matching the path parameter. The updated object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to delete|true|string||
|BodyParameter||The expected object with all required parameters.|true|MessageLogSchema||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The updated model element.|MessageLogSchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Put

### GET /statistics
##### Gives statistic information about GhostMonitor usage

#### Description

The get /statistics endpoint gives back a Json object with statistical informations about a page using GhostMonitor in a time range given as parameters. The object's schema is described at the end in the Definitions section.

Example call:
```
MessageLog.get('/statistics', {
  site_id: '12312312313',
  end:  'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)'
  start: 'Thu Feb 18 2016 12:25:45 GMT+0100 (CET)'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|site_id|The ID of the site you want to get informations about.|true|string||
|QueryParameter|end|The end date of the interval of time.|true|string||
|QueryParameter|start|The start date of the interval of time.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned statistic elements in a Json object.|Response_statistics|
|400|Returned error message if a parameter is required.|Response_400|


#### Tags

* Get

### GET /synchronize
##### Synchronize model elements

#### Description

The /synchronize endpoint prepares the model elements for Elasticsearch.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well.|string|


#### Tags

* Get

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
### MessageLogSchema
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|messageId||false|string||
|ghost|ID of a ghost.|false|string||
|site|ID of the site.|false|string||
|mandrillUpdatedAt|The date the mandrill was updated|false|string||
|subject||false|string||
|hadConversion||false|boolean||
|body||false|string||
|campaignItem|ID of a Campagn Item.|false|string||
|messageType||false|enum (sms, email)|email|
|status||false|string||
|openCount||false|integer||
|clickCount||false|integer||
|opens||false|string array||
|clicks||false|string array||


### MongoDB_Error
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|message|Error object by MongoDB|false|object||


### Response_400
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|400|false|string||
|message||false|object||


### Response_diagram
### Response_statistics
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|clickCount|The number of clicking to the link in sent emails.|false|integer||
|openCount|The number of opened emails.|false|integer||
|sentEmails|The number of sent emails.|false|integer||
|bounceCount|The number of ATC pop-up bounce.|false|integer||
|conversionCount|The number of recovered carts.|false|integer||
|clickRate|The percentage of clicking to the link in sent emails.|false|number||
|openRate|The percentage of opened emails.|false|number||
|bounceRate|The percentage of bounced ATC pop-ups.|false|number||


