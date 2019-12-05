package main

type Comparator interface {
	CompareValue(lhs interface{}, rhs interface{}) bool
	ToString() string
}

type CompareEqualTo struct{}

func (c *CompareEqualTo) CompareValue(lhs interface{}, rhs interface{}) bool {
	return (lhs == rhs)
}

func (c *CompareEqualTo) ToString() string {
	return "=="
}

type CompareGreaterThanEqual struct{}

func (c *CompareGreaterThanEqual) CompareValue(lhs interface{}, rhs interface{}) bool {
	switch d_type := lhs.(type) {
	case int64:
		return d_type >= rhs.(int64)
	case float64:
		return d_type >= rhs.(float64)
	case string:
		return d_type >= rhs.(string)
	}
	return false
}

func (c *CompareGreaterThanEqual) ToString() string {
	return ">="
}

type CompareGreaterThan struct{}

func (c *CompareGreaterThan) CompareValue(lhs interface{}, rhs interface{}) bool {
	switch d_type := lhs.(type) {
	case int64:
		return d_type > rhs.(int64)
	case float64:
		return d_type > rhs.(float64)
	case string:
		return d_type > rhs.(string)
	}
	return false
}

func (c *CompareGreaterThan) ToString() string {
	return ">"
}

type CompareLessThanEqual struct{}

func (c *CompareLessThanEqual) CompareValue(lhs interface{}, rhs interface{}) bool {
	switch d_type := lhs.(type) {
	case int64:
		return d_type <= rhs.(int64)
	case float64:
		return d_type <= rhs.(float64)
	case string:
		return d_type <= rhs.(string)
	}
	return false
}

func (c *CompareLessThanEqual) ToString() string {
	return "<="
}

type CompareLessThan struct{}

func (c *CompareLessThan) CompareValue(lhs interface{}, rhs interface{}) bool {
	switch d_type := lhs.(type) {
	case int64:
		return d_type < rhs.(int64)
	case float64:
		return d_type < rhs.(float64)
	case string:
		return d_type < rhs.(string)
	}
	return false
}

func (c *CompareLessThan) ToString() string {
	return "<"
}
