
%{
#include <stdlib.h>
#include <string>
#include "include/json_rule_engine.h" 
#include "json_analyzer.tab.hpp"
void yyerror(JsonRuleEngine *, char *);
%}

%%

^#.*\n+ 		; /* Skip anyline starting with # */

"json"	return JSON;

"if"	return IF;

"for"	return FOR;

"."		return DOT;

"\n"+	return END;

"in"	return IN;

"{"		return ('{');

"}"		return ('}');

"["		return ('[');

"]"		return (']');

"=="	return DOUBLE_EQUAL;

">="	return GREATER_THAN_EQUAL;

">"		return GREATER_THAN;

"<="	return LESS_THAN_EQUAL;

"<"		return LESS_THAN;

"pp"	return PP;

\"(.*?)\" {
	yylval.string = strdup(yytext);
	return QUOTED_STRING;
}

[-+]?[0-9]+\.[0-9]+ {
	yylval.doubleValue = std::stod(yytext);
	return DOUBLE_VALUE;
}

[-+]?[0-9]+ {
	yylval.sint64 = std::stol(yytext);
	return SIGNED_VALUE;
}

"true" {
	yylval.boolValue = true;
	return BOOL_VALUE;
}

"false" {
	yylval.boolValue = false;
	return BOOL_VALUE;
}

[a-zA-Z_]([a-zA-Z_\-0-9])* {
	yylval.string = strdup(yytext);
	return IDENTIFIER;
}

[ \t] ; /* skip whitespace */

. yyerror(NULL, "invalid character");
%%

int yywrap(void) {
	return 1;
}
