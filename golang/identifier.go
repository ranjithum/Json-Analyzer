package main

import (
	"bytes"
	"strconv"
)

type Identifier struct {
	m_expression string
	m_indices    []int
}

func (ident *Identifier) AddIndex(iVal int) {
	if len(ident.m_indices) == 0 {
		ident.m_indices = make([]int, 0)
	}
	ident.m_indices = append(ident.m_indices, iVal)
}

func (ident *Identifier) ToString() string {
	var identString bytes.Buffer
	identString.WriteString(ident.m_expression)

	for index, eachIndexValue := range ident.m_indices {
		if index == len(ident.m_indices) {
			break
		}
		identString.WriteString("[")
		identString.WriteString(strconv.Itoa(eachIndexValue))
		identString.WriteString("]")
	}
	return identString.String()
}
