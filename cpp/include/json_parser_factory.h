#pragma once

#include <memory>
#include "json_parser_interface.h"

//! Different implementer
enum JsonParserImplementer
{
    RAPIDJSON
};

//! Factory class for creating objects of Json parser implementor
class JsonParserFactory {
public:

    //! static method for creating object(s) who implements JsonParserInterface base on type
    static std::unique_ptr<JsonParserInterface> CreateJsonParserImplementer(JsonParserImplementer type);
};
