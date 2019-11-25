#pragma once

#include <iostream>
#include "generic_comparator.h"
#include "expression_value.h"

class CompareValueBase {
private:
    const BASIC_DTYPE m_basicDataType;
public:
    CompareValueBase(BASIC_DTYPE type):
        m_basicDataType(type)
    {}

    template<typename T>
    bool CompareIt(const T&);

    virtual std::string GetValue() = 0;

    virtual void SetComparator(CompareOperators oper) = 0;

    BASIC_DTYPE GetDataType()
    {
        return m_basicDataType;
    }

    virtual ~CompareValueBase() = default;
};

template<typename DTYPE>
class CompareValue : public CompareValueBase {
private:
    const DTYPE m_rhs;
    std::unique_ptr<ComparatorInterface<DTYPE>> m_comparator = 0;
public:

    CompareValue(const DTYPE r_val, BASIC_DTYPE type);

    void SetComparator(CompareOperators oper) override;

    std::string GetValue() override;

    bool CompareIt(const DTYPE& lhs);
};

template<typename T>
bool CompareValueBase::CompareIt(const T& lhs)
{
    CompareValue<T>* c_val = static_cast<CompareValue<T>*>(this);
    return c_val->CompareIt(lhs);
}
