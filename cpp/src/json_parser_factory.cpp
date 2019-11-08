
#include "include/json_parser_factory.h"
#include "include/RapidJsonImpl.h"

std::unique_ptr<JsonParserInterface> JsonParserFactory::CreateJsonParserImplementer(JsonParserImplementer type)
{
    switch(type)
    {
    case JsonParserImplementer::RAPIDJSON:
        return std::make_unique<RapidJsonImpl>();
    }
    return 0;
}
