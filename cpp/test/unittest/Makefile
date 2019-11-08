
TEST_FILES := $(wildcard *_test.cpp)
CPPFLAGS = -std=c++14 -ggdb3 -fPIC -Wall -Wextra -O2

CXX ?= g++
PARENT_PATH = ../..
INCLUDE_PATH = -I$(PARENT_PATH)/third_party/doctest -I$(PARENT_PATH) -I$(PARENT_PATH)/third_party/rapidjson/include
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

JSON_ANALYZER_LIB_PATH = $(PARENT_PATH)/src
LIB = $(PARENT_PATH)/src/libjson_analyzer.so

$(LIB):
	@make -C ../../src

test : $(LIB) 
	for test_file in $(TEST_FILES); do \
		$(CXX) $(INCLUDE_PATH) -o runner $$test_file -Wl,-rpath,$(JSON_ANALYZER_LIB_PATH) -L$(JSON_ANALYZER_LIB_PATH) -ljson_analyzer ; \
		./runner; rm -rf ./runner; \
		done

%_test.run : %_test.cpp $(LIB)
	$(CXX) $(INCLUDE_PATH) -o $(@) $< -Wl,-rpath,$(JSON_ANALYZER_LIB_PATH) -L$(JSON_ANALYZER_LIB_PATH) -ljson_analyzer
	./$(@)
	@rm -f $(@)

%_test.valgrind : %_test.cpp $(LIB)
	$(CXX) $(INCLUDE_PATH) -o $(@) $< -Wl,-rpath,$(JSON_ANALYZER_LIB_PATH) -L$(JSON_ANALYZER_LIB_PATH) -ljson_analyzer
	G_SLICE=always-malloc G_DEBUG=gc-friendly  valgrind -v --tool=memcheck --log-file=./$@.log --leak-check=full ./$(@)
	@rm -f $(@)
