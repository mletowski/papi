#ifndef  __grammar_h_
#define  __grammar_h_

#include  "compiling.h"
#include  "trow.h"

/* Template executor result */
struct  ExecutorResult
{
        unsigned                   depth;
        std::vector<LisData>        data;
};

/* Template executor */
struct  Executor
{
        NumTemplS  tpl;
        std::function<ExecutorResult(TRow, IStack)>  fun; 
};

#define  STRING(X) #X
#define  STRINGX(X) STRING(X)
#define  INF  __FILE__ ":" STRINGX(__LINE__)

const GMap &compileGrammar( GMap &map, LisData g, 
                const char *grammar_filename, 
                const char *input_filename );

int  run_grammar( const LisData &grammar, const char *input_filename );

#endif
