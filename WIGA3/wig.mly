
/* file: wig.mly */


%{
open Printf
open Tree

abstractTree = 
%}

%token <int> INTCONST
%token <string> STRINGCONST
%token <string> IDENTIFIER
%token INT BOOL STRING VOID
%token SCHEMA
%token PLUS MOD MINUS MULTIPLY DIVIDE
%token EQUALITY NOTEQUAL LESS GREATER GREATEROREQUAL LESSOREQUAL
%token SESSION SERVICE RETURN EXIT SHOW IF ELSE WHILE PLUG RECEIVE
%token FALSE TRUE AND OR NOT
%token SLASHPLUS SLASHMINUS DOUBLEVEE
%token ASSIGN
%token TUPLE
%token LPAREN RPAREN RBRACKET LBRACKET LBRACE RBRACE COMMA SEMICOLON DOT
%token NEWLINE

%left MOD DIVIDE MULTIPLY
%left PLUS MINUS
%nonassoc NOT
%left AND OR
%left EQUALITY NOTEQUAL LESS GREATER GREATEROREQUAL LESSOREQUAL
%left SLASHPLUS SLASHMINUS DOUBLEVEE
%left ASSIGN 

%start service
%type <unit> service

%% /* Grammar rules and actions follow */

session:    /* empty */		{}
        | session SESSION identifier LPAREN RPAREN compoundstm {}
;

sessions:
	session				{}
	| sessions session		{}
;

service: SERVICE LBRACE htmls schemas 
		variables functions 
		 sessions RBRACE	{}
;

htmls:	/*empty TODO*/			{}
;
/*(*html				{}
	| htmls html			{}
;

html:	CONST HTML identifier ASSIGN
		HTMLTAG htmlbodies HTMLTAG
					{}
;

htmlbodies:
			{}
	| nehtmlbodies			{}
;

nehtmlbodies:
	htmlbody			{}
	| nehtmlbodies htmlbody		{}
;

htmlbody:
	LESS identifier attributes
		GREATER			{}
	| LESS 
*)*/
variables:
	/*empty*/			{}
	| nevariables			{}
;
nevariables: 
	variable			{}
	| nevariables variable 		{}
;

variable:
	typepat identifiers SEMICOLON 	{ /*add variables to hash here*/}
;

typepat:
	simpletype			{}
	| TUPLE identifier		{}
;

simpletype:
	INT				{}
	| BOOL				{}
	| STRING			{}
	| VOID				{}
;

stms:	/*empty*/			{}
	| nestms			{}
;

nestms:	stm				{}
	| nestms stm			{}
;

stm:	SEMICOLON			{}
	| SHOW document receive SEMICOLON {}
	| EXIT document SEMICOLON	{}
	| RETURN SEMICOLON		{}
	| RETURN exp SEMICOLON		{}
	| IF LPAREN exp RPAREN stm	{}
	| IF LPAREN exp RPAREN ELSE stm {}
	| WHILE LPAREN exp RPAREN stm 	{}
	| compoundstm			{}
	| exp SEMICOLON			{}
;
document:
	identifier			{}
	| PLUG identifier LBRACKET plugs RBRACKET {}
;

receive: /*empty*/
	| RECEIVE LBRACKET inputs RBRACKET {}
;

compoundstm:
	LBRACE variables stms RBRACE 	{}
;

plugs:
	plug				{}
	| plugs COMMA plug		{}
;

plug:
	identifier ASSIGN exp		{}
;

inputs:	/*empty*/			{}
	| neinputs			{}
;

neinputs: input				{}
	| neinputs COMMA input		{}
;

input:  lvalue ASSIGN identifier	{}
;
	

exp:	lvalue				{}
	| lvalue ASSIGN exp		{ /*check value is in hash*/
					/*if not throw error */}
	| exp EQUALITY exp		{}
	| exp NOTEQUAL exp		{}
	| exp LESS exp			{}
	| exp GREATER exp		{}
	| exp LESSOREQUAL exp		{}
	| exp GREATEROREQUAL exp 	{}
	| NOT exp			{}
	| MINUS exp			{}
	| exp PLUS exp			{ Plus ($1, $3) }
	| exp MINUS exp			{}
	| exp MULTIPLY exp		{}
	| exp DIVIDE exp		{}
	| exp MOD exp			{}
	| exp AND exp			{}
	| exp OR exp			{}
	| exp DOUBLEVEE exp		{}
	| exp SLASHPLUS identifiers	{}
	| exp SLASHMINUS identifiers	{}
	| identifier LPAREN exps RPAREN	{}
	| INTCONST			{}
	| TRUE				{}
	| FALSE				{}
	| STRINGCONST			{}
	| TUPLE	LBRACE fieldvalues RBRACE {}
	| LPAREN exp RPAREN		{}
;

exps: /* empty*/			{}
	| neexps			{}
;

neexps:
	exp				{}
	| neexps COMMA exp		{}
;

lvalue:
	identifier			{}
	| identifier DOT identifier	{}
;

fieldvalues:
	/*empty*/			{}
	| nefieldvalues			{}
;

nefieldvalues:
	fieldvalue			{}
	| fieldvalues COMMA fieldvalue	{}
;

fieldvalue:
	identifier ASSIGN exp		{}
;

schemas: /*empty*/			{}
	| neschemas			{}
;

neschemas: schema			{}
	| neschemas schema		{}
;

schema:	SCHEMA identifier LBRACE fields RBRACE 
					{}
;

fields: /*empty*/			{}
	| nefields			{}
;

nefields: field				{}
	| nefields field		{}
;

field: simpletype identifier SEMICOLON	{}
;

functions: /*empty*/			{}
	| nefunctions			{}
;

nefunctions:
	functionpat			{}
	| nefunctions functionpat	{}
;

functionpat:
	typepat identifier LPAREN arguments RPAREN compoundstm
					{}
;

arguments:
	/*empty*/			{}
	| nearguments			{}
;

nearguments:
	argument			{}
	| nearguments COMMA argument	{}
;

argument:
	typepat identifier		{}
;

identifiers:
	identifier			{}
	| identifiers COMMA identifier	{}
;

identifier:
	IDENTIFIER			{}
;

%%
