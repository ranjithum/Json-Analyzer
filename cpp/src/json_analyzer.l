
%{
#include <stdlib.h>
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

"pp"	return PP;

\"(.*?)\" {
	yylval.string = strdup(yytext);
	return QUOTED_STRING;
}

[a-zA-Z_]([a-zA-Z_\-0-9])* {
	yylval.string = strdup(yytext);
	return IDENTIFIER;
}

[0-9]+ {
	yylval.int64 = strtol(yytext, NULL, 10);
	return INTEGER;
}

[ \t] ; /* skip whitespace */

. yyerror(NULL, "invalid character");
%%

int yywrap(void) {
	return 1;
}
