
#include <sstream>
#include "include/expression_attribute.h"

ExpressionAttribute::ExpressionAttribute(std::string attr_name):
    m_attributeName(attr_name),
    m_mapIndecies()
{
}

ExpressionAttribute::ExpressionAttribute(std::string attr_name, int attr_index):
    m_attributeName(attr_name)
{
    if (attr_index >= 0 )
    {
        AddIndice(attr_index);
    }
}

void ExpressionAttribute::AddIndice(int value)
{
    m_mapIndecies.push_back(value);
}

std::string& ExpressionAttribute::GetAttributeExprName()
{
    return m_attributeName;
}

std::vector<int>& ExpressionAttribute::GetExpressionIndecies()
{
    return m_mapIndecies;
}

Identifier::Identifier(std::string attr_name, int index)
{
    AddExprAttribute(attr_name, index);
}

void Identifier::AddExprAttribute(std::string attr_name, int index)
{
    m_listOfExprAttribute.emplace_back(
        new ExpressionAttribute(attr_name, index)
    );
}

bool Identifier::AddIndiceToLastExprAttribute(int value)
{
    if (m_listOfExprAttribute.size())
    {
        m_listOfExprAttribute.back()->AddIndice(value);
        return true;
    }
    return false;
}

std::string Identifier::ToString()
{
    std::string ss("");
    for(auto& expr_attr : m_listOfExprAttribute)
    {
        ss += expr_attr->GetAttributeExprName();
        for (auto i : expr_attr->GetExpressionIndecies())
        {
            ss += "[" + std::to_string(i) + "]";
        }
        ss += (".");
    }

    return (ss.length() == 0) ? ss : (ss.substr(0, ss.length() - 1));
}

const std::vector<std::unique_ptr<ExpressionAttribute>>& Identifier::GetListOfExprAttribute()
{
    return m_listOfExprAttribute;
}
