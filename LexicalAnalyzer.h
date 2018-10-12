#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum token_type {NONE = -1, EOF_T = 100, IDENT_T= 101, NUMLIT_T= 102, STRLIT_T= 103, LISTOP_T= 104, CONS_T= 105, IF_T= 106, COND_T= 107,
		 ELSE_T= 108, DISPLAY_T= 109, NEWLINE_T= 110, AND_T= 111, OR_T= 112, NOT_T= 113, DEFINE_T= 114, NUMBERP_T= 115, LISTP_T= 116,
		 ZEROP_T= 117, NULLP_T= 118, STRINGP_T= 119, PLUS_T= 120, MINUS_T= 121, DIV_T= 122, MULT_T= 123, MODULO_T= 124, ROUND_T= 125,
		 EQUALTO_T= 126, GT_T= 127, LT_T= 128, GTE_T= 129, LTE_T= 130, LPAREN_T= 131, RPAREN_T= 132, SQUOTE_T= 133, ERROR_T= 134,
		 Predicate= 135, NUM_TOKENS};

class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	token_type GetToken ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
    private:
	ifstream input;
	ofstream listingFile;
	ofstream tokenFile;
	ofstream debugFile;
	token_type token;
	vector<string> lines;
	int DFA[12][22] =
	  {
	    {1,2,3,4,5,5,5,ERROR_T,ERROR_T,EQUALTO_T,6,7,DIV_T,MULT_T,LPAREN_T,RPAREN_T,SQUOTE_T,9,0,5,8,0},
	    {PLUS_T,PLUS_T,3,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,9,PLUS_T,15,PLUS_T,PLUS_T},
	    {MINUS_T,MINUS_T,3,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,9,MINUS_T,16,MINUS_T,MINUS_T},
	    {NUMLIT_T,NUMLIT_T,3,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,9,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T},
	    {IDENT_T,IDENT_T,5,5,10,10,5,5,Predicate,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,5,IDENT_T,IDENT_T},
	    {IDENT_T,IDENT_T,5,5,5,5,5,5,Predicate,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,5,IDENT_T,IDENT_T},
	    {GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GTE_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T},
	    {LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LTE_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T},
	    {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,STRLIT_T,ERROR_T},
	    {NUMLIT_T,NUMLIT_T,9,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T, NUMLIT_T},
	    {IDENT_T,IDENT_T,5,5,5,10,11,5,Predicate,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,5,IDENT_T,IDENT_T},
	    {LISTOP_T,LISTOP_T,5,5,5,5,5,5,Predicate,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T}
	  };
	string line;
	string msg = "Invalid character found: ";
	int linenum;
	int pos;
	string lexeme;
	int errors;
	bool error_flag = false;
	int error_pos = 0;
};
	
#endif
