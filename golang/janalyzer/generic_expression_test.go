package janalyzer

import (
	"testing"
)

func TestJsonExpressionToString(t *testing.T) {
	param_index := []int{1, 2}
	ident1 := &Identifier{
		m_expression: "param",
		m_indices:    param_index,
	}

	ident2 := &Identifier{
		m_expression: "object",
	}

	jsonExpr1 := NewJsonExpression(0)
	jsonExpr1.AddIdentifier(ident1)
	jsonExpr1.AddIdentifier(ident2)

	wants := "json[0].param[1][2].object"
	if wants != jsonExpr1.ToString() {
		t.Errorf("JsonExpressionToString : wants : %v, got %v", wants, jsonExpr1.ToString())
	}

	jsonExpr2 := NewJsonExpression(-1)
	jsonExpr2.AddIdentifier(ident2)
	wants = "json.object"
	if wants != jsonExpr2.ToString() {
		t.Errorf("JsonExpressionToString(2) : wants : %v, got %v", wants, jsonExpr2.ToString())
	}
}

func TestNonJsonExpressionToString(t *testing.T) {
	param_index := []int{1, 2}
	ident1 := &Identifier{
		m_expression: "param",
		m_indices:    param_index,
	}

	ident2 := &Identifier{
		m_expression: "object",
	}

	nonJsonExpr := NewNonJsonExpression()
	nonJsonExpr.AddIdentifier(ident1)
	nonJsonExpr.AddIdentifier(ident2)

	wants := "param[1][2].object"
	got := nonJsonExpr.ToString()

	if wants != got {
		t.Errorf("NonJsonExpressionToString : wants : %v, got : %v", wants, got)
	}
}
