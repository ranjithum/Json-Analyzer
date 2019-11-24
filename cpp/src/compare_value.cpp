#include <iostream>
#include <memory>
#include <algorithm>
#include "include/compare_value.h"

template<typename DTYPE>
CompareValue<DTYPE>::CompareValue(const DTYPE r_val, BASIC_DTYPE type):
    CompareValueBase(type),
    m_rhs(r_val)
{}

template<>
CompareValue<std::string>::CompareValue(std::string r_val, BASIC_DTYPE type):
    CompareValueBase(type),
    m_rhs(r_val)
{
    auto IsQuote = [] (char c) -> bool
    {
        if (c == '"')
            return true;
        return false;
    };

    std::string& ref = const_cast<std::string&>(m_rhs);
    ref.erase(std::remove_if(ref.begin(), ref.end(), IsQuote), ref.end());
}


template<typename DTYPE>
void CompareValue<DTYPE>::SetComparator(CompareOperators oper)
{
    switch(oper)
    {
    case CompareOperators::DoubleEqualsOperator:
        m_comparator = std::make_unique<CompareDoubleEqualsOperator<DTYPE>>();
        break;
    case CompareOperators::GreaterThanEqualsOperator:
        m_comparator = std::make_unique<CompareGreaterThanEqualsOperator<DTYPE>>();
        break;
    case CompareOperators::GreaterThanOperator:
        m_comparator = std::make_unique<CompareGreaterThanOperator<DTYPE>>();
        break;
    case CompareOperators::LessThanEqualsOperator:
        m_comparator = std::make_unique<CompareLessThanEqualsOperator<DTYPE>>();
        break;
    case CompareOperators::LessThanOperator:
        m_comparator = std::make_unique<CompareLessThanOperator<DTYPE>>();
        break;
    }
}

template<typename DTYPE>
std::string CompareValue<DTYPE>::GetValue()
{
    return std::to_string(m_rhs);
}

template<>
std::string CompareValue<bool>::GetValue()
{
    return m_rhs == true ? "true" : "false";
}

template<>
std::string CompareValue<std::string>::GetValue()
{
    return m_rhs;
}

template<typename DTYPE>
bool CompareValue<DTYPE>::CompareIt(const DTYPE& lhs)
{
    //std::cout << "Comparing LHS : " << lhs << " With RHS : " << m_rhs << "\n";
    return m_comparator->DoCompare(lhs, m_rhs);
}

template class CompareValue<bool>;
template class CompareValue<int64_t>;
template class CompareValue<double>;
template class CompareValue<std::string>;
