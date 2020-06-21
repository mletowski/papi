 PAPI
======

Papi is a parser of user-defined languages.  The user specifies the language 
using notation, which is based on PEG (Parsing Expression Grammars).
Beside the grammar, the notation allows to define a form of result output.
In the second step papi parses the text coded in the language defined and
outputs the result basing on the templates.

 Compilation
-------------

Papi is written in C++.  Reasonably modern version of C++ compiler is sufficient
to compilation (the language version used is C++17).  No external dependencies 
are needed, the STL is enough.  Simply use ``make`` to compile the program.

 Documentation and examples
----------------------------

The user manual in the man(1) format is available in the ``docs/`` directory.
Several examples of grammars and data files are in ``examples/``.

 Author
--------

Marek Łętowski - letowski*(at)*gmail``( . )``com

 License
---------

The program is available under the MIT license (see the ``LICENSE`` file).
