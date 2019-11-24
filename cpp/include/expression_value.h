#pragma once

#include <map>

enum class BASIC_DTYPE
{
    BOOL = 0,
    SINT64,
    DOUBLE,
    STRING
};

static const std::map<BASIC_DTYPE, std::string> c_dataType_To_string =
{
    { BASIC_DTYPE::BOOL, "bool" },
    { BASIC_DTYPE::SINT64, "sint64" },
    { BASIC_DTYPE::DOUBLE, "double" },
    { BASIC_DTYPE::STRING, "string" }
};

struct ExpressionValue
{
    BASIC_DTYPE m_expressionType;

    bool boolValue = false;

    int64_t sint64Value = 0;

    double doubleValue = 0;

    std::string stringValue;
};

