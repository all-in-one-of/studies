function eat(food){
    return food + ' tasted really good.';
}
console.log(eat('bananas'));


 IIFE, Immediately Invoked Function Expression, is a common pattern for  
  creating local scopes example:  
   
         (function(){ // the function expression is surrounded by parenthesis  
             // variables defined here  
             // can't be accessed outside  
         })(); // the function is immediately invoked 