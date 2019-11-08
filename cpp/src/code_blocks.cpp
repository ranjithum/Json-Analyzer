
#include <sstream>
#include "include/code_blocks.h"

bool CodeBlocks::ExecuteCodeBlocks()
{
    auto CleanUp = [ this ] ()
    {
        for(auto &stmt : *this)
        {
            stmt->CleanUp();
        }
    };

    AtReturn<decltype(CleanUp)> atExit(CleanUp);

    for(auto &stmt : *this)
    {
        if (stmt->execute_statement())
        {
            return true;
        }
    }
    return false;
}

void CodeBlocks::AddCodeBlock(Statement* stmt)
{
    this->push_back(
        std::unique_ptr<Statement>(stmt)
    );
}

std::string CodeBlocks::ToString()
{
    std::stringstream ss;
    for(auto &stmt : *this)
    {
        ss << stmt->ToString();
    }
    return ss.str();
}

void CodeBlocks::SetParentBlock()
{
    for(auto &stmt : *this)
    {
        stmt->SetParent(0);
    }
}
