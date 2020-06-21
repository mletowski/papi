#ifndef  __info_h_
#define  __info_h_

/*  Exceptions and stream position information  */

#include  <string>

/*  Information about position in source file
    (grammar definition or data file).

    This is now defined as string, but it can be easily changed to <string, int, int>
    - tuple or structure, and refined in metagrammar.dp, where it is defined as single 
    string value.
 */   
using  Info = std::string;

/*  All exceptions thrown in the program belong to this class  */
struct   Exception
{
        std::string   message;              // textual information about the error
        std::string   toMessage() const { return message; };

        Exception( const char *msg ): message( msg ) {};
        Exception( std::string msg ): message( msg ) {}; 
};

#endif
