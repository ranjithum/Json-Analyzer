#pragma once

#include <sstream>
#include "errors.h"

class ExpressionEvaluationInterface;

//! This is an interface class Which should be implemented by a
//! concrete class for parsing Json stream and getting values
class JsonParserInterface {
public:
    //! Method for parsing json stream
    //! @param json_stream
    //!		json stream in string format
    //! @return ErrorCode
    //!		Check error.h for details
    virtual ErrorCode ParseJsonStream(const char* json_stream) = 0;

    //! Method for parsing json stream
    //! @param json_file
    //!		json stream in a file
    //! @return ErrorCode
    //!		Check error.h for details
    virtual ErrorCode ParseJsonStream(FILE* json_file) = 0;

    //! Method for getting an object who implements ExpressionEvaluationInterface
    //! @return
    //		a pointer who impements ExpressionEvaluationInterface
    virtual ExpressionEvaluationInterface* GetJsonExprEvalImpl() = 0;

    virtual void CleanUp() {}

    virtual ~JsonParserInterface() = default;
};
