#include <iostream>
#include <csignal>
#include "../external/httplib.h"
#include "controllers/UserController.hpp"
#include "utils/Logger.hpp"

class RestServer {
private:
    httplib::Server server;
    UserController userController;
    int port;

public:
    RestServer(int port = 8080) : port(port) {
        setupRoutes();
        setupMiddleware();
    }

    void setupMiddleware() {
        // CORS middleware
        server.set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
            return httplib::Server::HandlerResponse::Unhandled;
        });

        // Handle OPTIONS requests for CORS preflight
        server.Options(".*", [](const httplib::Request& req, httplib::Response& res) {
            return;
        });

        // Request logging middleware
        server.set_logger([](const httplib::Request& req, const httplib::Response& res) {
            Logger::info(req.method + " " + req.path + " - " + std::to_string(res.status));
        });
    }

    void setupRoutes() {
        // Health check endpoint
        server.Get("/health", [](const httplib::Request& req, httplib::Response& res) {
            nlohmann::json response;
            response["status"] = "healthy";
            response["timestamp"] = std::time(nullptr);
            response["service"] = "C++ REST API";
            res.set_content(response.dump(), "application/json");
        });

        // API info endpoint
        server.Get("/api", [](const httplib::Request& req, httplib::Response& res) {
            nlohmann::json response;
            response["message"] = "Welcome to C++ REST API";
            response["version"] = "1.0.0";
            response["endpoints"] = {
                {"GET /health", "Health check"},
                {"GET /api/users", "Get all users"},
                {"GET /api/users/:id", "Get user by ID"},
                {"POST /api/users", "Create new user"},
                {"PUT /api/users/:id", "Update user"},
                {"DELETE /api/users/:id", "Delete user"}
            };
            res.set_content(response.dump(), "application/json");
        });

        // User routes
        server.Get("/api/users", [this](const httplib::Request& req, httplib::Response& res) {
            userController.getAllUsers(req, res);
        });

        server.Get(R"(/api/users/(\d+))", [this](const httplib::Request& req, httplib::Response& res) {
            userController.getUserById(req, res);
        });

        server.Post("/api/users", [this](const httplib::Request& req, httplib::Response& res) {
            userController.createUser(req, res);
        });

        server.Put(R"(/api/users/(\d+))", [this](const httplib::Request& req, httplib::Response& res) {
            userController.updateUser(req, res);
        });

        server.Delete(R"(/api/users/(\d+))", [this](const httplib::Request& req, httplib::Response& res) {
            userController.deleteUser(req, res);
        });

        // 404 handler
        server.set_error_handler([](const httplib::Request& req, httplib::Response& res) {
            nlohmann::json response;
            response["success"] = false;
            response["message"] = "Endpoint not found";
            response["path"] = req.path;
            res.set_content(response.dump(), "application/json");
        });
    }

    void start() {
        Logger::info("Starting C++ REST API server on port " + std::to_string(port));
        Logger::info("Health check available at: http://localhost:" + std::to_string(port) + "/health");
        Logger::info("API info available at: http://localhost:" + std::to_string(port) + "/api");
        Logger::info("Users API available at: http://localhost:" + std::to_string(port) + "/api/users");
        
        if (!server.listen("0.0.0.0", port)) {
            Logger::error("Failed to start server on port " + std::to_string(port));
            throw std::runtime_error("Failed to start server");
        }
    }

    void stop() {
        Logger::info("Stopping server...");
        server.stop();
    }
};

// Global server instance for signal handling
RestServer* globalServer = nullptr;

void signalHandler(int signal) {
    Logger::info("Received signal " + std::to_string(signal) + ", shutting down gracefully...");
    if (globalServer) {
        globalServer->stop();
    }
    exit(0);
}

int main(int argc, char* argv[]) {
    try {
        // Setup signal handlers for graceful shutdown
        std::signal(SIGINT, signalHandler);
        std::signal(SIGTERM, signalHandler);

        // Parse command line arguments for port
        int port = 8080;
        if (argc > 1) {
            port = std::stoi(argv[1]);
        }

        Logger::info("Initializing C++ REST API Server");
        
        RestServer server(port);
        globalServer = &server;
        
        server.start();
        
    } catch (const std::exception& e) {
        Logger::error("Server error: " + std::string(e.what()));
        return 1;
    } catch (...) {
        Logger::error("Unknown server error occurred");
        return 1;
    }

    return 0;
}