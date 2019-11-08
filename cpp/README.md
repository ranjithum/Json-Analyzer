## C++ implementation internally makes use of flex and yacc for parsing the rules and RapidJSON[https://rapidjson.org/] for parsing the json stream.

**JsonRuleEngine** is the main class which maintains all the rules and runs the rules against each json stream.

These are the method which are exposed.

> Constructor which takes a rule file (or a filter file) as argument, throws **JsonRuleException** exception if there is something wrong with the rules or file path is incorrect.

```JsonRuleEngine::JsonRuleEngine(const char* filter_file);```

> Method for parsing json stream

```ErrorCode JsonRuleEngine::ParseJsonStream(const char* json_stream);```

> Possible ErrorCode

> * **OK** 					-> Json stream matched one of the rules
> * **JSON_STREAM_ERROR** 	-> Fail to parse Json stream
> * **RULE_MATCH_FAILURE** 	-> Json stream doesn't match any given rules

### How to build ?

Install necessary packages
```$ apt install cmake flex bison```

Execute `git submodule update --init` to get the files of thirdparty submodules.

Create directory called `build`.

Change to `build` directory and run `cmake ..`.

For building with test use `cmake .. -DBuildTest=ON`.

Once built you should be able to see `libjson_analyzer.so` library.
