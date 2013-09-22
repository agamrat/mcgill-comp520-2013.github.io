#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eval.h"

EXPresult evalEXP(EXP *e)

{ 
EXPresult result;
char * buffer = (char*)malloc(1000);
EXPresult left;
EXPresult right;

switch (e->kind) {
    case idK:
	 result.kind = string;
	 result.val.idE = e->val.idE;
         break;
    case intconstK:
	 result.kind = number;
	 result.val.intconstE = e->val.intconstE;
         break;
    case timesK:

	left = evalEXP(e->val.plusE.left);
	right = evalEXP(e->val.plusE.right);

	/*identities: a* 0*/
	if((left.kind == number && left.val.intconstE == 0) ||
		(right.kind == number && right.val.intconstE == 0)) {
		result.kind = number;
		result.val.intconstE = 0;
		break;
	}

	/*identities: 1*a */
  	if(left.kind == number && left.val.intconstE == 1) {
 	   result = right;
 	   break;
 	 }

 	/*identities: a*1 */
 	if(right.kind == number && right.val.intconstE == 1) {
 	  result = left;
 	  break;
 	}
 	
	/*basic evaluation*/
	if(left.kind == string) {
		result.kind = string;
		if(right.kind == string) {
	 		sprintf(buffer, "%s * %s", left.val.idE, right.val.idE);
			result.val.idE = buffer;	
		}
		else {
			sprintf(buffer, "%s * %d", left.val.idE, right.val.intconstE);	
			result.val.idE = buffer;
		}
	}
	else if (right.kind == string) {
		result.kind = string;
		sprintf(buffer, "%d * %s", left.val.intconstE, right.val.idE);
		result.val.idE = buffer;
	}
	else {
	        result.kind = number;
		result.val.intconstE = left.val.intconstE * right.val.intconstE;
   	}      
        break;
    case divK:

	left = evalEXP(e->val.plusE.left);
	right = evalEXP(e->val.plusE.right);

	/*divide by zero error*/
	if(right.kind == number && right.val.intconstE == 0) {
		printf("\nTiny Error Message: Divide by zero encountered.\n");
		result.kind = number;
		result.val.intconstE = 0;
		break;
	}

	/*identity: x/1 */
	if(right.kind == number && right.val.intconstE == 1) {
   		if(left.kind == number) {    
   	 		result.kind = number;
    			result.val.intconstE = left.val.intconstE;
    		} else  {
    			result.kind = string;
    			result.val.idE = left.val.idE;
    		}
   	 	break;
  	}	

	/*identity: 0/x */
	if(left.kind == number && left.val.intconstE == 0) {
		result.kind = number;
		result.val.intconstE = 0;
		break;
	}

	/*basic evaluation */
	 if(left.kind == string) {
		result.kind = string;
		if(right.kind == string) {
	 		sprintf(buffer, "%s / %s", left.val.idE, right.val.idE);
			result.val.idE = buffer;	
		}
		else {
			sprintf(buffer, "%s / %d", left.val.idE, right.val.intconstE);	
			result.val.idE = buffer;
		}
	}
	else if (right.kind == string) {
		result.kind = string;
		sprintf(buffer, "%d / %s", left.val.intconstE, right.val.idE);
		result.val.idE = buffer;
	}
	else {
	       result.kind = number;
		result.val.intconstE = left.val.intconstE / right.val.intconstE;
   	}      
        break;
    case plusK:

	left = evalEXP(e->val.plusE.left);
	right = evalEXP(e->val.plusE.right);

	/*identities: a+0 */
	if(right.kind == number && right.val.intconstE == 0) {
		if(left.kind == number) {
		result.kind = number;		
		result.val.intconstE = left.val.intconstE;
		}
		else {
		result.kind = string;
		result.val.idE = left.val.idE;
		}
		break;
	}
	if(left.kind == number && left.val.intconstE == 0) {
		if(right.kind == number) {
		result.kind = number;		
		result.val.intconstE = right.val.intconstE;
		}
		else {
		result.kind = string;
		result.val.idE = right.val.idE;
		}
		break;
	}

	/*basic evaluation */
	if(left.kind == string) {
		result.kind = string;
		if(right.kind == string) {
	 		sprintf(buffer, "%s + %s", left.val.idE, right.val.idE);
			result.val.idE = buffer;	
		}
		else {
			sprintf(buffer, "%s + %d", left.val.idE, right.val.intconstE);	
			result.val.idE = buffer;
		}
	}
	else if (right.kind == string) {
		result.kind = string;
		sprintf(buffer, "%d + %s", left.val.intconstE, right.val.idE);
		result.val.idE = buffer;
	}
	else {
	       result.kind = number;
		result.val.intconstE = left.val.intconstE + right.val.intconstE;
   	}      
        break;

    case minusK:

	left = evalEXP(e->val.plusE.left);
	right = evalEXP(e->val.plusE.right);

	/*identity: a-0 */
	if(right.kind == number && right.val.intconstE == 0) {
		if(left.kind == number) {
		result.kind = number;		
		result.val.intconstE = left.val.intconstE;
		}
		else {
		result.kind = string;
		result.val.idE = left.val.idE;
		}
		break;
	}

	/*basic evaluation */
	if(left.kind == string) {
		result.kind = string;
		if(right.kind == string) {
	 		sprintf(buffer, "%s - %s", left.val.idE, right.val.idE);
			result.val.idE = buffer;	
		}
		else {
			sprintf(buffer, "%s - %d", left.val.idE, right.val.intconstE);	
			result.val.idE = buffer;
		}
	}
	else if (right.kind == string) {
		result.kind = string;
		sprintf(buffer, "%d - %s", left.val.intconstE, right.val.idE);
		result.val.idE = buffer;
	}
	else {
	       result.kind = number;
		result.val.intconstE = left.val.intconstE - right.val.intconstE;
   	}   
	
        break;
    case modK:

	left = evalEXP(e->val.plusE.left);
	right = evalEXP(e->val.plusE.right);

	/*identity: a%1 */
	if(right.kind == number && right.val.intconstE == 1) {
		result.kind = number;
		result.val.intconstE = 0;
		break;
	}
	
	/*basic evaluation */	
	if(left.kind == string) {
		result.kind = string;
		if(right.kind == string) {
	 		sprintf(buffer, "%s %% %s", left.val.idE, right.val.idE);
			result.val.idE = buffer;	
		}
		else {
			sprintf(buffer, "%s %% %d", left.val.idE, right.val.intconstE);	
			result.val.idE = buffer;
		}
	}
	else if (right.kind == string) {
		result.kind = string;
		sprintf(buffer, "%d %% %s", left.val.intconstE, right.val.idE);
		result.val.idE = buffer;
	}
	else {
	       result.kind = number;
		result.val.intconstE = left.val.intconstE % right.val.intconstE;
   	}
   
        break;
    case powerK:

	left = evalEXP(e->val.powerE.left);
	right = evalEXP(e->val.powerE.right);

	/*identity: a^0 */
	if(right.kind == number && right.val.intconstE == 0) {
		result.kind = number;
		result.val.intconstE = 1;
		break;
	}
	
  	/*identity: a^1 */
  	if(right.kind == number && right.val.intconstE == 1) {
  		result = left;
    		break;
  	}

  	/*identity: 1^a */
  	if(left.kind == number && left.val.intconstE == 1) {
    		result = left;
    		break;
  	}

  	/*identity: 0^a */
  	if(left.kind == number && left.val.intconstE == 0) {
  		result = left;
    		break;
  	}
	
	/*basic evaluation */	
	if(left.kind == string) {
		result.kind = string;
		if(right.kind == string) {
	 		sprintf(buffer, "%s ^ %s", left.val.idE, right.val.idE);
			result.val.idE = buffer;	
		}
		else {
			sprintf(buffer, "%s ^ %d", left.val.idE, right.val.intconstE);	
			result.val.idE = buffer;
		}
	}
	else if (right.kind == string) {
		result.kind = string;
		sprintf(buffer, "%d ^ %s", left.val.intconstE, right.val.idE);
		result.val.idE = buffer;
	}
	else {
		result.kind = number;
		result.val.intconstE = (int)(pow(left.val.intconstE, right.val.intconstE));
   	}
   
        break;
        
    case absK:
    	right = evalEXP(e->val.absE.x);
    	if(right.kind == string) {
    		result.kind = string;
    		sprintf(buffer, "abs(%s)", right.val.idE);
		result.val.idE = buffer;
    	}
    	else {
    		result.kind = number;
    		result.val.intconstE = abs(right.val.intconstE);
    	}
    	break; 

    default: 
	printf("ERROR: Impossible type for an expression node.");
	result.kind = string;
	result.val.idE = "";
	break;

  }

free(buffer);
	
return result;

}
