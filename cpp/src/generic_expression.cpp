#include <iostream>
#include <sstream>
#include "include/generic_condition.h"
#include "include/generic_expression.h"

void GenericExpression::AddIdentifier(Identifier* e_attr)
{
    m_listOfIdentifier.emplace_back(
        std::unique_ptr<Identifier>(e_attr)
    );
}

std::string GenericExpression::ToString()
{
    std::stringstream ss("");
    for (auto& ident : m_listOfIdentifier)
    {
        ss << ident->ToString();
        ss.put('.');
    }
    std::string final_str = ss.str();
    return (final_str.length() == 0) ?
           final_str :
           (final_str.substr(0, final_str.length() - 1));
}

const std::vector<std::unique_ptr<Identifier>>& GenericExpression::GetIdentifier() const
{
    return m_listOfIdentifier;
}

std::string JsonExpression::ToString()
{
    std::stringstream ss;
    ss << "json";
    if (m_jsonIndex != -1)
    {
        ss << "[" << m_jsonIndex << "]";
    }
    ss << '.';
    ss << GenericExpression::ToString();

    return ss.str();
}

JsonExpression::JsonExpression(unsigned int j_index):
    m_jsonIndex(j_index)
{
}

int JsonExpression::GetIndex() const
{
    return m_jsonIndex;
}

bool JsonExpression::EvaluateExpression(std::string& expr_value)
{
    if ( m_blockType == 1 )
    {
        return m_expressionEvaluator->ValidateAndGetExprValue(this, expr_value);
    }
    else
    {
        m_valueArr = std::make_unique<ValueWrapper>(
                         m_expressionEvaluator->GetJsonArray()
                     );
        return m_expressionEvaluator->ValidateAndGetValueIterator(this, m_valueArr.get());
    }
    return false;
}

ValueWrapper* NonJsonExpression::GetValueIterator(std::string& str)
{
    std::string& first_nonjson_attr = m_listOfIdentifier.front()->GetListOfExprAttribute().front()->GetAttributeExprName();

    if (str.compare(first_nonjson_attr) == 0)
    {
        return m_valueArr.get();
    }
    else
    {
        return m_parentCondition->GetExpression(first_nonjson_attr)->GetValueIterator();
    }
}

bool NonJsonExpression::EvaluateExpression(std::string& expr_value)
{
    if ( m_blockType == 1 )
    {
        return m_expressionEvaluator->ValidateAndGetExprValue(this, GetValueIterator(expr_value), expr_value);
    }
    else
    {
        m_valueArr = std::make_unique<ValueWrapper>(
                         m_expressionEvaluator->GetJsonArray()
                     );
        return m_expressionEvaluator->ValidateAndGetValueIterator(this, GetValueIterator(expr_value), m_valueArr.get());
    }
    return false;
}
