#include <iostream>
#include <sstream>
#include "include/statement.h"
#include "include/generic_condition.h"

IfCondition::IfCondition(GenericExpression* expr, CompareValueBase* c_val, Statement* parent):
    Condition(parent),
    m_lhsExpr(std::unique_ptr<GenericExpression>(expr)),
    m_compareValue(std::unique_ptr<CompareValueBase>(c_val))
{
    m_lhsExpr->SetParent(this);
}

bool IfCondition::EvaluateCondition()
{
    ExpressionValue lhs_value;
    m_lhsExpr->EvaluateExpression(lhs_value);

    if (lhs_value.m_expressionType != m_compareValue->GetDataType())
    {
        std::cout << "LHS and RHS are not same data type for condition : " << this->ToString() << "\n";
        std::cout << "LHS = " << c_dataType_To_string.find(lhs_value.m_expressionType)->second << "\n";
        std::cout << "RHS = " << c_dataType_To_string.find(m_compareValue->GetDataType())->second << "\n";
        return false;
    }

    switch(lhs_value.m_expressionType)
    {
    case BASIC_DTYPE::BOOL:
        return m_compareValue->CompareIt(lhs_value.boolValue);
        break;
    case BASIC_DTYPE::SINT64:
        return m_compareValue->CompareIt(lhs_value.sint64Value);
        break;
    case BASIC_DTYPE::DOUBLE:
        return m_compareValue->CompareIt(lhs_value.doubleValue);
        break;
    case BASIC_DTYPE::STRING:
        return m_compareValue->CompareIt(lhs_value.stringValue);
        break;
    }
    return false;
}

std::string IfCondition::ToString()
{
    std::stringstream ss;

    ss << "if " << m_lhsExpr->ToString() <<
       " == " << m_compareValue->GetValue();
    return ss.str();
}

GenericExpression* IfCondition::GetExpression(std::string& ss)
{
    return m_parentStatement->get_condition(ss)->GetExpression(ss);
}

void IfCondition::CleanUp()
{
    m_lhsExpr->CleanUp();
}

ForCondition::ForCondition(std::string var, GenericExpression* expr, Statement* parent):
    Condition(parent),
    lhs_variable(var),
    m_rhsExpr(std::unique_ptr<GenericExpression>(expr))
{
    m_rhsExpr->SetParent(this);
}

bool ForCondition::EvaluateCondition()
{
    ExpressionValue dummy_val;
    return m_rhsExpr->EvaluateExpression(dummy_val);
}

std::string ForCondition::ToString()
{
    std::stringstream ss;
    ss << "for " << lhs_variable <<
       " in " << m_rhsExpr->ToString();
    return ss.str();
}

bool ForCondition::Increment()
{
    return m_rhsExpr->IncrementValueIterator();
}

GenericExpression* ForCondition::GetExpression(std::string& non_json_str)
{
    if (non_json_str.compare(lhs_variable) == 0)
    {
        return m_rhsExpr.get();
    }
    else
    {
        Condition* temp = m_parentStatement->get_condition(non_json_str);
        return temp->GetExpression(non_json_str);
    }
    return 0;
}

void ForCondition::CleanUp()
{
    m_rhsExpr->CleanUp();
}
