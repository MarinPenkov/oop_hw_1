#pragma once
#include <string>
#include <stdexcept>
#include <utility>

class Member {
    std::string name;
    std::string memberId;
    int yearJoined;

public:
    Member() : name("Unknown"), memberId("N/A"), yearJoined(2000) {}

    Member(std::string n, std::string id, int y)
        : name(std::move(n)), memberId(std::move(id)), yearJoined(y) {

        if (memberId.empty())
            throw std::invalid_argument("Member ID cannot be empty");
        if (y < 1900 || y > 2025)
            throw std::invalid_argument("Invalid join year");
    }

    const std::string& getName() const { return name; }
    const std::string& getId() const { return memberId; }

    std::string to_string() const {
        return name + " | ID: " + memberId +
               " | Joined: " + std::to_string(yearJoined);
    }
};
