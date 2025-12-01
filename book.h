#pragma once
#include <string>
#include <stdexcept>
#include <utility>
#include "Author.h"

class Book {
    std::string title;
    Author author;
    int year;
    double price;
    std::string isbn;
    static int totalBooks;

public:
    Book()
        : title("Unknown"), author(), year(1900), price(0.0), isbn("N/A") {
        ++totalBooks;
    }

    Book(std::string t, const Author& a, int y, double p, std::string i)
        : title(std::move(t)), author(a), year(y), price(p), isbn(std::move(i)) {

        if (p < 0) throw std::invalid_argument("Negative price");
        if (y < 1500 || y > 2025) throw std::invalid_argument("Invalid year");

        ++totalBooks;
    }

    ~Book(){totalBooks--;};

    const std::string& getTitle() const { return title; }
    const Author& getAuthor() const { return author; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    const std::string& getISBN() const { return isbn; }

    void setPrice(double p) {
        if (p < 0) throw std::invalid_argument("Negative price");
        price = p;
    }

    void setYear(int y) {
        if (y < 1500 || y > 2025)
            throw std::invalid_argument("Invalid year");
        year = y;
    }

    std::string to_string() const {
        return title + " (" + std::to_string(year) + ") - " +
               std::to_string(price) + " lv. | ISBN: " + isbn +
               " | Author: " + author.to_string();
    }

    static int getTotalBooks() { return totalBooks; }
};


