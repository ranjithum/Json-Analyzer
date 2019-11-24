#include <iostream>
#include "rapidjson/filereadstream.h"
#include "rapidjson/prettywriter.h"
#include "include/RapidJsonImpl.h"
#include "include/generic_expression.h"

static void jPrint(const rapidjson::Value& json)
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    json.Accept(writer);
    auto str = sb.GetString();
    printf("%s\n", str);
}

Value* RapidJsonImpl::ValidateAndGetRapidJsonValue(const GenericExpression* expr)
{
    Value* refExpr = NULL;
    const JsonExpression* json_expr = static_cast<const JsonExpression*>(expr);
    int json_index = json_expr->GetIndex();
    if (json_index >= 0)
    {
        if (! m_jsonDom.IsArray())
        {
            return 0;
        }

        if ( m_jsonDom.Size() < json_index)
        {
            return 0;
        }

        refExpr = &m_jsonDom[json_index];
    }
    else
    {
        refExpr = &m_jsonDom;
    }

    for (auto& ident : json_expr->GetIdentifier())
    {
        for (auto& exprAttr : ident->GetListOfExprAttribute())
        {
            if (!refExpr->HasMember(exprAttr->GetAttributeExprName().c_str()))
            {
                return 0;
            }
            refExpr = GetNextValue(refExpr, exprAttr->GetAttributeExprName().c_str());

            if (exprAttr->GetExpressionIndecies().size() > 0)
            {
                for (auto index : exprAttr->GetExpressionIndecies())
                {
                    if (!refExpr->IsArray())
                        return 0;

                    if (refExpr->Size() < index)
                        return 0;

                    refExpr = GetNextValue(refExpr, index);
                }
            }
        }
    }

    return &(*refExpr);
}

bool RapidJsonImpl::ValidateAndGetExprValue(const GenericExpression* expr, ExpressionValue& value)
{
    Value* vPtr = ValidateAndGetRapidJsonValue(expr);
    if (vPtr)
    {
        GetFinalValue(*vPtr, value);
        return true;
    }
    return false;
}

bool RapidJsonImpl::ValidateAndGetValueIterator(const GenericExpression* expr, ValueWrapper* value)
{
    Value *vPtr = ValidateAndGetRapidJsonValue(expr);

    if (!vPtr)
    {
        return false;
    }
    if (!vPtr->IsArray())
    {
        return false;
    }

    Value& tmp = *(RapidJsonArrayRep*)(value->GetValueArr());
    tmp = *vPtr;
    return true;
}

bool RapidJsonImpl::ValidateAndGetExprValue(const GenericExpression* expr, ValueWrapper* valueWrapper, ExpressionValue& value)
{
    Value* refExpr = (RapidJsonArrayRep*)(valueWrapper->GetValueArr());
    //jPrint(*refExpr);

    if (expr->GetIdentifier().front()->GetListOfExprAttribute().front()->GetExpressionIndecies().size() > 0)
    {
        for (auto index : expr->GetIdentifier().front()->GetListOfExprAttribute().front()->GetExpressionIndecies())
        {
            if (refExpr->IsObject() || refExpr->IsArray())
            {
                if (refExpr->Size() < valueWrapper->GetCurrentIndex())
                    return false;

                Value* tmpPtr = &(*refExpr)[valueWrapper->GetCurrentIndex()];
                refExpr = &(*tmpPtr)[index];
            }
        }
    }

    for (auto ident = std::next(expr->GetIdentifier().begin()); ident != expr->GetIdentifier().end(); ++ident)
    {
        for (auto& exprAttr : ident->get()->GetListOfExprAttribute())
        {
            if (refExpr->IsObject() && refExpr->HasMember(exprAttr->GetAttributeExprName().c_str()))
            {
                refExpr = GetNextValue(refExpr, exprAttr->GetAttributeExprName().c_str());
            }
            else if (refExpr->IsArray())
            {
                if (exprAttr->GetExpressionIndecies().size() > 0)
                {
                    for (auto index : exprAttr->GetExpressionIndecies())
                    {
                        if (refExpr->Size() < index)
                            return false;

                        refExpr = GetNextValue(refExpr, index);
                    }
                }
                else
                {
                    if (refExpr->Size() < valueWrapper->GetCurrentIndex())
                        return false;

                    Value* tmpPtr = &(*refExpr)[valueWrapper->GetCurrentIndex()];
                    refExpr = &(*tmpPtr)[exprAttr->GetAttributeExprName().c_str()];
                    break;
                }
            }
            else
                break;
        }
    }

    GetFinalValue(*refExpr, value);
    return true;
}

bool RapidJsonImpl::ValidateAndGetValueIterator(const GenericExpression* non_json_expr, ValueWrapper* valueWrapper, ValueWrapper* value)
{
    Value* refExpr = (RapidJsonArrayRep*)(valueWrapper->GetValueArr());

    if (non_json_expr->GetIdentifier().front()->GetListOfExprAttribute().front()->GetExpressionIndecies().size() > 0)
    {
        for (auto index : non_json_expr->GetIdentifier().front()->GetListOfExprAttribute().front()->GetExpressionIndecies())
        {
            if (refExpr->IsObject() || refExpr->IsArray())
            {
                if (refExpr->Size() < valueWrapper->GetCurrentIndex())
                    return false;

                Value* tmpPtr = &(*refExpr)[valueWrapper->GetCurrentIndex()];
                refExpr = &(*tmpPtr)[index];
            }
        }
    }

    for (auto ident = std::next(non_json_expr->GetIdentifier().begin()); ident != non_json_expr->GetIdentifier().end(); ++ident)
    {
        for (auto& exprAttr : ident->get()->GetListOfExprAttribute())
        {
            if (refExpr->IsObject() && refExpr->HasMember(exprAttr->GetAttributeExprName().c_str()))
            {
                refExpr = GetNextValue(refExpr, exprAttr->GetAttributeExprName().c_str());
            }
            else if (refExpr->IsArray())
            {
                if (exprAttr->GetExpressionIndecies().size() > 0)
                {
                    for (auto index : exprAttr->GetExpressionIndecies())
                    {
                        if (refExpr->Size() < index)
                            return false;

                        refExpr = GetNextValue(refExpr, index);
                    }
                }
                else
                {
                    if (refExpr->Size() < valueWrapper->GetCurrentIndex())
                        return false;

                    Value* tmpPtr = &(*refExpr)[valueWrapper->GetCurrentIndex()];
                    refExpr = &(*tmpPtr)[exprAttr->GetAttributeExprName().c_str()];
                    break;
                }
            }
            else
                break;
        }
    }


    Value& temp = *(RapidJsonArrayRep*)(value->GetValueArr());
    temp = *refExpr;
    return true;
}

void RapidJsonImpl::GetFinalValue(const Value& rapid_json_ref, ExpressionValue& final_value)
{
    if (rapid_json_ref.IsObject())
    {
        std::cout << "There is something wrong with the rules.. Your are expecting a leaf value, but this is still an object\n";
        return;
    }

    if (rapid_json_ref.IsArray())
    {
        std::cout << "There is something wrong with the rules.. Your are expecting a leaf value, but this is still an array\n";
        return;
    }

    if(rapid_json_ref.IsInt())
    {
        final_value.m_expressionType = BASIC_DTYPE::SINT64;
        final_value.sint64Value = rapid_json_ref.GetInt();
    }
    else if(rapid_json_ref.IsUint())
    {
        final_value.m_expressionType = BASIC_DTYPE::SINT64;
        final_value.sint64Value = rapid_json_ref.GetUint();
    }
    else if(rapid_json_ref.IsUint64())
    {
        final_value.m_expressionType = BASIC_DTYPE::SINT64;
        final_value.sint64Value = rapid_json_ref.GetUint64();
    }
    else if(rapid_json_ref.IsInt64())
    {
        final_value.m_expressionType = BASIC_DTYPE::SINT64;
        final_value.sint64Value = rapid_json_ref.GetInt64();
    }
    else if (rapid_json_ref.IsDouble())
    {
        final_value.m_expressionType = BASIC_DTYPE::DOUBLE;
        final_value.doubleValue = rapid_json_ref.GetDouble();
    }
    else if (rapid_json_ref.IsBool())
    {
        final_value.m_expressionType = BASIC_DTYPE::BOOL;
        final_value.boolValue = rapid_json_ref.GetBool();
    }
    else if (rapid_json_ref.IsString())
    {
        final_value.m_expressionType = BASIC_DTYPE::STRING;
        final_value.stringValue = rapid_json_ref.GetString();
    }
}

ErrorCode RapidJsonImpl::ParseJsonStream(FILE* json_file)
{
    char readBuffer[65536] = {};
    FileReadStream is(json_file, readBuffer, sizeof(readBuffer));
    return m_jsonDom.ParseStream(is).HasParseError() ? ErrorCode::JSON_STREAM_ERROR : ErrorCode::OK;
}

ErrorCode RapidJsonImpl::ParseJsonStream(const char* json_buf)
{
    return m_jsonDom.ParseInsitu((char*)json_buf).HasParseError() ? ErrorCode::JSON_STREAM_ERROR : ErrorCode::OK;
}

void RapidJsonImpl::CleanUp()
{
    m_jsonDom.SetObject();
    m_jsonDom.RemoveAllMembers();
}
