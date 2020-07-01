% Papi(1) Version 0.99 | Parsing and printing interpreter

NAME
====

**papi** - interpreter for user-defined parsers

SYNOPSIS
========

| **papi** \[options] _grammar-file_ _input-file_

Options
-------

-d

:  Debug mode, dumps parser stack even after parsing success

-g

:  Prints user grammar as JSON array

-h

:  Prints usage information

-j

:  Forces result output format to be JSON array

-m

:  Prints the papi metalanguage grammar in the form of limited JSON

-r

:  Prints the result in the form of a raw string

-s

:  Silent mode - do not dump parser stack after failure

DESCRIPTION
===========

Papi (Parsing And Printing Interpreter) is an interpreter of parsers for 
user-defined languages.  Grammar of user language is defined using notation 
based on PEG (Parsing Expression Grammars).  The notation is hereinafter 
referred to as the "papi metalanguage".

The command **papi grammar-file input-file** reads definition of user language
from _grammar-file_.  It is parsed by built-in parser of the papi metalanguage.

If this step is successful, the program reads text from _input-file_, 
parses it with the user parser obtained in the previous step, and if this step 
is also successful, the result will be printed on the output.  How it will be 
printed depends on the type of result and program options.  
If the result is a single string (and not a sequence or list) or when 
the **-r** option is used, it is treated as a raw string 
and printed directly on the output.  In turn, if it is not a string, 
or the **-j** option is used, the result is printed using JSON notation, 
limiting the notation to tables and strings.

If any of the steps fail, papi dumps the stack of parser that failed 
(metalanguage parser or user language parser),
saved when the parser reached the position farthest to the right.

Structure and operation of the papi parser
------------------------------------------

Both the parser of user grammar and
the user language parser used in the second phase are based on the same mechanism.
In fact, the grammar of the metalanguage is also written in the metalanguage itself.
It is available in the file "metagrammar.dp" in the program source.  
The line numbers used in the metalanguage parser error messages refer to this file.

The papi parser is based on modified PEG (Parsing Expression Grammars) formalism.
The original PEG formalism does not specify mechanisms for defining and passing
 data which is a result of parser operations.  For that purpose, papi utilises variables (written as identifiers prefixed with "$")
and templates describing the form of results.

Hence, the metalanguage uses two types of identifiers: production names (written as a sequence of digits and letters, starting from a letter) and variable names (starting from the "$").

Data types
----------

The data object in papi can be a string or a list, with the elements of the list
being objects.  

The parser, as understood by papi, is a procedure which reads input text data,
accepts them - and then it produces some result, or rejects them - and then there is no result.

The result of parser procedure is a sequence of objects - zero, one or more objects -
the sequence hence can be empty.  One should also note that the sequence is not the same as the list.
The list is a single object, with elements inside, and the sequence is a zero, one or more objects.

Lists and sequences in the metalanguage are denoted in different ways:

       Sequence  :       {object1, object2, ...}
       List      :       [object1, object2, ...]

The difference between them is that the sequence is not an object, so it can be
an element of another sequence nor some list.  If it is appended, it means that
all its elements are appended in turn:


       { "a", {"b", "c"} } = { "a", "b", "c" }
       [ "a", {"b", "c"} ] = [ "a", "b", "c" ]

The same rule does not apply to lists, because the list is a single
object that is indivisible:

       [ "a", ["b", "c"] ] = [ "a", ["b", "c"] ]
       { "a", ["b", "c"] } = { "a", ["b", "c"] }

Structure of grammar
--------------------

The grammar in papi consist of productions.  Each production has a unique name
and describes a parser.  Production called "goal" is an entry point to the grammar
and describes a parser which is the final product of parsing the grammar, i.e. the user parser.

The production consists of the name and one or more branches.
During execution of the procedure described by the production
the parser tries to pass full branch, one after another, until one of them is finished with success.

During execution of the procedure described by the production
the parser tries to finish one of the branches, one after another, until one of them is finished with success.
When all branches fail, the whole production procedure is considered failed - then there is no result.

The branches in the metalanguage code are separated by "|".
This corresponds to the operator of the alternative in PEG formalism.

Here is an example production with two branches  (note the comments starting with "#"):

        alnum = letter $c -> $c       # branch 1
              | digit $c -> $c        # branch 2

Repetition operators
--------------------

The branch of production consists of a series of parsing elements optionally 
equipped with a variable name.  Repetition operators are used to mark fragments of these series to be repeated zero, one or more times.  There are three kind of repetition operators, known from the ENBF notation, 
from regular expressions and from PEG:

        ( ... )?    - repeat zero or one time - in other words - "optionally"
        ( ... )*    - repeat zero or more times
        ( ... )+    - repeat one or more times

The repetition operators repeat its component parsers in a loop doing this as many times as it is possible.
If this succeeds, they collect the results in the variables which were declared inside.
In effect, each variable collects the sequences of results repeated as many times as the expression succeeds.
When used in the template, the sequences are restored with the same number of elements as collected in the parsing phase.

Prefix operators
----------------

In the metalanguage (similarly as in PEG) we have also prefix operators.
They are the negation operator "!" and the "&" predicate tag.
The negation and the predicate are described below when discussing 
parsing elements.

Templates
---------

What is to the right of the "->" arrow symbol is the template.
It is an expression consisting of variables (those that collect data
during parsing) and constants (strings written as in C or javascript),
possibly enclosed in  repetition operators that correspond to analogous ones
on the left side of the production.  

The repetition operators determine also the way in which the sequence of variable values is joined.
The way is selected depending on the type od used brackets:

        ( $a, "x", ... )*  - connecting to string
        { $a, "x", ... }*  - combining into a sequence
        [ $a, "x", ... ]*  - joining into a list

The variables in templates are also used in the scope of repetition operators "+" and "?", and prefix predicate tag "&":

        ($a, "x")*
        ($a, "x")+
        ($a, "x")?
        &($a, "x")

There is no need to use the negation operator "!" in the templates because negation 
produces no result.

Parsing elements
----------------

Here are the types of parsing elements that are defined in the papi metalanguage:

Call of production
:  Call of production is written as the called production name with optional variable name.
   The variable is a destination of the sequence of results.  For example:

        expr $x

Constant string
:  The constant is written as in "C" or javascript. 
   The execution of such element succeeds when the parser manages to read from input exactly the characters from the string.
   The variable name may be also optionally given after the string.
   Inside the literal one can use backslashed escape sequences "\\n", "\\r", "\\t" and
  "\\\"", "\\\\".  Such a details may be found in the definition of the metalanguage grammar in the file "metagrammarp.dp".
   Example:

        "The end\\n"  $footer

Any character
:  This basic parser accepts any character from input and fails at the end of the input file.  Example:

        . $ch

Character class
:  List of characters enclosed by "[" and "]".  Accepts any single character from the set.  Some characters
have to be escaped by backslash: "\\\[", "\\\]", "\\\\".  One can also use the "\\r" and "\\n" sequences.  Example:

        [0123456789] $digit

Predicate
:  Sequence of elements in parentheses preceded by "&".  The predicate executes all its components in turn and makes their results available (using the "&" operator in the template), but finally moves the reading pointer back to the starting position.
This is a notion derived from PEG.  It extends the meaning of the grammar class that can be created using this notation.  For example:

        &(name $n value $x)

Negation
:  Using the negation operator ("!") before an element we get the parser which works in a way opposite to the original one. 
At first, it tries to parse the data with its inner element, and then it inverts the decision - if the parsing succeeds it reverts the read pointer to the starting position and returns the false.  If not, it returns the success (the negation succeeds).  The negation never has meaningful data associated with its result, so the variable cannot be used.

FILES
=====

*metagrammar.dp* - Description of the language of metagramatics (metalanguage) written in the metalanguage itself.  This file is used in booststrap process to generate the parser of metagrammar in papi.

The current version does not use any configuration files nor environment variables.

