# Game-of-life

Usage:

./life < file > < t >
  
An input file <file> contains a description of the initial situation of the boards. The maximum execution time is <t>.
  
The input file follows this format:
 
<number of boards> <A> <B> <C> <D>
<name of board 1> <cel_1> <x1> <y1> <x2> <y2> ... <xcel_1> <ycel_1>
...
<name of board n> <cel_n> <x1> <y1> <x2> <y2> ... <xcel_n> <ycel_n>
  
A: Cell is born if there are A alive cells around it.
B: Cell is still alive next turn if there are more or equal than B alive cells around it.
C: Cell is still alive next turn if there are less or equal than C alive cells around it.
D: Board is DxD.
