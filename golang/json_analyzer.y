%{
package main

import (
    "fmt"
)
%}

%union {
	stringValue string
	doubleValue double
	sint64Value int64
	boolValue	bool
}

%token IN IF FOR END
%token DOUBLE_EQUAL GREATER_THAN_EQUAL GREATER_THAN LESS_THAN_EQUAL LESS_THAN 
%token JSON
%token PP
%token DOT

%token <stringValue> IDENTIFIER
%token <stringValue> QUOTED_STRING
%token <doubleValue> DOUBLE_VALUE
%token <boolValue> BOOL_VALUE
%token <sint64Value> SIGNED_VALUE

%%
