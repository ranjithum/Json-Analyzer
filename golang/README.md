## GO implementation internally make use of [Ragel](https://en.wikipedia.org/wiki/Ragel), [goyacc](https://godoc.org/golang.org/x/tools/cmd/goyacc) for parsing the rules and [Json](https://golang.org/pkg/encoding/json/) package for parsing json stream.

**JsonRuleEngine** is the main struct which maintains all the rules and runs the rules against json object.

Below functions have been exposed

> Function which takes a rule file (or a filter file) as argument, returns a pointer to JsonRuleEngine and errors if there is something wrong with the rules or file path is incorrect. 

```func NewJsonRuleEngine(filename string) (*JsonRuleEngine, error)```

> Method for parsing json stream

```func (jR *JsonRuleEngine) ParseJsonStream(json_stream []byte) ErrorCode```

> Possible ErrorCode

> * **OK**					-> Json stream matched one of the rule(s)
> * **JSON_STREAM_ERROR**	-> Fail to parse Json stream, Something wrong with the Json stream
> * **RULE_MATCH_FAILURE**  -> Json stream doesn't match any given rule(s)
