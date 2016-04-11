# Intercom service

## Overview
Service with controlling intercom requests functionality.

### Version information
Version: 0.13.1

## Paths
### GET /all
##### Starts the processing of the statistics of each sites, and puts them into an SQS queue
```
GET /all
```

#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|Expected response to a valid request|Response_ok|


#### Tags

* Get

### Push segment informations about trial_expired to Intercom api
```
POST /push/account_cancelled
```

#### Description

The /push/account_cancelled endpoint adds the date when a users account had been cancelled, in an object with 2 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
IntercomService.post('/push/account_cancelled', {
  site_id: '12312312313',
  account_cancelled: 'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)'
})

```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 2 parameters.|true|Account_cancelled||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_account_cancelled|


#### Tags

* GhostMonitor Usage

### Push segment informations about cart_recovered to Intercom api
```
POST /push/cart_recovered
```

#### Description

The /push/cart_recovered endpoint adds information about how many carts had been recovered to the user's site, in an object with 2 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
IntercomService.post('/push/cart_recovered', {
  site_id: '12312312313',
  cart_recovered: '25',
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 2 parameters.|true|Cart_recovered||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_cart_recovered|


#### Tags

* GhostMonitor Statistics

### Push segment informations about trial_expired to Intercom api
```
POST /push/days_left
```

#### Description

The /push/trial_expired endpoint adds the number of days left from the trial period, in an object with 2 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
IntercomService.post('/push/trial_expired', {
  site_id: '12312312313',
  trial_days_left: 'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)'
})

```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 2 parameters.|true|Days_left||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_days_left|


#### Tags

* GhostMonitor Usage

### Push segment informations about emails_sent to Intercom api
```
POST /push/emails_sent
```

#### Description

The /push/emails_sent endpoint adds information about how many emails had been sent to the user's customers, in an object with 2 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
IntercomService.post('/push/emails_sent', {
  site_id: '12312312313',
  emails_sent: '32',
})

```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 2 parameters.|true|Emails_sent||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_emails_sent|


#### Tags

* GhostMonitor Statistics

### Push segment informations about first_ghost to Intercom api
```
POST /push/first_customer_ghost
```

#### Description

The /push/first_customer_ghost endpoint adds the email address of the first returned ghost, and the number and value of items the ghost customer purchased to the Intercom, in an object with 4 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
IntercomService.post('/push/first_customer_ghost', {
  site_id: '12312312313',
  first_customer_ghost_total: '32',
  first_customer_ghost_item_count: '32'
  first_customer_ghost_email: 'john@doe.com'
})

```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 4 parameters.|true|First_customer_ghost||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_first_customer_ghost|


#### Tags

* GhostMonitor Statistics

### Push segment informations about first_entered to Intercom api
```
POST /push/first_entered
```

#### Description

The /push/first_entered endpoint adds the date when a certain user first enterd the site to the Intercom, in an object with 2 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
  IntercomService.post('/push/first_entered', {
    site_id: '12312312313',
    first_entered: 'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)',
  })
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 2 parameters.|true|First_entered||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_first_entered|


#### Tags

* GhostMonitor Usage

### Push segment informations about first_ghost to Intercom api
```
POST /push/first_ghost
```

#### Description

The /push/first_ghost endpoint adds the number and value of items the first ghost wanted to buy, and also the email address of the ghost, in an object with 4 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
IntercomService.post('/push/first_customer_ghost', {
  site_id: '12312312313',
  first_ghost_total: '32',
  first_ghost_item_count: '32'
  first_ghost_email: 'john@doe.com'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 4 parameters.|true|First_ghost||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_first_ghost|


#### Tags

* GhostMonitor Statistics

### Push segment informations about money_recovered to Intercom api
```
POST /push/money_recovered
```

#### Description

The /push/money_recovered endpoint adds information about how much money was recovered to the user, in an object with 2 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
IntercomService.post('/push/money_recovered', {
  site_id: '12312312313',
  money_recovered: '$ 5000',
})

```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 2 parameters.|true|Money_recovered||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_money_recovered|


#### Tags

* GhostMonitor Statistics

### Push segment informations about payment_activated to Intercom api
```
POST /push/payment_activated
```

#### Description

The /push/payment_activated endpoint adds information about the status of the payment to the Intercom, in an object with the site ID given in the body.

Example call:
```
IntercomService.post('/push/payment_activated', {
  site_id: '12312312313'
})

```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 1 parameter.|true|Payment||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_payment|


#### Tags

* GhostMonitor Usage

### Push segment informations about payment_deactivated to Intercom api
```
POST /push/payment_deactivated
```

#### Description

The /push/payment_deactivated endpoint adds information about the status of the payment to the Intercom, in an object with the site ID given in the body.

Example call:
```
IntercomService.post('/push/payment_deactivated', {
  site_id: '12312312313'
})

```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 1 parameter.|true|Payment||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_payment|


#### Tags

* GhostMonitor Usage

### Push segment informations about plugin_activated to Intercom api
```
POST /push/plugin_activated
```

#### Description

The /push/plugin_activated endpoint adds information about the status of the plugin to the Intercom, in an object with the site ID given in the body.

Example call:
```
IntercomService.post('/push/plugin_activated', {
  site_id: '12312312313'
})

```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 1 parameter.|true|Plugin||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_plugin|


#### Tags

* GhostMonitor Usage

### Push segment informations about plugin_deactivated to Intercom api
```
POST /push/plugin_deactivated
```

#### Description

The /push/plugin_activated endpoint adds information about the status of the plugin to the Intercom, in an object with the site ID given in the body.

Example call:
```
IntercomService.post('/push/plugin_deactivated', {
  site_id: '12312312313'
})

```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 1 parameter.|true|Plugin||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_plugin|


#### Tags

* GhostMonitor Usage

### Push segment informations about signup_ended to Intercom api
```
POST /push/signup_ended
```

#### Description

The /push/signup_ended endpoint adds the name, and the email address of a new user, the platform of the user's site, the duration of the registration, and the date when the user finished the sign up to the Intercom. The details are added in an object with 6 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
IntercomService.post('/push/platform', {
  site_id: '12312312313',
  name: 'John Doe',
  platform: 'WooCommerce'
  sender_email: 'john@doe.com'
  time_spent_on_registration: '5m35s',
  signup_ended: 'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)',
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with the 6 parameters.|true|Signup_ended||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_signup_end|


#### Tags

* Signup

### Push segment informations about signup_started to Intercom api
```
POST /push/signup_started
```

#### Description

The /push/signup_started endpoint adds the email address, and the site domain of a new user, and also the date when the user started its sign up to the Intercom. The details are added in an object with 4 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
IntercomService.post('/push/signup_started', {
  site_id: '12312312313',
  email: 'john@doe.com',
  domain: 'http://john-doe.com',
  signup_started: 'Thu Feb 18 2016 14:22:45 GMT+0100 (CET)'
})
```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 4 parameters.|true|Signup_started||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_signup_start|


#### Tags

* Signup

### Push segment informations about statistics to Intercom api
```
POST /push/statistics
```

#### Description

The /push/statistics endpoint adds all statistical information to the Intercom api, in an object with 18 parameters given in the body. The object's schema is described at the end in the Definitions section.


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 18 parameters.|true|Statistics||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_statistics|


#### Tags

* GhostMonitor Statistics

### Push segment informations about wizard_page_1 to Intercom api
```
POST /push/wizard_page_1
```

#### Description

The /push/wizard_page_1 endpoint adds information about how much time a certain user spent on filling the sign up wizard's first page to the Intercom, in an object with 2 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
  IntercomService.post('/push/platform', {
    site_id: '12312312313',
    wizard_page_1: '23.2',
  })
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 2 parameters.|true|Wizard_page_1||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_wizard1|


#### Tags

* Signup

### Push segment informations about wizard_page_2 to Intercom api
```
POST /push/wizard_page_2
```

#### Description

The /push/wizard_page_2 endpoint adds information about how much time a certain user spent on filling the sign up wizard's second page to the Intercom, in an object with 2 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
  IntercomService.post('/push/platform', {
    site_id: '12312312313',
    wizard_page_2: '25.4',
  })
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 2 parameters.|true|Wizard_page_2||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_wizard2|


#### Tags

* Signup

### Push segment informations about wizard_page_3 to Intercom api
```
POST /push/wizard_page_3
```

#### Description

The /push/wizard_page_3 endpoint adds information about how much time a certain user spent on filling the sign up wizard's third page to the Intercom, in an object with 2 parameters given in the body. The object's schema is described at the end in the Definitions section.

Example call:
```
  IntercomService.post('/push/platform', {
    site_id: '12312312313',
    wizard_page_2: '27.7',
  })
  ```


#### Parameters
|Type|Name|Description|Required|Schema|Default|
|----|----|----|----|----|----|
|BodyParameter||Object that is needed, with 2 parameters.|true|Wizard_page_3||


#### Responses
|HTTP Code|Description|Schema|
|----|----|----|
|200|The response is 'ok', if everything went well. Otherwise it returns one of the error messages from the Response schema.|Response_wizard3|


#### Tags

* Signup

## Definitions
### Account_cancelled
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|account_cancelled|The date when the account was cancelled.|true|string||


### Cart_recovered
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|cart_recovery|The number of recovered carts.|true|string||


### Days_left
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|trial_days_left|The number of days left from trial version.|true|string||


### Emails_sent
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|emails_sent|The number of emails sent out to the user's customers.|true|string||


### First_customer_ghost
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|first_customer_ghost_total|Value of the first customer ghost's cart.|true|string||
|first_customer_ghost_item_count|Number of items recovered.|true|string||
|first_customer_ghost_email|Email address of the first customer ghost.|true|string||


### First_entered
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|first_entered|The date when the user first entered our page.|true|string||


### First_ghost
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|first_ghost_total|Value of the first ghost's cart.|true|string||
|first_ghost_item_count|Number of items in cart.|true|string||
|first_ghost_email|Email address of the first ghost.|true|string||


### Money_recovered
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|money_recovered|The amount of money recovered.|true|string||


### Payment
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||


### Plugin
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||


### Response_account_cancelled
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_cart_recovered
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_days_left
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_emails_sent
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_first_customer_ghost
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_first_entered
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_first_ghost
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_money_recovered
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_ok
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|content|ok|false|string||


### Response_payment
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_plugin
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_signup_end
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_signup_start
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_statistics
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_wizard1
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_wizard2
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Response_wizard3
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|code|200|false|string||
|message||false|object||


### Signup_ended
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|name|Name of the newly registered user.|true|string||
|platform|The ecommerce platform of the site registered.|true|string||
|sender_email|The date when the signup of the site started.|true|string||
|time_spent_on_registration|The whole duration of the registration.|true|string||
|signup_ended|The date when the signup of the user ended.|true|string||


### Signup_started
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|email|Email address of site or its owner.|true|string||
|domain|Domain of the site.|true|string||
|signup_started|The date when the signup of the user started.|true|string||


### Statistics
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|recovered_revenue|The amount of recovered revenue.|true|integer||
|recovered_revenue_2|The amount of recovered revenue.|true|integer||
|revenue_with_gm|The amount of revenue using GhostMonitor.|true|integer||
|revenue_without_gm|The amount of revenue without GhostMonitor.|true|integer||
|lost_revenue|The amount of lost revenue.|true|integer||
|revenue_growth|The growth of income.|true|integer||
|started_checkout|The date the user started the checkout.|true|integer||
|abandonment_rate|The percentage of the abandoned shoppings.|true|number||
|abandoned_carts|The number of abandoned carts.|true|integer||
|identifiable_rate||true|number||
|abandoned_carts_with_email|The number of emails sent to cart abandoners.|true|integer||
|conversion_rate|The number of abandoned carts.|true|number||
|carts_recovered||true|integer||
|emails_sent|The number of emails sent out.|true|integer||
|open_rate|The percentage of opened emails.|true|number||
|click_rate|The percentage of clicking to the link in the email.|true|number||
|query_statistics_at||true|integer||
|currency_symbol|The symbol of the currency the site uses.|true|string||


### Wizard_page_1
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|wizard_page_1|The time it took to fill the first page of the sign up wizard.|true|string||


### Wizard_page_2
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|wizard_page_2|The time it took to fill the second page of the sign up wizard.|true|string||


### Wizard_page_3
|Name|Description|Required|Schema|Default|
|----|----|----|----|----|
|site_id|ID of the site you want to add information about.|true|string||
|wizard_page_3|The time it took to fill the third page of the sign up wizard.|true|string||


