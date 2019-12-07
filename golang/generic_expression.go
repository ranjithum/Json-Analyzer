package main

import (
	"bytes"
	"strconv"
)

type BlockType int8

const (
	IF_BLOCK BlockType = iota
	FOR_BLOCK
)

type GenericExpression interface {
	ToString() string
	AddIdentifier(ident *Identifier)
	GetValue() interface{}
	SetJsonDecoder(dec JsonByteDecoderInterface)
	SetBlockType(_type BlockType)
	CleanUp()
	OperatorPlusPlus() bool
	SetParent(blk GenericBlock)
	GetJsonArray() interface{}
}

type CommonExpression struct {
	m_listOfIdentifier []*Identifier
	m_jsonDecoder      JsonByteDecoderInterface
	m_jsonArray        interface{}
	m_currentIndex     int
	m_blockType        BlockType
	m_parentBlock      GenericBlock
}

func (ce *CommonExpression) AddIdentifier(ident *Identifier) {
	if len(ce.m_listOfIdentifier) == 0 {
		ce.m_listOfIdentifier = make([]*Identifier, 0)
	}

	ce.m_listOfIdentifier = append(ce.m_listOfIdentifier, ident)
}

func (ce *CommonExpression) SetJsonDecoder(decoder JsonByteDecoderInterface) {
	ce.m_jsonDecoder = decoder
}

func (ce *CommonExpression) SetBlockType(_type BlockType) {
	ce.m_blockType = _type
}

func (ce *CommonExpression) CleanUp() {
	ce.m_jsonArray = nil
	ce.m_currentIndex = -1
}

func (ce *CommonExpression) SetParent(blk GenericBlock) {
	ce.m_parentBlock = blk
}

func (ce *CommonExpression) GetJsonArray() interface{} {
	switch arr_interface := ce.m_jsonArray.(type) {
	case []interface{}:
		return arr_interface[ce.m_currentIndex]
	}
	return nil
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
			m_currentIndex:     -1,
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
	if je.m_blockType == IF_BLOCK {
		return je.m_jsonDecoder.ValidateAndGetExprValue(je)
	} else {
		je.m_jsonArray = je.m_jsonDecoder.ValidateAndGetJsonArray(je)
		if je.m_jsonArray != nil {
			je.m_currentIndex = 0
			return true
		}
	}
	return nil
}

func (je *JsonExpression) OperatorPlusPlus() bool {
	je.m_currentIndex += 1
	switch arr_interface := je.m_jsonArray.(type) {
	case []interface{}:
		if len(arr_interface) < je.m_currentIndex+1 {
			return false
		}
		return true
	}
	return false
}

type NonJsonExpression struct {
	CommonExpression
}

func NewNonJsonExpression() *NonJsonExpression {
	return &NonJsonExpression{
		CommonExpression: CommonExpression{
			m_listOfIdentifier: make([]*Identifier, 0),
			m_currentIndex:     -1,
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
	if nje.m_blockType == IF_BLOCK {
		return nje.m_jsonDecoder.ValidateAndGetExprValueFromArray(nje, nje.m_parentBlock.GetJsonValueArray(nje.m_listOfIdentifier[0].m_expression))
	} else {
	}
	return nil
}

func (nje *NonJsonExpression) OperatorPlusPlus() bool {
	return true
}
