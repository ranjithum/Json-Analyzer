#pragma once

#include <memory>
#include <vector>
#include "expression_attribute.h"
#include "expression_evaluation_interface.h"
#include "json_array_value_bridge.h"

class Condition;

//! Enum representing type of expression
enum class BlockType : std::int8_t
{
    IF = 1,
    FOR = 2
};

//! This class represents an expression
class GenericExpression {
protected:

    // ! List of identifiers
    std::vector<std::unique_ptr<Identifier>> m_listOfIdentifier;

    //! Expression Evaluator for evaluating JSON expression
    ExpressionEvaluationInterface* m_expressionEvaluator = 0;

    //! Type expression
    BlockType m_blockType;

    //! Parent Condition
    Condition* m_parentCondition = 0;

    //! Pointer to ValueWrapper
    std::unique_ptr<ValueWrapper> m_valueArr;

    //! Method for getting Value Wrapper if identifier matches
    virtual ValueWrapper* GetValueIterator(std::string& str) = 0;
public:

    //! Method for adding Identifier
    //! @param e_attr
    //!		pointer to identifier
    void AddIdentifier(Identifier* e_attr);

    //! Method to set parent Condition
    void SetParent(Condition* parent)
    {
        m_parentCondition = parent;
    }

    //! Method to set block type
    void SetBlockType(std::int8_t t)
    {
        m_blockType = (BlockType)t;
    }

    //! Method to get expression in string format
    virtual std::string ToString();

    //! Method to get the list of identifiers
    const std::vector<std::unique_ptr<Identifier>>& GetIdentifier() const;

    //! Method for setting expression Evaluator
    void SetExpressionEvaluator(ExpressionEvaluationInterface* eval)
    {
        m_expressionEvaluator = eval;
    }

    //! Method of incrementing Value Iterator
    bool IncrementValueIterator()
    {
        return m_valueArr->Increment();
    }

    //! Method to cleanup after evaluating each expression
    virtual void CleanUp()
    {
        m_valueArr.reset();
    }

    //! Method fot getting Value Wrapper
    ValueWrapper* GetValueIterator()
    {
        return m_valueArr.get();
    }

    //! Method for Evaluating the expression
    virtual bool EvaluateExpression(std::string& expr_val) = 0;

    virtual ~GenericExpression()
    {
        m_listOfIdentifier.clear();
    }

};

//! Class representing Json expression
class JsonExpression : public GenericExpression {
private:
    //! Json index
    int m_jsonIndex = -1;

protected:
    //! @copydoc GenericExpression::GetValueIterator
    ValueWrapper* GetValueIterator([[gnu::unused]] std::string& dummy) override
    {
        return GenericExpression::GetValueIterator();
    }
public:
    //! Default Ctor
    JsonExpression () = default;

    //! Ctor with index
    JsonExpression(unsigned int j_index);

    //! copydoc GenericExpression::ToString
    std::string ToString() override;

    //! Method to get json index value
    int GetIndex() const;

    //! @copydoc GenericExpression::EvaluateExpression
    bool EvaluateExpression(std::string& expr_val) override;
};

//! Class representing non-json expression
class NonJsonExpression : public GenericExpression {
protected:
    //! @copydoc GenericExpression::GetValueIterator
    ValueWrapper* GetValueIterator(std::string& str) override;
public:
    //! @copydoc GenericExpression::EvaluateExpression
    bool EvaluateExpression(std::string& expr_val) override;

};
