#pragma once

#include <memory>
#include <vector>
#include "generic_condition.h"

//! This interface class represents each block of code
class Statement {
public:
    //! Method for executing code block
    //! @return true if any of the statement matches the condition
    virtual bool execute_statement() = 0;

    //! Setter method for setting the Condition
    //! @param cond
    //		pointer to Condition
    virtual void set_condition(Condition* cond) = 0;

    //! Method for adding statement to the code block
    //! @param stmt
    //		pointer to statement
    virtual void add_statement(Statement* stmt) = 0;

    //! Method for getting total number of statement
    //! present in this code block
    //! @return
    //		Number of statements
    virtual int GetNumberOfStatements() = 0;

    //! Method for getting Condition representing this code-block
    //! @param str
    //!		Match this string with Condition variable
    //! @return pointer to matched condition
    virtual Condition* get_condition(std::string& str) = 0;

    //! Method for displaying all the statements in string format
    //! @return string
    virtual std::string ToString() = 0;

    //! Setter method for setting the parent statement
    virtual void SetParent(Statement* prnt) = 0;

    //! Method for cleaning up stuff after executing rules
    //! for each json stream
    virtual void CleanUp() = 0;

    //! Dtor
    virtual ~Statement() = default;
};

//! This class represents the match statement for the json stream
class print_packet_statement : public Statement {
public:
    //! @copydoc Statement::execute_statement
    bool execute_statement() override
    {
        return true;
    }

    //! @copydoc Statement::set_condition
    void set_condition([[gnu::unused]] Condition* cond) override
    {
        abort();
    }

    //! @copydoc Statement::add_statement
    void add_statement([[gnu::unused]] Statement* stmt) override
    {
        abort();
    }

    //! @copydoc Statement::GetNumberOfStatements
    int GetNumberOfStatements() override
    {
        return 1;
    }

    //! @copydoc Statement::get_condition
    Condition* get_condition([[gnu::unused]] std::string& str) override
    {
        abort();
        return 0;
    }

    //! @copydoc Statement::ToString
    std::string ToString() override
    {
        return "pp";
    }

    //! @copydoc Statement::SetParent
    void SetParent([[gnu::unused]] Statement* prnt) override
    {
        // There is no point setting parent to this
    }

    //! @copydoc Statement::CleanUp
    void CleanUp() override {}

    //! Dtor
    ~print_packet_statement() = default;
};

//! This class implements some of method common between if-statement
//! and for-statement
class AbstractStatement : public Statement {
protected:
    //! unique-ptr to the condition
    std::unique_ptr<Condition> m_Condition;

    //! vector of statements present in this code block
    std::vector<std::unique_ptr<Statement>> m_listOfStatements;

    //! pointer to the parent statement
    Statement* m_parent = 0;

public:

    //! @copydoc Statement::set_condition
    void set_condition(Condition* cond) override;

    //! @copydoc Statement::add_statement
    void add_statement(Statement* stmt) override;

    //! @copydoc Statement::GetNumberOfStatements
    int GetNumberOfStatements() override;

    //! @copydoc Statement::ToString
    std::string ToString() override;

    //! @copydoc Statement::SetParent
    void SetParent(Statement* prnt) override;

    //! @copydoc Statement::CleanUp
    void CleanUp() override;

    //! Dtor
    virtual ~AbstractStatement()
    {
        m_listOfStatements.clear();
    }
};

//! This class represent a if-block, where it executes the if-condition
//! If the condition matches then it would execute all the statement/code-blocks
//! inside it
class IfStatement : public AbstractStatement {
public:
    //! @copydoc Statement::execute_statement
    bool execute_statement() override;

    //! @copydoc Statement::get_condition
    Condition* get_condition([[gnu::unused]] std::string& str) override
    {
        return m_parent->get_condition(str);
    }
};

//! This class represents a for-block, if the expression is of array type
//! if would execute all the statements within this block
class ForStatement : public AbstractStatement {
public:
    //! @copydoc Statement::execute_statement
    bool execute_statement() override;

    //! @copydoc Statement::get_condition
    Condition* get_condition(std::string& str) override;
};
