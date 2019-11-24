#pragma once

#include "json_array_value_bridge.h"
#include "expression_value.h"

class GenericExpression;

//! Interface class which will be used internal by rules
class ExpressionEvaluationInterface {
public:
    //! Method for validating the expression, if validated get the value in string
    //! @param expr
    //!		Expression value containing Identifier
    //! @param value
    //!		If expression gets validated, store the value
    //! @return true if expression is valid
    virtual bool ValidateAndGetExprValue(const GenericExpression* expr, ExpressionValue& value) = 0;

    //! Method for validating the expression, if validated get the array object
    //! @param expr
    //! 	Expression value containing Identifier
    //! @param value
    //! 	ValueWapper which stores the array object
    //! @return true if expression is valid
    virtual bool ValidateAndGetValueIterator(const GenericExpression* expr, ValueWrapper* value) = 0;

    //! Method for validating the expression, if validated get the expression value from array object
    //! @param expr
    //!		Expression value containing Identifier
    //! @param valueWrap
    //!		ValueWapper which has the array object
    //! @param value
    //! 	If expression gets validated, save the value
    //! @return true if expression is valid
    virtual bool ValidateAndGetExprValue(const GenericExpression* expr, ValueWrapper* valueWrap, ExpressionValue& value) = 0;

    //! Method for validating the expression, if validated get the array object from parent array object
    //! @param expr
    //! 	Expression value containing Identifier
    //! @param p_valWrapper
    //! 	Parent array object
    //! @param value
    //!		store array object
    //! @return true if expression is valid
    virtual bool ValidateAndGetValueIterator(const GenericExpression* expr, ValueWrapper* p_valWrapper, ValueWrapper* value) = 0;

    //! Method for Getting an implementor representing Json Array type
    //! @return pointer to JsonArrayRep
    virtual JsonArrayRep* GetJsonArray() = 0;
};
