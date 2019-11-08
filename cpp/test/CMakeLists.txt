
option (ValgrindTest "Execute test suite with Valgrind" OFF)

if(ValgrindTest)
    find_program(CMAKE_MEMORYCHECK_COMMAND valgrind)
    message("Executing test suite with Valgrind (${CMAKE_MEMORYCHECK_COMMAND})")
    set(memcheck_command "${CMAKE_MEMORYCHECK_COMMAND} ${CMAKE_MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full -v
	--tool=memcheck")
    separate_arguments(memcheck_command)
endif()

set(unitTest
	unittest/expression_attribute_test.cpp
	unittest/generic_condition_test.cpp
	unittest/generic_expression_test.cpp
	unittest/statement_test.cpp
	unittest/json_rule_engine_test.cpp
	)

foreach(ut ${unitTest})
	get_filename_component(file_name ${ut} NAME_WE)
	STRING(REGEX REPLACE "([^$]+)_test.cpp" "test-\\1" testcase ${file_name})
	add_executable(${testcase} ${ut})
	target_include_directories(${testcase} PRIVATE
		${CMAKE_SOURCE_DIR}/third_party/doctest
		${CMAKE_SOURCE_DIR}/third_party/rapidjson/include
		)
	target_link_libraries(${testcase} json_analyzer)

	add_test(NAME "${testcase}_default"
		COMMAND ${testcase}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test/unittest
		)
endforeach()
