#  This is an example file for papi.
#  Arithmetic with dc(1) 
#
#  Converts infix arithmetic expressions to reverse-polish
#  notation to be processed by dc(1)
#

#  entry point - infix aritmetic expression
#  examples:  10-2, (2 - 1) * (10*(3-2-1))
goal = EXPRESSION $x -> ($x, "\np\n" )

#  optional white space:
ow = ([ \t\r\n])* -> {}

#  minus sign is converted to "_" for dc
MINUS = ow "-" -> "_"

#  number in decimal notation, with optional fractional part.
NUMBER = (MINUS $minus)? ow ([0123456789] $digit)+ ("." ([0123456789] $frac)+ )? 
     -> (($minus)?, ($digit)+ , (".", ($frac)+)?)

#  factor - single number or expression in parentheses
FACTOR = NUMBER $x                    -> $x
     | ow "(" EXPRESSION $x ow ")"    -> $x
    
#  high priority arithmetic operators
MUL = ow [/*] $op -> $op

#  multiplication or division
PRODUCT = FACTOR $x (MUL $op FACTOR $y)* 
     -> ($x, " ", ($y, " ", $op, " ")* )

#  top level arithmetic expression
EXPRESSION = PRODUCT $x (ADD $op PRODUCT $y)*
     -> ($x, " ", ($y, " ", $op, " ")* )

#  low priority operators
ADD = ow [+-] $op -> $op

