# Grammar
It's console calculater. The basis is Interpreter pattern.  
Functions:  
add(arg1,arg2);  
sub(arg1,arg2);  
div(arg1,arg2);  
mult(arg1,arg2);  
let(var,value,expression);  

Examples:  

  |  Input                             | output |
  |------------------------------------|:------:|
  |"add(5,7)"                          | 12     |    
  |"div(sub(add(-5,7),mult(3,-2)),2)"  | 4      |  	 
  |"let(x,4.3,add(-4,x))"              | 0.3    |  	 
  |"mult(let(y,sub(1,5),div(y,8)),5)"  | -2.5   |    
 																		  	


class Context store variables and its values.  
class FuncExp2nd give analysise of string and calculate functions with two args.  
class FuncExp3nd give analysise of string and calculate let function.  
