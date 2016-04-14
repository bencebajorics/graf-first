# Site Model Service

## Overview
Manages the statistical information of the sites using GhostMonitor

### Version information
Version: 0.4.3

## Paths
### Returns 'OK' to show that the service is working
```
GET /__healthy
```

#### Description

The /__healthy endpoint gives back 'OK' with code 200, to enable the user to check whether the service is working or not.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|An OK answer.|string|


#### Tags

* Get

### Counts the model elements in the database
```
GET /count
```

#### Description

The /count endpoint gives back the number of service model elements in the database. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The number of elements.|integer|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### Search database for all the service model elements
```
GET /rest
```

#### Description

The /rest get endpoint gives back the service model elements from the database. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned model elements.|SiteSchema array|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### Creates a new model element with the data object given as body parameter
```
POST /rest
```

#### Description

The /rest post endpoint creates and adds a new element to the database, in form of a SiteSchema. The object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||The expected object with two required parameters.|true|SiteSchema||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|201|The response is 'ok', if everything went well.|string|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Post

### Search in database and update one service model element
```
PATCH /rest
```

#### Description

The /rest patch endpoint find and update one service model element from the database. The element is determined by an array's first object. In the secound object of the array you give the parameters you want to change. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The updated model elements.|SiteSchema array|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Patch

### Search database for a particular service model element
```
GET /rest/{id}
```

#### Description

The /rest/:id get endpoint gives back the service model element with matching ID from the database. The object's schema is described at the end in the Definitions section.

  Example call:
  ```
  SiteMService.get('/rest/12312312313')
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to get|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned model element.|SiteSchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### Delete a particular service model element
```
DELETE /rest/{id}
```

#### Description

The /rest/:id delete endpoint search and then delete a model element with the ID matching the path parameter. The deleted object's schema is described at the end in the Definitions section.

  Example call:
  ```
  SiteMService.delete('/rest/12312312313')
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to delete|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The deleted model element.|SiteSchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Delete

### Find and update an element
```
PUT /rest/{id}
```

#### Description

The /rest/:id put endpoint search and then update a model element with the ID matching the path parameter. The updated object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to delete|true|string||
|BodyParameter||The expected object with all required parameters.|true|SiteSchema||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The updated model element.|SiteSchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Put

### Shows the version number
```
GET /version
```

#### Description

The /version endpoint gives back version number of the current service.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The version number of the service.|integer|


#### Tags

* Get

## Definitions
### Account
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|city||false|string||
|zipCode||false|string||
|company|The name of the company or the site owner.|false|string||
|country||false|string||
|state||false|string||
|address||false|string||
|industry|The industry/industries the webshop supplies.|false|string array||
|phone||false|string||


### AntiSpam
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|city||false|string||
|zipCode||false|string||
|company||false|string||
|country||false|string||
|state||false|string||
|address||false|string||
|industry||false|string array||


### Billing
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|accountManagementUrl||false|string||
|editBillingUrl||false|string||


### Discount
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|amount||false|integer||
|enabled||false|boolean|false|


### EmailSettings
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|senderName||false|string||
|senderEmail||false|string||


### MongoDB_Error
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|message|Error object by MongoDB|false|object||


### Payment
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|cardName||false|string||
|cardNumber||false|string||
|expMonth||false|string||
|expYear||false|string||
|securityCode||false|string||


### SiteSchema
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|name||true|string||
|domain||true|string||
|wizardFinished||false|boolean|false|
|startedTimeout||false|integer||
|heartbeatTimeout||false|integer||
|currency||false|string||
|engine||false|string||
|timeZone||false|string||
|campaigns||false|string array||
|account||false|Account||
|antiSpam||false|AntiSpam||
|payment||false|Payment||
|billing||false|Billing||
|notifications||false|object array||
|discount||false|Discount||
|plan|ID of a plan.|false|string||
|emailSettings||false|EmailSettings||
|installData||false|string||
|trialEndsAt||false|string||
|isBillingActive||false|enum (active, inactive, trial)|trial|
|campaignItemLanguage|ID of campaignItemLanguage.|false|string||
|tracking||false|object||
|hasFirstGhost||false|boolean|false|
|hasFirstCustomerGhost||false|boolean|false|
|shopify||false|object||
|atcSelectors||false|string array||


