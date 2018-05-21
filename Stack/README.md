The structure of this directory is:

file "README.md"
file "stack.h"
directory "example"
	file "README.md"
	file "example.cpp"
	file "Makefile"

"stack.h" has constructed a stack template class named "Stack". It has realised following functions:

* Use "Stack<DataType> A;" to define a empty Stack A;
* Use "Stack<DataType> A(B);" or "Stack<DataType> A = B;" to define a Stack A and initialize it by B;
* Use "A.push(x)" to push element x into Stack;
* Use "A.top()" get the element on the top of A (But don't delete the top element of A);
* Use "x = A.pop()" to pop out the top element of A and recieve it by x;
* Use "A = B" to clone Stack A to Stack B;
* Use "A.empty()" to judge if Stack A is empty;
* Use "A.length()" to get the number of elements in Stack A;
* Use "A.inverse()" to reverse Stack A;
* Use "A.clear()" to clear Stack A's memory.

There is an example program in "./examples/". You can compile the example by the guiding of "./example/README.md".

The object to build this Stack class is to parsing math expression from string.
In the class "MathFunc"(defined in "../MathFunc/"), the processes of converting infix expression to postfix expression and calculate the value of expression have both used class "Stack".