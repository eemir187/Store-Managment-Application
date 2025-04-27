#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "db.hpp"
#include <string>

class Location : public Database {

    public:
        Location(const std::string& conninfo) : Database(conninfo) {}

        void add(const std::string& name, const std::string& address);

        void list();

};



#endif