#include  "grammar.h"
#include  "compiling.h"

#include  <cstdlib>
#include  <cstring>
#include  <fstream>        
#include  <iostream>
#include  <set>
#include  <unistd.h>

Parser<Info, TRow>  compileReceipt( GMap &map, LisData r, 
                std::set<std::string> &needed_productions, 
                std::set<std::string> &declared_variables );

Parser<Info, std::vector<LisData>>  compileScalarElement( GMap &map, LisData elem );

Executor  compileNumeratedTemplate( const NumTempl &nt );

/*  If vp contains exactly one element, this is a number of scalar, and then
 *  findSelectedRow() returns exactly r.  This scalar will then be selected from r.
 *  If there are some other numbers in vp (despite the last element, which is
 *  always a number of scalar), they are row indexes in next tables.
 */
TRow *findSelectedRow( TRow *r, const VarPath &vp, const IStack &ind )
{
        TRow *selected = r;

        auto it = vp.begin();
        auto iit = ind.begin();

        while ( true )
        {
                auto next = it;
                next++;

                if ( next == vp.end() ) 
                        break;

                auto  indt = *it++;
                auto  &table = selected->tables[ indt ];
                auto  ind0 = *iit++;

                try {
                        selected = &table.at( ind0 );
                }
                catch ( const std::out_of_range& )
                {
                        return  nullptr;
                }
        }

        return  selected;
}

std::string  makeString( const std::vector<LisData> &sequence )
{
        std::string  s;

        for ( auto x: sequence ) 
                s += x.getString();

        return s;
}

std::string  show( const IStack &p )
{
        std::string  s( "[" ), sep;
        for ( auto it: p )
        {
                s += sep + std::to_string(it);
                sep = ",";
        }

        return s + "]";
}

Executor   compileTemplateVariable( VarPath vp )
{
        int  index = vp.back();

        return  Executor{ NumTemplS(vp), 
                [vp, index]( TRow r, IStack ind ) 
                {
                        TRow *cr = findSelectedRow( &r, vp, ind );

                        return  cr ? ExecutorResult{ 
                                        unsigned(vp.size()-1), 
                                        {cr->fields.at( index )} 
                                }: ExecutorResult{ 0, {} };
                }};
}

Executor  buildListExecutor( const NumTemplLoop &ntl, 
                const std::vector<Executor> &executors )
{
        /* Pseudoloop, or in other words "block instruction" */
        if ( ntl.kind==':' )
                return  Executor{ NumTempl{ntl}, 
                        [executors]( TRow r, IStack ist ) -> ExecutorResult
                        {
                                std::vector<LisData>  result;
                                bool  started = false;
                                unsigned  max_depth = 0;

                                for ( auto ex: executors )
                                {
                                        ExecutorResult x = ex.fun( r, ist );

                                        if ( x.depth >= ist.size() ) 
                                                started = true;

                                        result.insert( result.end(), 
                                                        x.data.begin(), 
                                                        x.data.end() );

                                        max_depth = std::max( max_depth, x.depth );
                                }

                                if ( started )
                                        return  ExecutorResult{ max_depth, 
                                                        {LisData(result)} };
                                else
                                        return  ExecutorResult{ 0, {LisData({})} };
                        }};
        else
        {
                char  kind = ntl.kind;

                return  Executor{ NumTempl{ntl}, 
                        [executors, kind]( TRow r, IStack ist ) -> ExecutorResult
                        {
                                bool   started = false;
                                unsigned  maxd = 0;

                                std::vector<LisData>  result;

                                for ( int i=0;; i++ )
                                {
                                        int  number_of_values = 0;

                                        IStack  ist1 = ist;
                                        ist1.push_back( i );

                                        std::vector<LisData>  row_result;

                                        for ( auto ex: executors )
                                        {
                                                std::optional<ExecutorResult> x;
                                                x = ex.fun( r, ist1 );

                                                if ( x ) {
                                                        if ( x->depth >= ist1.size() ) 
                                                        {
                                                                number_of_values++;
                                                                started = true;
                                                        }

                                                        row_result.insert( 
                                                               row_result.end(), 
                                                               x->data.begin(), 
                                                               x->data.end() );

                                                        maxd = std::max(maxd, x->depth);
                                                }
                                        }

                                        if ( !number_of_values )
                                        {
                                                if ( started )
                                                        return  ExecutorResult{ maxd, 
                                                                    {LisData(result)} };
                                                else
                                                        return  ExecutorResult{0, {}};
                                        }

                                        result.insert( result.end(), 
                                                        row_result.begin(), 
                                                        row_result.end() );
                                }

                                return  ExecutorResult{ maxd, {LisData(result)} };
                        }};
        }
}

Executor  buildSequenceExecutor( const NumTemplLoop &ntl, 
                const std::vector<Executor> &executors )
{
        if ( ntl.kind==':' ) /* Pseudoloop, ie "block instruction" */
                return  Executor{ NumTempl{ntl}, 
                        [executors]( TRow r, IStack ist ) -> ExecutorResult
                        {
                                std::vector<LisData>  result;
                                bool  started = false;
                                unsigned  maxd = 0;

                                for ( auto ex: executors )
                                {
                                        ExecutorResult x = ex.fun( r, ist );

                                        if ( x.depth >= ist.size() ) 
                                                started = true;

                                        result.insert( result.end(), 
                                                        x.data.begin(), x.data.end() );

                                        maxd = std::max( maxd, x.depth );
                                }

                                if ( started )
                                        return  ExecutorResult{ maxd, result };
                                else
                                        return  ExecutorResult{ 0, {} };
                        }};
        else
        {
                char  kind = ntl.kind;

                return  Executor{ NumTempl{ntl}, 
                        [executors, kind]( TRow r, IStack ist ) -> ExecutorResult
                        {
                                bool   started = false;
                                unsigned  maxd = 0;

                                std::vector<LisData>  result;

                                for ( int i=0;; i++ )
                                {
                                        int  number_of_values = 0;

                                        IStack  ist1 = ist;
                                        ist1.push_back( i );

                                        std::vector<LisData>  row_result;

                                        for ( auto ex: executors )
                                        {
                                                std::optional<ExecutorResult> x = 
                                                        ex.fun( r, ist1 );

                                                if ( x ) {
                                                        if ( x->depth >= ist1.size() ) 
                                                        {
                                                                number_of_values++;
                                                                started = true;
                                                        }

                                                        row_result.insert( 
                                                                row_result.end(), 
                                                                x->data.begin(), 
                                                                x->data.end() );

                                                        maxd = std::max( maxd, x->depth );
                                                }
                                        }

                                        if ( !number_of_values )
                                        {
                                                if ( started )
                                                        return  ExecutorResult{ maxd, result };
                                                else
                                                        return  ExecutorResult{0, {}};
                                        }

                                        result.insert( result.end(), 
                                                       row_result.begin(), 
                                                       row_result.end() );
                                }

                                return  ExecutorResult{ maxd, result };
                        }};
        }
}

Executor  buildStringExecutor( const NumTemplLoop &ntl, 
                const std::vector<Executor> &executors )
{
        if ( ntl.kind==':' ) /* Pseudoloop, or "block instruction" */
                return  Executor{ NumTempl{ntl}, 
                        [executors]( TRow r, IStack ist ) -> ExecutorResult
                        {
                                std::string  result;
                                unsigned  max_depth = 0;

                                for ( auto ex: executors )
                                {
                                        ExecutorResult x = ex.fun( r, ist );
                                        result += makeString( x.data );
                                        max_depth = std::max( max_depth, x.depth );
                                }

                                return  ExecutorResult{ max_depth, {LisData(result)} };
                        }};
        else
        {
                char  kind = ntl.kind;

                return  Executor{ NumTempl{ntl}, 
                        [executors, kind]( TRow r, IStack ist ) -> ExecutorResult
                        {
                                unsigned  maxd = 0;

                                std::string  result;

                                for ( int i=0;; i++ )
                                {
                                        int  number_of_values = 0;

                                        IStack  ist1 = ist;
                                        ist1.push_back( i );

                                        std::string  row_result;

                                        for ( auto ex: executors )
                                        {
                                                std::optional<ExecutorResult> x = 
                                                        ex.fun( r, ist1 );

                                                if ( x ) {
                                                        if ( x->depth >= ist1.size() ) 
                                                                number_of_values++;

                                                        row_result += makeString( x->data );

                                                        maxd = std::max( maxd, x->depth );
                                                }
                                        }

                                        if ( !number_of_values )
                                                return  ExecutorResult{ maxd, {LisData(result)} };

                                        result += row_result;
                                }

                                return  ExecutorResult{ maxd, {LisData(result)} };
                        }};
        }
}


Executor  compileTemplateLoop( const NumTemplLoop &ntl )
{
        std::vector<Executor>  executors;

        for ( auto e: ntl.elements )
        {
                Executor  ex = compileNumeratedTemplate( e );
                executors.push_back( ex );
        }

        switch ( ntl.type ) 
        {
                case  LoopType::list:
                        return  buildListExecutor( ntl, executors );
                case  LoopType::string:
                        return  buildStringExecutor( ntl, executors );
                case  LoopType::sequence:
                        return  buildSequenceExecutor( ntl, executors );
                default:
                        throw   Exception( "unknown template loop type" );
        }
}


Executor  compileNumeratedTemplate( const NumTempl &nt )
{
        std::string  s;

        switch ( nt.index() ) 
        {
                case 0:
                        s = std::get<std::string>( nt );
                        return Executor{ nt, [s](TRow, IStack) {
                                return  ExecutorResult{0, std::vector{LisData(s)}};
                        }};
                case 1: 
                        return  compileTemplateVariable( std::get<VarPath>( nt ) );
                case 2:
                        return  compileTemplateLoop( std::get<NumTemplLoop>( nt ) );
                default:
                        throw   Exception( Info() + ": bad numerated template variant" );
        }
}

Executor   compileTemplate( LisData rcpt, LisData t )
{
        auto  nt = numerateTemplate( rcpt, t, 0 );
        return  compileNumeratedTemplate( nt );
}

TRow  appendSubtable( TRow r, TTable t )
{
        TRow  newRow = r;
        newRow.tables.push_back( t );
        return  newRow;
}

Parser<Info, TTable>  compileLoopTable( GMap &map, LisData loop, 
                std::set<std::string> &needed_productions,
                std::set<std::string> &declared_variables )
{
        std::string kind = getArg( loop, 0 );

        char  LoopType = kind.size()==1 ? kind[0]: 0;

        Parser<Info, TRow>  rowparser = 
                compileReceipt( map, LisData(getListArg( loop, 1 )),
                                needed_productions, declared_variables );

        switch ( LoopType ) 
        {
                case '+':
                case '*':
                        {
                                auto  vp = pLoop( LoopType, rowparser );

                                return  [vp]( ParserState<Info> &ps ) -> std::optional<TTable> 
                                {
                                        auto r = vp( ps );
                                        if ( r ) 
                                                return  TTable( *r );
                                        else
                                                return  std::optional<TTable>();
                                };
                        }
                        break;
                case '!': 
                        {
                                auto  np = pNot( rowparser );

                                return  [np]( ParserState<Info> &ps ) -> std::optional<TTable>
                                {
                                        auto r = np( ps );
                                        
                                        if ( r ) 
                                                return  TTable();
                                        else 
                                                return  std::optional<TTable>();
                                };
                        }
                        break;
                case '&': 
                        {
                                auto  vp = pPredicate( rowparser );

                                return  [vp]( ParserState<Info> &ps ) -> std::optional<TTable>
                                {
                                        auto r = vp( ps );
                                        
                                        if ( r ) 
                                        {
                                                TTable  t;      
                                                t.push_back( *r );
                                                return  t;
                                        }
                                        else 
                                                return  std::optional<TTable>();
                                };
                        }
                        break;
                case '?':
                        {
                                auto  vp = pOpt( rowparser );

                                return  [vp]( ParserState<Info> &ps ) -> std::optional<TTable>
                                {
                                        auto r = vp( ps );
                                        
                                        if ( r ) 
                                        {
                                                if ( *r ) 
                                                {
                                                        TTable  t;      
                                                        t.push_back( **r );
                                                        return  t;
                                                }
                                                else
                                                        return  TTable();
                                        }

                                        /* impossible - pOpt always succeedes */
                                        return  TTable();
                                };      
                        }
                default:
                        throw  Exception( getInfo(loop) + ": bad loop type tag: " + kind );
        }
                        
        throw  Exception( getInfo(loop) + ": bad loop type tag: " + kind );
}


TRow  noOperation( TRow r, std::vector<LisData> x )
{
        return r;
}

TRow  appendScalar( TRow r, std::vector<LisData> x )
{
        TRow  newRow = r;
        newRow.fields.push_back( x );
        return  newRow;
}

static bool  elemHasName( LisData elem )
{
        auto  l = elem.getList();
        bool  ret = (l.size() > 3 || (l.size() > 2 && getTag(elem)=="ElementAnyChar"));
        return  ret;
}

std::string  getProductionName( LisData p )
{
        checkNode( p, "Production" );
        
        if ( p.getList().size() < 3 )
                throw  Exception( getInfo(p) + ": expected produciton name" );

        return  p.getList()[2].getString();
}

bool  isScalarElement( LisData elem )
{
        if ( !elem.isList() ) return false;

        try {
                checkNode( elem, "ElementLoop" );
        }
        catch ( const Exception& )
        {
                return  true;
        }

        return  false;
}


Parser<Info, std::vector<LisData>>  compileScalarElement( GMap &map, LisData elem, 
                std::set<std::string> &needed_productions )
{
        std::string  tag = getTag( elem );

        if ( tag == "ElementCall" )
        {
                auto  name = getArg(elem, 0);

                std::function<Parser<Info, std::vector<LisData>>*()> parser = 
                [&map, name]()
                {
                        /*  Do not catch std::out_of_range here, it should be 
                         *  treated as severe error, since we intend 
                         *  to check the names during compilation.
                         */
                        return  map.at( name );
                };        

                needed_productions.insert( name );
                return  pCallParser( getInfo( elem ), parser );
        }
        else if ( tag == "ElementConst" )
        {
                return  pConst( getInfo( elem ), std::vector{LisData(getArg(elem, 0))} );
        }  
        else if ( tag == "ElementClass" )
        {
                std::string  s = getArg( elem, 0 );

                return  pFun( pConditional( anyChar( getInfo(elem) ), 
                                        std::function([s]( char c ) -> bool
                                        {
                                                bool ret = strchr( s.c_str(), c );
                                                return ret;
                                        }) ), 

                                        std::function([]( char c ) -> std::vector<LisData>
                                        {
                                                return  {LisData( std::string( 1, c ) )};
                                        }) );    
        }  
        else if ( tag == "ElementString" )
        {
                std::string  s = getArg( elem, 0 );

                return  pFun( pString( getInfo(elem), s ), 
                                std::function([]( std::string s ) -> std::vector<LisData>
                                        {
                                                return  {LisData( s )};
                                        }) );
        }
        else if ( tag == "ElementAnyChar" )
        {
                return  pFun( anyChar( getInfo( elem ) ), 
                             std::function<std::vector<LisData>(char)>(
                                     []( char c ) -> std::vector<LisData>
                                     {
                                        char s[2] = {c, '\0'};

                                        return  {LisData(std::string( s ))};
                                     }) );
        }
        else if ( tag == "ElementNegation" )
        {
                return  pFun( pNot( compileScalarElement( 
                               map, LisData(getListArg( elem, 0 )),
                               needed_productions )), 

                               std::function([]( bool ) -> std::vector<LisData>
                               {
                                     return  {};
                               }) );
        }  
        else throw Exception( getInfo(elem) + ": expected scalar element, got '" + tag + "'" );

        throw  Exception( getInfo(elem) + ": Not implemented tag: " + tag );
}
                        

Parser<Info, TRow>  compileReceipt( GMap &map, LisData r, 
                std::set<std::string> &needed_productions, 
                std::set<std::string> &declared_variables )
{
        Parser<Info, TRow>  result = pConst( getInfo(r), TRow() );
        std::function<TRow(TRow, std::vector<LisData>)>  reducer;

        checkNode( r, "Receipt" );

        auto l = r.getList();
       
        for ( auto it = l.begin() + 2; it != l.end(); it++ ) 
        {
                if ( isScalarElement( *it ) )
                {
                        Parser<Info, std::vector<LisData>>  p = 
                                compileScalarElement( map, LisData(*it), needed_productions );

                        if ( elemHasName( *it ) )
                        {
                                std::string  name = getElementVarName( *it );

                                if ( declared_variables.count( name ) )
                                        throw  Exception( getInfo(*it) + ": duplicated variable " + name );
                                else
                                        declared_variables.insert( name );

                                reducer = appendScalar;
                        }
                        else
                                reducer = noOperation;

                        result = pAnd( result, p, reducer );
                }
                else 
                {
                        Parser<Info, TTable>  p = 
                                compileLoopTable( map, *it, needed_productions, declared_variables );
                        result = pAnd( result, p, appendSubtable );
                }
        } 

        return  result;
}


Parser<Info, std::vector<LisData>>  compileBranch( GMap &map, LisData branch, 
                std::set<std::string> &needed_productions )
{
        checkNode( branch, "Branch" );

        if ( branch.getList().size() != 4 )
                throw  Exception( getInfo(branch) + ": bad branch definition, list length = " + 
                                std::to_string( branch.getList().size() ));

        LisData rcpt( getListArg( branch, 0 ));
        LisData tpl( getListArg( branch, 1 ));

        std::set<std::string>  declared_variables;

        auto  ttparser = compileReceipt( map, rcpt, needed_productions, declared_variables );
        Executor  tplfun = compileTemplate( rcpt, tpl );

        auto  parser = 
        [ttparser, tplfun]( ParserState<Info> &state ) -> std::optional<std::vector<LisData>>
        {
                auto  row = ttparser( state );
                if ( row ) 
                {
                        auto  r = tplfun.fun( *row, {} );
                        return  r.data;
                }
                else
                        return  std::optional<std::vector<LisData>>();
        };

        return  parser;
}


Parser<Info, std::vector<LisData>>  *compileProduction( GMap &map, LisData p, 
                std::set<std::string> &needed_productions )
{
        checkNode( p, "Production" );

        Parser<Info, std::vector<LisData>>  *result = new Parser<Info, std::vector<LisData>>;
        bool   first = true;

        auto   l = p.getList();
        if ( l.size() < 3 )
                throw  Exception( getInfo(p) + ": the list too short, production expected" );

        auto   it = l.begin();
        it += 3;

        while ( it != l.end() )
        {
                if ( first )
                {
                        *result = compileBranch( map, *it, needed_productions );
                        first = false;
                }
                else
                {
                        auto  next = compileBranch( map, *it, needed_productions );
                        *result = pOr( *result, next );
                }

                ++it;
        } 

        return  result;
}


const GMap &compileGrammar( GMap &map, LisData g, 
                const char *grammar_filename, const char *input_filename )
{
        std::set<std::string>  needed_productions;
        checkNode( g, "Grammar" );

        auto  gr = g.getList();  

        int  n_productions_compiled = 0;

        for ( auto it = gr.begin() + 2; it != gr.end(); it++ ) 
        {
                std::string  name = getProductionName( *it );
                Parser<Info, std::vector<LisData>>  *production = 
                        compileProduction( map, *it, needed_productions );
                
                if ( map.count(name) )
                        throw  Exception( getInfo(*it) + ": production '" + name 
                                        + "' already defined" );

                map[ name ] = production;
                n_productions_compiled++;
        }

        map[ "::input" ] = compileProduction( map, {INF, "Production", "::input", 
                        {INF, "Branch", 
                        {INF, "Receipt", 
                        {INF, "ElementConst", ""}}, 
                        {INF, "TemplateConst", input_filename}}}, needed_productions );

        auto  uint_to_vec = std::function([]( unsigned n ) -> std::vector<LisData>
        {
             std::string  s = std::to_string( n );
             return  std::vector<LisData>{ LisData(s) };
        });

        Parser<Info, std::vector<LisData>> *ptr = new Parser<Info, std::vector<LisData>>();

        *ptr = pFun<Info, unsigned, std::vector<LisData>>( pInputLine<Info>(), uint_to_vec );

        map[ "::line" ] = ptr;

        ptr = new Parser<Info, std::vector<LisData>>();

        *ptr = pFun<Info, unsigned, std::vector<LisData>>( pInputColumn<Info>(), uint_to_vec );

        map[ "::column" ] = ptr;

        for ( const auto &name: needed_productions )
        {
                if ( !map.count(name) )
                        throw  Exception( std::string(grammar_filename) + ": production name '" + name 
                                        + "' used in grammar, but never defined" );
        }

        return  map;
}


int  run_grammar( const LisData &grammar, const char *input_filename )
{
        ParserState<Info> *ps = nullptr;

        try {
                ps = new ParserState<Info>( new std::ifstream(input_filename) );

                GMap  parsers;
                compileGrammar( parsers, grammar, "internal metagrammar", input_filename );

                auto  p = *parsers.at("goal");
                std::optional<std::vector<LisData>>  r = p( *ps );

                if ( r ) 
                {
                        std::string  s;

                        try {
                                s = "Success: '";
                                for ( auto x: *r )
                                        s += x.getString();
                                s += "'\n";

                                std::cout << s;
                        }
                        catch ( const std::bad_variant_access& )
                        {
                                std::cout << "Success:\n";
                                for ( auto x: *r )
                                        std::cout << "   " << show( x ) << '\n';
                        }
                }
                else
                        std::cout << "Failure\n";

                for ( auto it: ps->getInfo() )
                {
                        std::cout << "(at grammar in " << it.first << 
                                "), at file in: " << it.second.pos << 
                                " [line " << it.second.line << ": column " << 
                                it.second.column << ']' << '\n';
                }
        }
        catch ( const Exception &e )
        {
                std::cout << e.toMessage() << '\n';
                return 1;
        }
        catch ( const RuntimeError &e )
        {
                std::cout << "\nParser execution error: " << e.what << '\n';
                return 2;
        }
        catch ( const std::exception &e )
        {
                std::cout << "\nException " << typeid(e).name() << ":" << e.what() << '\n';

                for ( auto it: ps->getInfo() )
                {
                        std::cout << "(at grammar in " << it.first << 
                                "), at file in: " << it.second.pos << 
                                " [line " << it.second.line << ": column " << 
                                it.second.column << ']' << '\n';
                }
                return 1;
        }
        
        return 0;
}
