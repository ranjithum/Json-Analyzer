#pragma once

#include <rapidjson/document.h>
#include "expression_evaluation_interface.h"
#include "json_parser_interface.h"
#include "RapidJsonArray.h"

using namespace rapidjson;

class RapidJsonImpl : public JsonParserInterface,
    public ExpressionEvaluationInterface {
private:
    Document m_jsonDom;

    RapidJsonArrayRep m_rapidJsonArray;

    void GetFinalValue(const Value& rapid_json_ref, std::string& final_string);

    Value* GetNextValue(Value* ref, auto index)
    {
        return &(*ref)[index];
    }
    Value* ValidateAndGetRapidJsonValue(const GenericExpression* expr);
public:
    bool ValidateAndGetExprValue(const GenericExpression* expr, std::string& value) override;

    bool ValidateAndGetValueIterator(const GenericExpression* expr, ValueWrapper* value) override;

    bool ValidateAndGetExprValue(const GenericExpression* expr, ValueWrapper* valueWrapper, std::string& value) override;

    bool ValidateAndGetValueIterator(const GenericExpression* expr, ValueWrapper* p_valWrapper, ValueWrapper* value) override;

    ErrorCode ParseJsonStream(const char* json_stream) override;

    ErrorCode ParseJsonStream(FILE* json_file) override;

    ExpressionEvaluationInterface* GetJsonExprEvalImpl() override
    {
        return this;
    }

    JsonArrayRep* GetJsonArray() override
    {
        return &m_rapidJsonArray;
    }

    void CleanUp() override;

    ~RapidJsonImpl()
    {
        CleanUp();
    }
};
