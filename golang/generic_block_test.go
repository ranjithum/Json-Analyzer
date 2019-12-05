package main

import (
	"testing"
)

func TestIfBlockToString(t *testing.T) {
	param_index := []int{1}
	ident1 := &Identifier{
		m_expression: "params",
		m_indices:    param_index,
	}

	ident2 := &Identifier{
		m_expression: "object",
	}

	jsonExpr1 := NewJsonExpression(0)
	jsonExpr1.AddIdentifier(ident1)
	jsonExpr1.AddIdentifier(ident2)

	oper := &CompareGreaterThanEqual{}
	compareValue := NewCompareValue(INT64, 1234512)
	compareValue.SetComparator(oper)

	pifBlock := NewIfBlock(jsonExpr1, compareValue)
	pifBlock.AddCodeBlocks(NewPrintPacketBlock())

	wants := "if json[0].params[1].object >= 1234512 {\npp\n}\n"
	got := pifBlock.ToString()

	if wants != got {
		t.Errorf("TestIfBlockToString : wants : %v, got : %v", wants, got)
	}
}

func TestForBlockToString(t *testing.T) {

	ident1 := &Identifier{
		m_expression: "params",
	}

	ident2 := &Identifier{
		m_expression: "oldObject",
	}

	ident3 := &Identifier{
		m_expression: "gxRules",
	}

	jsonExpr1 := NewJsonExpression(-1)
	jsonExpr1.AddIdentifier(ident1)
	jsonExpr1.AddIdentifier(ident2)
	jsonExpr1.AddIdentifier(ident3)

	pforBlk := NewForBlock("gxRules", jsonExpr1)

	nonjsonExpr1 := NewNonJsonExpression()
	nonjsonExpr1.AddIdentifier(&Identifier{m_expression: "gxRule"})
	nonjsonExpr1.AddIdentifier(&Identifier{m_expression: "activated"})

	compareValue := NewCompareValue(BOOL, true)
	compareValue.SetComparator(&CompareEqualTo{})
	cifBlock := NewIfBlock(nonjsonExpr1, compareValue)
	cifBlock.AddCodeBlocks(NewPrintPacketBlock())

	pforBlk.AddCodeBlocks(cifBlock)

	wants := "for gxRules in json.params.oldObject.gxRules {\nif gxRule.activated == true {\npp\n}\n\n}\n"
	got := pforBlk.ToString()
	if wants != got {
		t.Errorf("TestForBlockToString : wants : %v, got : %v", wants, got)
	}
}
