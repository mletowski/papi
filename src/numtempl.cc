#include  <iostream>
#include  "compiling.h"
#include  "numtempl.h"

std::string  print_path( VarPath path )
{
        std::string  s, separator;

        for ( auto it = path.begin(); it != path.end(); it++ ) 
        {
                s += separator + "$";

                s += std::to_string( *it );
                separator = ".";
        }

        return  s;
}

std::string  show( const NumTempl &tpl );

std::string  print_sequence( std::vector<NumTemplS> seq, char loopKind )
{
        std::string  s( "(" ), separator;

        for ( auto it: seq )
        {
                s += separator + show( (const NumTempl &)it );
                separator = " ";
        }

        return s += std::string(")") + (loopKind == ':' ? ' ': loopKind);
}

std::string  show( const NumTempl &tpl )
{
        switch ( tpl.index() )
        {
                case 0:
                        return "\"" + std::get<std::string>( tpl ) + "\"";
                case 1:
                        return  print_path( std::get<VarPath>( tpl ) ); 
                default:
                        return  print_sequence( std::get<NumTemplLoop>( tpl ).elements,
                                                std::get<NumTemplLoop>( tpl ).kind );
        }
}

std::string  getElementVarName( const LisData &e )
{
        const auto &tag = getTag( e );

        if  ( tag == "ElementCall" || tag == "ElementConst" || tag == "ElementClass" || tag == "ElementString" )
        {
                if ( e.getList().size() > 3 ) 
                        return  getArg( e, 1 );
        }
        else if ( tag == "ElementAnyChar" )
        {
                if ( e.getList().size() > 2 ) 
                        return  getArg( e, 0 );
        }

        return "";
}

/** 
   First, search for the name in the main level (ElementCall, ElementConst, ElementClass, ElementString), 
   counting scalars - when found, return $n, where n is a number.

   If we don't find the scalar, we look in the loop, checking the elements which are 
   itself loops - if we find the variable, we add the number n to the returned array.
**/
std::list<int>  getVariablePath( const std::string &varname, const LisData &rcpt )
{
        auto  l = rcpt.getList();
        int   n = 0;
        std::list<int>  result;

        for ( auto i = 0u; i < l.size()-2; i++ ) 
        {       
                const std::vector<LisData>  &arg = getListArg( rcpt, i );

                const auto &tag = getTag( LisData(arg) );

                std::string  name = getElementVarName( LisData(arg));

                if ( !name.empty() ) 
                {
                        if ( name == varname )
                                return  { n };
                        else 
                                n++; 
                }
        }

        n = 0;

        for ( auto i = 0u; i < l.size()-2; i++ ) 
        {       
                const  std::vector<LisData> &arg = getListArg( rcpt, i );

                const auto &tag = getTag( LisData(arg) );
                if  ( tag == "ElementLoop" )
                {
                       auto  num = getVariablePath( varname, 
                                       LisData(getListArg( LisData(arg), 1 )) );

                       if ( num.empty() ) 
                                n++;
                       else
                       {
                                num.push_front( n );
                                return num;
                       }   
                }
        }

        return {};
}

std::vector<NumTemplS>  numerateArguments( const LisData &tloop, 
                const LisData &rcpt, int depth )
{
        std::vector<NumTemplS>  nums;

        auto  l = tloop.getList();
        for ( auto  i = 2ul; i < l.size() - 2; i++ ) 
        {
                auto  nt = numerateTemplate( rcpt, 
                                LisData(getListArg( tloop, i )), depth );
                nums.push_back( nt );
        }

        return  nums;
}

NumTempl   numerateTemplate( const LisData &rcpt, const LisData &t, unsigned depth )
{
        /*  
            Template t has three variants:

            string   ->  { "Info", "TemplateConst", "data" }     
                -> NumTempl( string )

            variable ->  { "Info", "TemplateVariable", "name" }  
                -> NumTempl( std::vector<int> ) - variable path

            loop     ->  { "Info", "TemplateLoop", "kind", "type", ... } 
                -> NumTempl( std::vector<NumTemplS>, ... ) - loop

            This function calculates numbering based on variable positions
            found in the rcpt recipe.  

            The recipe rcpt is a context in which we determine the numbering.
            It has a form { "Info", "Receipt", ... Elements } 
         */
  
        if ( rcpt.invalid() )
                throw  Exception( "Internal error: invalid receipt object" );

        if ( t.invalid() )
                throw  Exception( "Internal error: invalid template object" );
        
        auto  info = getInfo( t );
        auto  tag = getTag( t );
        
        if ( tag == "TemplateConst" )
                return  NumTempl( getArg( t, 0 ) );
        else if ( tag == "TemplateVariable" )
        {
                auto  path = getVariablePath( getArg( t, 0 ), rcpt );
                if ( path.size() > depth+1 )
                {
                        throw  Exception( info + ": variable " +
                                        getArg( t, 0 ) + " is too deep (" + 
                                        std::to_string( path.size() ) +
                                        " - 1) for the template of depth " +
                                        std::to_string( depth ) );
                }
                else if ( path.empty() )
                        throw  Exception( info + ": variable " +
                                        getArg( t, 0 ) + " not found in receipt at " + 
                                        getInfo( rcpt ) );

                return  NumTempl( path );
        }
        else if ( tag == "TemplateLoop" )
        {
                auto  kind = getArg( t, 0 );
                bool  pseudoloop = (kind==":");

                auto  ts = getArg( t, 1 );
                LoopType  type;
                if ( ts == "sequence" )
                        type = LoopType::sequence;
                else if ( ts == "list" )
                        type = LoopType::list;
                else if ( ts == "string" )
                        type = LoopType::string;
                else
                        throw  Exception( getInfo(t) + " :bad template type: " + ts );

                return  NumTemplLoop( numerateArguments( t, rcpt, depth + (pseudoloop ? 0: 1) ), 
                                kind[0], type );
        }
        else 
                throw   Exception( info + ": bad template tag " + tag );
}

