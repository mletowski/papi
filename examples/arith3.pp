#  This is an example file for papi.
#  Arithmetic with dc(1) 
#
#  Converts infix arithmetic expressions to reverse-polish
#  notation to be processed by dc(1)
#

#  entry point - sequence of commands.
#  examples:  x = 2*(300 - 1);  x;  x+2
goal = COMMAND_SEQ $seq ow EOF -> $seq

#  command sequence, used in goal and in macro definition,
#  the commands are separated by semicolon, after the last one
#  the semicolon is optional
COMMAND_SEQ = COMMAND $cmd (ow ";" COMMAND $cmds)* (ow ";")?
        -> ( $cmd, "\n", ( $cmds, "\n" )* )

#  macro definition - used as value, which can be called with 
#  usual function call syntax:  f()
MACRO = ow "{" COMMAND_SEQ $cs ow "}" -> $cs

#  command is an expression, assignment, macro declaration, or special command ("print")
COMMAND = SPECIAL_COMMAND $c -> $c
        | VARIABLE $v FUNCALL_OP MACRO $m    -> ("[", $m, "]s", $v)
        | VARIABLE $v ow "=" EXPRESSION $x   -> ($x, "s", $v)
        | EXPRESSION $x -> $x

EOF = !. -> {}

FUNCALL_OP = ow "(" ow ")" -> {}

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
     | VARIABLE $v FUNCALL_OP         -> ("l", $v, "x")
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


