#include <iomanip>
#include <vector>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T", "IDENT_T", "NUMLIT_T", "STRLIT_T", "LISTOP_T", "CONS_T", "IF_T", "COND_T", "ELSE_T", "DISPLAY_T", "NEWLINE_T", "AND_T", "OR_T", "NOT_T", "DEFINE_T",
                 "NUMBERP_T", "LISTP_T", "ZEROP_T", "NULLP_T", "STRINGP_T", "PLUS_T", "MINUS_T", "DIV_T", "MULT_T", "MODULO_T", "ROUND_T", "EQUALTO_T", "GT_T", "LT_T", "GTE_T", "LTE_T",
                 "LPAREN_T", "RPAREN_T", "SQUOTE_T", "ERROR_T"};
string filenameNoExtension;

// This function will initialize the lexical analyzer class
// The input is processed into the lines vector here
LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
    string file = filename;
    int extensionIndex = file.find_last_of(".");
    if (file.substr(extensionIndex, file.size()) != ".ss") {
        cout << "Invalid input file type" << endl;
        return;
    }
    filenameNoExtension = file.substr(0, extensionIndex);

    vector<string> tmp;
    string line = "";
    ifstream input(filename); //should be using the ifstream declared in the h file???
    while (getline(input, line))
    {
      cout << line << endl;
      tmp.push_back(line);
    }
    lines = tmp;
    linenum = 0; pos = 0; errors = 0;
    token = EOF_T;
    lexeme = "";
    tokenFile.open(filenameNoExtension + ".p1");
    listingFile.open(filenameNoExtension + ".lst");
    listingFile << "Input file: " << filename << std::endl;
}

// This function will complete the execution of the lexical analyzer class
LexicalAnalyzer::~LexicalAnalyzer ()
{
    listingFile << errors << " errors found in input file" << endl;
    listingFile.close();
    tokenFile.close();
}

// This function will find the next lexeme int the input file and return
// the token_type value associated with that lexeme
token_type LexicalAnalyzer::GetToken ()
{
  int state = 0;
  int value = 0;
  cout << linenum << endl;
  if (linenum == lines.size())
    {
      state = 100;
      token = token_type(state);
      listingFile << "    " << linenum + 1 << ": " << endl;
      tokenFile << GetTokenName(token) << "   " <<  endl;
      return token;
    }
  line = lines[linenum];
  char c;
  lexeme = "";
  bool done = false;
  cout << pos << endl;
  while(done == false)
    {
      c = line[pos];
      lexeme += c;
      //cout << "Back" << endl;
      cout << lexeme << endl;
      //cout << state << endl;
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
      else if(iswspace(c))
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
	  //cout << "Hit" << endl << endl;
	  //exit(0);
          value = 20;
          state = DFA[state][value];
	  //cout << state << endl;
        }
      else if (pos >= line.length())
	{
	  value = 21;
          state = DFA[state][value];
	}
      else
	{
	  state = 134;
	}
      if(state == 0)
	{
	  lexeme = "";
	}
      if(state == 101)
	{
	  lexeme.erase(lexeme.end()-1, lexeme.end());
	  //cout << "|" << lexeme << "|" << endl;
	  if(lexeme == "cons")
	    state = CONS_T;
	  else if (lexeme == "if")
	    state = IF_T;
	  else if (lexeme == "else")
	    state = ELSE_T;
	  else if (lexeme == "cond")
	    state = COND_T;
	  else if (lexeme == "display")
	    state = DISPLAY_T;
	  else if (lexeme == "newline")
	    state = NEWLINE_T;
	  else if (lexeme == "and")
	    state = AND_T;
	  else if (lexeme == "or")
	    state = OR_T;
	  else if (lexeme == "not")
	    state = NOT_T;
	  else if (lexeme == "define")
	    state = DEFINE_T;
	  else if (lexeme == "modulo")
	    state = MODULO_T;
	  else if (lexeme == "round")
	    state = ROUND_T;	      
	}
      if(state == 135)
	{
	if(lexeme == "number?")
	  state = NUMBERP_T;
	else if( lexeme == "list?")
	  state = LISTP_T;
	else if(lexeme == "zero?")
	  state = ZEROP_T;
	else if (lexeme == "null?")
	  state = NULLP_T;
	else if (lexeme == "string?")
	  state = STRINGP_T;
	else
	  state = IDENT_T;
	}
      if (state == 120 || state == 121 || state == 102 || state == 101 || state == 127 || state == 128 ||
          state == 104 || state == 105 || state == 106 || state == 107 || state == 108 || state == 109 ||
          state == 110 || state == 111 || state == 112 || state == 113 || state == 114)
        {
          pos--;
          //cout << lexeme << endl;
	  if(c != ' ')
	    lexeme.erase(lexeme.end()-1, lexeme.end());
	  if(state == 102)
	    {
	      if(lexeme == ".")
		state = 134;
	    }
          token = token_type(state);
          done = true;
        }
      else if (state == 126 || state == 129 || state == 130 || state == 103 || state == 122 ||state == 123 ||
	       state == 124 || state == 125 || state == 131 || state == 132 || state == 133 ||state == 134 ||
	       state == 115 || state == 116 || state == 117 || state == 118 || state == 119)
        {
          //cout << lexeme << endl;
	  //cout << "Yup" << endl;
          token = token_type(state);
          done = true;
        }
      if(state == 134 && error_flag == false)
	{
	  error_pos = pos;
	  error_flag = true;
	}
      if(pos >= line.length() - 1 || line.length() == 0)
        {
	  //cout << "Hit" << endl;
          if (state == 0)
            {
	      listingFile << "    " << linenum + 1 << ": " << lines[linenum] << endl;
              if(error_flag)
                {
                  msg += line[error_pos];
                  ReportError(msg);
                  error_flag = false;
                  msg.erase(msg.end()-1, msg.end());
                }
              pos = 0;
              linenum = linenum + 1;
              //tokenFile << GetTokenName(token) << "   " << GetLexeme() << endl;
              return GetToken();
            }
	  else
	    {
	      if (state <= 100)
		{
		  value = 21;
		  state = DFA[state][value];
		  token = token_type(state);
		  done = true;
		}
	      listingFile << "    " << linenum + 1 << ": " << lines[linenum] << endl;
	      if(error_flag)
                {
                  msg += line[error_pos];
                  ReportError(msg);
		  error_flag = false;
                  msg.erase(msg.end()-1, msg.end());
                }
	      cout << state << endl;
	      pos = 0;
	      linenum = linenum + 1;
	      done = true;
	    }
        }
      else
	pos++;
    }
  //listingFile << "    " << linenum << ": " << lines[linenum-1] << endl;
  tokenFile << GetTokenName(token) << "   " << GetLexeme() << endl;
  return token;
}

// The GetTokenName function returns a string containing the name of the
// token passed to it.
string LexicalAnalyzer::GetTokenName (token_type t) const
{
  int idx = 0;
  string name = "";
  idx = t - 100;
  if (idx < 0)
    idx = 0;
  name = token_names[idx];
  return name;
}

// This function will return the lexeme found by the most recent call to
// the get_token function
string LexicalAnalyzer::GetLexeme () const
{
    if (token != -1)
        return lexeme;
    else {
        return NULL;
    }
}

void LexicalAnalyzer::ReportError (const string & msg)
{
    listingFile << "Error at " << linenum+1 << "," << error_pos + 1 << ": ";
    listingFile << msg << endl;
    errors++;
}
