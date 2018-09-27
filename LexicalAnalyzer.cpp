#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T", "IDENT_T", "NUMLIT_T", "STRLIT_T", "LISTOP", "CONS_T", "IF_T", "COND_T", "ELSE_T", "DISPLAY_T", "NEWLINE_T", "AND_T", "OR_T", "NOT_T", "DEFINE_T",
                 "NUMBERP_T", "LISTP_T", "ZEROP_T", "NULLP_T", "STRINGP_T", "PLUS_T", "MINUS_T", "DIV_T", "MULT_T", "MODULO_T", "ROUND_T", "EQUALTO_T", "GT_T", "LT_T", "GTE_T", "LTE_T",
                 "LPAREN_T", "RPAREN_T", "SQUOTE_T", "ERROR_T"}; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
  // This function will initialize the lexical analyzer class
  vector<string> lines;
  string line = ""
  ifstream input(filename);
  while (getline(input, line))
    {
      lines.append(line);
    }
  int linenum = 0;
  int pos = 0;
  string lexeme = "EOF_T";
  int errors = 0;
  int DFA[11][21] = {
    {1,2,3,4,5,5,5,ERROR_T,ERROR_T,EQUALTO_T,7,8,DIV_T,MULT_T,LPAREN_T,RPAREN_T,SQUOTE_T,ERROR_T,0,5,9},
    {PLUS_T,PLUS_T,3,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,18,PLUS_T,15,PLUS_T},
    {MINUS_T,MINUS_T,3,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,18,MINUS_T,16,MINUS_T},
    {NUMLIT_T,NUMLIT_T,3,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,18,NUMLIT_T,NUMLIT_T,NUMLIT_T},
    {IDENT_T,IDENT_T,5,5,19,19,5,5,Predicate,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,5,IDENT_T},
    {IDENT_T,IDENT_T,5,5,5,5,5,5,Predicate,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,5,IDENT_T},
    {GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GTE_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T},
    {LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LTE_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T},
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,STRIT_T},
    {NUMLIT_T,NUMLIT_T,18,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T},
    {IDENT_T,IDENT_T,5,5,5,19,LISTOP_T,5,Predicate,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,5,IDENT_T}
  };
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
}

token_type LexicalAnalyzer::GetToken ()
{
  // This function will find the next lexeme int the input file and return
  // the token_type value associated with that lexeme
  int state = 0;
  int value = GD;
  line = lines[linenum];
  char c = line[pos];
  string word = "";
  bool done = false
  while(done == false)
    {
      word += c;
      if(c == '+')
	{
	  value = 0;
	  state = DFA[state][value];
	}
      else if(c == '-')
        {
          value	= 1;
          state	= DFA[state][value];
        }
      else if(isdigit(c))
        {
          value = 2;
          state = DFA[state][value];
        }
      else if(c == 'C' || c == 'c')
        {
          value = 3;
          state = DFA[state][value];
        }
      else if(c == 'A' || c == 'a')
        {
          value = 4;
          state = DFA[state][value];
        }
      else if(c == 'D' || c == 'd')
        {
          value = 5;
          state = DFA[state][value];
        }
      else if(c == 'R' || c == 'r')
        {
          value = 6;
          state = DFA[state][value];
        }
      else if(c == '_')
        {
          value = 7;
          state = DFA[state][value];
        }
      else if(c == '?')
        {
          value = 8;
          state = DFA[state][value];
        }
      else if(c == '=')
        {
          value = 9;
          state = DFA[state][value];
        }
      else if(c == '>')
        {
          value = 10;
          state = DFA[state][value];
        }
      else if(c == '<')
        {
          value = 11;
          state = DFA[state][value];
        }
      else if(c == '/')
        {
          value = 12;
          state = DFA[state][value];
        }
      else if(c == '*')
        {
          value = 13;
          state = DFA[state][value];
        }
      else if(c == '(')
        {
          value = 14;
          state = DFA[state][value];
        }
      else if(c == ')')
        {
          value = 15;
          state = DFA[state][value];
        }
      else if(c == '\'')
        {
          value = 16;
          state = DFA[state][value];
        }
      else if(c == '.')
        {
          value = 17;
          state = DFA[state][value];
        }
      else if(c == ' ')
        {
          value = 18;
          state = DFA[state][value];
        }
      else if(isalpha(c))
        {
          value = 19;
          state = DFA[state][value];
        }
      else if(c == '"')
        {
          value = 20;
          state = DFA[state][value];
        }
      if(state == IDENT_T)
	{
	  if(word == "cons")
	    state = CONS_T;
	  else if (word == "if")
	    state = IF_T
	      
	}
      if (state == PLUS_T || state == MINUS_T || state == NUMLIT_T || state == IDENT_T || state == GT_T || state == LT_T)
	{
	  pos--;
	  token = token_names[state]
	}
    }
  
  return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it. 
	return "";
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return "";
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}