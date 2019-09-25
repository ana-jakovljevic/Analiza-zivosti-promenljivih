%option noyywrap
%option nounput
%option noinput

%{
#include <cstdlib>
#include <iostream>
#include <string>
#include "instructions.hpp"
#include "parser.tab.hpp"

using namespace std;
%}

%%

"if"                 {return if_token;}
"goto"               {return goto_token;}
"return"             {return return_token;}
[+*/-]               {
    yylval.ch = *yytext;
    return op_token;
}
[<>]("=")? {
    yylval.str = new string(yytext);
    return rel_op_token;
} 
[;();:=\[\]]    {return *yytext;}
[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = new string(yytext);
    return id_token;
}
([0-9]+\.)?[0-9]* { 
    yylval.num = atoi(yytext);
    return num_token;
}
[ \t\n] {  }

. {
    cerr << "Nepoznata leksema " << endl;
}

%%
