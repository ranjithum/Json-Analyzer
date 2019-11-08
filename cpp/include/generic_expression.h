#pragma once

#include <memory>
#include <vector>
#include "expression_attribute.h"
#include "expression_evaluation_interface.h"
#include "json_array_value_bridge.h"

class Condition;
class GenericExpression {
protected:

    enum class Block : std::int8_t {IF = 1, FOR = 2};

    std::vector<std::unique_ptr<Identifier>> m_listOfIdentifier;
    ExpressionEvaluationInterface* m_expressionEvaluator = 0;
    std::int8_t m_blockType;
    Condition* m_parentCondition = 0;
public:

    virtual void AddIdentifier(Identifier* e_attr);

    virtual void SetParent(Condition* parent)
    {
        m_parentCondition = parent;
    }

    void SetBlockType(std::int8_t t)
    {
        m_blockType = t;
    }

    virtual std::string ToString();

    const std::vector<std::unique_ptr<Identifier>>& GetIdentifier() const;

    virtual bool EvaluateExpression(std::string& expr_val) = 0;

    virtual void SetExpressionEvaluator(ExpressionEvaluationInterface*) = 0;

    virtual ValueWrapper* GetValueIterator(std::string& str) = 0;
    virtual ValueWrapper* GetValueIterator() = 0;

    virtual bool IncrementValueIterator() = 0;

    virtual ~GenericExpression()
    {
        m_listOfIdentifier.clear();
    }

    virtual void CleanUp() = 0;
};

class JsonExpression : public GenericExpression {
private:
    int m_jsonIndex = -1;

    std::unique_ptr<ValueWrapper> m_valueArr;
public:
    JsonExpression () = default;

    JsonExpression(unsigned int j_index);

    std::string ToString() override;

    int GetIndex() const;

    bool EvaluateExpression(std::string& expr_val) override;

    void SetExpressionEvaluator(ExpressionEvaluationInterface* eval) override
    {
        m_expressionEvaluator = eval;
    }

    ValueWrapper* GetValueIterator([[gnu::unused]] std::string& dummy) override
    {
        return m_valueArr.get();
    }

    virtual ValueWrapper* GetValueIterator()
    {
        return m_valueArr.get();
    }

    virtual bool IncrementValueIterator()
    {
        return m_valueArr->Increment();
    }

    void CleanUp() override
    {
        m_valueArr.reset();
    }
};

class NonJsonExpression : public GenericExpression {
private:
    std::unique_ptr<ValueWrapper> m_valueArr;
public:
    bool EvaluateExpression(std::string& expr_val) override;

    void SetParent(Condition* parent) override
    {
        m_parentCondition = parent;
    }

    void SetExpressionEvaluator(ExpressionEvaluationInterface* eval) override
    {
        m_expressionEvaluator = eval;
    }


    ValueWrapper* GetValueIterator(std::string& str) override;
    ValueWrapper* GetValueIterator() override
    {
        return m_valueArr.get();
    }

    virtual bool IncrementValueIterator()
    {
        return m_valueArr->Increment();
    }

    void CleanUp() override
    {
        m_valueArr.reset();
    }
};
