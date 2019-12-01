package main

import "testing"

func TestCompareValue(t *testing.T) {
	var oper Comparator
	oper = &CompareEqualTo{}

	compareValue := CompareValue{
		m_dataType: STRING,
		m_rhsValue: "Vegeta",
	}

	compareValue.SetComparator(oper)
	bVal := compareValue.CompareIt("Vegeta")
	if !bVal {
		t.Errorf(" CompareValue got %v, want %v", bVal, true)
	}
}
