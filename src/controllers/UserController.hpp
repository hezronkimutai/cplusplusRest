#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include "../../external/httplib.h"
#include "../../external/nlohmann/json.hpp"
#include "../services/UserService.hpp"
#include "../utils/Response.hpp"
#include "../utils/Logger.hpp"

class UserController {
private:
    UserService userService;

    // Helper method to send JSON response
    void sendJsonResponse(httplib::Response& res, const Response::ApiResponse& apiResponse) {
        res.set_content(apiResponse.toJson().dump(), "application/json");
        res.status = apiResponse.statusCode;
    }

public:
    // GET /api/users - Get all users
    void getAllUsers(const httplib::Request& req, httplib::Response& res) {
        try {
            Logger::info("GET /api/users - Fetching all users");
            
            auto users = userService.getAllUsers();
            nlohmann::json usersJson = nlohmann::json::array();
            
            for (const auto& user : users) {
                usersJson.push_back(user.toJson());
            }
            
            auto response = Response::success("Users retrieved successfully", usersJson);
            sendJsonResponse(res, response);
            
            Logger::info("GET /api/users - Successfully returned " + std::to_string(users.size()) + " users");
        }
        catch (const std::exception& e) {
            Logger::error("GET /api/users - Error: " + std::string(e.what()));
            auto response = Response::internalError("Failed to retrieve users");
            sendJsonResponse(res, response);
        }
    }

    // GET /api/users/:id - Get user by ID
    void getUserById(const httplib::Request& req, httplib::Response& res) {
        try {
            std::string idStr = req.matches[1].str();
            int id = std::stoi(idStr);
            
            Logger::info("GET /api/users/" + idStr + " - Fetching user by ID");
            
            auto user = userService.getUserById(id);
            if (user) {
                auto response = Response::success("User found", user->toJson());
                sendJsonResponse(res, response);
                Logger::info("GET /api/users/" + idStr + " - User found and returned");
            } else {
                auto response = Response::notFound("User not found");
                sendJsonResponse(res, response);
                Logger::warning("GET /api/users/" + idStr + " - User not found");
            }
        }
        catch (const std::invalid_argument& e) {
            Logger::error("GET /api/users/:id - Invalid ID format");
            auto response = Response::badRequest("Invalid user ID format");
            sendJsonResponse(res, response);
        }
        catch (const std::exception& e) {
            Logger::error("GET /api/users/:id - Error: " + std::string(e.what()));
            auto response = Response::internalError("Failed to retrieve user");
            sendJsonResponse(res, response);
        }
    }

    // POST /api/users - Create new user
    void createUser(const httplib::Request& req, httplib::Response& res) {
        try {
            Logger::info("POST /api/users - Creating new user");
            
            auto json = nlohmann::json::parse(req.body);
            User user = User::fromJson(json);
            
            if (!user.isValid()) {
                auto response = Response::validationError("Invalid user data. Name, email, and age are required.");
                sendJsonResponse(res, response);
                Logger::warning("POST /api/users - Validation failed");
                return;
            }
            
            User createdUser = userService.createUser(user);
            auto response = Response::created("User created successfully", createdUser.toJson());
            sendJsonResponse(res, response);
            
            Logger::info("POST /api/users - User created with ID: " + std::to_string(createdUser.id));
        }
        catch (const nlohmann::json::parse_error& e) {
            Logger::error("POST /api/users - JSON parse error: " + std::string(e.what()));
            auto response = Response::badRequest("Invalid JSON format");
            sendJsonResponse(res, response);
        }
        catch (const std::exception& e) {
            Logger::error("POST /api/users - Error: " + std::string(e.what()));
            auto response = Response::internalError("Failed to create user");
            sendJsonResponse(res, response);
        }
    }

    // PUT /api/users/:id - Update user
    void updateUser(const httplib::Request& req, httplib::Response& res) {
        try {
            std::string idStr = req.matches[1].str();
            int id = std::stoi(idStr);
            
            Logger::info("PUT /api/users/" + idStr + " - Updating user");
            
            auto json = nlohmann::json::parse(req.body);
            User updatedUser = User::fromJson(json);
            
            if (!updatedUser.isValid()) {
                auto response = Response::validationError("Invalid user data. Name, email, and age are required.");
                sendJsonResponse(res, response);
                Logger::warning("PUT /api/users/" + idStr + " - Validation failed");
                return;
            }
            
            if (userService.updateUser(id, updatedUser)) {
                updatedUser.id = id;
                auto response = Response::success("User updated successfully", updatedUser.toJson());
                sendJsonResponse(res, response);
                Logger::info("PUT /api/users/" + idStr + " - User updated successfully");
            } else {
                auto response = Response::notFound("User not found");
                sendJsonResponse(res, response);
                Logger::warning("PUT /api/users/" + idStr + " - User not found");
            }
        }
        catch (const std::invalid_argument& e) {
            Logger::error("PUT /api/users/:id - Invalid ID format");
            auto response = Response::badRequest("Invalid user ID format");
            sendJsonResponse(res, response);
        }
        catch (const nlohmann::json::parse_error& e) {
            Logger::error("PUT /api/users/:id - JSON parse error: " + std::string(e.what()));
            auto response = Response::badRequest("Invalid JSON format");
            sendJsonResponse(res, response);
        }
        catch (const std::exception& e) {
            Logger::error("PUT /api/users/:id - Error: " + std::string(e.what()));
            auto response = Response::internalError("Failed to update user");
            sendJsonResponse(res, response);
        }
    }

    // DELETE /api/users/:id - Delete user
    void deleteUser(const httplib::Request& req, httplib::Response& res) {
        try {
            std::string idStr = req.matches[1].str();
            int id = std::stoi(idStr);
            
            Logger::info("DELETE /api/users/" + idStr + " - Deleting user");
            
            if (userService.deleteUser(id)) {
                auto response = Response::success("User deleted successfully");
                sendJsonResponse(res, response);
                Logger::info("DELETE /api/users/" + idStr + " - User deleted successfully");
            } else {
                auto response = Response::notFound("User not found");
                sendJsonResponse(res, response);
                Logger::warning("DELETE /api/users/" + idStr + " - User not found");
            }
        }
        catch (const std::invalid_argument& e) {
            Logger::error("DELETE /api/users/:id - Invalid ID format");
            auto response = Response::badRequest("Invalid user ID format");
            sendJsonResponse(res, response);
        }
        catch (const std::exception& e) {
            Logger::error("DELETE /api/users/:id - Error: " + std::string(e.what()));
            auto response = Response::internalError("Failed to delete user");
            sendJsonResponse(res, response);
        }
    }
};

#endif // USER_CONTROLLER_HPP