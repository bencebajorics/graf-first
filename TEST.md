# Ghost Service


<a name="overview"></a>
## ï¿½bersicht
Service for finding ghost sessions


### Aktuelle Version
*Version* : 1.0.0




<a name="paths"></a>
## Pfade

<a name="inspectsession-post"></a>
### Inspects a session on a site, logs the result parameters, and puts them in an SQS queue.
```
POST /inspectSession
```


#### Beschreibung
The /inspectSession post endpoint inspects a specific session given by its ID. It takes the session_id as a query parameter, checks if it's correct, and then checks the site where the session occurred. If everything checks out it sends an object, described below as ResultObject, to the AWS.SQS.


#### Parameter

|Typ|Name|Beschreibung|Schema|Standard|
|---|---|---|---|---|
|**Query**|**session_id**  <br>*required*|The Id of a session.|string||


#### Antworten

|HTTP Code|Beschreibung|Schema|
|---|---|---|
|**200**|The response is an object from AWS SQS, if everything went well.|[ResponseObject](#responseobject)|
|**400**|Validation error.|[Error](#error)|


#### Tags

* Post




<a name="definitions"></a>
## Definitionen

<a name="error"></a>
### Error

|Name|Beschreibung|Schema|
|---|---|---|
|**message_1**  <br>*optional*|Session id is missing!|string|
|**message_2**  <br>*optional*|Invalid session!|string|
|**message_3**  <br>*optional*|Invalid site!|string|


<a name="responseobject"></a>
### ResponseObject
the response object containing error, data properties, and the original request object.


|Name|Beschreibung|Schema|
|---|---|---|
|**MessageId**  <br>*optional*|An identifier for the message.|string|
|**RequestObject**  <br>*optional*||[ResultObject](#resultobject)|
|**err**  <br>*optional*|the error object returned from the request. Set to null if the request is successful.|object|


<a name="resultobject"></a>
### ResultObject
The object sent to the SQS.


|Name|Beschreibung|Schema|
|---|---|---|
|**DelaySeconds**  <br>*optional*|The delay/heartbeatTimeout of the site.|number|
|**MessageBody**  <br>*optional*|The sessionId.|string|
|**QueueUrl**  <br>*optional*|The sqsQueueUrl.|string|
