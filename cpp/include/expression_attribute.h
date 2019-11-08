#pragma once

#include <vector>
#include <memory>
#include <string>

// This is the leaf class, each string represents
// ExpressionAttribute..
// Eg :- In json.param -> "param" is one ExpressionAttribute
class ExpressionAttribute {
private:
    //! Name of the expression attribute
    std::string m_attributeName;

    //! vector to save map index
    std::vector<int> m_mapIndecies;

public:
    //! Ctor - Stores attribute/expression
    //! @param attr_name
    //!		expression atribute or name
    ExpressionAttribute(std::string attr_name);

    //! Ctor - Stores attribute/expression
    //! @param attr_name
    //!		expression atribute or name
    //! @param attr_index
    //! 	index value
    ExpressionAttribute(std::string attr_name, int attr_index);

    //! AddIndice - Method to add map index eg :- params[3][2]
    //! @param value
    //!		index of the map
    void AddIndice(int value);

    //! GetAttributeExprName - for getting attribute name
    //! @return attribute name
    std::string& GetAttributeExprName();

    //! Method for getting all indecies associated with that
    //! expression attribute
    //! return vector of indecies
    std::vector<int>& GetExpressionIndecies();
};

class Identifier {
private:
    //! vector to save all ExpressionAttribute
    std::vector<std::unique_ptr<ExpressionAttribute>> m_listOfExprAttribute;

public:
    //! Default ctor
    Identifier() = default;

    //! Ctor
    //! @param attr_name : Name of the expr attribute
    //! @param index : First index value
    Identifier(std::string attr_name, int index = -1);

    //! AddExprAttribute - Helper method to add ExpressionAttribute
    //! object
    //! @param attr_name
    //! 	expression atribute or name
    void AddExprAttribute(std::string attr_name, int index = -1);

    //! AddIndiceToLastExprAttribute - Method to add index
    //! for last expression attribute
    //! @param value
    //!		index of last expression
    bool AddIndiceToLastExprAttribute(int value);

    //! ToString - Method to print all expression attribute
    //! used only for debugging
    //! return Identifier expression in string format
    std::string ToString();

    //! GetListOfExprAttribute - Returns vector ExpressionAttribute
    //! @return vector of ExpressionAttribute
    const std::vector<std::unique_ptr<ExpressionAttribute>>& GetListOfExprAttribute();

    ~Identifier()
    {
        m_listOfExprAttribute.clear();
    }
};
