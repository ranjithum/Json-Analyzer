package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"testing"
)

const filterRulePath string = "../sample-filter-rules/"
const json_file_path string = "../sample-json-files/"

func TestJsonRuleEngineToString(t *testing.T) {
	/*
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
	*/
}

func TestValidateAndGetExprValue(t *testing.T) {
	jsonExpr := NewJsonExpression(0)
	jsonExpr.AddIdentifier(NewIdentifier("params"))
	jsonExpr.AddIdentifier(NewIdentifier("oldObject"))
	jsonExpr.AddIdentifier(NewIdentifier("oid"))

	data, err := ioutil.ReadFile(json_file_path + "diam_test_1.json")
	if err != nil {
		fmt.Println("File read error : ", err)
		return
	}
	jR := JsonRuleEngine{}

	err = json.Unmarshal(data, &jR.m_decodedJson)
	if err != nil {
		fmt.Println("Json Parse error : ", err)
		return
	}

	f_value := jR.ValidateAndGetExprValue(jsonExpr)

	final_value := f_value.(float64)
	if final_value != 205793453 {
		t.Errorf("Wants : %v, got : %v", 205793453, final_value)
	}
}

func TestFilterTest1(t *testing.T) {
	jR, err := NewJsonRuleEngine(filterRulePath + "filter_test_1.rule")

	if err != nil {
		fmt.Println("File read error : ", err)
		return
	}

	json_stream, j_err := ioutil.ReadFile(json_file_path + "diam_test_1.json")
	if j_err != nil {
		fmt.Println("Json Parse error : ", err)
		return
	}

	got := jR.ParseJsonStream(json_stream)
	wants := OK
	if got != wants {
		t.Errorf("wants : %v, Got : %v", wants, got)
	}
}

func TestFilterTest2(t *testing.T) {
	jR, err := NewJsonRuleEngine(filterRulePath + "filter_test_2.rule")

	if err != nil {
		fmt.Println("File read error : ", err)
		return
	}

	json_stream, j_err := ioutil.ReadFile(json_file_path + "diam_test_2.json")
	if j_err != nil {
		fmt.Println("Json Parse error : ", err)
		return
	}

	got := jR.ParseJsonStream(json_stream)
	wants := OK
	if got != wants {
		t.Errorf("wants : %v, Got : %v", wants, got)
	}
}

func TestFilterTest3(t *testing.T) {
	jR, err := NewJsonRuleEngine(filterRulePath + "filter_test_3.rule")
	if err != nil {
		fmt.Println("File read error : ", err)
		return
	}

	json_stream, j_err := ioutil.ReadFile(json_file_path + "diam_test_1.json")
	if j_err != nil {
		fmt.Println("Json Parse error : ", err)
		return
	}

	got := jR.ParseJsonStream(json_stream)
	wants := OK
	if got != wants {
		t.Errorf("wants : %v, Got : %v", wants, got)
	}
}

func TestFilterTest4(t *testing.T) {
	jR, err := NewJsonRuleEngine(filterRulePath + "filter_test_4.rule")

	if err != nil {
		fmt.Println("File read error : ", err)
		return
	}

	json_stream, j_err := ioutil.ReadFile(json_file_path + "diam_test_2.json")
	if j_err != nil {
		fmt.Println("Json Parse error : ", err)
		return
	}

	// GetLogger().SetLogLevel(DEBUG_LEVEL)
	got := jR.ParseJsonStream(json_stream)
	wants := OK
	if got != wants {
		t.Errorf("wants : %v, Got : %v", wants, got)
	}
}

func TestFilterTestBackery(t *testing.T) {

	jR, err := NewJsonRuleEngine(filterRulePath + "backery_filter.rule")
	if err != nil {
		fmt.Println("File read error : ", err)
		return
	}

	json_stream, j_err := ioutil.ReadFile(json_file_path + "backery.json")
	if j_err != nil {
		fmt.Println("Json Parse error : ", err)
		return
	}

	// GetLogger().SetLogLevel(DEBUG_LEVEL)
	got := jR.ParseJsonStream(json_stream)
	wants := OK
	if got != wants {
		t.Errorf("wants : %v, Got : %v", wants, got)
	}
}

func TestMedication(t *testing.T) {
	jR, err := NewJsonRuleEngine(filterRulePath + "medication_filter.rule")
	if err != nil {
		fmt.Println("File read error : ", err)
		return
	}

	json_stream, j_err := ioutil.ReadFile(json_file_path + "medication.json")
	if j_err != nil {
		fmt.Println("Json Parse error : ", err)
		return
	}

	// GetLogger().SetLogLevel(DEBUG_LEVEL)
	got := jR.ParseJsonStream(json_stream)
	wants := RULE_MATCH_FAILURE
	if got != wants {
		t.Errorf("wants : %v, Got : %v", wants, got)
	}
}

func TestGreaterThanRules(t *testing.T) {
	jR, err := NewJsonRuleEngine(filterRulePath + "filter_test_greaterThan.rule")
	if err != nil {
		fmt.Println("File read error : ", err)
		return
	}

	json_stream, j_err := ioutil.ReadFile(json_file_path + "diam_test_1.json")
	if j_err != nil {
		fmt.Println("Json Parse error : ", err)
		return
	}

	// GetLogger().SetLogLevel(DEBUG_LEVEL)
	got := jR.ParseJsonStream(json_stream)
	wants := OK
	if got != wants {
		t.Errorf("wants : %v, Got : %v", wants, got)
	}
}

func TestLessThanRules(t *testing.T) {
	jR, err := NewJsonRuleEngine(filterRulePath + "filter_test_lessThan.rule")
	if err != nil {
		fmt.Println("File read error : ", err)
		return
	}

	json_stream, j_err := ioutil.ReadFile(json_file_path + "diam_test_1.json")
	if j_err != nil {
		fmt.Println("Json Parse error : ", err)
		return
	}

	// GetLogger().SetLogLevel(DEBUG_LEVEL)
	got := jR.ParseJsonStream(json_stream)
	wants := OK
	if got != wants {
		t.Errorf("wants : %v, Got : %v", wants, got)
	}
}

func TestWrongFilter(t *testing.T) {

	_, got := NewJsonRuleEngine(filterRulePath + "wrong_filter.rule")
	wants := "Parsing rules failed"
	if got.Error() != wants {
		t.Errorf("wants : %v, Got : %v", wants, got)
		return
	}
}
