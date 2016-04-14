# Session Model Service

## Overview
The Service provides statistical information about the ghost sessions of pages using GhostMonitor.

### Version information
Version: 0.5.1

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

### GET /activeSites
##### Gives the number of active sites, and the users status on these sites

#### Description

The /activeSites endpoint gives back a Json object with the number of active sites, and the summary of visitors in different states from GhostMonitor's perspective. These numbers are from a certain time interval, which is given as query parameter. The object's schema is described at the end in the Definitions section.

Example call:
```
Session.get('/activeSites', {
  end:  'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)'
  start: 'Thu Feb 18 2016 12:25:45 GMT+0100 (CET)'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|end|The end date of the given interval of time.|true|string||
|QueryParameter|start|The start date of the given interval of time.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned statistic elements in a Json object.|Response_activeSites|
|400|Returned error message if a parameter is required.|Response_400|


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

### GET /diagram
##### Gives the recovery data to fill a diagram

#### Description

The /diagram endpoint gives back an array filled with dates given as timestamps, and recovered money amounts paired up. These pairs are used as data of a diagram. The object's schema is described at the end in the Definitions section.

Example call:
```
Session.get('/diagram', {
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
|400|Returned error message if a parameter is required.|Response_400_2|


#### Tags

* Get

### GET /emailAcquireTypes
##### Gives statistical information about ATC popup

#### Description

The /emailAcquireTypes endpoint gives back a Json object with information about GhostMonitors ATC popup usage. These numbers are from a certain time interval, which is given as query parameter. The object's schema is described at the end in the Definitions section.

Example call:
```
Session.get('/emailAcquireTypes', {
  site_id: '12312312313',
  end:  'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)'
  start: 'Thu Feb 18 2016 12:25:45 GMT+0100 (CET)'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|site_id|The ID of the site you want to get informations about.|true|string||
|QueryParameter|end|The end date of the given interval of time.|true|string||
|QueryParameter|start|The start date of the given interval of time.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned statistic elements in a Json object.|Response_emailAcquireTypes|
|400|Returned error message if a parameter is required.|Response_400|


#### Tags

* Get

### GET /ghosts
##### Gives back the session details of the ghosts.

#### Description

The /ghosts endpoint gives back a Json object with the number of ghosts, and the session statistics of each ghost. The number, sort, and order of the returned ghosts can be set in query parameters. The object's schema is described at the end in the Definitions section.

Example call:
```
Session.get('/ghosts', {
  site_id: '12312312313',
  type: 'ghost',
  skip: 100,
  limit: 300,
  sort: 50,
  order: 1
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|site|The identifier of the site, you want to get the information about.|true|string||
|QueryParameter|type|The type of sessions you are looking for.|true|string||
|QueryParameter|skip|The number of ghosts you want to skip from the begining of the list of ghosts.|true|string||
|QueryParameter|limit|The total number of ghosts you want to get.|true|string||
|QueryParameter|sort|The number of ghosts in one array.|true|string||
|QueryParameter|order|The order of returned ghosts in one array.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned statistic elements in a Json object.|Response_ghosts|
|400|Returned error message if a parameter is required.|Response_400_2|


#### Tags

* Get

### GET /rest
##### Search database for all the service model elements

#### Description

The /rest get endpoint gives back the service model elements from the database. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned model elements.|SessionSchema array|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### POST /rest
##### Creates a new model element with the data object given as body parameter

#### Description

The /rest post endpoint creates and adds a new element to the database, in form of a SessionSchema. The object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||The expected object.|true|SessionSchema||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|201|The response is 'ok', if everything went well.|string|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Post

### PATCH /rest
##### Search in database and update one service model element

#### Description

The /rest patch endpoint find and update one service model element from the database. The element is determined by an array's first object. In the secound object of the array, you give the parameters you want to change. The object's schema is described at the end in the Definitions section.


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The updated model elements.|SessionSchema array|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Patch

### PUT /rest/{id}
##### Find and update an element

#### Description

The /rest/:id put endpoint search and then update a model element with the ID matching the path parameter. The updated object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to delete|true|string||
|BodyParameter||The expected object with all required parameters.|true|SessionSchema||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The updated model element.|SessionSchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Put

### GET /rest/{id}
##### Search database for a particular service model element

#### Description

The /rest/:id get endpoint gives back the service model element with matching ID from the database. The object's schema is described at the end in the Definitions section.

  Example call:
  ```
  Session.get('/rest/12312312313')
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to get|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned model element.|SessionSchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Get

### DELETE /rest/{id}
##### Delete a particular service model element

#### Description

The /rest/:id delete endpoint search and then delete a model element with the ID matching the path parameter. The deleted object's schema is described at the end in the Definitions section.

  Example call:
  ```
  Session.delete('/rest/12312312313')
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|PathParameter|id|The ID of the element you want to delete|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The deleted model element.|SessionSchema|
|400|Validation error by MongoDB.|MongoDB_Error|


#### Tags

* Delete

### GET /sessionStat
##### Gives the number of users in different status on all the pages

#### Description

The /sessionStat endpoint gives back a Json object with the statistics of the visitors status from a certain time interval. The object's schema is described at the end in the Definitions section.

Example call:
```
Session.get('/sessionStat', {
  end:  'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)'
  start: 'Thu Feb 18 2016 12:25:45 GMT+0100 (CET)'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|QueryParameter|end|The end date of the interval of time.|true|string||
|QueryParameter|start|The start date of the interval of time.|true|string||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The returned statistic elements in a Json object.|Response_sessionStat|
|400|Returned error message if a parameter is required.|Response_400|


#### Tags

* Get

### POST /setCartItem
##### Push informations about a cart item

#### Description

The /setCartItem endpoint adds a Cart Item object to the Cart Items array with the sessionID property as ID. The object is given as a body parameter. The object's schema is described at the end in the Definitions section.

Example call:
```
Session.post('/setCartItem', {
  productID: '12312312313',
  name: 'Beer',
  price: 12,
  qty: 4,
  qtyPrice: 3,
  imageUrl: 'http://pngimg.com/img/food/beer',
  category: 'Booze'
  productUrl: 'http://john-doe.com'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||The expected object with 6 required parameters.|true|Cart_item||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well.|string|


#### Tags

* Post

### GET /statistics
##### Gives statistical information GhostMonitor uses

#### Description

The /statistics endpoint gives back a Json object with statistical informations about a page using GhostMonitor in a time range given as parameters. The object's schema is described at the end in the Definitions section.

Example call:
```
Session.get('/statistics', {
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

### POST /synchronize
##### Synchronize model elements

#### Description

The /synchronize endpoint prepares the Cart Items for Elasticsearch. The object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object to synchronize as body parameter.|true|SessionSchema||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well.|string|


#### Tags

* Post

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
### ATC
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|show||false|integer||
|hide||false|integer||
|emailProvide||false|integer||


### Cart_data
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|value|The value of the items the customer wants to buy.|false|integer||
|itemCount|The number of the items the customer wants to buy.|false|integer||
|returnUrl||false|string||


### Cart_item
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|productId|The ID of the product.|true|string||
|name|The name of the product.|true|string||
|price|The price of goods.|true|integer||
|qty|The number of products.|true|integer||
|qtyPrice|The price of a sigle item.|true|integer||
|imageUrl|The url to the image of the product.|true|string||
|category|The category of the goods.|false|string||
|productUrl|The url to a product.|false|string||


### MongoDB_Error
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|message|Error object by MongoDB|false|object||


### Response_400
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|400|false|string||
|message||false|object||


### Response_400_2
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|400|false|string||
|message||false|object||


### Response_activeSites
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|400|false|string||
|message||false|object||


### Response_diagram
### Response_emailAcquireTypes
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|atc||false|integer||
|login||false|integer||
|pre_submit||false|integer||
|conversionRate|The rate of emails sent becuse of the atc popup.|false|number||


### Response_ghosts
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|total|The total number of ghosts.|false|integer||
|ghosts|Array of sessions of the ghosts.|false|SessionSchema array||


### Response_sessionStat
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|visitors|Number of visitors|false|integer||
|ghost|Number of ghosts|false|integer||
|customer_ghost|Number of customer_ghosts|false|integer||
|customer|Number of customers|false|integer||


### Response_statistics
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|recoveredRevenue|The amount of recovered revenue.|true|integer||
|shopRevenueWithoutGM|The amount of revenue without GhostMonitor.|true|integer||
|shopRevenueWithGM|The amount of revenue using GhostMonitor.|true|integer||
|startedCheckout|The number of started checkouts.|true|integer||
|abandonedCarts|The number of abandoned carts.|true|integer||
|recoveredCarts|The number of recovered carts.|true|integer||
|lostRevenue|The amount of lost revenue.|true|integer||
|abandonedCartsWithEmail|The number of abandoned carts, with emails sent by GhostMonitor.|true|integer||
|revenueGrowth|The growth of income.|true|integer||
|abandonmentRate|The percentage of the abandoned shoppings.|true|number||
|identifiableRate|The percentage of the identifiable changes.|true|number||
|conversionRate|The percentage of succesful recoveries.|true|number||


### SessionSchema
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|email|The email address of the ghost|false|string||
|emailAcquireType|The acquire type, it's optional values are atc, login, pre_submit.|false|string||
|phone|The phone number of the ghost.|false|string||
|name|Name of the ghost visitor.|false|string||
|site|The ID of the site the ghost visited.|false|string||
|isArActive||false|boolean||
|sessionType|State of session the customer is in.|false|string||
|fields||false|object||
|cartData||false|Cart_data||
|cartItems||false|Cart_item array||
|shortCartUrl||false|string||
|startedAt|The date the ghost started the purchase.|false|string||
|lastHeartbeatAt|The date the ghost was on the site for the last time.|false|string||
|cartStartedAt|The date the ghost started filling it's cart.|false|string||
|convertedAt|The date the ghost's cart was recovered.|false|string||
|atc||false|ATC||
|shopifyCartId||false|string||
|shopify||false|object||
