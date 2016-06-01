# Ghost Service


<a name="overview"></a>
## Overview
Service for finding ghost sessions


### Version information
*Version* : 1.0.0




<a name="paths"></a>
## Paths

<a name="inspectsession-post"></a>
### POST /inspectSession
##### Inspects a session on a site, logs the result parameters, and puts them in an SQS queue.


#### Description
The /inspectSession post endpoint inspects a specific session given by its ID. It takes the session_id as a query parameter, checks if it's correct, and then checks the site where the session occurred. If everything checks out it sends an object, described below as ResultObject, to the AWS.SQS.


#### Parameters

|Type|Name|Description|Schema|Default|
|---|---|---|---|---|
|**Query**|**session_id**  <br>*required*|The Id of a session.|string||


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|The response is an object from AWS SQS, if everything went well.|[ResponseObject](#responseobject)|
|**400**|Validation error.|[Error](#error)|


#### Tags

* Post




<a name="definitions"></a>
## Definitions

<a name="error"></a>
### Error

|Name|Description|Schema|
|---|---|---|
|**message_1**  <br>*optional*|Session id is missing!|string|
|**message_2**  <br>*optional*|Invalid session!|string|
|**message_3**  <br>*optional*|Invalid site!|string|


<a name="responseobject"></a>
### ResponseObject
the response object containing error, data properties, and the original request object.


|Name|Description|Schema|
|---|---|---|
|**MessageId**  <br>*optional*|An identifier for the message.|string|
|**RequestObject**  <br>*optional*||[ResultObject](#resultobject)|
|**err**  <br>*optional*|the error object returned from the request. Set to null if the request is successful.|object|


<a name="resultobject"></a>
### ResultObject
The object sent to the SQS.


|Name|Description|Schema|
|---|---|---|
|**DelaySeconds**  <br>*optional*|The delay/heartbeatTimeout of the site.|number|
|**MessageBody**  <br>*optional*|The sessionId.|string|
|**QueueUrl**  <br>*optional*|The sqsQueueUrl.|string|





