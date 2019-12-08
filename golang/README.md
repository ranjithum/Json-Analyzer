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

### How to build ?

Install necessary pacakges - ragel, goyacc
```
$ apt install ragel
$ go get golang.org/x/tools/cmd/goyacc
```

Build the package
```
$ cd golang/janalyzer/
$ make
```
> Note :- Above command have been tested on Ubuntu 18.04, where go env is already setup.

### How to use ?
```
package main

import (
        "fmt"

        "github.com/ranjithum/Json-Analyzer/golang/janalyzer"
)

func main() {
        jR, j_err := janalyzer.NewJsonRuleEngine("./simpsons.character")

        if j_err != nil {
                fmt.Println(j_err)
        }

        var json_stream [5][]byte
        json_stream[0] = []byte(`{"Name":"Homer Simpsons", "Age":36, "Gender":"Male"}`)
        json_stream[1] = []byte(`{"Name":"Marge Simpsons", "Age":34, "Gender":"Female"}`)
        json_stream[2] = []byte(`{"Name":"Bart Simpsons", "Age":10, "Gender":"Male"}`)
        json_stream[3] = []byte(`{"Name":"Lisa Simpsons", "Age":8, "Gender":"Female"}`)
        json_stream[4] = []byte(`{"Name":"Maggie Simpsons", "Age":1, "Gender":"Female"}`)

        var errCode janalyzer.ErrorCode
        for _, eachJsonByteStream := range json_stream {
                errCode = jR.ParseJsonStream(eachJsonByteStream)
                if errCode == janalyzer.OK {
                        fmt.Println(string(eachJsonByteStream))
                }
        }

}

$ cat simpsons.character
# if age is greater than equal to 10
if json.Age >= 10 {
        pp
}

$ go run .
{"Name":"Homer Simpsons", "Age":36, "Gender":"Male"}
{"Name":"Marge Simpsons", "Age":34, "Gender":"Female"}
{"Name":"Bart Simpsons", "Age":10, "Gender":"Male"}

```
