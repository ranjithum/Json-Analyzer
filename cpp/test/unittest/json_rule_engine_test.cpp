
#include <fstream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest/doctest.h"

#include "include/json_rule_engine.h"
#include "include/json_rule_exception.h"

std::string filter_rule_path("../../../sample-filter-rules/");
std::string json_file_path("../../../sample-json-files/");

TEST_CASE("JsonRuleEngineTest - FileOpenException")
{
	try {
		JsonRuleEngine("abc.txt");
	}catch(JsonRuleException& e) {
		CHECK(e.what() == "An error occurred while opening abc.txt");
	}
}

TEST_CASE("JsonRuleEngineTest - ParseSimpleJsonStream")
{
    JsonRuleEngine jR(std::string(filter_rule_path + "filter_test_1.rule").c_str());

    CHECK(jR.GetCodeBlock().GetNumberOfCodeBlocks() == 1);
    FILE* fp = fopen(std::string(json_file_path + "diam_test_1.json").c_str(), "r");
    CHECK(jR.ParseJsonStream(fp) == ErrorCode::OK);
	fclose(fp);

    JsonRuleEngine jR2(std::string(filter_rule_path + "filter_test_2.rule").c_str());

    CHECK(jR2.GetCodeBlock().GetNumberOfCodeBlocks() == 1);
    FILE* fp2 = fopen(std::string(json_file_path + "diam_test_2.json").c_str(), "r");
    CHECK(jR2.ParseJsonStream(fp2) == ErrorCode::OK);
	fclose(fp2);
}

TEST_CASE("JsonRuleEngineTest - ParseComplexJsonStream")
{
    JsonRuleEngine jR(std::string(filter_rule_path + "filter_test_3.rule").c_str());

    CHECK(jR.GetCodeBlock().GetNumberOfCodeBlocks() == 1);
    FILE* fp = fopen(std::string(json_file_path + "diam_test_1.json").c_str(), "r");
    CHECK(jR.ParseJsonStream(fp) == ErrorCode::OK);
	fclose(fp);

    JsonRuleEngine jR1(std::string(filter_rule_path + "filter_test_4.rule").c_str());

    CHECK(jR1.GetCodeBlock().GetNumberOfCodeBlocks() == 1);
    FILE* fp1 = fopen(std::string(json_file_path + "diam_test_2.json").c_str(), "r");
    CHECK(jR1.ParseJsonStream(fp1) == ErrorCode::OK);
	fclose(fp1);
}

TEST_CASE("JsonRuleEngineTest - ParseRecursiveForLoop")
{
	JsonRuleEngine jR(std::string(filter_rule_path + "medication_filter.rule").c_str());

	CHECK(jR.GetCodeBlock().GetNumberOfCodeBlocks() == 1);
	FILE* fp = fopen(std::string(json_file_path + "medication.json").c_str(), "r");
    CHECK(jR.ParseJsonStream(fp) == ErrorCode::RULE_MATCH_FAILURE);
	fclose(fp);
}

TEST_CASE("JsonRuleEngineTest - FinalTest")
{
    JsonRuleEngine jR(std::string(filter_rule_path + "multiple_filters.rule").c_str());

    std::ifstream in(std::string(json_file_path + "multiple_json_objects.json"));
    std::string str;
    int count =0;

    while (std::getline(in, str)) {
        ErrorCode retVal = jR.ParseJsonStream(str.c_str());
        if (retVal == ErrorCode::OK)
        {
        	count++;
        }
    }
    in.close();
	CHECK(count == 5);
}

TEST_CASE("JsonRuleEngineTest - ParseIfForIfForCondition")
{
	JsonRuleEngine jR(std::string(filter_rule_path + "backery_filter.rule").c_str());
	FILE* fp = fopen(std::string(json_file_path + "backery.json").c_str(), "r");

	CHECK(jR.ParseJsonStream(fp) == ErrorCode::OK);
	fclose(fp);
}

TEST_CASE("JsonRuleEngineTest - FilterRuleException")
{
	std::string wrong_file(std::string(filter_rule_path + "wrong_filter.rule").c_str());
	try {
		JsonRuleEngine(wrong_file.c_str());
	} catch(JsonRuleException& e) {
		CHECK(e.what() == "An error occurred while parsing ../../../sample-filter-rules/wrong_filter.rule");
	}
}


