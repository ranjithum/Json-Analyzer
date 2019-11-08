
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest/doctest.h"

#include "include/generic_condition.h"

TEST_CASE("IfConditionTest - ToString") {
    GenericExpression* json_exp_with_index = new JsonExpression(0);
    Identifier *ident1 = new Identifier();
    Identifier *ident2 = new Identifier();
    Identifier *ident3 = new Identifier();
    ident1->AddExprAttribute(std::string("param"));
    ident1->AddExprAttribute(std::string("oldObject"));
    ident1->AddExprAttribute(std::string("oid"));

    json_exp_with_index->AddIdentifier(ident1);
    json_exp_with_index->AddIdentifier(ident2);
    json_exp_with_index->AddIdentifier(ident3);

    IfCondition if_conf(json_exp_with_index, "205793453", 0);
    CHECK(if_conf.ToString().c_str() == "if json[0].param.oldObject.oid.. == 205793453");
}

TEST_CASE("ForConditionTest - ToString") {
    Identifier *ident1 = new Identifier();
    ident1->AddExprAttribute(std::string("param"));
    ident1->AddIndiceToLastExprAttribute(5);
    Identifier *ident2 = new Identifier();
    ident2->AddExprAttribute(std::string("counter"));
    ident2->AddIndiceToLastExprAttribute(3);

    GenericExpression* nonjson_exp = new NonJsonExpression();
    nonjson_exp->AddIdentifier(ident1);
    nonjson_exp->AddIdentifier(ident2);

    ForCondition for_cond("variable", nonjson_exp, 0);
    CHECK(for_cond.ToString().c_str() == "for variable in param[5].counter[3]");
}
