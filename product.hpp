#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include "db.hpp"
#include <string>

class Product : public Database {
public:
    explicit Product(const std::string& conninfo) : Database(conninfo) {}

    void add(const std::string& name, double price, const std::string& category);

    void list();
};

#endif // PRODUCT_HPP
