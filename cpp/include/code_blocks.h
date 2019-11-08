#pragma once

#include <memory>
#include <vector>

#include "statement.h"
#include "at_return.h"

//! Class managing all the code-blocks
class CodeBlocks : public std::vector<std::unique_ptr<Statement>> {
public:
    //! Method for executing all the code blocks one by one
    //! If any of the statement passes, subsequent statement will
    //! not be executed
    //! @return
    //		true if any of statement executes to be true
    bool ExecuteCodeBlocks();

    //! Helper method for adding global code-blocks
    //! internally used by parser
    //! @param stmt
    //!		One complete code block
    void AddCodeBlock(Statement* stmt);

    //! Debug helper method for converting all the code-blocks
    //! into string
    //! @return code-blocks in string format
    std::string ToString();

    //! Helper method for getting number of code-blocks
    int GetNumberOfCodeBlocks()
    {
        return this->size();
    }

    //! Method to set all parent class once the parsing
    //! is complete
    void SetParentBlock();

    ~CodeBlocks()
    {
        clear();
    }
};
