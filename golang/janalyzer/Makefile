
JSON_GO_LEX_OUT = json_analyzer_lex.go
JSON_GO_REGEL_IN = json_analyzer.rl

JSON_GO_YACC_IN = json_analyzer.y
JSON_GO_YACC_OUT = json_analyzer_yacc.go

build: $(JSON_GO_LEX_OUT) $(JSON_GO_YACC_OUT)
	go build

test:
	go test

$(JSON_GO_YACC_OUT) : $(JSON_GO_YACC_IN)
	goyacc -o $(@) $^

$(JSON_GO_LEX_OUT) : $(JSON_GO_REGEL_IN)
	ragel -Z -G2 -o $(@) $(^)

clean:
	@rm -rf $(JSON_GO_LEX_OUT) $(JSON_GO_YACC_OUT) $(BIN) *.output
