package main

import (
	"testing"
)

func TestToString(t *testing.T) {
	iden := &Identifier{
		m_expression: "param",
	}

	iden.AddIndex(5)
	iden.AddIndex(3)
	iden.AddIndex(0)

	if iden.ToString() != "param[5][3][0]" {
		t.Errorf("IdentifierToString : got : %v, want %v", iden.ToString(), "param[5][3][0]")
	}
}
