package janalyzer

import "testing"

func TestCompareValue(t *testing.T) {
	var oper Comparator
	oper = &CompareEqualTo{}

	compareValue := NewCompareValue(STRING, "Vegeta")

	compareValue.SetComparator(oper)
	bVal := compareValue.CompareIt("Vegeta")
	if !bVal {
		t.Errorf(" CompareValue got %v, want %v", bVal, true)
	}
}
