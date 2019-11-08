
#include <algorithm>
#include <sstream>
#include "include/statement.h"
#include "include/generic_condition.h"

IfCondition::IfCondition(GenericExpression* expr, std::string quoted_string, Statement* parent):
    Condition(parent),
    m_lhsExpr(std::unique_ptr<GenericExpression>(expr)),
    m_quotedValue(quoted_string)
{
    auto IsQuote = [] (char c) -> bool
    {
        if (c == '"')
            return true;
        return false;
    };

    m_quotedValue.erase(std::remove_if(m_quotedValue.begin(), m_quotedValue.end(), IsQuote), m_quotedValue.end());
    m_lhsExpr->SetParent(this);
}

bool IfCondition::EvaluateCondition()
{
    std::string lhs_value;
    m_lhsExpr->EvaluateExpression(lhs_value);

    if (m_quotedValue.compare(lhs_value) == 0)
        return true;

    return false;
}

std::string IfCondition::ToString()
{
    std::stringstream ss;
    ss << "if " << m_lhsExpr->ToString() <<
       " == " << m_quotedValue;
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
    std::string dummy_val;
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
