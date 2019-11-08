#pragma once

#include "json_array_rep.h"
#include "rapidjson/document.h"

class RapidJsonArrayRep : public JsonArrayRep, public rapidjson::Value {
public:

    JsonArrayRep& Clone() override
    {
        return *(new RapidJsonArrayRep);
    }

    int GetArraySize() override
    {
        return ((rapidjson::Value*)this)->Size();
    }
};
