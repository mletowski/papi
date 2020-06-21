#  This is an example file for papi.
#  Arithmetic with dc(1) 
#
#  Converts infix arithmetic expressions to reverse-polish
#  notation to be processed by dc(1)
#

#  entry point - sequence of commands.
#  examples:  x = 2*(300 - 1);  x;  x+2
goal = COMMAND $cmd (ow ";" COMMAND $cmds)* -> ( $cmd, "\n", ( $cmds, "\n" )* )

#  command is an expression, assignment, or special command ("print")
COMMAND = SPECIAL_COMMAND $c -> $c
        | VARIABLE $v ow "=" EXPRESSION $x   -> ($x, "s", $v)
        | EXPRESSION $x -> $x

SPECIAL_COMMAND = ow "print" -> "p"

#  variables are named by a single character, just as in dc(1), 
#  we use only letters and '_'
VARIABLE = ow [abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_] $v -> $v

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
     | VARIABLE $v                    -> ("l", $v)
    
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


