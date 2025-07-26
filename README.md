# C++ REST API Application

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/yourusername/cpp-rest-api)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20|%20Linux%20|%20macOS-lightgrey)](https://github.com/yourusername/cpp-rest-api)

A production-ready, modern C++ REST API server demonstrating CRUD operations with JSON handling, built using cpp-httplib and nlohmann/json. Features thread-safe operations, comprehensive error handling, and cross-platform compatibility.

## 🚀 Quick Start

```bash
# Clone the repository
git clone https://github.com/yourusername/cpp-rest-api.git
cd cpp-rest-api

# Build and run (Windows)
build.bat
build\bin\CppRestAPI.exe

# Build and run (Linux/macOS)
make
./build/bin/CppRestAPI
```

**Server will start on http://localhost:8080**

## Features

- **RESTful API**: Full CRUD operations for user management
- **JSON Support**: Request/response handling with nlohmann/json
- **Modern C++**: Uses C++17 features and best practices
- **Thread-Safe**: Concurrent request handling
- **Logging**: Comprehensive logging with timestamps
- **Error Handling**: Proper HTTP status codes and error responses
- **CORS Support**: Cross-origin resource sharing enabled
- **Health Checks**: Built-in health monitoring endpoint

## API Endpoints

### Health & Info
- `GET /health` - Health check endpoint
- `GET /api` - API information and available endpoints

### User Management
- `GET /api/users` - Get all users
- `GET /api/users/{id}` - Get user by ID
- `POST /api/users` - Create new user
- `PUT /api/users/{id}` - Update existing user
- `DELETE /api/users/{id}` - Delete user

## Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.14 or higher
- Internet connection (for downloading dependencies)

## Building

### Windows Build
```batch
REM Dependencies are already included in the external/ directory
REM Simply run the build script:
build.bat

REM Or manually compile with Visual Studio:
cl /std:c++17 /EHsc /I external /I src src\main.cpp /Fe:build\bin\CppRestAPI.exe /link ws2_32.lib wsock32.lib

REM Or with MinGW/GCC:
g++ -std=c++17 -Wall -Wextra -O2 -I external -I src src\main.cpp -o build\bin\CppRestAPI.exe -lws2_32 -lwsock32
```

### Linux/macOS Build
```bash
# Using make (if available)
make

# Or manually with g++:
mkdir -p build/bin
g++ -std=c++17 -Wall -Wextra -O2 -I external -I src src/main.cpp -o build/bin/CppRestAPI -pthread

# Using CMake (if available):
mkdir build && cd build
cmake .. && cmake --build .
```

## Running the Server

```bash
# Run on default port (8080)
./bin/CppRestAPI

# Run on custom port
./bin/CppRestAPI 9000
```

The server will start and display:
```
[2024-01-01 12:00:00.000] [INFO] Starting C++ REST API server on port 8080
[2024-01-01 12:00:00.001] [INFO] Health check available at: http://localhost:8080/health
[2024-01-01 12:00:00.002] [INFO] API info available at: http://localhost:8080/api
[2024-01-01 12:00:00.003] [INFO] Users API available at: http://localhost:8080/api/users
```

## Testing

### Automated Testing Scripts

**PowerShell (Windows):**
```powershell
# Start the server first, then run:
powershell -ExecutionPolicy Bypass -File examples\test_api.ps1
```

**Bash (Linux/macOS):**
```bash
# Start the server first, then run:
chmod +x examples/test_api.sh
./examples/test_api.sh
```

## Usage Examples

### Health Check
```bash
curl http://localhost:8080/health
```

### Create User
```bash
curl -X POST http://localhost:8080/api/users \
  -H "Content-Type: application/json" \
  -d '{"name": "John Doe", "email": "john@example.com", "age": 30}'
```

### Get All Users
```bash
curl http://localhost:8080/api/users
```

### Get User by ID
```bash
curl http://localhost:8080/api/users/1
```

### Update User
```bash
curl -X PUT http://localhost:8080/api/users/1 \
  -H "Content-Type: application/json" \
  -d '{"name": "John Smith", "email": "john.smith@example.com", "age": 31}'
```

### Delete User
```bash
curl -X DELETE http://localhost:8080/api/users/1
```

## Response Format

All API responses follow this format:
```json
{
  "success": true,
  "message": "Operation successful",
  "data": { /* response data */ }
}
```

Error responses:
```json
{
  "success": false,
  "message": "Error description"
}
```

## Project Structure

```
cplusplusRest/
├── src/
│   ├── controllers/
│   │   └── UserController.hpp      # HTTP request handlers
│   ├── models/
│   │   └── User.hpp                # User data model
│   ├── services/
│   │   └── UserService.hpp         # Business logic
│   ├── utils/
│   │   ├── Logger.hpp              # Logging utility
│   │   └── Response.hpp            # Response helpers
│   └── main.cpp                    # Application entry point
├── memory-bank/                    # Project documentation
├── CMakeLists.txt                  # Build configuration
└── README.md                       # This file
```

## Dependencies

- **cpp-httplib**: HTTP server library (automatically downloaded)
- **nlohmann/json**: JSON library (automatically downloaded)

Dependencies are automatically downloaded and configured by CMake using FetchContent.

## Configuration

### Default Settings
- **Port**: 8080 (configurable via command line)
- **Host**: 0.0.0.0 (binds to all interfaces)
- **CORS**: Enabled for all origins
- **Logging**: Enabled with timestamps

### Environment Variables
Currently, configuration is done via command-line arguments. Future versions may support environment variables.

## Development

### Adding New Endpoints
1. Add route handler to `UserController.hpp`
2. Register route in `main.cpp` `setupRoutes()` method
3. Rebuild and test

### Extending Models
1. Modify `User.hpp` or create new model in `src/models/`
2. Update corresponding service and controller
3. Add validation and JSON serialization

## Troubleshooting

### Build Issues
- Ensure CMake 3.14+ is installed
- Check internet connectivity for dependency downloads
- Verify C++17 compiler support

### Runtime Issues
- Check if port is already in use
- Verify firewall settings
- Check console logs for error messages

### Common Errors
- **Port in use**: Try different port with `./bin/CppRestAPI 9000`
- **Permission denied**: Run with appropriate privileges
- **Connection refused**: Check server logs and firewall

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for details.

### Quick Contribution Steps
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📝 Changelog

See [CHANGELOG.md](CHANGELOG.md) for a detailed history of changes and releases.

## 🐛 Issues and Support

- **Bug Reports**: [Create an issue](https://github.com/yourusername/cpp-rest-api/issues/new?template=bug_report.md)
- **Feature Requests**: [Create an issue](https://github.com/yourusername/cpp-rest-api/issues/new?template=feature_request.md)
- **Questions**: [Start a discussion](https://github.com/yourusername/cpp-rest-api/discussions)

## ⭐ Star History

If you find this project useful, please consider giving it a star! ⭐

[![Star History Chart](https://api.star-history.com/svg?repos=yourusername/cpp-rest-api&type=Date)](https://star-history.com/#yourusername/cpp-rest-api&Date)

## 👥 Contributors

Thanks to all the contributors who have helped make this project better!

[![Contributors](https://contrib.rocks/image?repo=yourusername/cpp-rest-api)](https://github.com/yourusername/cpp-rest-api/graphs/contributors)

## 🔗 Related Projects

- [cpp-httplib](https://github.com/yhirose/cpp-httplib) - HTTP library for C++
- [nlohmann/json](https://github.com/nlohmann/json) - JSON for Modern C++
- [CMake](https://cmake.org/) - Cross-platform build system

## 📊 Project Statistics

![GitHub repo size](https://img.shields.io/github/repo-size/yourusername/cpp-rest-api)
![GitHub language count](https://img.shields.io/github/languages/count/yourusername/cpp-rest-api)
![GitHub top language](https://img.shields.io/github/languages/top/yourusername/cpp-rest-api)
![GitHub last commit](https://img.shields.io/github/last-commit/yourusername/cpp-rest-api)

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### What this means:
- ✅ Commercial use
- ✅ Modification
- ✅ Distribution
- ✅ Private use
- ❌ Liability
- ❌ Warranty

## 🙏 Acknowledgments

- [cpp-httplib](https://github.com/yhirose/cpp-httplib) for the excellent HTTP server library
- [nlohmann/json](https://github.com/nlohmann/json) for the modern JSON library
- The C++ community for continuous innovation and support
- All contributors and users of this project

---

**Made with ❤️ by the C++ community**

[⬆ Back to top](#c-rest-api-application)