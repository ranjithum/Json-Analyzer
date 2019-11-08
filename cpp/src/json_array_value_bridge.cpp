
#include <iostream>
#include "include/json_array_value_bridge.h"

ValueWrapper::ValueWrapper(JsonArrayRep* rep):
    m_arrayValue(rep->Clone()),
    m_currentIndex(0)
{
}

bool ValueWrapper::Increment()
{
    if (m_currentIndex >= m_arrayValue.GetArraySize() - 1)
    {
        return false;
    }

    ++m_currentIndex;
    return true;
}
