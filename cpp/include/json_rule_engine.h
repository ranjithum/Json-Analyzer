#pragma once

#include "json_parser_interface.h"
#include "errors.h"
#include "code_blocks.h"

class JsonRuleEngine {
private:
    const char* m_filterConditionFile;

    CodeBlocks m_CodeBlocks;

    std::unique_ptr<JsonParserInterface> m_jsonParserImpl;

    void InitRules();

    JsonRuleEngine() = delete;

    JsonRuleEngine(const JsonRuleEngine& ) = delete;

    JsonRuleEngine& operator=(const JsonRuleEngine&) = delete;
public:
    JsonRuleEngine(const char* filter_file);

    CodeBlocks& GetCodeBlock()
    {
        return m_CodeBlocks;
    }

    JsonParserInterface* GetJsonParserImplementer()
    {
        return m_jsonParserImpl.get();
    }

    ErrorCode ParseJsonStream(const char* json_stream);

    ErrorCode ParseJsonStream(FILE* json_file);

    ~JsonRuleEngine()
    {
        m_CodeBlocks.clear();
    }
};
