
SRC := $(wildcard *.cpp)
HEADER := $(shell find ../include -name "*.h")
OBJS := $(patsubst %.cpp, %.o, $(SRC))

CPPFLAGS = -std=c++14 -ggdb3 -fPIC -Wall -Wextra -O2 -Wno-unused-function -Wno-sign-compare -Wno-write-strings
CXX ?= g++
PARENT_PATH = ../
INCLUDE_PATH = -I$(PARENT_PATH) -I$(PARENT_PATH)/third_party/rapidjson/include
LDFLAGS = -shared

LIB = ./libjson_analyzer.so

BISON = bison
FLEX = flex
LEX_IN = json_analyzer.l
LEX_OUT = json_analyzer.yy.cc
LEX_OBJ = json_analyzer.yy.o
BISON_IN = json_analyzer.ypp
BISON_OUT = json_analyzer.tab.cpp
BISON_OBJ = json_analyzer.tab.o

%.o: %.cpp
	$(CXX) $(INCLUDE_PATH) $(CPPFLAGS) -c $<

$(LIB): $(LEX_OBJ) $(BISON_OBJ) $(OBJS)
	$(CXX) $(LDFLAGS) -o $(@) $^

$(OBJS) : $(HEADER)

$(LEX_OUT): $(LEX_IN)
	$(FLEX) -o $(@) -i json_analyzer.l

$(LEX_OBJ) : $(LEX_OUT) $(BISON_OUT)
	$(CXX) $(INCLUDE_PATH) $(CPPFLAGS) -c $<

$(BISON_OUT): $(BISON_IN)
	$(BISON) -dv json_analyzer.ypp -o $(@)

$(BISON_OBJ) : $(BISON_OUT)
	$(CXX) $(INCLUDE_PATH) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o $(LIB) *.tab.* json_analyzer.output $(LEX_OUT) $(BISON_OUT)

test: $(LIB)
	@make -C test/unittest test

format :
	for eachFile in $(SRC) $(HEADER); do \
		astyle --style=allman -xc $$eachFile; \
		[ -f $$eachFile.orig ] && rm $$eachFile.orig || : ; \
		done
