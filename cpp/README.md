## C++ implementation internally makes use of flex and yacc for parsing the rules and [RapidJSON](https://rapidjson.org/) for parsing the json stream.

**JsonRuleEngine** is the main class which maintains all the rules and runs the rules against json object.

These are the method which are exposed.

> Constructor which takes a rule file (or a filter file) as argument, throws **JsonRuleException** exception if there is something wrong with the rules or file path is incorrect.

```JsonRuleEngine::JsonRuleEngine(const char* filter_file);```

> Method for parsing json stream

```ErrorCode JsonRuleEngine::ParseJsonStream(const char* json_stream);```

> Possible ErrorCode

> * **OK** 			-> Json stream matched one of the rules
> * **JSON_STREAM_ERROR** 	-> Fail to parse Json stream
> * **RULE_MATCH_FAILURE** 	-> Json stream doesn't match any given rules

### How to build ?

Install necessary packages - cmake, flex, bison

Execute `git submodule update --init` to get the files of thirdparty submodules.

Create directory called `build`.

Change to `build` directory and run `cmake ..` (For building with test use `cmake .. -DBuildTest=ON`).

Once built you should be able to see `libjson_analyzer.so` library.
```
$ apt install cmake flex bison
$ git submodule update --init
$ mkdir build; cd build
$ cmake .. -DBuildTest=ON
$ ls libjson_analyzer.so
libjson_analyzer.so
```

> Note :- Above command have been tested on Ubuntu 18.04.

### Sample example.
```
#include <iostream>
#include "include/json_rule_engine.h"
#include "include/json_rule_exception.h"

int main()
{
        std::string json_array[] = {
                "{\"name\": \"Melisandre\", \"age\": 26, \"city\": \"Melony\"}",
                "{\"name\": \"Sansa\", \"age\": 26, \"city\": \"Winterfell\"}",
                "{\"name\": \"shae\", \"age\": 36, \"city\": \"Green Fort\"}",
                "{\"name\": \"John snow\", \"age\": 31, \"city\": \"York\"}",
                "{\"name\": \"Daenerys\", \"age\": 26, \"city\": \"Targaryen\"}"
        };

        JsonRuleEngine *jR;
        try
        {
                 jR = new JsonRuleEngine("./GOT_CHAR.rule");
        } catch(JsonRuleException& e)
        {
                std::cerr << e.what() << "\n";
                return 1;
        }
        auto IsAge26 = [jR] (std::string& json_str) -> bool
        {
                ErrorCode retVal =  jR->ParseJsonStream(json_str.c_str());
                return ErrorCode::OK == retVal ? true: false;
        };

        for (auto& str : json_array)
        {
                if(IsAge26(str))
                        std::cout << str << "\n";
        }
        delete jR;
        return 0;
}

$ cat GOT_CHAR.rule
# Basically i m filtering any character who are aged 26
if json.age == "26" {
pp
}

$ g++ sample_eg.cpp -I. -Wl,-rpath,./build -L./build -ljson_analyzer
$ ./a.out
{"name": "Melisandre", "age": 26, "city": "Melony"}
{"name": "Sansa", "age": 26, "city": "Winterfell"}
{"name": "Daenerys", "age": 26, "city": "Targaryen"}
```
