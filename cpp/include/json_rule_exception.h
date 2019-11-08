#pragma once

#include <exception>

//! Class representing an exception which can occur during
//! initialization
class JsonRuleException : public std::exception {
public:
    //! Ctor
    //! @param messageString
    //!		possible messages
    JsonRuleException(std::string messageString)
    {
        m_what += messageString;
    }

    //! @copydoc std::exception::what
    const char* what() const throw() override
    {
        return m_what.c_str();
    }
private:

    //! Initial message
    std::string m_what{"An error occurred while "};
};
