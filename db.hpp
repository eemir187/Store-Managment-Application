#ifndef DB_HPP
#define DB_HPP

#include <postgresql/libpq-fe.h>
#include <string>

class Database {
    protected:
        PGconn* conn_;
    
    public:
        Database(const std::string& conninfo);
        ~Database();

        void execute(const std::string& sql);

        PGresult* query(const std::string& sql);

        void init_schema();


};




#endif