package main

import (
	"fmt"
	"io/ioutil"
	"testing"
)

const filterRulePath string = "../sample-filter-rules/"
const json_file_path string = "../sample-json-files/"

func TestJsonRuleEngineToString(t *testing.T) {
	var jR *JsonRuleEngine
	var err error

	files, _ := ioutil.ReadDir(filterRulePath)

	for _, f := range files {
		fmt.Println("Reading file : ", f.Name())
		jR, err = NewJsonRuleEngine(filterRulePath + f.Name())
		if err != nil {
			fmt.Println(err)
			break
		}

		fmt.Println(jR.ToString())
	}
}
