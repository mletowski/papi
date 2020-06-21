#ifndef  __lisdata_h_
#define  __lisdata_h_

#include  <initializer_list>
#include  <string>
#include  <variant>
#include  <vector>

class  LisData:  private  std::variant<std::string, std::vector<LisData>> 
{
        private:
                using  V = std::variant<std::string, std::vector<LisData>>;
        public:  
                LisData(): V( std::vector<LisData>{} ) {};

                LisData( const char *s ): V( std::string(s) ) {};

                LisData( std::string s ): V( s ) {};

                explicit LisData( const std::vector<LisData> &v ): V( v ) {};

                LisData( std::initializer_list<LisData> l ): 
                        V( std::vector<LisData>(l) ) {};

                bool  invalid() const 
                { 
                        return index()!=0 && index()!=1; 
                };

                bool  isString() const 
                { 
                        return index()==0; 
                };

                bool  isString( const char *s ) const  
                { 
                        return isString( std::string(s) ); 
                };

                bool  isString( std::string s ) const  
                { 
                        return isString() && getString()==s; 
                };

                bool  isList( size_t minsize=0 ) const 
                { 
                        return index()==1 && getList().size() >= minsize;
                };

                const LisData &car() const 
                { 
                        return getList()[ 0 ]; 
                };

                std::string getString() const 
                { 
                        return std::get<std::string>( *this ); 
                };

                const std::vector<LisData>  &getList() const 
                { 
                        return std::get<std::vector<LisData>>( *this ); 
                };

                LisData  join( const LisData& ) const;

                LisData  append( const LisData& ) const;

                LisData  insertto( const LisData& ) const;

                /* Convert to string, if possible.  */
                LisData  convertToString() const;

                /* Convert string to list of characters 
                 * (if it is really a string) */
                LisData  convertFromString() const;
                
};

/* Display data as standard string */
std::string  show( const LisData &x, std::string eol = "" );

#endif
