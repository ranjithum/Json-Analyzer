#pragma once

//! This enum class defines all the possible error code
enum class ErrorCode
{
    OK = 0,					// Condition evalation passes
    JSON_STREAM_ERROR = 1,	// Something wrong with the Json stream
    RULE_MATCH_FAILURE = 2	// Json stream doesn't match any of the rules
};
