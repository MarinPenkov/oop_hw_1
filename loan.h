#pragma once
#include <string>
#include <stdexcept>
#include <utility>

class Loan {
    std::string isbn;
    std::string memberId;
    std::string startDate;
    std::string dueDate;
    bool returned;

public:
    Loan(std::string i, std::string m, std::string start, std::string due)
        : isbn(std::move(i)), memberId(std::move(m)),
          startDate(std::move(start)), dueDate(std::move(due)),
          returned(false) {

        if (dueDate < startDate)
            throw std::invalid_argument("Due date before start date");
    }

    const std::string& getISBN() const { return isbn; }
    const std::string& getMemberId() const { return memberId; }
    bool isReturned() const { return returned; }

    void markReturned() { returned = true; }

    bool isOverdue(const std::string& today) const {
        return !returned && today > dueDate;
    }

    std::string to_string() const {
        return "Loan: " + isbn +
               " -> " + memberId +
               " | Start: " + startDate +
               " | Due: " + dueDate +
               " | Returned: " + (returned ? std::string("Yes")
                                          : std::string("No"));
    }
};

