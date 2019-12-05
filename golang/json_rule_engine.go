package main

import (
	"errors"
	"io/ioutil"
)

type ErrorCode int8

const (
	OK ErrorCode = iota
	JSON_STREAM_ERROR
	RULE_MATCH_FAILURE
)

type JsonRuleEngine struct {
	m_listOfStatements listOfCodeBlocks
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
	return OK
}

func (jR *JsonRuleEngine) ToString() string {
	return jR.m_listOfStatements.ToString()
}
