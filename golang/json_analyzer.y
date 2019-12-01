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
	comparator	Comparator
	comparevalue *CompareValue
	ident *Identifier
	expression GenericExpression
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

%type <comparator> COMPARATOR 
%type <comparevalue> COMPARING_VALUE
%type <ident> STRING_IDENTIFIER
%type <expression> exp
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
	IF exp COMPARATOR COMPARING_VALUE START_BRACE code_block
	{
	fmt.Println("IF exp COMPARATOR COMPARING_VALUE START_BRACE code_block")
	}

for_block :
	FOR IDENTIFIER IN exp START_BRACE code_block
	{
	fmt.Println("FOR IDENTIFIER IN exp START_BRACE code_block")
	}

exp :
	JSON
	{
		fmt.Println("JSON")
		$$ = NewJsonExpression(-1)
	}
	| JSON '[' SIGNED_VALUE ']'
	{
		fmt.Println("JSON [ SIGNED_VALUE ]")
		$$ = NewJsonExpression($3)
	}
	| STRING_IDENTIFIER
	{
		fmt.Println("STRING_IDENTIFIER")
		$$ = NewNonJsonExpression()
		$$.AddIdentifier($1)
	}
	| exp STRING_IDENTIFIER
	{
		fmt.Println("exp STRING_IDENTIFIER")
		$1.AddIdentifier($2)
	}

STRING_IDENTIFIER :
	IDENTIFIER
	{
		fmt.Println("IDENTIFIER")
		$$ = &Identifier {
			m_expression: $1,
			}
	}
	| DOT IDENTIFIER
	{
		fmt.Println("DOT IDENTIFIER")
		$$ = &Identifier {
			m_expression: $2,
			}
	}
	| STRING_IDENTIFIER '[' SIGNED_VALUE ']'
	{
		fmt.Println("STRING_IDENTIFIER [ SIGNED_VALUE ]")
		if $1 == nil {
			$1 = &Identifier{}
		}
		$1.AddIndex(int($3))
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

COMPARATOR :
	DOUBLE_EQUAL
	{
		fmt.Println("Double Equals")
		$$ = &CompareEqualTo{}
	}
	|
	GREATER_THAN_EQUAL
	{
		fmt.Println("Greater than Equal")
		$$ = &CompareGreaterThanEqual{}
	}
	|
	GREATER_THAN
	{
		fmt.Println("Greater than")
		$$ = &CompareGreaterThan{}
	}
	|
	LESS_THAN_EQUAL
	{
		fmt.Println("Less than Equal")
		$$ = &CompareLessThanEqual{}
	}
	|
	LESS_THAN
	{
		fmt.Println("Less than")
		$$ = &CompareLessThan{}
	}

COMPARING_VALUE :
	QUOTED_STRING
	{
		fmt.Println("Quoted String")
		$$ = &CompareValue{
			m_dataType: STRING,
			m_rhsValue: $1,
			}
	}
	|
	SIGNED_VALUE
	{
		fmt.Println("Signed Value")
		$$ = &CompareValue{
			m_dataType: INT64,
			m_rhsValue: $1,
			}
	}
	|
	BOOL_VALUE
	{
	fmt.Println("Bool Value")
		$$ = &CompareValue{
			m_dataType: BOOL,
			m_rhsValue: $1,
			}
	}
	|
	DOUBLE_VALUE
	{
		fmt.Println("Double Value")
		$$ = &CompareValue{
			m_dataType: DOUBLE,
			m_rhsValue: $1,
			}
	}
%%
