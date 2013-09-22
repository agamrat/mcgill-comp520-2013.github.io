#include <stdio.h>
#include "pretty.h"
 
void prettyEXP(EXP *e){
 EXP *left;
 EXP *right;
 switch (e->kind) {
    case idK:
         printf("%s",e->val.idE);
         break;
    case intconstK:
         printf("%i",e->val.intconstE);
         break;
    case timesK:
     	left = e->val.timesE.left;
     	right = e->val.timesE.right;
	if(left->kind == minusK || left->kind == plusK || left->kind == divK || left->kind == modK){
		printf("(");
		prettyEXP(left);
		printf(")");
	}
     	else{
        	prettyEXP(left);
        }
         printf("*");
         
        if(right->kind == plusK || right->kind == divK || right->kind == minusK || right->kind == modK){
		printf("(");
		prettyEXP(right);
		printf(")");
	}
	else{
        	prettyEXP(right);
        }

         break;
    case divK:
	 left = e->val.divE.left;
	 right = e->val.divE.right;
	if(left->kind == plusK || left->kind == timesK || left->kind == divK || left->kind == minusK || left->kind == modK){
		printf("(");
		prettyEXP(left);
		printf(")");
	}
	else{
        	prettyEXP(left);
        }
         printf("/");
         
         if(right->kind == timesK || right->kind == divK || right->kind == plusK || right->kind == minusK || right->kind == modK){
		printf("(");
		prettyEXP(right);
		printf(")");
	}
	else{
        	prettyEXP(right);
        }
        break;
    case plusK:
	left = e->val.plusE.left;
	right = e->val.plusE.right;
	if(left->kind == minusK){
		printf("(");
		prettyEXP(left);
		printf(")");
	}
	else{
        	prettyEXP(left);
        }
        
        printf("+");
         
        if(right->kind == minusK){
		printf("(");
		prettyEXP(right);
		printf(")");
	}
	else{
        	prettyEXP(right);
        }
         
         break;
    case minusK:
	left = e->val.minusE.left;
	right = e->val.minusE.right;
	if(left->kind == plusK || left->kind == minusK){
		printf("(");
		prettyEXP(left);
		printf(")");
	}
	else{
        	prettyEXP(left);
        }
         printf("-");
         
         if(right->kind == plusK || right->kind == minusK){
		printf("(");
		prettyEXP(right);
		printf(")");
	}
	else{
        	prettyEXP(right);
        }
         break;
    case absK:
    	 printf("abs(");
    	 prettyEXP(e->val.absE.x);
    	 printf(")");
    	 break;
    case modK:
    	left = e->val.modE.left;
    	right = e->val.modE.right;
 	if(left->kind == plusK || left->kind == timesK || left->kind == divK || left->kind == minusK || left->kind == modK){
		printf("(");
		prettyEXP(left);
		printf(")");
	}
	else{
        	prettyEXP(left);
        }
         printf("%%");
         
         if(right->kind == timesK || right->kind == divK || right->kind == plusK || right->kind == minusK || right->kind == modK){
		printf("(");
		prettyEXP(right);
		printf(")");
	}
	else{
        	prettyEXP(right);
        }
        break;
    case powerK:
    	left = e->val.powerE.left;
    	right = e->val.powerE.right;
    	
	if(left->kind == plusK || left->kind == timesK || left->kind == divK || left->kind == minusK || left->kind == modK || left->kind == powerK){
		printf("(");
		prettyEXP(left);
		printf(")");
	}
	else{
        	prettyEXP(left);
        }
         printf("**");
         
         if(right->kind == timesK || right->kind == divK || right->kind == plusK || right->kind == minusK || right->kind == modK || right->kind == powerK){
		printf("(");
		prettyEXP(right);
		printf(")");
	}
	else{
        	prettyEXP(right);
        }
    	
    	break;
  }
}
