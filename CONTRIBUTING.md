# Contributing to C++ REST API

Thank you for your interest in contributing to this C++ REST API project! This document provides guidelines and information for contributors.

## Getting Started

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Git for version control
- Basic understanding of REST APIs and C++

### Development Setup
1. Fork the repository
2. Clone your fork:
   ```bash
   git clone https://github.com/yourusername/cpp-rest-api.git
   cd cpp-rest-api
   ```
3. Build the project:
   ```bash
   # Windows
   build.bat
   
   # Linux/macOS
   make
   ```

## Development Guidelines

### Code Style
- Follow modern C++17 practices
- Use RAII for resource management
- Prefer smart pointers over raw pointers
- Use meaningful variable and function names
- Include comprehensive comments for complex logic

### Architecture Principles
- **MVC Pattern**: Maintain separation between Models, Views (JSON responses), and Controllers
- **Single Responsibility**: Each class should have one clear purpose
- **Thread Safety**: All shared resources must be properly synchronized
- **Error Handling**: Always provide meaningful error messages and proper HTTP status codes

### File Organization
```
src/
├── controllers/    # HTTP request handlers
├── models/         # Data structures and validation
├── services/       # Business logic
├── utils/          # Utility classes (logging, responses)
└── main.cpp       # Application entry point
```

## Adding New Features

### Adding New Endpoints
1. Create route handler in appropriate controller
2. Add business logic to corresponding service
3. Update main.cpp to register the route
4. Add tests for the new functionality
5. Update API documentation

### Adding New Models
1. Create header file in `src/models/`
2. Implement JSON serialization/deserialization
3. Add validation logic
4. Include comprehensive unit tests

### Example: Adding a New Endpoint
```cpp
// In UserController.hpp
void getUserByEmail(const httplib::Request& req, httplib::Response& res) {
    // Implementation here
}

// In main.cpp setupRoutes()
server.Get("/api/users/email/:email", [this](const httplib::Request& req, httplib::Response& res) {
    userController.getUserByEmail(req, res);
});
```

## Testing

### Running Tests
```bash
# Run the demo server
python demo_server.py

# In another terminal, run tests
# Windows
powershell -ExecutionPolicy Bypass -File examples\test_api.ps1

# Linux/macOS
./examples/test_api.sh
```

### Writing Tests
- Test all CRUD operations
- Test error cases and edge conditions
- Verify proper HTTP status codes
- Test JSON response format
- Include performance tests for concurrent requests

## Code Review Process

### Before Submitting
- [ ] Code builds successfully on all platforms
- [ ] All tests pass
- [ ] Code follows style guidelines
- [ ] Documentation is updated
- [ ] No memory leaks or resource issues

### Pull Request Guidelines
1. Create a feature branch from main
2. Make atomic commits with clear messages
3. Include tests for new functionality
4. Update documentation as needed
5. Ensure CI/CD passes

## Documentation

### API Documentation
- Update README.md for new endpoints
- Include example requests/responses
- Document error conditions
- Update Postman collection if available

### Code Documentation
- Use clear, descriptive comments
- Document complex algorithms
- Include usage examples
- Document thread safety considerations

## Performance Considerations

### Guidelines
- Minimize memory allocations in hot paths
- Use appropriate data structures (e.g., unordered_map for lookups)
- Consider async processing for long-running operations
- Profile code for bottlenecks

### Benchmarking
```bash
# Example load testing with Apache Bench
ab -n 1000 -c 10 http://localhost:8080/api/users
```

## Security

### Best Practices
- Validate all input data
- Use proper error handling to avoid information leakage
- Implement rate limiting for production use
- Use HTTPS in production
- Sanitize user input to prevent injection attacks

## Release Process

### Version Numbering
We follow Semantic Versioning (SemVer):
- MAJOR.MINOR.PATCH
- MAJOR: Breaking changes
- MINOR: New features (backward compatible)
- PATCH: Bug fixes

### Release Checklist
- [ ] All tests pass
- [ ] Documentation updated
- [ ] Version number bumped
- [ ] CHANGELOG.md updated
- [ ] Tag created
- [ ] Release notes written

## Getting Help

### Resources
- [C++ REST API Documentation](README.md)
- [HTTP Status Codes Reference](https://httpstatuses.com/)
- [JSON for Modern C++](https://json.nlohmann.me/)
- [cpp-httplib Documentation](https://github.com/yhirose/cpp-httplib)

### Support
- Open an issue for bug reports
- Use discussions for questions
- Check existing issues before creating new ones
- Provide minimal reproducible examples

## Recognition

Contributors are recognized in:
- README.md Contributors section
- Release notes
- Git commit history

Thank you for contributing to make this project better!