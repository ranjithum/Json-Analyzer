
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest/doctest.h"

#include "include/generic_expression.h"

TEST_CASE("GenericExpressionTest - ToString") {
    Identifier *ident1 = new Identifier();
    ident1->AddExprAttribute(std::string("param"));
    ident1->AddIndiceToLastExprAttribute(5);
    Identifier *ident2 = new Identifier();
    ident2->AddExprAttribute(std::string("counter"));
    ident2->AddIndiceToLastExprAttribute(3);
    ident2->AddIndiceToLastExprAttribute(2);
    ident2->AddIndiceToLastExprAttribute(1);

    NonJsonExpression nonjson_exp;
    nonjson_exp.AddIdentifier(ident1);
    nonjson_exp.AddIdentifier(ident2);

    CHECK(nonjson_exp.ToString().c_str() == "param[5].counter[3][2][1]");
}

TEST_CASE("JsonExpressionTest - ToString") {
    Identifier *ident1 = new Identifier();
    ident1->AddExprAttribute(std::string("param"));
    ident1->AddIndiceToLastExprAttribute(5);
    Identifier *ident2 = new Identifier();
    ident2->AddExprAttribute(std::string("counter"));
    ident2->AddIndiceToLastExprAttribute(3);
    ident2->AddIndiceToLastExprAttribute(2);
    ident2->AddIndiceToLastExprAttribute(1);

    JsonExpression json_exp;
    json_exp.AddIdentifier(ident1);
    json_exp.AddIdentifier(ident2);

    CHECK(json_exp.ToString().c_str() == "json.param[5].counter[3][2][1]");

    JsonExpression json_exp_with_index(1);
    Identifier *ident3 = new Identifier();
    ident3->AddExprAttribute(std::string("param"));
    Identifier *ident4 = new Identifier();
    ident4->AddExprAttribute(std::string("newObect"));
    json_exp_with_index.AddIdentifier(ident3);
    json_exp_with_index.AddIdentifier(ident4);

    CHECK(json_exp_with_index.ToString().c_str() == "json[1].param.newObect");

}
