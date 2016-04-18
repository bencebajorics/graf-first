# Message Service

## Overview
Service for message sending

### Version information
Version: 0.4.0

## Paths

### POST /email
##### Sends out an email.

#### Description

The /email endpoint send out an email with the given template data to a user. The data is given as query parameter.

Example call:
```
Message.post('/email', {
    to: 'john@doe.com',
    subject: 987987987,
    html: '<h1> Com back and finish your purchase!! <h1>',
    sender_email: 'master@ip.com',
    sender_name:  'Master Ip'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|to|The ID of a campaign item.|true|string||
|QueryParameter|subject||true|string||
|QueryParameter|html|The body of an email.|true|string||
|QueryParameter|sender_email|The ID of a session.|true|string||
|QueryParameter|sender_name||true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well.|string|
|400|Missing parameter error.|Error_email|


#### Tags

* Post

### DELETE /emailByEmail
##### Cancel all mails defined by an email.

#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|email|The email you want to cancel|true|string||
|QueryParameter|site_id|The ID of the site you want to cancel mails from.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well.|string|
|400|Error|Error_deleteByEmail|


#### Tags

* Delete

### DELETE /emailByMessageId
##### Cancels mail by message id.

#### Description

Example call:
```
Message.post('/emailByMessageId', {
    message_id: 123013013123
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|message_id|The ID of the message you want to cancel.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well.|string|
|400|Missing parameter error.|string|
|404|Validation error by Mandrill.|Mandrill_Error|


#### Tags

* Delete

### DELETE /emailBySessionId
##### Cancels mail by session id.

#### Description

Example call:
```
Message.post('/emailBySessionId', {
    session_id: 68545513123
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|session_id|The ID of the session you want to cancel mails from.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well.|string|
|400|Missing parameter error.|string|


#### Tags

* Delete

### POST /ghostMessage
##### Process the given query parameters, and puts the result into an SQS queue.

#### Description

Example call:
```
Message.post('/ghostMessage', {
  campaign_item_id: 342342342,
  session_id: 987987987,
  subject: 'Shopping',
  body: 'Come back and finish your purchase now!!'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|campaign_item_id|The ID of a campaign item.|true|string||
|QueryParameter|session_id|The ID of a session.|true|string||
|QueryParameter|subject||true|string||
|QueryParameter|body|The body of an email.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well.|string|
|400|Missing parameter error.|Error_ghostMessage|


#### Tags

* Post

## Definitions
### Error_deleteByEmail
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|400|false|string||
|message||false|object||


### Error_email
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|400|false|string||
|message||false|object||


### Error_ghostMessage
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|400|false|string||
|message||false|object||


### Mandrill_Error
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|message|Error message by Mandrill|false|string||


