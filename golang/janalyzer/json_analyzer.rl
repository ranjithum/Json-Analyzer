package janalyzer 

import (
        "strconv"
)

%%{
	machine json_analyzer;
	write data;
	access lex.;
	variable p lex.m_p;
	variable pe lex.m_pe;
	variable ts lex.m_ts;
	variable te lex.m_te;
	variable cs lex.m_cs;
	variable act lex.m_act;
	variable data lex.m_unScannedData;
}%%

type lexer struct {
	m_unScannedData []byte	// Data required for scanning will be stored here
	m_p int					// Pointer/pos pointing to begging of unscanned data
	m_pe int				// Pointer/pos pointing to end of unscanned data
	m_ts int				// Pointer/pos pointing to begging of current scanned token
	m_te int				// Pointer/pos pointing to end of current scanned token
	m_cs int
	m_act int
}

func newLexer(unscanned_data []byte) *lexer {
	lex := &lexer{
		m_unScannedData: unscanned_data,
		m_p: 0,
		m_pe: len(unscanned_data),
	}

	%% write init;
	return lex
}

/* 
According to https://godoc.org/golang.org/x/tools/cmd/goyacc we need to implement 
type yyLexer interface {
	Lex(lval *yySymType) int
	Error(e string)
}
*/

func (lex *lexer) Lex(yylval *yySymType) int {
	eof := lex.m_pe
	current_token := 0

	%%{
		newline 	= '\r'? '\n';
		whitespace  = ' ' | '\f' | '\t' | '\v';
		dquote 		= '"';
		emptyline   = whitespace* newline;
		utf8        = 0x09 | 0x0a | 0x0d | (0x20..0x7e) |
                  (0xc2..0xdf) (0x80..0xbf) |
                  (0xe0..0xef 0x80..0xbf 0x80..0xbf) |
                  (0xf0..0xf4 0x80..0xbf 0x80..0xbf 0x80..0xbf);
		comment     = '#'+ (utf8 - newline)*;
		commentline = whitespace* comment newline?;
		identifier  = [a-zA-Z_][a-zA-Z0-9_]*;
		quoted_string = dquote (any - newline)* dquote ;
		signed_value = [\-+]? digit+;
		float_value = [\-+]? digit+ '.' digit+;

		main := |*
			commentline;
			whitespace;
			'json' => 
			{
				current_token = JSON;
				//fmt.Println("json")
				fbreak;
			};
			'if' =>
			{
				current_token = IF;
				//fmt.Println("if")
				fbreak;
			};
			'for' =>
			{
				current_token = FOR;
				//fmt.Println("for")
				fbreak;
			};
			'.' =>
			{
				current_token = DOT;
				//fmt.Println(".")
				fbreak;
			};
			newline =>
			{
				//fmt.Println("newline")
				current_token = END;
				fbreak;
			};
			'in' =>
			{
				//fmt.Println("IN")
				current_token = IN;
				fbreak;
			};
			'{' =>
			{
				current_token = '{';
				//fmt.Println("{")
				fbreak;
			};
			'}' =>
			{
				current_token = '}';
				//fmt.Println("}")
				fbreak;
			};
			'[' =>
			{
				current_token = '[';
				//fmt.Println("[")
				fbreak;
			};
			']' =>
			{
				current_token = ']';
				//fmt.Println("]")
				fbreak;
			};
			'==' =>
			{
				current_token = DOUBLE_EQUAL;
				//fmt.Println("==")
				fbreak;
			};
			'>=' =>
			{
				current_token = GREATER_THAN_EQUAL;
				//fmt.Println(">=")
				fbreak;
			};
			'>' =>
			{
				current_token = GREATER_THAN;
				//fmt.Println(">")
				fbreak;
			};
			'<=' =>
			{
				current_token = LESS_THAN_EQUAL;
				//fmt.Println("<=")
				fbreak;
			};
			'<' =>
			{
				current_token = LESS_THAN;
				//fmt.Println("<")
				fbreak;
			};
			'pp' =>
			{
				current_token = PP;
				//fmt.Println("pppp")
				fbreak;
			};
			quoted_string =>
			{
				current_token = QUOTED_STRING;
				yylval.stringValue = string(lex.m_unScannedData[lex.m_ts:lex.m_te]);
				//fmt.Println("quoted string : ", yylval.stringValue)
				fbreak;
			};
			float_value =>
			{
				current_token = DOUBLE_VALUE;
				yylval.doubleValue, _ = strconv.ParseFloat(string(lex.m_unScannedData[lex.m_ts:lex.m_te]), 64);
				//fmt.Println("double value : ", yylval.doubleValue)
				fbreak;
			};
			signed_value =>
			{
				current_token = SIGNED_VALUE;
				yylval.sint64Value, _ = strconv.ParseInt(string(lex.m_unScannedData[lex.m_ts:lex.m_te]),10, 64);
				//fmt.Println("signed value : ", yylval.sint64Value)
				fbreak;
			};
			'true' =>
			{
				current_token = BOOL_VALUE;
				yylval.boolValue = true;
				//fmt.Println("true")
				fbreak;
			};
			'false' =>
			{
				current_token = BOOL_VALUE;
				yylval.boolValue = false;
				//fmt.Println("false")
				fbreak;
			};
			identifier =>
			{
				current_token = IDENTIFIER;
				yylval.stringValue = string(lex.m_unScannedData[lex.m_ts:lex.m_te]);
				//fmt.Println("Identifier : ", yylval.stringValue)
				fbreak;
			};
		*|;
		write exec;
	}%%
	return current_token
}

func (lex *lexer) Error(e string) {
	//fmt.Println("error:", e)
}
