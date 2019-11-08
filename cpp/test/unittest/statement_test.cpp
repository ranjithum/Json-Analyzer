
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest/doctest.h"

#include "include/statement.h"

TEST_CASE("StatementTest - add_statement")
{
	IfStatement parent_stmt;
	
	Identifier *parent_ident = new Identifier();
	parent_ident->AddExprAttribute(std::string("method"));
	GenericExpression* parent_json_exp = new JsonExpression(0);
	parent_json_exp->AddIdentifier(parent_ident);
	Condition *parent_cond = new IfCondition(parent_json_exp, "object.updated", 0);
	parent_stmt.set_condition(parent_cond);

	Statement* child_stmt1 = new IfStatement(); 

	Identifier *child_ident1 = new Identifier();
	child_ident1->AddExprAttribute(std::string("params"));
	child_ident1->AddExprAttribute(std::string("oldObject"));
	child_ident1->AddExprAttribute(std::string("oid"));
	GenericExpression *child_json_exp1 = new JsonExpression(0);
	child_json_exp1->AddIdentifier(child_ident1);
	Condition* child_cond1 = new IfCondition(child_json_exp1, "205793453", 0);
	child_stmt1->set_condition(child_cond1);
	Statement* child_stmt1_1 = new print_packet_statement();
	child_stmt1->add_statement(child_stmt1_1);

	Statement* child_stmt2 = new ForStatement();
	
	Identifier *child_ident2 = new Identifier();
	child_ident2->AddExprAttribute(std::string("params"));
	child_ident2->AddExprAttribute(std::string("oldObject"));
	child_ident2->AddExprAttribute(std::string("gxRules"));
	GenericExpression *child_json_exp2 = new JsonExpression(0);
	child_json_exp2->AddIdentifier(child_ident2);
	Condition* child_cond2 = new ForCondition("gxRule", child_json_exp2, 0);
	child_stmt2->set_condition(child_cond2);
	
	Statement* child_stmt2_1 = new IfStatement();

	Identifier *child_ident2_1 = new Identifier();
	child_ident2_1->AddExprAttribute(std::string("gxRule"));
	child_ident2_1->AddExprAttribute(std::string("ruleName"));
	GenericExpression *child_nonjson_exp2_1 = new NonJsonExpression();
	child_nonjson_exp2_1->AddIdentifier(child_ident2_1);
	Condition* child_cond2_1 = new IfCondition(child_nonjson_exp2_1, "DEF_SOS_GPRS_QOS_UNLIM", 0);
	child_stmt2_1->set_condition(child_cond2_1);
	Statement* child_stmt2_1_1 = new print_packet_statement();
	child_stmt2_1->add_statement(child_stmt2_1_1);

	child_stmt2->add_statement(child_stmt2_1);

	parent_stmt.add_statement(child_stmt1);
	parent_stmt.add_statement(child_stmt2);
	CHECK(parent_stmt.GetNumberOfStatements() == 2);

	CHECK("if json[0].method == object.updated {\nif json[0].params.oldObject.oid == 205793453 {\npp\n}\nfor gxRule in json[0].params.oldObject.gxRules {\nif gxRule.ruleName == DEF_SOS_GPRS_QOS_UNLIM {\npp\n}\n\n}\n\n}\n" == parent_stmt.ToString().c_str());
}
