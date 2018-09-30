#include <iomanip>
#include <vector>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T", "IDENT_T", "NUMLIT_T", "STRLIT_T", "LISTOP", "CONS_T", "IF_T", "COND_T", "ELSE_T", "DISPLAY_T", "NEWLINE_T", "AND_T", "OR_T", "NOT_T", "DEFINE_T",
                 "NUMBERP_T", "LISTP_T", "ZEROP_T", "NULLP_T", "STRINGP_T", "PLUS_T", "MINUS_T", "DIV_T", "MULT_T", "MODULO_T", "ROUND_T", "EQUALTO_T", "GT_T", "LT_T", "GTE_T", "LTE_T",
                 "LPAREN_T", "RPAREN_T", "SQUOTE_T", "ERROR_T"}; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
  // This function will initialize the lexical analyzer class
  vector<string> tmp;
  string line = "";
  ifstream input(filename);
  while (getline(input, line))
    {
      cout << line << endl;
      tmp.push_back(line);
    }
  lines = tmp;
  int linenum = 0;
  int pos = 0;
  string lexeme = "EOF_T";
  int errors = 0;
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
  int value = 0;
  line = lines[linenum];
  char c;
  string word = "";
  bool done = false;
  while(done == false)
    {
      c = line[pos];
      word += c;
      cout << word << endl;
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
	  //cout << "state " << state << endl;
        }
      else if(c == ' ')
        {
          value = 18;
          state = DFA[state][value];
        }
      else if(isalpha(c))
        {
	  //cout << "hit" << endl;
          value = 19;
          state = DFA[state][value];
        }
      else if(c == '"')
        {
	  cout << "Hit" << endl << endl;
          value = 20;
          state = DFA[state][value];
	  cout << state << endl << endl;
        }
      if(state == 0)
	{
	  word = "";
	}
      if(state == 101)
	{
	  word.erase(word.end()-1, word.end());
	  cout << "|" << word << "|" << endl;
	  if(word == "cons")
	    state = CONS_T;
	  else if (word == "if")
	    state = IF_T;
	  else if (word == "else")
	    state = ELSE_T;
	  else if (word == "cond")
	    state = COND_T;
	  else if (word == "display")
	    state = DISPLAY_T;
	  else if (word == "newline")
	    state = NEWLINE_T;
	  else if (word == "and")
	    state = AND_T;
	  else if (word == "or")
	    state = OR_T;
	  else if (word == "not")
	    state = NOT_T;
	  else if (word == "define")
	    state = DEFINE_T;
	  else if (word == "modulo")
	    state = MODULO_T;
	  else if (word == "round")
	    state = ROUND_T;	      
	}
      if(state == 135)
	if(word == "number?")
	  state = NUMBERP_T;
	else if( word == "list?")
	  state = LISTP_T;
	else if(word == "zero?")
	  state = ZEROP_T;
	else if (word == "null?")
	  state = NULLP_T;
	else if (word == "string?")
	  state = STRINGP_T;
      if (state == 120 || state == 121 || state == 102 || state == 101 || state == 127 || state == 128 ||
	  state == 104 || state == 105 || state == 106 || state == 107 || state == 108 || state == 109 ||
	  state == 110 || state == 111 || state == 112 || state == 113 || state == 114)
	{
	  pos--;
	  //cout << word << endl;
	  token = token_type(state);
	  done = true;
	}
      else if (state == 104 || state == 126 || state == 129 || state == 130 || state == 103 || state == 122 ||
	       state == 123 || state == 131 || state == 132 || state == 133 || state == 134)
	{
	  //cout << word << endl;
	  token = token_type(state);
	  done = true;
	}
      if(pos == line.length())
	{
	  value = 18;
	  state = DFA[state][value];
	  linenum = linenum + 1;
	  pos = -1;
	  token = token_type(state);
	  done = true;
	}
      pos++;
    }
  
  return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it.
  int idx = 0;
  string name = "";
  idx = t - 100;
  if (idx < 0)
    idx = 0;
  name = token_names[idx];
  return name;
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
