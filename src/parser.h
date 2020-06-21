#ifndef  __parser_h__
#define  __parser_h__

#include  <functional>
#include  <iostream>
#include  <istream>

#define   HARD_STACK_LIMIT        1800

struct  RuntimeError {
        std::string  what;
        RuntimeError( std::string err ): what( err ) {};
};

template<typename Info>
class  ParserState;

template  <typename Info, typename T>
using  Parser = std::function< std::optional<T>( ParserState<Info> & )>;

template<typename Info>
class  ParserState
{
        public:
                /* Input stream position */
                struct  position {
                        /* Underlying stream position */
                        std::istream::pos_type   pos;

                        /* Line numers start from 1 */
                        unsigned                line;

                        /* Column numbers start from 1 */
                        unsigned               column;

                        position(): pos( 0 ), line( 1 ), column( 1 ) {};

                        void  count_char( char c, auto newpos )
                        {
                                pos = newpos;

                                if ( c == '\n' )
                                {
                                        column = 1;
                                        line++;
                                }
                                else
                                        column++;
                        }

                };

                ParserState(): data( nullptr ) {};
                ParserState( std::istream &ins ): data( &ins ) {};
                ParserState( std::istream *ins ): data( ins ) {};

                char  getch()
                {
                        char c = data->get();
                        cursor.count_char( c, data->tellg() );
                        return c;
                }

                char  peek()
                {
                        return  data->peek();
                }

                void  push( Info info )
                {
                        if ( stack.size() >= HARD_STACK_LIMIT ) 
                                throw  RuntimeError( "Stack overflow error" );

                        stack.push_back( {info, cursor} );

                        if ( max_stack.empty() || 
                                        max_stack.back().second.pos < cursor.pos )
                                max_stack = stack;
                }

                void  pop()
                {
                        stack.pop_back();
                }

                const std::vector<std::pair<Info, position>> &getInfo() const 
                {
                        return  max_stack;
                }
                
                std::pair<size_t, position>  save() const
                {
                        return  {stack.size(), cursor};
                }

                std::string  show_state() const 
                {
                        std::string  s("(");
                        s += std::to_string( stack.size() ) + "," +
                                std::to_string( cursor.pos ) + "=(" +
                                std::to_string( cursor.line ) + ":" +
                                std::to_string( cursor.column ) + ")";

                        return s + ")";
                }

                void  restore( std::pair<size_t, position> state )
                {
                        stack.resize( state.first );
                        cursor = state.second;
                        data->clear();

                        if ( cursor.pos >= 0 )
                                data->seekg( cursor.pos );
                        else if ( cursor.pos == EOF )
                                data->seekg( 0, std::ios_base::end );
                }

                bool  eof() const
                {
                        return  data ? data->eof(): true;
                };

        private:
                position  cursor;
                std::istream *data;
                std::vector<std::pair<Info, position>>  stack;
                std::vector<std::pair<Info, position>>  max_stack;
};

template  <typename Info>
Parser<Info, char>   anyChar( Info info )
{
        return  [info]( ParserState<Info> &ps ) -> std::optional<char>
        {
                char  ret = ps.getch();

                if ( ps.eof() || ret==EOF ) {
                        return  std::optional<char>();
                }

                ps.push( info );
                ps.pop();

                return  ret;
        };
}

template  <typename Info>
Parser<Info, char>   aChar( Info info, char x )
{
        return  [info, x]( ParserState<Info> &ps ) -> std::optional<char>
        {
                auto  ret = ps.peek();

                if ( ret == x )
                {
                        ps.getch();
                        ps.push( info );
                        ps.pop();
                        return  ret;
                }
                        
                return  std::optional<char>();
        };
}

template  <typename Info, typename T>
Parser<Info, T>   pOr( Parser<Info, T> p1, Parser<Info, T> p2 )
{
        return  [p1, p2]( ParserState<Info> &ps ) -> std::optional<T>
        {
                auto  r = p1( ps );
                if ( r )
                        return r;
                return  p2( ps );
        };
}

template  <typename Info, typename T>
Parser<Info, T>      pConst( Info info, T data )
{
        return  [info, data]( ParserState<Info> &ps ) -> std::optional<T>
        {
                ps.push( info );
                ps.pop();
                return  data;
        };
}

template  <typename Info, typename T>
Parser<Info, bool>   pNot( Parser<Info, T> p )
{
        return  [p]( ParserState<Info> &ps ) -> std::optional<bool>
        {
                auto  state = ps.save();
                auto  r = p( ps );
                if ( r ) {
                        ps.restore( state );
                        return std::optional<bool>();
                }

                return  true;
        };
}

template  <typename Info, typename A, typename T>
Parser<Info, T>   pFun( Parser<Info, A> a, std::function<T(A)> fun )
{
        return  [a, fun] ( ParserState<Info> &ps ) -> std::optional<T>
        {
                auto  r = a( ps );

                if ( r ) 
                {
                        auto  fres = fun( *r );
                        return  fres;
                }
                else return  std::optional<T>();
        };
}

template  <typename Info, typename A, typename B, typename T>
Parser<Info, T>   pAnd( Parser<Info, A> a, Parser<Info, B> b, 
                std::function<T(A, B)> combine )
{
        return  [a, b, combine]( ParserState<Info> &ps ) -> std::optional<T>
        {
                auto  state = ps.save();
                auto  r1 = a( ps );

                if ( r1 ) 
                {
                        auto  r2 = b( ps );

                        if ( r2 ) 
                                return  combine(*r1, *r2);
                        else
                                ps.restore( state );
                }

                return  std::optional<T>();
        };
}

template  <typename Info, typename A, typename B, typename T>
Parser<Info, T>   pAnd( Parser<Info, A> a, Parser<Info, B> b, T (*combine)(A,B) )
{
        return  pAnd<Info, A, B, T>( a, b, std::function<T(A,B)>( combine ) );
}

template  <typename Info, typename T>
Parser<Info, T>   pPredicate( Parser<Info, T> p )
{
        return  [p]( ParserState<Info> &ps ) -> std::optional<T>
        {
                auto  state = ps.save();
                auto  r = p( ps );

                if ( r )
                        ps.restore( state );

                return r;
        };
}

template  <typename Info, typename T>
Parser<Info, T>   pConditional( Parser<Info, T> p, 
                std::function<bool(T)> condition )
{
        return  [p, condition]( ParserState<Info> &ps ) -> std::optional<T>
        {
                auto  state = ps.save();
                auto  r = p( ps );
                if ( r && !condition( *r ) )
                {
                        ps.restore( state );
                        return std::optional<T>();
                }
                else  
                        return r ? r: std::optional<T>();
        };
}

template  <typename Info, typename T>
Parser<Info, T>   pCallParser( Info info, std::function<Parser<Info, T>*()> parser )
{
        return  [info, parser]( ParserState<Info> &ps ) -> std::optional<T>
        {
                ps.push( info );
                const auto  *p = parser();
                auto  ret = (*p)( ps );
                ps.pop(); 

                return  ret;
        };
}

template  <typename Info, typename T>
Parser<Info, T>   pCall( Info info, Parser<Info, T> *callee )
{
        return  [info, callee]( ParserState<Info> &ps ) -> std::optional<T>
        {
                ps.push( info );
                auto  ret = (*callee)( ps );
                ps.pop(); 
                return  ret;
        };
}

template  <typename Info, typename T>
Parser<Info, std::vector<T>>  pLoop( char mode, Parser<Info, T> p )
{
        return  [mode, p]( ParserState<Info> &ps ) -> std::optional<std::vector<T>>
        {
                std::vector<T>  v;
                while ( true )
                {
                        auto r = p( ps );
                        if ( r ) 
                                v.push_back( *r );
                        else
                        {
                                if ( v.size() || mode=='*' )
                                        return v;
                                else
                                        return std::optional<std::vector<T>>();
                        }
                }
        }; 
}

template  <typename Info>
Parser<Info, std::string>  pString( Info info, std::string s )
{
        return  [info, s]( ParserState<Info> &ps ) -> std::optional<std::string>
        {
                for ( auto ch: s )
                {
                        char  ret = ps.getch();

                        if ( ps.eof() || ret!=ch )
                                return  std::optional<std::string>();
                }

                ps.push( info );
                ps.pop();
                return s;
        }; 
}

template  <typename Info, typename T>
Parser<Info, std::optional<T>>  pOpt( Parser<Info, T> p )
{
        return  [p]( ParserState<Info> &ps ) -> std::optional<std::optional<T>>
        {
                return  p( ps );
        };
}

template  <typename Info>
Parser<Info, unsigned>  pInputLine() 
{
        return   std::function( []( ParserState<Info> &ps ) -> std::optional<unsigned>
        {
                auto  sp = ps.save();
                return  sp.second.line;
        } );
};

template  <typename Info>
Parser<Info, unsigned>  pInputColumn()
{
        return   std::function( []( ParserState<Info> &ps ) -> std::optional<unsigned>
        {
                auto  sp = ps.save();
                return  sp.second.column;
        } );
};

#endif
