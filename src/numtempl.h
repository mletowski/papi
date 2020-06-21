#ifndef  __numtempl_h__
#define  __numtempl_h__

#include  "lisdata.h"
#include  <list>

struct  NumTemplS;

enum  struct LoopType{ sequence, string, list };

struct  NumTemplLoop
{
        char          kind;
        LoopType      type;

        std::vector<NumTemplS>  elements;

        NumTemplLoop( const std::vector<NumTemplS> &e, char kind, LoopType type ):
                kind( kind ), type(type), elements(e) {};
};

/*  Path to variable in loops/tables:
 *  {2, 0, 1} means:  tables[2][0].1, ie variable #1 in table #0 in table #2
 */  
using   VarPath = std::list<int>;

using   NumTempl = std::variant<std::string, VarPath, NumTemplLoop>;

struct  NumTemplS
{
        NumTempl  tpl;

        NumTemplS( NumTempl t ): tpl( t ) {};
        operator  const NumTempl&() const { return tpl; };
        operator  NumTempl&() { return tpl; };

        unsigned  depth() const 
        {
                unsigned max = 0;

                switch (tpl.index()) 
                {
                        case 0:
                                return 0;
                        case 1:
                                return std::get<VarPath>( tpl ).size() - 1;
                        case 2:
                                for ( auto e: std::get<NumTemplLoop>( tpl ).elements )
                                        max = std::max( max, e.depth() );

                                return max;

                }
                return  tpl.index()==1 ? std::get<VarPath>( tpl ).size()-1: 0;
        };

        bool  isLoop() const { return tpl.index()==2; }
};

std::string   show( const NumTempl& );
        
NumTempl   numerateTemplate( const LisData &rcpt, const LisData &t, unsigned depth );

std::string  getElementVarName( const LisData& );

#endif
