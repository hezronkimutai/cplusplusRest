#!/usr/bin/env python3
"""
Demo Python server that mimics the C++ REST API structure
This demonstrates what the C++ server would do when compiled and run
"""

from http.server import HTTPServer, BaseHTTPRequestHandler
import json
import re
import time
from urllib.parse import urlparse, parse_qs

class User:
    def __init__(self, id=0, name="", email="", age=0):
        self.id = id
        self.name = name
        self.email = email
        self.age = age
    
    def to_dict(self):
        return {"id": self.id, "name": self.name, "email": self.email, "age": self.age}
    
    @classmethod
    def from_dict(cls, data):
        return cls(data.get("id", 0), data.get("name", ""), data.get("email", ""), data.get("age", 0))
    
    def is_valid(self):
        return self.name and self.email and self.age > 0 and "@" in self.email

class UserService:
    def __init__(self):
        self.users = []
        self.next_id = 1
    
    def get_all_users(self):
        return [user.to_dict() for user in self.users]
    
    def get_user_by_id(self, user_id):
        for user in self.users:
            if user.id == user_id:
                return user.to_dict()
        return None
    
    def create_user(self, user_data):
        user = User.from_dict(user_data)
        user.id = self.next_id
        self.next_id += 1
        self.users.append(user)
        return user.to_dict()
    
    def update_user(self, user_id, user_data):
        for user in self.users:
            if user.id == user_id:
                user.name = user_data.get("name", user.name)
                user.email = user_data.get("email", user.email)
                user.age = user_data.get("age", user.age)
                return user.to_dict()
        return None
    
    def delete_user(self, user_id):
        for i, user in enumerate(self.users):
            if user.id == user_id:
                del self.users[i]
                return True
        return False

class APIHandler(BaseHTTPRequestHandler):
    user_service = UserService()
    
    def log_message(self, format, *args):
        timestamp = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
        print(f"[{timestamp}] [INFO] {self.command} {self.path} - {format % args}")
    
    def send_json_response(self, status_code, data):
        self.send_response(status_code)
        self.send_header('Content-Type', 'application/json')
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        self.end_headers()
        self.wfile.write(json.dumps(data, indent=2).encode())
    
    def do_OPTIONS(self):
        self.send_response(200)
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        self.end_headers()
    
    def do_GET(self):
        if self.path == '/health':
            response = {
                "status": "healthy",
                "timestamp": int(time.time()),
                "service": "C++ REST API (Demo)"
            }
            self.send_json_response(200, response)
        
        elif self.path == '/api':
            response = {
                "message": "Welcome to C++ REST API (Demo)",
                "version": "1.0.0",
                "endpoints": {
                    "GET /health": "Health check",
                    "GET /api/users": "Get all users",
                    "GET /api/users/:id": "Get user by ID",
                    "POST /api/users": "Create new user",
                    "PUT /api/users/:id": "Update user",
                    "DELETE /api/users/:id": "Delete user"
                }
            }
            self.send_json_response(200, response)
        
        elif self.path == '/api/users':
            users = self.user_service.get_all_users()
            response = {
                "success": True,
                "message": "Users retrieved successfully",
                "data": users
            }
            self.send_json_response(200, response)
        
        elif re.match(r'/api/users/(\d+)', self.path):
            user_id = int(re.match(r'/api/users/(\d+)', self.path).group(1))
            user = self.user_service.get_user_by_id(user_id)
            if user:
                response = {
                    "success": True,
                    "message": "User found",
                    "data": user
                }
                self.send_json_response(200, response)
            else:
                response = {
                    "success": False,
                    "message": "User not found"
                }
                self.send_json_response(404, response)
        
        else:
            response = {
                "success": False,
                "message": "Endpoint not found",
                "path": self.path
            }
            self.send_json_response(404, response)
    
    def do_POST(self):
        if self.path == '/api/users':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            try:
                user_data = json.loads(post_data.decode())
                user = User.from_dict(user_data)
                if user.is_valid():
                    created_user = self.user_service.create_user(user_data)
                    response = {
                        "success": True,
                        "message": "User created successfully",
                        "data": created_user
                    }
                    self.send_json_response(201, response)
                else:
                    response = {
                        "success": False,
                        "message": "Validation Error: Invalid user data. Name, email, and age are required."
                    }
                    self.send_json_response(422, response)
            except json.JSONDecodeError:
                response = {
                    "success": False,
                    "message": "Invalid JSON format"
                }
                self.send_json_response(400, response)
    
    def do_PUT(self):
        if re.match(r'/api/users/(\d+)', self.path):
            user_id = int(re.match(r'/api/users/(\d+)', self.path).group(1))
            content_length = int(self.headers['Content-Length'])
            put_data = self.rfile.read(content_length)
            try:
                user_data = json.loads(put_data.decode())
                user = User.from_dict(user_data)
                if user.is_valid():
                    updated_user = self.user_service.update_user(user_id, user_data)
                    if updated_user:
                        response = {
                            "success": True,
                            "message": "User updated successfully",
                            "data": updated_user
                        }
                        self.send_json_response(200, response)
                    else:
                        response = {
                            "success": False,
                            "message": "User not found"
                        }
                        self.send_json_response(404, response)
                else:
                    response = {
                        "success": False,
                        "message": "Validation Error: Invalid user data. Name, email, and age are required."
                    }
                    self.send_json_response(422, response)
            except json.JSONDecodeError:
                response = {
                    "success": False,
                    "message": "Invalid JSON format"
                }
                self.send_json_response(400, response)
    
    def do_DELETE(self):
        if re.match(r'/api/users/(\d+)', self.path):
            user_id = int(re.match(r'/api/users/(\d+)', self.path).group(1))
            if self.user_service.delete_user(user_id):
                response = {
                    "success": True,
                    "message": "User deleted successfully"
                }
                self.send_json_response(200, response)
            else:
                response = {
                    "success": False,
                    "message": "User not found"
                }
                self.send_json_response(404, response)

if __name__ == '__main__':
    port = 8080
    server_address = ('', port)
    httpd = HTTPServer(server_address, APIHandler)
    
    print(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] [INFO] Starting C++ REST API Demo Server on port {port}")
    print(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] [INFO] Health check available at: http://localhost:{port}/health")
    print(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] [INFO] API info available at: http://localhost:{port}/api")
    print(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] [INFO] Users API available at: http://localhost:{port}/api/users")
    print(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] [INFO] This demonstrates the C++ REST API functionality")
    
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print(f"\n[{time.strftime('%Y-%m-%d %H:%M:%S')}] [INFO] Server stopping...")
        httpd.server_close()