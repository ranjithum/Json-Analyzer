package main

import (
	"encoding/json"
	"errors"
	"fmt"
	"io/ioutil"
	"reflect"
)

type ErrorCode int8

const (
	OK ErrorCode = iota
	JSON_STREAM_ERROR
	RULE_MATCH_FAILURE
)

type JsonByteDecoderInterface interface {
	ValidateAndGetExprValue(expr GenericExpression) interface{}
	ValidateAndGetJsonArray(expr GenericExpression) []interface{}
	ValidateAndGetExprValueFromArray(expr GenericExpression, value_arr []interface{}) interface{}
	ValidateAndGetJsonArrayFromArray(expr GenericExpression, value_arr []interface{}) []interface{}
}

type JsonRuleEngine struct {
	m_listOfStatements listOfCodeBlocks
	m_decodedJson      interface{}
}

func NewJsonRuleEngine(filename string) (*JsonRuleEngine, error) {

	data, err := ioutil.ReadFile(filename)
	if err != nil {
		return nil, err
	}

	lex := newLexer(data)
	e := yyParse(lex)

	defer func() {
		global_listOfCodeBlocks = nil
	}()

	if e != 0 {
		return nil, errors.New("Parsing rules failed")
	}

	return &JsonRuleEngine{
		m_listOfStatements: global_listOfCodeBlocks,
	}, nil

}

func (jR *JsonRuleEngine) ParseJsonStream(json_stream []byte) ErrorCode {

	defer func() {
		jR.m_decodedJson = nil
		for _, eachBlock := range jR.m_listOfStatements {
			eachBlock.CleanUp()
		}
	}()

	err := json.Unmarshal(json_stream, &jR.m_decodedJson)

	if err != nil {
		fmt.Println("Json Parse error : ", err)
		return JSON_STREAM_ERROR
	}

	for _, eachBlock := range jR.m_listOfStatements {
		if eachBlock.EvaluateBlock() {
			return OK
		}
	}
	return RULE_MATCH_FAILURE
}

func (jR *JsonRuleEngine) ToString() string {
	return jR.m_listOfStatements.ToString()
}

func GetNextValueFromkey(decoded_json interface{}, key string) interface{} {
	switch decoded_json.(type) {
	case map[string]interface{}:
		return decoded_json.(map[string]interface{})[key]
	}
	return nil
}

func GetNextValueFromIndex(decoded_json interface{}, index int) interface{} {
	switch decoded_json.(type) {
	case []interface{}:
		return decoded_json.([]interface{})[index]
	}
	return nil
}

func (jR *JsonRuleEngine) ValidateAndGetExprValue(expr GenericExpression) interface{} {

	var actual_json interface{}
	var final_value interface{}
	switch e := expr.(type) {
	case *JsonExpression:
		valid := false
		// If json index is specified, then decoded json
		// must be of array type
		if e.m_index > -1 {
			switch jR.m_decodedJson.(type) {
			case []interface{}:
				// If provided index is greater than available length
				// then its not valid
				if e.m_index+1 >= len(jR.m_decodedJson.([]interface{})) {
					actual_json = jR.m_decodedJson.([]interface{})[e.m_index]
					valid = true
				}
			}
		} else {
			switch jR.m_decodedJson.(type) {
			case map[string]interface{}:
				actual_json = jR.m_decodedJson
				valid = true
			}
		}
		if !valid {
			fmt.Println("Json Message is of Type : ", reflect.TypeOf(jR.m_decodedJson), " But rule is : ", e.ToString())
			return nil
		}

		final_value = actual_json
		for _, eachIdentifier := range e.m_listOfIdentifier {
			final_value = GetNextValueFromkey(final_value, eachIdentifier.m_expression)
			if final_value == nil {
				return nil
			}

			for _, eachIndex := range eachIdentifier.m_indices {
				final_value = GetNextValueFromIndex(final_value, eachIndex)
				if final_value == nil {
					return nil
				}
			}
		}
	}
	return final_value
}
func (jR *JsonRuleEngine) ValidateAndGetJsonArray(expr GenericExpression) []interface{} {
	var arr_inteface []interface{}
	return arr_inteface
}
func (jR *JsonRuleEngine) ValidateAndGetExprValueFromArray(expr GenericExpression, value_arr []interface{}) interface{} {
	return "hello"
}
func (jR *JsonRuleEngine) ValidateAndGetJsonArrayFromArray(expr GenericExpression, value_arr []interface{}) []interface{} {
	var arr_inteface []interface{}
	return arr_inteface
}
