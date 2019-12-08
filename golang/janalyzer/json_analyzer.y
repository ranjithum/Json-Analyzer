%{
package janalyzer 

//import (
//    "fmt"
//)

var g_trackCodeBlock []bool

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
	generic_block GenericBlock
	l_codeBlocks *listOfCodeBlocks
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
%type <generic_block> if_block for_block print_packet
%type <l_codeBlocks> code_block statements

%start statements
%%

statements :
	if_block
	{
		//fmt.Println("if_block statements", len(g_trackCodeBlock))
		if len(g_trackCodeBlock) > 0 {
			//fmt.Println("len(g_trackCodeBlock) > 0")
			$$ = NewListOfCodeBlock()
			$$.AppendCodeBlock($1)
		} else {
			//fmt.Println("Adding to the global code block if_block")
			global_listOfCodeBlocks.AppendCodeBlock($1)	
		}
	}
	| for_block
	{
		//fmt.Println("for_block")
		if len(g_trackCodeBlock) > 0 {
			$$ = NewListOfCodeBlock()
			$$.AppendCodeBlock($1)
		} else {
			//fmt.Println("Adding to the global code block for_block")
			global_listOfCodeBlocks.AppendCodeBlock($1)	
		}
	}
	| statements for_block
	{
		//fmt.Println("statements for_block")
		if len(g_trackCodeBlock) > 0 {
			$1.AppendCodeBlock($2)
		} else {
			
			global_listOfCodeBlocks.AppendCodeBlock($2)
		}
	}
	| statements if_block
	{
		//fmt.Println("statements if_block")
		if len(g_trackCodeBlock) > 0 {
			$1.AppendCodeBlock($2)
		} else {
			global_listOfCodeBlocks.AppendCodeBlock($2)
		}
	}
	| print_packet
	{
		//fmt.Println(" print_packet ")
		$$ = NewListOfCodeBlock()
		$$.AppendCodeBlock($1)
	}

print_packet :
	PP
	{
		//fmt.Println("pp")
		$$ = NewPrintPacketBlock()
	}

if_block :
	IF exp COMPARATOR COMPARING_VALUE START_BRACE code_block
	{
		$$ = NewIfBlock($2, $4)
		$4.SetComparator($3)
		for _, each_block := range *$6 {
			$$.AddCodeBlocks(each_block)
		}
		//fmt.Println($$.ToString())
	}

for_block :
	FOR IDENTIFIER IN exp START_BRACE code_block
	{
		$$ = NewForBlock($2, $4) 
		for _, each_block := range *$6 {
			$$.AddCodeBlocks(each_block)
		}
		//fmt.Println("FOR IDENTIFIER IN exp START_BRACE code_block")
	}

exp :
	JSON
	{
		//fmt.Println("JSON")
		$$ = NewJsonExpression(-1)
	}
	| JSON '[' SIGNED_VALUE ']'
	{
		//fmt.Println("JSON [ SIGNED_VALUE ]")
		$$ = NewJsonExpression(int($3))
	}
	| STRING_IDENTIFIER
	{
		//fmt.Println("STRING_IDENTIFIER")
		$$ = NewNonJsonExpression()
		$$.AddIdentifier($1)
	}
	| exp STRING_IDENTIFIER
	{
		//fmt.Println("exp STRING_IDENTIFIER")
		$1.AddIdentifier($2)
	}

STRING_IDENTIFIER :
	IDENTIFIER
	{
		//fmt.Println("IDENTIFIER")
		$$ = NewIdentifier($1)
	}
	| DOT IDENTIFIER
	{
		//fmt.Println("DOT IDENTIFIER")
		$$ = NewIdentifier($2)
	}
	| STRING_IDENTIFIER '[' SIGNED_VALUE ']'
	{
		//fmt.Println("STRING_IDENTIFIER [ SIGNED_VALUE ]")
		if $1 == nil {
			$1 = NewIdentifier("")
		}
		$1.AddIndex(int($3))
	}

START_BRACE :
	'{'
	{
		//fmt.Println("Start Brace")
		g_trackCodeBlock = append(g_trackCodeBlock, true)
	}

code_block :
	END statements END END_BLOCK END
	{
		//fmt.Println("END statements END END_BLOCK END")
		$$ = NewListOfCodeBlock()
		for _, each_block := range *$2 {
			$$.AppendCodeBlock(each_block)
		}
	}
	| END statements END_BLOCK END
	{
		//fmt.Println("END statements END_BLOCK END")
		$$ = NewListOfCodeBlock()
		for _, each_block := range *$2 {
			$$.AppendCodeBlock(each_block)
		}
	}

END_BLOCK :
	'}'
	{
		//fmt.Println("End Brance")
		track_size := len(g_trackCodeBlock)
		if (track_size > 0) {
			g_trackCodeBlock = g_trackCodeBlock[:track_size - 1]
		}
	}

COMPARATOR :
	DOUBLE_EQUAL
	{
		//fmt.Println("Double Equals")
		$$ = &CompareEqualTo{}
	}
	|
	GREATER_THAN_EQUAL
	{
		//fmt.Println("Greater than Equal")
		$$ = &CompareGreaterThanEqual{}
	}
	|
	GREATER_THAN
	{
		//fmt.Println("Greater than")
		$$ = &CompareGreaterThan{}
	}
	|
	LESS_THAN_EQUAL
	{
		//fmt.Println("Less than Equal")
		$$ = &CompareLessThanEqual{}
	}
	|
	LESS_THAN
	{
		//fmt.Println("Less than")
		$$ = &CompareLessThan{}
	}

COMPARING_VALUE :
	QUOTED_STRING
	{
		//fmt.Println("Quoted String")
		$$ = NewCompareValue(STRING, $1)
	}
	|
	SIGNED_VALUE
	{
		//fmt.Println("Signed Value")
		// Unfortunately the default Json package provided by go
		// can unmarshall only float64, bool and string base type
		$$ = NewCompareValue(DOUBLE, $1)
	}
	|
	BOOL_VALUE
	{
	//fmt.Println("Bool Value")
		$$ = NewCompareValue(BOOL, $1)
	}
	|
	DOUBLE_VALUE
	{
		//fmt.Println("Double Value")
		$$ = NewCompareValue(DOUBLE, $1)
	}
%%
