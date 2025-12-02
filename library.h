#pragma once
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#include "Book.h"
#include "Member.h"
#include "Loan.h"

class Library {
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;

public:
    Library() = default;

    void addBook(const Book& b) { books.push_back(b); }
    void addMember(const Member& m) { members.push_back(m); }

    bool hasBook(const std::string& isbn) const {
        for (const auto& b : books)
            if (b.getISBN() == isbn)
                return true;
        return false;
    }

    bool isBookAvailable(const std::string& isbn) const {
        for (const auto& l : loans)
            if (l.getISBN() == isbn && !l.isReturned())
                return false;
        return true;
    }

    bool loanBook(const std::string& isbn, const std::string& memberId,
                  const std::string& start, const std::string& due) {

        if (!hasBook(isbn)) return false;
        if (!isBookAvailable(isbn)) return false;

        bool memberExists = false;
        for (const auto& m : members)
            if (m.getId() == memberId)
                memberExists = true;

        if (!memberExists) return false;

        loans.emplace_back(isbn, memberId, start, due);
        return true;
    }

    bool returnBook(const std::string& isbn, const std::string& memberId) {
        for (auto& l : loans) {
            if (l.getISBN() == isbn && l.getMemberId() == memberId && !l.isReturned()) {
                l.markReturned();
                return true;
            }
        }
        return false;
    }

    std::vector<Book> findByAuthor(const std::string& authorName) const {
        std::vector<Book> result;
        for (const auto& b : books)
            if (b.getAuthor().getName().find(authorName) != std::string::npos)
                result.push_back(b);
        return result;
    }

    std::string to_string() const {
        int activeLoans = 0;
        for (const auto& l : loans)
            if (!l.isReturned())
                activeLoans++;

        return "Library info:\nBooks: " + std::to_string(books.size()) +
               "\nMembers: " + std::to_string(members.size()) +
               "\nActive loans: " + std::to_string(activeLoans);
    }
};
