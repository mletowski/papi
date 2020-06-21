#include  "compiling.h"

/* Helper functions for compiling papi parsers */

/* Get info field from AST node - without type checking */
std::string  getInfo( const LisData &node )
{
        return  node.getList()[ 0 ].getString();
}

/* Get type tag from AST node - without type checking */
std::string  getTag( const LisData &node )
{
        return  node.getList()[ 1 ].getString();
}

/* Get string argument, checking the argument type and range.
 * Arguments counting is zero-based.
 */ 
std::string  getArg( const LisData &node, int index )
{
        auto l = node.getList();

        if ( int(l.size()) <= index + 2 )
        {
                throw  Exception( getInfo(node) + ": expecting argument " +
                        getTag( node ) + "[" + std::to_string( index ) + "]" );
        }

        if ( !l[ index + 2 ].isString() )
                throw   Exception( getInfo(node) + ": argument " +
                        getTag( node ) + "[" + std::to_string( index ) + 
                        "] is not a string" );
                                
        return  l[ index + 2 ].getString();
}

/* Get list argument, with type checking and range checking.
 * Arguments counting is zero-based.
 */ 
std::vector<LisData> getListArg( const LisData &node, int index )
{
        auto l = node.getList();

        if ( int(l.size()) <= index + 2 )
                throw  Exception( getInfo(node) + ": expecting argument @ " +
                        getTag( node ) + "[" + std::to_string( index ) + "]" );

        if ( !l[ index + 2 ].isList() )
                throw  Exception( getInfo(node) + ": argument " +
                        getTag( node ) + "[" + std::to_string( index ) + 
                        "] is not a list" );
                                
        return  l[ index + 2 ].getList();
}

/*  Check if the node is a list with Info string and with given name.
 *  If not, throw an exception
 */  
void  checkNode( const LisData &node, std::string name )
{
        if ( !node.isList() )
                throw  Exception( Info() + ": non-list data, expected node: " + 
                                name + ", got: " + node.getString() );

        if ( !node.isList(1) )
                throw  Exception( Info() + ": short list data, expected node: "
                                + name );

        if ( !node.getList()[ 0 ].isString() )
                throw  Exception( Info() + ": bad node: expected source info" );

        if ( !node.isList(2) )
                throw  Exception( getInfo(node) + ": node list too short" );

        if ( !node.getList()[ 1 ].isString() )
                throw  Exception( getInfo(node) + ": expected type tag '" + 
                                name + "'" );

        if ( getTag(node) != name )
                throw  Exception( getInfo(node) + ": expected type tag '" + 
                                name + "', got '" + getTag(node) + "'" );
}
