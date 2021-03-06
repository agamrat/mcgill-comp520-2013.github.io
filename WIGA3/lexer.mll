(* file: lexer.mll *)

{
  open Wig (* Assumes the parser file is "wig.mly". *)
}
let digit = ['0'-'9']
let stringId = ['a'-'z''A'-'Z']['a'-'z''A'-'Z''0'-'9']+
(*add stringids to hashtable*)
rule exp = parse
  | [' ' '\t']	{ exp lexbuf }
  | '\n'	{ NEWLINE }

  | "session"	{ SESSION }
  | "service"	{ print_endline "lexed service"; flush stdout; SERVICE }
  | "schema"	{ SCHEMA }
  | "return"	{ RETURN }
  | "exit"	{ EXIT }
  | "show"	{ SHOW }
  | "if"	{ IF }
  | "else"	{ ELSE }
  | "while"	{ WHILE }
  | "plug"	{ PLUG }
  | "receive"	{ RECEIVE }

  | "int"	{ INTDEC }
  | "string"	{ STRINGDEC }
  | "bool"	{ BOOLDEC }
  | "void"	{ VOIDDEC }
  | "const"	{ CONST }
  | "html"	{ HTML }

  | "false"	{ FALSE }
  | "true"	{ TRUE }

(*boolean ops*)
  | "=="	{ EQUALITY }
  | "!="	{ NOTEQUAL }
  | "<="	{ GREATEROREQUAL }
  | ">="	{ LESSOREQUAL }

  | "\\+"	{ SLASHPLUS }
  | "\\-"	{ SLASHMINUS }

(*logic ops*)
  | "&&"	{ AND }
  | "||"	{ OR }
  | "<<"	{ DOUBLEVEE }
  | "!"		{ NOT }

(*arithmetic ops *)
  | "+"		{ PLUS }
  | "%"		{ MOD }
  | "-"		{ MINUS }
  | "*"		{ MULTIPLY }
  | "/"		{ DIVIDE }

  | ">"		{ GREATER }
  | "<"		{ LESS }
  | "="		{ ASSIGN }

(*misc*)
  | "("		{ LPAREN }
  | ")"		{ RPAREN }
  | "["		{ RBRACKET }
  | "]"		{ LBRACKET }
  | "{"		{ print_endline "lexed lbrace"; flush stdout; LBRACE }
  | "}"		{ print_endline "lexed rbrace"; flush stdout; RBRACE }
  | ","		{ COMMA }
  | ";"		{ SEMICOLON }

  | digit+ as number
		{ INTCONST (int_of_string number) }
  | stringId as id
		{ print_endline (("lexed id=\"" ^ id) ^"\""); flush stdout; IDENTIFIER id }

  | "<html>"	{ OHTML; htmlexp lexbuf }

  | _		{ exp lexbuf }
  | eof		{ raise End_of_file } 

(*HTML syntax*)  
and htmlexp = parse
  | "</html>"	{ CHTML; exp lexbuf }
  | "<" 	{ OPENTAG; htmltagexp lexbuf }
  | "</"	{ OENDTAG; htmltagexp lexbuf }
  | "<["	{ OPENGAP; holeexp lexbuf }
  | stringId as s{ STRINGCONST (s); htmlexp lexbuf }
  | [' ' '\t']	{ htmlexp lexbuf }
  (*| eof		{ parse_error "premature end of file" }*) (*raise some sort of error if we reach eof without closing the html*)

(*HTML tags*)
and htmltagexp = parse
  | ">" 	{ CLOSETAG; htmlexp lexbuf }
  | "input"	{ INPUT }
  | "name="	{ NAME; htmlvalues lexbuf }
  | "type="	{ TYPE; htmlvalues lexbuf }
  | "size="	{ SIZE; htmlvalues lexbuf }

(*Holes*)
and holeexp = parse
  | "]>"	{ CLOSEGAP; htmlexp lexbuf }
 
(*HTML right-hand side values*)
and htmlvalues = parse
  | digit+ as number
		{ INTCONST (int_of_string number); htmltagexp lexbuf }
