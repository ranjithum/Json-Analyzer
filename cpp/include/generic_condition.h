#pragma once

#include <string>
#include "generic_expression.h"

class Statement;

//! This class represents a condition within a statement
class Condition {
protected:
    //! pointer to parent statement
    Statement* m_parentStatement;
public:

    //! ctor
    //! @param prnt
    //!		parent statement
    Condition(Statement* prnt):
        m_parentStatement(prnt)
    {}

    //! Method for evaluating the condition
    //! @return true
    //!		if condition matches
    virtual bool EvaluateCondition() = 0;

    //! Helper method to display the condition
    //! in string format
    //! @return string
    virtual std::string ToString() = 0;

    //! In case of for statement, after each evaluation
    //! condition must be incremented
    //! @return if increment was succesful
    virtual bool Increment() = 0;

    //! Method for getting the expression associated with this condition
    //! mainly used by for statement
    //! @param non_json_str
    //		string representation of the expression
    virtual GenericExpression* GetExpression(std::string& non_json_str) = 0;

    virtual std::string& GetVariable()
    {
        static std::string dummy("");
        return dummy;
    }

    //! Method to cleanup, after each evalaluation
    virtual void CleanUp() = 0;

    //! Dtor
    virtual ~Condition() = default;
};

//! Class representing a IF condition
class IfCondition: public Condition {
private:
    //! Represents the expression
    std::unique_ptr<GenericExpression> m_lhsExpr;

    //! Reprents the value to be compared
    std::string m_quotedValue;

public:
    //! Ctor
    //! @param expr
    //!		generic lhs expression
    //!	@param quoted_string
    //!		comparing value
    //! @param parent
    //		pointer to parent statement
    IfCondition(GenericExpression* expr, std::string quoted_string, Statement* parent);

    //! @copydoc Condition::EvaluateCondition
    bool EvaluateCondition() override;

    //! @copydoc Condition::ToString
    std::string ToString() override;

    //! @copydoc Condition::Increment
    bool Increment() override
    {
        // If condition shouldn't have any return
        abort();
        return true;
    }

    //! @copydoc Condition::GetExpression
    GenericExpression* GetExpression(std::string& ss) override;

    //! @copydoc Condition::CleanUp
    void CleanUp() override;

    //! Dtor
    ~IfCondition()
    {
        // Not needed, but just being safer :)
        m_quotedValue.clear();
    }

};

//! Class representing a FOR condition
class ForCondition: public Condition {
private:
    //! lhs_variable denoting each iterator
    std::string lhs_variable;

    //! expression denoting a valid iterator
    std::unique_ptr<GenericExpression> m_rhsExpr;

public:
    //! Ctor
    //! @param var
    //! 	representing lhs variable
    //! @param expr
    //!		generic rhs expression
    //! @param parent
    //!		pointer to parent statement
    ForCondition(std::string var, GenericExpression* expr, Statement* parent);

    //! copydoc Condition::EvaluateCondition
    bool EvaluateCondition() override;

    //! @copydoc Condition::ToString
    std::string ToString() override;

    //! @copydoc Condition::Increment
    bool Increment() override;

    //! @copydoc Condition::GetExpression
    GenericExpression* GetExpression(std::string& non_json_str) override;

    //! @copydoc Condition::GetVariable
    std::string& GetVariable() override
    {
        return lhs_variable;
    }

    //! @copydoc Condition::CleanUp
    void CleanUp() override;

    //! Dtor
    ~ForCondition()
    {
        lhs_variable.clear();
    }
};
