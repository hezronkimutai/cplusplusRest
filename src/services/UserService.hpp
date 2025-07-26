#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP

#include <vector>
#include <memory>
#include <mutex>
#include <algorithm>
#include "../models/User.hpp"

class UserService {
private:
    std::vector<User> users;
    int nextId;
    mutable std::mutex usersMutex;

public:
    UserService() : nextId(1) {}

    // Get all users
    std::vector<User> getAllUsers() const {
        std::lock_guard<std::mutex> lock(usersMutex);
        return users;
    }

    // Get user by ID
    std::shared_ptr<User> getUserById(int id) const {
        std::lock_guard<std::mutex> lock(usersMutex);
        auto it = std::find_if(users.begin(), users.end(),
            [id](const User& user) { return user.id == id; });
        
        if (it != users.end()) {
            return std::make_shared<User>(*it);
        }
        return nullptr;
    }

    // Create new user
    User createUser(const User& user) {
        std::lock_guard<std::mutex> lock(usersMutex);
        User newUser = user;
        newUser.id = nextId++;
        users.push_back(newUser);
        return newUser;
    }

    // Update user
    bool updateUser(int id, const User& updatedUser) {
        std::lock_guard<std::mutex> lock(usersMutex);
        auto it = std::find_if(users.begin(), users.end(),
            [id](const User& user) { return user.id == id; });
        
        if (it != users.end()) {
            it->name = updatedUser.name;
            it->email = updatedUser.email;
            it->age = updatedUser.age;
            return true;
        }
        return false;
    }

    // Delete user
    bool deleteUser(int id) {
        std::lock_guard<std::mutex> lock(usersMutex);
        auto it = std::find_if(users.begin(), users.end(),
            [id](const User& user) { return user.id == id; });
        
        if (it != users.end()) {
            users.erase(it);
            return true;
        }
        return false;
    }

    // Check if user exists
    bool userExists(int id) const {
        std::lock_guard<std::mutex> lock(usersMutex);
        return std::find_if(users.begin(), users.end(),
            [id](const User& user) { return user.id == id; }) != users.end();
    }
};

#endif // USER_SERVICE_HPP