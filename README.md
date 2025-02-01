# MAT416_Isomorphism_Type_Enumerator
Enumerates the isomporphism types for simple graphs of a given size, optionally under certain constraints.

To compile and run (UNIX):
make
./iso_calculator -v <vertex count>

Usage:

iso_calculator [options]

Options:

-v num
Sets the vertex count to num vertices. The vertex count is the number of vertices for the isomorphism types to be enumerated.

-min num
Sets the minimum number of edges. All isomorphism types enumerated will have at least this many edges. If this number is less than zero, it will be ignored. It cannot exceed the maximum.

-max num
Sets the maximum number of edges. All isomorphism types enumerated will have at most this many edges. If this number is less than zero, it will be ignored. It cannot exceed the number of possible edges.

-e num1 num2
Equivalent to -min num1 -max num2.

-tex file
Enables LaTeX printing. The program will output LaTeX code to the given file.

-ts num
Sets the scale for the latex graph. "num" is a floating point value.

To run unit tests (UNIX):
make testing
./testing
