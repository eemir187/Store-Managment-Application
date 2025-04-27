#include "location.hpp"
#include <iostream>

void Location::add(const std::string& name, const std::string& address) {
    std::string sql = "INSERT INTO locations (name, address) VALUES ('" + name + "', '" + address + "');";
    execute(sql);
    std::cout << "Location added.\n";
}

void Location::list() {
    PGresult* res = query("SELECT id, name, address FROM locations;");
    int rows = PQntuples(res);
    if (rows != 0) {
        for(int i = 0; i < rows; i++) {
            std::cout
                << "ID: "      << PQgetvalue(res, i, 0)
                << ", Name: "  << PQgetvalue(res, i, 1)
                << ", Addr: "  << PQgetvalue(res, i, 2)
                << "\n";
        }
    }
    else {
        std::cout << "There is no data in the list\n";
    }
    PQclear(res);
}
