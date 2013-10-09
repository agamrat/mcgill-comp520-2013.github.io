
type lineNumber = int

type abstractTree = (lineNumber * node) 

and node =
	Plus of (abstractTree * abstractTree)
	| Number of int
	| String of string





