
/* file: wig.mly */


%{
open Printf
%}

%token <float> NUMBER 
%token <string> IDENTIFIER
%token PLUS
%token EQUALITY NOTEQUAL LESS GREATER
%token NEWLINE

%left PLUS

%start input
%type <unit> input

%% /* Grammar rules and actions follow */

input:    /* empty */		{ }
        | input line		{ }
;

line:     NEWLINE		{ }
        | exp NEWLINE		{ printf "\t%s\n" $1; flush stdout }
;
/*here is where you need to call a different function to do the ast or something*/

exp:	NUMBER 			{ string_of_float $1 }
	| IDENTIFIER		{ $1 }


	| exp EQUALITY exp	{ $1 ^ " == " ^ $3 }
	| exp NOTEQUAL exp	{ $1 ^ " != " ^ $3 }
	| exp LESS exp		{ $1 ^ " < " ^ $3 }
	| exp GREATER exp	{ $1 ^ " > " ^ $3 }
	| exp PLUS exp		{ $1 ^ " + " ^ $3 }

;
%%
