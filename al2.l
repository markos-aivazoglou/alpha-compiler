%{
	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>
       #include "parser.h"
    
    

    	int indx = 0; 
	char strValue[150];
	char strType[150];
	   
%}

%option noyywrap
%option yylineno



id		        [a-zA-Z][a-zA-Z_0-9]*
int		        [0-9]+
real		   	 [0-9]*\.[0-9](e|E)?[0-9]*
string		   	 \"([^\"\\]|\\.)*\"
comment2	    	 "//".*
	    	

%x COMMENT1


%%			
"/*" {
int counter = 1; // Init with 1 coz we already have 1 "/*" as we entered this section.
char c;
while (((c=input()) != EOF) && counter>0){
      if (c == '/'){
           c = input();
            if (c == '*'){
                  counter++;// Increase counter when we meet a '/' followed by '*' within the comment section.
                  }
            else{
                 unput(c);
                 }
            }
      else if(c == '*'){
           c = input();
           if (c == '/'){
                 counter--;//If requirments are met, that means the end of a comment.
                 }
           else{
                unput(c);
                }
           }
      }
	if (c != EOF)unput(c);//Coz while took already a character from input.
	if (counter == 0){
		//return COMMENT_1;
                  }
      	else{
		//return (COMMENT_ERROR);
           }
}

	
if              {return IF;}
else            {return ELSE;}
while           {return WHILE;}
for             {return FOR;}
function        {return FUNCTION;}
return          {return RETURN;}
break           {return BREAK;}
continue        {return CONTINUE;}
and             {return AND;}
or              {return OR;}
not             {return NOT;}
local           {return LOCAL;}
true            {return TRUE;}
false           {return FALSE;}
nil             {return NIL;}
\{              {return LBRACKET;}             
\}              {return RBRACKET;}
\[              {return LTAB;}
\]              {return RTAB;}
\(              {return LPAR;}
\)              {return RPAR;}
\;              {return SEMICOLON;}
\,              {return COMMA;}
\:\:            {return DCOLON;}
\:              {return COLON;}
\.\.            {return DOTDOT;}
\.              {return FULLSTOP;}
==              {return EQUAL; }
!=              {return NEQUAL; }
=               {return ASSIGNMENT; }
\>=             {return GREATEROREQ; }
\<=             {return LESSOREQ; }
\>              {return GREATER; }
\<              {return LESS; }
\-\-            {return MINUSMINUS; }
\-              {return MINUS; }
\+\+            {return PLUSPLUS; }
\+              {return PLUS; }
\*              {return MULTI; }
\/              {return DIV; }
\%		  {return MOD; }


{comment2}		{}
{id}			{yylval.stringValue=strdup(yytext);return ID; }
{int}			{yylval.intValue = atoi(yytext);return INTEGER; }
{string} 		{
		strcpy(strValue, yytext);
		strcpy(strType,"");
		char c;
		char temp[150];
		char buff[150];
		strcpy(temp,"");
	    strcpy(buff,yytext);
		int i,j=0;
	    for(i=0;i<strlen(buff);i++){
		
            if(buff[i] == '\\'){
				if(buff[i+1] == 'n'){
                    temp[j] = '\n';
					}
				else if(buff[i+1] == 't'){
                    temp[j] = '\t';
					}
				else if(buff[i+1] == 'v'){
					temp[j] = '\v';
					}
				else if(buff[i+1] == '\"'){
					temp[j] = '\"';
					}
				else if(buff[i+1] == '\''){
					temp[j] = '\'';
					}
				else if(buff[i+1] == '\\'){
					temp[j] = '\\';
					}
				else{
					temp[j] = buff[i+1];
					}
            			j++;
            			i++;
			}
			else{
				temp[j]=buff[i];
				j++;
				}
		}
		temp[j]='\0';
		strcpy(strType,temp);
		yylval.stringValue = strdup(yytext);
		return STRING;
	}
{real}          	{yylval.realValue=atof(yytext);   return REAL; }
[\r\n \t\v]+  	{}
<<EOF>>	        	{return -1;}
.[\\]*			{return ERROR;}
%%







