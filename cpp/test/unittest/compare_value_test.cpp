
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest/doctest.h"

#include "include/compare_value.h"

TEST_CASE("CompareValue - GetValue") {
	SUBCASE("GetValue - BOOL") {
		CompareValueBase* cvPtr = new CompareValue<bool>(true, BASIC_DTYPE::BOOL);
		CHECK_EQ(cvPtr->GetValue(), "true");
		delete cvPtr;
	}
	SUBCASE("GetValue - string") {
		CompareValueBase *cvPtr = new CompareValue<std::string>(std::string("Gowda"), BASIC_DTYPE::STRING);
		CHECK_EQ(cvPtr->GetValue(), "Gowda");
		delete cvPtr;
	}

	SUBCASE("GetValue - SINT64") {
		CompareValueBase *cvPtr = new CompareValue<int64_t>(66666666, BASIC_DTYPE::SINT64);
		CHECK_EQ(cvPtr->GetValue(), "66666666");
		delete cvPtr;
	}

	SUBCASE("GetValue -DOUBLE") {
		CompareValueBase *cvPtr = new CompareValue<double>(123.45, BASIC_DTYPE::DOUBLE);
		CHECK_EQ(cvPtr->GetValue(), "123.450000");
		delete cvPtr;
	}
}

TEST_CASE("CompareValue - CompareIt") {
	SUBCASE("CompareValue - BOOL") {
		CompareValueBase* cvPtr = new CompareValue<bool>(true, BASIC_DTYPE::BOOL);
		cvPtr->SetComparator(CompareOperators::DoubleEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(true), true);

		cvPtr->SetComparator(CompareOperators::GreaterThanEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(true), true);

		cvPtr->SetComparator(CompareOperators::GreaterThanOperator);
		CHECK_EQ(cvPtr->CompareIt(false), false);

		cvPtr->SetComparator(CompareOperators::LessThanEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(true), true);

		cvPtr->SetComparator(CompareOperators::LessThanOperator);
		CHECK_EQ(cvPtr->CompareIt(false), true);

		delete cvPtr;
	}

	SUBCASE("CompareValue - int64") {
		CompareValueBase* cvPtr = new CompareValue<int64_t>(123456, BASIC_DTYPE::SINT64);
		cvPtr->SetComparator(CompareOperators::DoubleEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(int64_t(123456)), true);
		
		cvPtr->SetComparator(CompareOperators::GreaterThanEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(int64_t(1234567)), true);

		cvPtr->SetComparator(CompareOperators::GreaterThanOperator);
		CHECK_EQ(cvPtr->CompareIt(int64_t(222222)), true);

		cvPtr->SetComparator(CompareOperators::LessThanEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(int64_t(123456)), true);

		cvPtr->SetComparator(CompareOperators::LessThanOperator);
		CHECK_EQ(cvPtr->CompareIt(int64_t(12345)), true);
		
		delete cvPtr;
	}

	SUBCASE("CompareValue - double") {
		CompareValueBase* cvPtr = new CompareValue<double>(12345.678, BASIC_DTYPE::DOUBLE);
		cvPtr->SetComparator(CompareOperators::DoubleEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(12345.678), true);

		cvPtr->SetComparator(CompareOperators::GreaterThanEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(12346.0), true);

		cvPtr->SetComparator(CompareOperators::GreaterThanOperator);
		CHECK_EQ(cvPtr->CompareIt(222222.87), true);

		cvPtr->SetComparator(CompareOperators::LessThanEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(12344.456), true);

		cvPtr->SetComparator(CompareOperators::LessThanOperator);
		CHECK_EQ(cvPtr->CompareIt(123.1234), true);
		
		delete cvPtr;
	}

	SUBCASE("CompareValue - string") {
		CompareValueBase* cvPtr = new CompareValue<std::string>("Hello", BASIC_DTYPE::STRING);
		cvPtr->SetComparator(CompareOperators::DoubleEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(std::string("Hello")), true);
		
		cvPtr->SetComparator(CompareOperators::GreaterThanEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(std::string("Iello")), true);

		cvPtr->SetComparator(CompareOperators::GreaterThanOperator);
		CHECK_EQ(cvPtr->CompareIt(std::string("Hello")), false);

		cvPtr->SetComparator(CompareOperators::LessThanEqualsOperator);
		CHECK_EQ(cvPtr->CompareIt(std::string("HELLO")), true);

		cvPtr->SetComparator(CompareOperators::LessThanOperator);
		CHECK_EQ(cvPtr->CompareIt(std::string("ABBBB")), true);
		delete cvPtr;
	}
}
