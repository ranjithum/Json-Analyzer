#pragma once

//! Simple template class which takes input as lambda function/simple function
//! which require auto clean-up on function/method return
template<class l>
class AtReturn {
    //! template variable type
    l& m_func;
public:
    //! Ctor
    AtReturn(l& ref) : m_func(ref) {}

    //! Dtor
    //! On destruction method is called
    ~AtReturn()
    {
        m_func();
    }
};

