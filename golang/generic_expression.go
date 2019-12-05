package main

import (
	"bytes"
	"strconv"
)

type GenericExpression interface {
	ToString() string
	AddIdentifier(ident *Identifier)
	GetValue() interface{}
}

type CommonExpression struct {
	m_listOfIdentifier []*Identifier
}

func (ce *CommonExpression) AddIdentifier(ident *Identifier) {
	if len(ce.m_listOfIdentifier) == 0 {
		ce.m_listOfIdentifier = make([]*Identifier, 0)
	}

	ce.m_listOfIdentifier = append(ce.m_listOfIdentifier, ident)
}

type JsonExpression struct {
	m_index int
	CommonExpression
}

func NewJsonExpression(index int) *JsonExpression {
	return &JsonExpression{
		m_index: index,
		CommonExpression: CommonExpression{
			m_listOfIdentifier: make([]*Identifier, 0),
		},
	}
}

func (je *JsonExpression) ToString() string {
	var expressionString bytes.Buffer

	expressionString.WriteString("json")
	if je.m_index > -1 {
		expressionString.WriteString("[")
		expressionString.WriteString(strconv.Itoa(je.m_index))
		expressionString.WriteString("]")
	}

	if len(je.m_listOfIdentifier) > 0 {
		expressionString.WriteString(".")
	}

	for index, ident := range je.m_listOfIdentifier {
		expressionString.WriteString(ident.ToString())
		if index+1 == len(je.m_listOfIdentifier) {
			break
		}
		expressionString.WriteString(".")
	}

	return expressionString.String()
}

func (je *JsonExpression) GetValue() interface{} {
	return "json-expression"
}

type NonJsonExpression struct {
	CommonExpression
}

func NewNonJsonExpression() *NonJsonExpression {
	return &NonJsonExpression{
		CommonExpression: CommonExpression{
			m_listOfIdentifier: make([]*Identifier, 0),
		},
	}
}

func (nje *NonJsonExpression) ToString() string {
	var expressionString bytes.Buffer

	for index, ident := range nje.m_listOfIdentifier {
		expressionString.WriteString(ident.ToString())
		if index+1 == len(nje.m_listOfIdentifier) {
			break
		}
		expressionString.WriteString(".")
	}

	return expressionString.String()
}

func (nje *NonJsonExpression) GetValue() interface{} {
	return "non-json-expression"
}
