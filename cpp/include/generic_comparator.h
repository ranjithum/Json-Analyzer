#pragma once

enum class CompareOperators
{
	DoubleEqualsOperator,
	GreaterThanEqualsOperator,
	GreaterThanOperator,
	LessThanEqualsOperator,
	LessThanOperator
};

class CompareDoubleEqualsOperator
{
public:
	bool DoCompare(auto& lhs, auto& rhs)
	{
		return lhs == rhs;
	}
};

class CompareGreaterThanEqualsOperator 
{
public:
	bool DoCompare(auto& lhs, auto& rhs)
	{
		return lhs >= rhs;
	}
};

class CompareGreaterThanOperator 
{
public:
	bool DoCompare(auto& lhs, auto& rhs)
	{
		return lhs > rhs;
	}
};

class CompareLessThanEqualsOperator 
{
public:
	bool DoCompare(auto& lhs, auto& rhs)
	{
		return lhs <= rhs;
	}
};

class CompareLessThanOperator 
{
public:
	bool DoCompare(auto& lhs, auto& rhs)
	{
		return lhs < rhs;
	}
};
