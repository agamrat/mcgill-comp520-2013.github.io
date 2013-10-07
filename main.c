#include "tree.h"
#include "pretty.h"
#include "eval.h"
#include "stdio.h"

void yyparse();

EXP *theexpression;

int lineno;

int main()
{ lineno = 1;

  printf("Type in a tiny exp folowed by one or two Ctrl-d's:\n");
  yyparse();
  printf("\nThe result of evaluating:\n");
  prettyEXP(theexpression);
  printf("\n");
  EXPresult x = evalEXP(theexpression);
  if(x.kind == number) {
  printf("is: %d\n", x.val.intconstE);
}
else 
{
printf("is: %s\n", x.val.idE);
}
  return(1);
}
