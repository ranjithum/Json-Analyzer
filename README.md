# Json Analyzer
A simple library used for parsing and filtering json packet.

### For analyzing a custom JSON stream we don't have any tools today. Hence this library provides some simple API for parsing and filtering json packet.

## How does a sample filter rules look like ?
```if json[0].method == "object.updated" {
    if json[0].params.oldObject.oid == "205793453" {
        pp
    }
    for gxRule in json[0].params.oldObject.gxRules {
        if gxRule.ruleName == "DEF_SOS_GPRS_QOS_UNLIM" {
            if gxRule.activated == "true" {
                pp
            }
        }
    }
```
    
As you can see above, you can write your own custom rules for filtering the json packet. if a match condition (pp) is encountered then it just returs success.
Parent node can be either "**json[0].**" or "**json.**"

#### List of keywords present 

> * **json**   -> Denotes parent node
> * **if**     -> Comparing conditions
> * **for**    -> Loops through a list
> * **in**     -> Used along with for
> * **pp**     -> pass condition

## Supported features in v-1.0

> * Supports recurssive if and for loop.
> * Supports comparison in the form of string.

## Supported features in upcoming release

> * Support for some basic data types (int64, float, bool).
> * Support for more binary operators (!=, >=, <=).
> * Support for declaring variables.
> * **GOLANG** support.
> * **PYTHON** support.

## Some Caveats
* Supports only string comparison, all other basic data types must be converted to string (in "").
* Beggining of the line must not be empty.
* Validation of the statements are not done.
