#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "../../external/nlohmann/json.hpp"

class User {
public:
    int id;
    std::string name;
    std::string email;
    int age;

    User() : id(0), age(0) {}
    
    User(int id, const std::string& name, const std::string& email, int age)
        : id(id), name(name), email(email), age(age) {}

    // Validation method
    bool isValid() const {
        return !name.empty() && !email.empty() && age > 0 && email.find('@') != std::string::npos;
    }

    // JSON serialization
    nlohmann::json toJson() const {
        return nlohmann::json{
            {"id", id},
            {"name", name},
            {"email", email},
            {"age", age}
        };
    }

    // JSON deserialization
    static User fromJson(const nlohmann::json& j) {
        User user;
        j.at("name").get_to(user.name);
        j.at("email").get_to(user.email);
        j.at("age").get_to(user.age);
        
        if (j.contains("id")) {
            j.at("id").get_to(user.id);
        }
        
        return user;
    }
};

#endif // USER_HPP