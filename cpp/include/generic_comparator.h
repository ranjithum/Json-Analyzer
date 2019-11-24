#pragma once

enum class CompareOperators
{
    DoubleEqualsOperator,
    GreaterThanEqualsOperator,
    GreaterThanOperator,
    LessThanEqualsOperator,
    LessThanOperator
};

template<typename T>
class ComparatorInterface {
public:
    virtual bool DoCompare(const T&, const T&) = 0;
};

template<typename T>
class CompareDoubleEqualsOperator : public ComparatorInterface<T> {
public:
    bool DoCompare(const T& lhs, const T& rhs) override
    {
        return lhs == rhs;
    }
};

template<typename T>
class CompareGreaterThanEqualsOperator : public ComparatorInterface<T> {
public:
    bool DoCompare(const T& lhs, const T& rhs) override
    {
        return lhs >= rhs;
    }
};

template<typename T>
class CompareGreaterThanOperator : public ComparatorInterface<T> {
public:
    bool DoCompare(const T& lhs, const T& rhs) override
    {
        return lhs > rhs;
    }
};

template<typename T>
class CompareLessThanEqualsOperator : public ComparatorInterface<T> {
public:
    bool DoCompare(const T& lhs, const T& rhs) override
    {
        return lhs <= rhs;
    }
};

template<typename T>
class CompareLessThanOperator : public ComparatorInterface<T> {
public:
    bool DoCompare(const T& lhs, const T& rhs) override
    {
        return lhs < rhs;
    }
};
