#include "product.hpp"
#include <iostream>

void Product::add(const std::string& name, double price, const std::string& category) {
    std::string sql = "INSERT INTO products (name, price, category) VALUES ('" +
        name + "', " + std::to_string(price) + ", '" + category + "');";
    execute(sql);
    std::cout << "Product added.\n";
}

void Product::list() {
    PGresult* res = query("SELECT id, name, price, category FROM products;");
    int rows = PQntuples(res);
    for (int i = 0; i < rows; ++i) {
        std::cout
            << "ID: "       << PQgetvalue(res, i, 0)
            << ", Name: "   << PQgetvalue(res, i, 1)
            << ", Price: "  << PQgetvalue(res, i, 2)
            << ", Cat: "    << PQgetvalue(res, i, 3)
            << "\n";
    }
    PQclear(res);
}
