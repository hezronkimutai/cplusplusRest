# System Patterns - C++ REST Application

## Architecture Overview
```
┌─────────────────┐
│   HTTP Client   │
└─────────────────┘
         │
         ▼
┌─────────────────┐
│  HTTP Server    │
│  (cpp-httplib)  │
└─────────────────┘
         │
         ▼
┌─────────────────┐
│  Route Handler  │
│   Controller    │
└─────────────────┘
         │
         ▼
┌─────────────────┐
│  User Service   │
│  (Business Logic)│
└─────────────────┘
         │
         ▼
┌─────────────────┐
│  Data Storage   │
│  (In-Memory)    │
└─────────────────┘
```

## Key Design Patterns
- **MVC Pattern**: Separation of concerns with controllers, models, and views
- **Repository Pattern**: Abstract data access layer
- **Factory Pattern**: For creating response objects
- **RAII**: Automatic resource management
- **Singleton**: For server instance and configuration

## Component Relationships
- **Server**: Main HTTP server using cpp-httplib
- **Controllers**: Handle HTTP requests and responses
- **Services**: Business logic and data manipulation
- **Models**: Data structures and validation
- **Utils**: JSON handling, logging, error management

## Critical Implementation Paths
1. HTTP Request → Route Matching → Controller → Service → Data Layer
2. Error Handling → Status Code → JSON Response
3. JSON Parsing → Validation → Business Logic → Response