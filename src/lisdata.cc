#include  <algorithm>
#include  "lisdata.h"

std::string  show( const LisData &x, std::string eol )
{
        std::string  image;

        if ( x.invalid() )
                return "<invalid>";

        if ( x.isString() )
                image = "'" + x.getString() + "'";
        else
        {
                std::string  sep;
                image = "(";

                for ( auto i: x.getList() )
                {
                        image += sep;
                        image += show( i );
                        sep = " ";
                }

                image += ")" + eol;
        }

        return  image;
}

LisData  LisData::join( const LisData &x ) const
{
        LisData  left, right;

        left = convertToString();
        if ( left.isString() )
        {
                right = x.convertToString();
                if ( right.isString() ) 
                        return  left.getString() + right.getString();
                else 
                        left = convertFromString();
        }
        else
                right = x.convertFromString();

        std::vector<LisData>  result = left.getList();
        const std::vector<LisData>  &r = right.getList();
        result.insert( result.end(), r.begin(), r.end() );

        return  LisData( result );
}

LisData  LisData::append( const LisData &x ) const
{
        LisData left = convertFromString();
        auto vec = left.getList();
        vec.push_back( x.convertToString() );
        return  LisData( vec ).convertToString();
}

LisData  LisData::insertto( const LisData &x ) const
{
        return  LisData{ "error" };
}

LisData  LisData::convertToString() const 
{
        std::string  result;

        if ( isList() )
        {
                const  std::vector<LisData> &vec = getList();

                for ( auto i: vec )
                {
                        if ( i.isString() )
                        {
                                std::string s = i.getString();
                                if ( s.size() == 1 )
                                        result += s;
                                else
                                        return *this;
                        }
                }

                return  result;
        }

        return  *this;
}

LisData  LisData::convertFromString() const 
{
        if ( isString() )
        {
                std::vector<LisData>  vec;

                for ( auto ch: getString() )
                        vec.push_back( LisData(std::string(1, ch)) );

                return  LisData( vec );
        }

        return  *this;
}
