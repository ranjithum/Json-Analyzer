%{
package main

import (
    "fmt"
)
%}

%union {
	stringValue string
	doubleValue float64 
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

statements :
	if_block
	{
	fmt.Println("if_block")
	}
	| for_block
	{
	fmt.Println("for_block")
	}
	| statements for_block
	{
	fmt.Println("statements for_block")
	}
	| statements if_block
	{
	fmt.Println("statements if_block")
	}
	| print_packet
	{
	fmt.Println(" print_packet ")
	}

print_packet :
	PP
	{
	fmt.Println("pp")
	}

if_block :
	IF exp comparator comparing_value START_BRACE code_block
	{
	fmt.Println("IF exp comparator comparing_value START_BRACE code_block")
	}

for_block :
	FOR IDENTIFIER IN exp START_BRACE code_block
	{
	fmt.Println("FOR IDENTIFIER IN exp START_BRACE code_block")
	}

exp :
	JSON
	{
	fmt.Println("JSON");
	}
	| JSON '[' SIGNED_VALUE ']'
	{
	fmt.Println("JSON [ SIGNED_VALUE ]")
	}
	| STRING_IDENTIFIER
	{
	fmt.Println("STRING_IDENTIFIER")
	}
	| exp STRING_IDENTIFIER
	{
	fmt.Println("exp STRING_IDENTIFIER")
	}

STRING_IDENTIFIER :
	IDENTIFIER
	{
	fmt.Println("IDENTIFIER")
	}
	| DOT IDENTIFIER
	{
	fmt.Println("DOT IDENTIFIER")
	}
	| STRING_IDENTIFIER '[' SIGNED_VALUE ']'
	{
	fmt.Println("STRING_IDENTIFIER [ SIGNED_VALUE ]")
	}

START_BRACE :
	'{'
	{
	fmt.Println("Start Brace")
	}

code_block :
	END statements END END_BLOCK END
	{
	fmt.Println("END statements END END_BLOCK END")
	}
	| END statements END_BLOCK END
	{
	fmt.Println("END statements END_BLOCK END")
	}

END_BLOCK :
	'}'
	{
	fmt.Println("End Brance")
	}

comparator :
	DOUBLE_EQUAL
	{
	fmt.Println("Double Equals")
	}
	|
	GREATER_THAN_EQUAL
	{
	fmt.Println("Greater than Equal")
	}
	|
	GREATER_THAN
	{
	fmt.Println("Greater than")
	}
	|
	LESS_THAN_EQUAL
	{
	fmt.Println("Less than Equal")
	}
	|
	LESS_THAN
	{
	fmt.Println("Less than")
	}

comparing_value :
	QUOTED_STRING
	{
	fmt.Println("Quoted String")
	}
	|
	SIGNED_VALUE
	{
	fmt.Println("Signed Value")
	}
	|
	BOOL_VALUE
	{
	fmt.Println("Bool Value")
	}
	|
	DOUBLE_VALUE
	{
	fmt.Println("Double Value")
	}
%%
