#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include "../../external/nlohmann/json.hpp"

class Response {
public:
    struct ApiResponse {
        bool success;
        std::string message;
        nlohmann::json data;
        int statusCode;

        ApiResponse(bool success, const std::string& message, 
                   const nlohmann::json& data = nlohmann::json::object(), 
                   int statusCode = 200)
            : success(success), message(message), data(data), statusCode(statusCode) {}

        nlohmann::json toJson() const {
            nlohmann::json response;
            response["success"] = success;
            response["message"] = message;
            
            if (!data.is_null() && !data.empty()) {
                response["data"] = data;
            }
            
            return response;
        }
    };

    // Success responses
    static ApiResponse success(const std::string& message, const nlohmann::json& data = nlohmann::json::object()) {
        return ApiResponse(true, message, data, 200);
    }

    static ApiResponse created(const std::string& message, const nlohmann::json& data = nlohmann::json::object()) {
        return ApiResponse(true, message, data, 201);
    }

    // Error responses
    static ApiResponse badRequest(const std::string& message) {
        return ApiResponse(false, message, nlohmann::json::object(), 400);
    }

    static ApiResponse notFound(const std::string& message) {
        return ApiResponse(false, message, nlohmann::json::object(), 404);
    }

    static ApiResponse internalError(const std::string& message) {
        return ApiResponse(false, message, nlohmann::json::object(), 500);
    }

    static ApiResponse methodNotAllowed(const std::string& message) {
        return ApiResponse(false, message, nlohmann::json::object(), 405);
    }

    // Validation error
    static ApiResponse validationError(const std::string& message) {
        return ApiResponse(false, "Validation Error: " + message, nlohmann::json::object(), 422);
    }
};

#endif // RESPONSE_HPP