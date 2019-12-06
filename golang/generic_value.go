package main

import "fmt"

type DataType int8

const (
	BOOL DataType = iota
	DOUBLE
	STRING
)

func (d DataType) String() string {
	return [...]string{"Bool", "Double", "String"}[d]
}

type CompareValue struct {
	// Data type of rhs value
	m_dataType DataType

	// Actual rhs value
	m_rhsValue interface{}

	// Comparator for comparing values
	m_comparator Comparator
}

func NewCompareValue(dtype DataType, rhs interface{}) *CompareValue {
	return &CompareValue{
		m_dataType: dtype,
		m_rhsValue: rhs,
	}
}

func (cv *CompareValue) SetComparator(c Comparator) {
	cv.m_comparator = c
}

func (cv *CompareValue) CompareIt(lhs interface{}) bool {
	return cv.m_comparator.CompareValue(lhs, cv.m_rhsValue)
}

func (cv *CompareValue) ToString() string {
	return fmt.Sprintf("%v", cv.m_rhsValue)
}
