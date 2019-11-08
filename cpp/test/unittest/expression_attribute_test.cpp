
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest/doctest.h"

#include "include/expression_attribute.h"

TEST_CASE("ExpressionAttributeTest") {
	SUBCASE("GetAttributeExprName") {
		std::string p("params");
		ExpressionAttribute e_attr(p);
		CHECK(e_attr.GetAttributeExprName().c_str() == p.c_str());
	}

	SUBCASE("AddIndice") {
		std::string p("params");
		ExpressionAttribute e_attr(p);
		e_attr.AddIndice(1);
		e_attr.AddIndice(2);
		CHECK(e_attr.GetExpressionIndecies().size() == 2);
	}
}

TEST_CASE("IdentifierTest") {
	SUBCASE("ToString") {
		std::string c("counter");
		std::string p("param");
		Identifier ident;
		ident.AddExprAttribute(c);
		ident.AddExprAttribute(p);
		ident.AddIndiceToLastExprAttribute(1);
		ident.AddIndiceToLastExprAttribute(2);
		CHECK(ident.ToString().c_str() == "counter.param[1][2]");
	}
}
