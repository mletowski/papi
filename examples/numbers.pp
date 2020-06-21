#! ./papi

digit = [0123456789] $c -> $c
number = (digit $c)+ -> ($c)+
w = [ \t\r\n] $c -> $c

goal = ((w)* number $x)+ -> { $x, "\n" }+
