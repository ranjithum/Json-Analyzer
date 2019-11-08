
#include <cassert>
#include <cstring>
#include "json_analyzer.tab.hpp"
#include "include/json_rule_engine.h"
#include "include/json_parser_factory.h"
#include "include/json_rule_exception.h"
#include "include/at_return.h"

extern FILE *yyin;

JsonRuleEngine::JsonRuleEngine(const char* filter_file):
    m_filterConditionFile(filter_file)
{
    m_jsonParserImpl = std::move(JsonParserFactory::CreateJsonParserImplementer(JsonParserImplementer::RAPIDJSON));
    try
    {
        InitRules();
    }
    catch(JsonRuleException& j_e)
    {
        // Resetting this would make sure no other methods from this class gets called
        m_jsonParserImpl.reset();
        throw j_e;
    }
}

void JsonRuleEngine::InitRules()
{
    yyin = fopen(m_filterConditionFile, "r");
    if (yyin == NULL)
    {
        std::string exception("opening ");
        exception += m_filterConditionFile;
        throw JsonRuleException(exception);
    }

    // Enable yydebug flag for debugging
    //yydebug = 1;

    if (yyparse(this))
    {
        m_CodeBlocks.clear();
        std::string exception("parsing ");
        exception += m_filterConditionFile;
        throw JsonRuleException(exception);
    }

    m_CodeBlocks.SetParentBlock();
}

ErrorCode JsonRuleEngine::ParseJsonStream(FILE* json_file)
{
    assert(m_jsonParserImpl.get() || json_file);
    ErrorCode value = m_jsonParserImpl->ParseJsonStream(json_file);
    if (value == ErrorCode::OK)
    {
        return m_CodeBlocks.ExecuteCodeBlocks() ? ErrorCode::OK : ErrorCode::RULE_MATCH_FAILURE;
    }
    return value;
}

ErrorCode JsonRuleEngine::ParseJsonStream(const char* json_dump)
{
    assert(m_jsonParserImpl.get());

    auto CleanUp = [ this ] ()
    {
        this->m_jsonParserImpl->CleanUp();
    };
    AtReturn<decltype(CleanUp)> atExit(CleanUp);

    size_t l_json_stream = strlen(json_dump) + 1;
    char copy_json_buf[l_json_stream] = {'\0'};
    memcpy(copy_json_buf, json_dump, l_json_stream);

    ErrorCode value = m_jsonParserImpl->ParseJsonStream((const char*)copy_json_buf);
    if (value == ErrorCode::OK)
    {
        return m_CodeBlocks.ExecuteCodeBlocks() ?  ErrorCode::OK : ErrorCode::RULE_MATCH_FAILURE;
    }
    return value;
}
