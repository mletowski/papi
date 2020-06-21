#include  "grammar.h"

#include  <cstdlib>
#include  <cstring>
#include  <fstream>        
#include  <iostream>
#include  <unistd.h>

#define  PROGRAM_VERSION  "0.99"

static const char *banner = "papi  " PROGRAM_VERSION "\n";

static const char *usage_string =
"Usage   :  papi [options] grammar_file data_file\n"
"Options:  -d    - debug mode, always dump parser stack\n"
"          -g    - dump user grammar (in json list format)\n"
"          -h    - help\n"
"          -j    - result output format = json lists\n"
"          -m    - dump metagrammar (in json list format)\n"
"          -r    - result output format = raw string result\n"
"          -s    - silent mode - do not dump parser stack on error\n";

static  void  show_usage()
{
        std::cout << banner << usage_string;
}

/*  Output modes  */
enum class OutputMode {
        Undefined,   //  to be recognized based on data structure 
        JsonList,    //  using subset of JSON (strings and lists)
        Text         //  as raw string text
};

/*  Command line options values  */
bool  op_debug = false;
bool  op_dump_grammar = false;
OutputMode  op_output_mode = OutputMode::Undefined;
bool  op_silent = false;

std::string  grammar_filename, data_filename;
bool  action_performed = false;

OutputMode  recognize_output_mode( const std::vector<LisData> &data )
{
        if ( data.size() == 1 )
        {
                try {
                        data.at( 0 ).getString();
                        return  OutputMode::Text;
                }
                catch ( const std::bad_variant_access& )
                {
                }
        }

        return  OutputMode::JsonList;
}

std::string  json_escape_string( const std::string &s )
{
        std::string  es = "\"";

        for ( auto ch: s )
                switch( ch )
                {
                        case '\r':
                                es += "\\r";
                                break;
                        case '\n':
                                es += "\\n";
                                break;
                        case '\t':
                                es += "\\t";
                                break;
                        case '\"':
                                es += "\\\"";
                                break;
                        case '\\':
                                es += "\\\\";
                                break;
                        default:
                                if ( isprint(ch) )
                                        es += ch;
                                else
                                {
                                        char xbuf[ 8 ];
                                        snprintf( xbuf, sizeof(xbuf), "\\x%02x", int(ch) );
                                        es += xbuf;
                                }
                }

        return es + "\"";
}

std::string  output_as_string( const std::vector<LisData> &data )
{
        std::string  s;

        for ( const auto it: data )
        {
                try {
                        s += it.getString();
                }
                catch ( const std::bad_variant_access& )
                {
                }
        }

        return s;
}

std::string  output_as_json_list( const std::vector<LisData> &data )
{
        std::string  s = "[";
        std::string  sep;

        for ( const auto it: data )
        {
                try {
                        s += sep + json_escape_string( it.getString() );
                }
                catch ( const std::bad_variant_access& )
                {
                        s += sep + output_as_json_list( it.getList() );
                }

                sep = ",";
        }

        return s + "]";
}

std::string  output_as_json_sequence( const std::vector<LisData> &data )
{
        std::string  s, sep;
        bool  numbers = true;

        if ( data.size() == 1 )
                numbers = false;

        int  number = 1;

        for ( const auto it: data )
        {
                s += sep;

                if ( numbers )
                        s += std::to_string( number++ ) + ": ";

                try {
                        s += json_escape_string( it.getString() );
                }
                catch ( const std::bad_variant_access& )
                {
                        s += output_as_json_list( it.getList() );
                }

                sep = "\n";
        }

        return s;
}

std::string  output_result( OutputMode  mode,  const std::vector<LisData> &data )
{
        switch ( mode ) 
        {
                case  OutputMode::Text:
                        return output_as_string( data );
                case  OutputMode::JsonList:
                        return output_as_json_sequence( data );
                default:
                        mode = recognize_output_mode( data );
                        return  output_result( mode, data );
        }
}

void  dump_parser_stack( ParserState<Info> *ps, const std::string &filename, 
                const std::string &message )
{
        std::cout << message << ",\nParser stack:\n";

        std::string  dump;

        for ( auto it: ps->getInfo() )
        {
                dump = it.first + ", at '" + filename + 
                        "' in: " + std::to_string( it.second.pos ) + 
                        " [line " + std::to_string( it.second.line ) + ": column " + 
                        std::to_string( it.second.column ) + ']' + '\n' + dump;
        }

        std::cout << dump;
}

int  main( int argc, char *argv[] )
{
#include  "metagenerated.h"
        LisData  metagrammarStruct = metagenerated;

        int op = 0;

        while ( op >= 0 )
        {
                op = getopt( argc, argv, "dhjgmrs" );
                switch ( op )
                {
                        case 'd':
                                op_debug = true;
                                break;
                        case 'g':
                                op_dump_grammar = true;
                                break;
                        case 'h':
                                show_usage();
                                action_performed = true;
                                std::exit( 0 );
                        case 'j':
                                op_output_mode = OutputMode::JsonList;
                                break;
                        case 'm':
                                std::cout << 
                                        output_as_json_sequence( {metagrammarStruct} ) << '\n';

                                action_performed = true;
                                break;
                        case 'r':
                                op_output_mode = OutputMode::Text;
                                break;
                        case 's':
                                op_silent = true;
                                break;
                        case -1:
                                break;
                        default:
                                exit( 1 );
                }
        }

        if ( optind < argc )
                grammar_filename = argv[ optind++ ];

        if ( optind < argc )
                data_filename = argv[ optind++ ];

        try {
                LisData   userGrammarStruct;
                GMap      metagrammar, userGrammar;      
                std::vector<LisData>   userData;  

                if ( grammar_filename.empty() )
                {
                        if ( !action_performed ) 
                                show_usage();

                        std::exit( 0 );
                }

                compileGrammar( metagrammar, metagrammarStruct, 
                                "internal metagrammar", grammar_filename.c_str() );

                if ( !metagrammar.count( "goal" ))
                {
                        std::cout << "Internal error - no 'goal' in the metagrammar\n";
                        std::exit( 2 );
                }

                ParserState<Info> *ps = nullptr;
                ps = new ParserState<Info>( new std::ifstream(grammar_filename) );

                Parser<Info, std::vector<LisData>>  p = *metagrammar.at("goal");
                std::optional<std::vector<LisData>>  r = p( *ps );

                if ( r ) 
                {
                        if ( r->size() != 1 )
                                throw  Exception( grammar_filename + 
                                        ": internal problem - vector parsed has " + 
                                        std::to_string( r->size() ) +
                                        " elements" );

                        userGrammarStruct = r->at( 0 );
                        
                        if ( op_debug )
                                dump_parser_stack( ps, grammar_filename, 
                                                "Metagrammar parser succeeded" );

                        if ( op_dump_grammar )        
                                std::cout << 
                                        output_as_json_sequence( {userGrammarStruct} ) << '\n';

                }
                else
                {
                        if ( op_silent )
                                std::cout << "Metagrammar parser failed\n";
                        else
                                dump_parser_stack( ps, grammar_filename, 
                                                "Metagrammar parser failed" );

                        std::exit( 1 );
                }

                compileGrammar( userGrammar, userGrammarStruct, 
                                grammar_filename.c_str(), data_filename.c_str() );

                if ( !( data_filename.empty() || userGrammar.count( "goal" )))
                {
                        std::cout << grammar_filename << ": no 'goal' in the grammar\n";
                        std::exit( 2 );
                }

                if ( data_filename.empty() ) 
                        std::exit( 0 );

                Parser<Info, std::vector<LisData>>  *ptr = nullptr;
                ptr = userGrammar.at( "goal" );

                delete ps;
                ps = new ParserState<Info>( new std::ifstream(data_filename) );

                const auto &up = *ptr;
                r = up( *ps );

                if ( r ) 
                {
                        userData = *r;
                        std::string  s = output_result( op_output_mode, userData );
                        std::cout << s << '\n';

                        if ( op_debug )
                                dump_parser_stack( ps, data_filename, "Parsing succeeded" );

                        std::exit( 0 );
                }
                else
                {
                        if ( op_silent ) 
                                std::cout << "Failure parsing data from '" << 
                                        data_filename << "'\n";
                        else
                                dump_parser_stack( ps, data_filename, "Parsing failed" );

                        std::exit( 1 );
                }
        }
        catch ( const std::exception &e )
        {
                std::cout << "Unexpected exception: " << e.what() << '\n';
                std::exit( 1 );
        }
        catch ( const Exception &e )
        {
                std::cout << e.toMessage() << '\n';
                std::exit( 2 );
        }
        catch ( const RuntimeError &e )
        {
                std::cout << "Parser execution error: " << e.what << '\n';
                std::exit( 3 );
        }

        return 0;
}
