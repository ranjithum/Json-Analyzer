
#include <sstream>
#include "include/statement.h"

void AbstractStatement::SetParent(Statement* prnt)
{
    for(auto &stmt : m_listOfStatements)
    {
        stmt->SetParent(this);
    }
    m_parent = prnt;
}

void AbstractStatement::CleanUp()
{
    m_Condition->CleanUp();
    for(auto &stmt : m_listOfStatements)
    {
        stmt->CleanUp();
    }
}

std::string AbstractStatement::ToString()
{
    std::stringstream ss;
    ss << m_Condition->ToString() << " {\n";

    for(auto &stmt : m_listOfStatements)
    {
        ss << stmt->ToString();
    }

    ss << "\n}\n";
    return ss.str();
}

void AbstractStatement::set_condition(Condition* cond)
{
    m_Condition = std::unique_ptr<Condition>(cond);
}

void AbstractStatement::add_statement(Statement* stmt)
{
    m_listOfStatements.push_back(
        std::unique_ptr<Statement>(stmt)
    );
}

int AbstractStatement::GetNumberOfStatements()
{
    return m_listOfStatements.size();
}

bool IfStatement::execute_statement()
{
    if (m_Condition->EvaluateCondition())
    {
        for(auto& st : m_listOfStatements)
        {
            if (st->execute_statement())
            {
                return true;
            }
        }
    }
    return false;
}

bool ForStatement::execute_statement()
{
    for (bool eval = m_Condition->EvaluateCondition(); eval; )
    {
        for(auto& st : m_listOfStatements)
        {
            if (st->execute_statement())
            {
                return true;
            }
        }
        eval = m_Condition->Increment();
    }
    return false;
}

Condition* ForStatement::get_condition(std::string& str)
{
    if (m_Condition->GetVariable().compare(str) == 0)
    {
        return m_Condition.get();
    }
    else
    {
        return m_parent->get_condition(str);
    }
}
