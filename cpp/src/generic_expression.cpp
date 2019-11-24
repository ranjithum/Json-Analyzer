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

bool JsonExpression::EvaluateExpression(ExpressionValue& expr_value)
{
    if ( m_blockType == BlockType::IF )
    {
        // For the Json **if** expression, this would get the value
        return m_expressionEvaluator->ValidateAndGetExprValue(this, expr_value);
    }
    else
    {
        // For the Json **for** expression, this would get us the iterator
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

    //! If the string matches then return this value iterator, else parent Value Iterator
    if (str.compare(first_nonjson_attr) == 0)
    {
        return m_valueArr.get();
    }
    else
    {
        return m_parentCondition->GetExpression(first_nonjson_attr)->GetValueIterator();
    }
}

bool NonJsonExpression::EvaluateExpression(ExpressionValue& expr_value)
{
    if ( m_blockType == BlockType::IF )
    {
        //! This would be internally used by **if** statement used within **for**
        //! For eg :-
        //  for eachRep in json {
        //        if eachRep.id == "0003" {
        //        	pp
        //        }
        //  }
        //! "eachRep.id" is a non-json expression
        std::string dummy("");
        return m_expressionEvaluator->ValidateAndGetExprValue(this, GetValueIterator(dummy), expr_value);
    }
    else
    {
        //! This would be internally used by **for** statement used within **for**
        m_valueArr = std::make_unique<ValueWrapper>(
                         m_expressionEvaluator->GetJsonArray()
                     );
        std::string dummy("");
        return m_expressionEvaluator->ValidateAndGetValueIterator(this, GetValueIterator(dummy), m_valueArr.get());
    }
    return false;
}
