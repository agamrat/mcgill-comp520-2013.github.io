
(* file: lexer.mll *)

{
  open Wig (* Assumes the parser file is "wig.mly". *)
}
let digit = ['0'-'9']
let stringId = ['a'-'z''A'-'Z']['a'-'z''A'-'Z''0'-'9']+

rule exp = parse
  | [' ' '\t']	{ exp lexbuf }
  | '\n'	{ NEWLINE }


 (*
  | "false"	{ FALSE }
  | "true"	{ TRUE }
*)
(*boolean ops*)
  | "=="	{ EQUALITY }
  | "!="	{ NOTEQUAL }
 (* | "<="	{ GREATEROREQUAL }
  | ">="	{ LESSOREQUAL }*)
(*
(*logic ops*)
  | "&&"	{ AND }
  | "||"	{ OR }
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
*)
  | digit+
  | "." digit+
  | digit+ "." digit+ as number
		{ NUMBER (float_of_string number) }
 (* | stringId as id
		{ IDENTIFIER id }*)

  | _		{ exp lexbuf }
  | eof		{ raise End_of_file } 

