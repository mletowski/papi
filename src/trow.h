#ifndef  __trow_h_
#define  __trow_h_

class  TTable;

class  TRow
{
        public:
               std::vector<std::vector<LisData>>  fields;
               std::vector<TTable>   tables;
};

class  TTable: public std::vector<TRow>
{
        public:
                TTable() {};

                TTable( const std::vector<TRow> &v ): std::vector<TRow>( v ) {};
};


#endif
