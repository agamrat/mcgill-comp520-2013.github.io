

type node =
	Plus of (abstractTree * abstractTree)
	| Number of int
	| String of string

type lineNumber = int

type abstractTree =
	(lineNumber * node) 



