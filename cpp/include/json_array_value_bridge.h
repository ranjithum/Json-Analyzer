#pragma once

#include "json_array_rep.h"

class ValueWrapper {
    JsonArrayRep& m_arrayValue;
    int m_currentIndex = -1;

public:
    ValueWrapper(JsonArrayRep* rep);

    bool Increment();

    JsonArrayRep* GetValueArr()
    {
        return &m_arrayValue;
    }

    int GetCurrentIndex()
    {
        return m_currentIndex;
    }

    ~ValueWrapper()
    {
        delete &m_arrayValue;
    }
};
