package main

import (
        "fmt"
        "strconv"
)

%%{
	machine json_analyzer;
	write data;
}%%

type lexer struct {
	m_unScannedData []byte	// Data required for scanning will be stored here
	m_p int					// Pointer/pos pointing to begging of unscanned data
	m_pe int				// Pointer/pos pointing to end of unscanned data
	m_ts int				// Pointer/pos pointing to begging of current scanned token
	m_te int				// Pointer/pos pointing to end of current scanned token
}

func newLexer(unscanned_data []byte) *lexer {
	lex := &lexer{
		m_unScannedData: unscanned_data,
		m_p: 0,
		m_pe: len(unScannedData),
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
	eof := lex.pe
	current_token := 0

	%%{
		main := |*
			'json' => 
			{
				current_token = JSON;
				fbreak;
			};
			'if' =>
			{
				current_token = IF;
				fbreak;
			};
			'for' =>
			{
				current_token = FOR;
				fbreak;
			};
			'.' =>
			{
				current_token = DOT;
				fbreak;
			};
			'{' =>
			{
				current_token = '{';
				fbreak;
			};
			'}' =>
			{
				current_token = '}';
				fbreak;
			};
			'[' =>
			{
				current_token = '[';
				fbreak;
			};
			']' =>
			{
				current_token = ']';
				fbreak;
			};
			'==' =>
			{
				current_token = DOUBLE_EQUAL;
				fbreak;
			};
			'>=' =>
			{
				current_token = GREATER_THAN_EQUAL;
				fbreak;
			};
			'>' =>
			{
				current_token = GREATER_THAN;
				fbreak;
			};
			'<=' =>
			{
				current_token = LESS_THAN_EQUAL;
				fbreak;
			};
			'<' =>
			{
				current_token = LESS_THAN;
				fbreak;
			};
			'pp' =>
			{
				current_token = PP;
				fbreak;
			};
			/\"(.*?)\"/ =>
			{
				current_token = QUOTED_STRING;
				yylval.stringValue = lex.data[lex.ts:lex.te];
				fbreak;
			};
			/\[-+\]?\[0-9\]+\.\[0-9\]+/ =>
			{
				current_token = DOUBLE_VALUE;
				yylval.doubleValue = strconv.ParseFloat(lex.data[lex.ts:lex.te], 64);
				fbreak;
			};
			/\[-+\]?\[0-9\]+/ =>
			{
				current_token = SIGNED_VALUE;
				yylval.sint64Value = strconv.ParseInt(lex.data[lex.ts:lex.te],10, 64);
				fbreak;
			};
			'true' =>
			{
				current_token = BOOL_VALUE;
				yylval.boolValue = true;
				fbreak;
			};
			'false' =>
			{
				current_token = BOOL_VALUE;
				yylval.boolValue = false;
				fbreak;
			};
			/\[a-zA-Z_\](\[a-zA-Z_\-0-9\])*/ =>
			{
				current_token = IDENTIFIER;
				yylval.stringValue = lex.data[lex.ts:lex.te];
				fbreak;
			};
			space;
		*|;
		write exec;
	}%%
	return current_token
}

func (lex *lexer) Error(e string) {
	fmt.Println("error:", e)
}
