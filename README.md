# Json Analyzer
A simple library used for parsing and filtering json packet.

### For analyzing/filtering a custom JSON stream there are not much tools available. Hence this library provides some simple API for parsing and filtering json packet.

## How does a sample filter rules look like ?
```
# Anything starting with # are comments
# Parent node being an Array
if json[0].method == "object.updated" {
    if json[0].params.object.id == "205793453" {
        pp
    }
    # Iterate through the list
    for rule in json[0].params.object.rules {
        if rule.ruleName == "Match" {
            if rule.active == "true" {
                pp
            }
        }
    }
}

# Parent node being an object
if json.method == "object.update" {
	pp
}

# Many such rules can be written
```
    
As you can see above, you can write your own custom rules for filtering the json packet. if a match condition (pp) is encountered then it just returns success.
Parent node can be either "**json[0].**" or "**json.**."

Please note :- once a match condition is encountered it doesn't execute subsequent statements. 

Please check these [sample filter rules](https://github.com/ranjithum/Json-Analyzer/tree/master/sample-filter-rules) for more complex rules.

### List of keywords present 

> * **json**   -> Denotes parent node
> * **if**     -> Comparing conditions
> * **for**    -> Loops through a list
> * **in**     -> Used along with for
> * **pp**     -> pass condition

## Supported features in version-1.0

> * Supports recurssive if and for loop.
> * Supports comparison in the form of string.
> * Support implementation in c++. Please check [c++](https://github.com/ranjithum/Json-Analyzer/tree/master/cpp) for more details.

## Supported features in upcoming release

> * Support for basic data types (int64, float, bool).
> * Support for more binary operators (!=, >=, <=).
> * Support for declaring variables.
> * **GOLANG** support.
> * **PYTHON** support.

## Some Caveats
* Supports only string comparison, all other basic data types must be converted to string (in "").
* Beggining of the line must not be empty.
* Validation of the statements are not done.
