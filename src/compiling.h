#ifndef  __compiling_h__
#define  __compiling_h__

#include  "info.h"
#include  "lisdata.h"
#include  "numtempl.h"
#include  "parser.h"

#include  <map>

using   GMap    = std::map<std::string, Parser<Info, std::vector<LisData>>*>;
using   IStack  = std::vector<int>;

/* Get info field from AST node - without type checking */
std::string  getInfo( const LisData& );

/* Get type tag from AST node - without type checking */
std::string  getTag( const LisData& );

/* Get string argument, checking the argument type and range.
 * Arguments counting is zero-based.
 */ 
std::string  getArg( const LisData&, int );

/* Get list argument, with type checking and range checking.
 * Arguments counting is zero-based.
 */ 
std::vector<LisData> getListArg( const LisData&, int );

/*  Check if the node is a list with Info string and with given name.
 *  If not, throw an exception
 */  
void  checkNode( const LisData&, std::string name );

std::string  getProductionName( LisData p );

std::string  show( const IStack& );

#endif
