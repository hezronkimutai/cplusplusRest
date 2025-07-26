#!/bin/bash
# Bash script to test the C++ REST API using curl
# Run this after starting the server with: ./build/bin/CppRestAPI

BASE_URL="http://localhost:8080"

echo "Testing C++ REST API..."

# Test health check
echo -e "\n1. Testing health check..."
curl -s -X GET "$BASE_URL/health" | jq . || echo "Health check failed"

# Test API info
echo -e "\n2. Testing API info..."
curl -s -X GET "$BASE_URL/api" | jq . || echo "API info failed"

# Test get all users (should be empty initially)
echo -e "\n3. Testing GET all users..."
curl -s -X GET "$BASE_URL/api/users" | jq . || echo "Get all users failed"

# Test create user
echo -e "\n4. Testing POST create user..."
USER_RESPONSE=$(curl -s -X POST "$BASE_URL/api/users" \
  -H "Content-Type: application/json" \
  -d '{
    "name": "John Doe",
    "email": "john.doe@example.com",
    "age": 30
  }')

echo "$USER_RESPONSE" | jq .

# Extract user ID for subsequent tests
USER_ID=$(echo "$USER_RESPONSE" | jq -r '.data.id // 1')
echo "Created user with ID: $USER_ID"

# Test get user by ID
echo -e "\n5. Testing GET user by ID..."
curl -s -X GET "$BASE_URL/api/users/$USER_ID" | jq . || echo "Get user by ID failed"

# Test update user
echo -e "\n6. Testing PUT update user..."
curl -s -X PUT "$BASE_URL/api/users/$USER_ID" \
  -H "Content-Type: application/json" \
  -d '{
    "name": "John Smith",
    "email": "john.smith@example.com",
    "age": 31
  }' | jq . || echo "Update user failed"

# Test get all users again (should show updated user)
echo -e "\n7. Testing GET all users (after update)..."
curl -s -X GET "$BASE_URL/api/users" | jq . || echo "Get all users failed"

# Test delete user
echo -e "\n8. Testing DELETE user..."
curl -s -X DELETE "$BASE_URL/api/users/$USER_ID" | jq . || echo "Delete user failed"

# Test get all users again (should be empty)
echo -e "\n9. Testing GET all users (after delete)..."
curl -s -X GET "$BASE_URL/api/users" | jq . || echo "Get all users failed"

# Test error cases
echo -e "\n10. Testing error cases..."

# Test invalid user ID
echo -e "\nTesting non-existent user..."
curl -s -X GET "$BASE_URL/api/users/999" | jq .

# Test invalid JSON
echo -e "\nTesting invalid JSON..."
curl -s -X POST "$BASE_URL/api/users" \
  -H "Content-Type: application/json" \
  -d '{ invalid json }' | jq .

# Test missing required fields
echo -e "\nTesting missing required fields..."
curl -s -X POST "$BASE_URL/api/users" \
  -H "Content-Type: application/json" \
  -d '{
    "name": "Test User"
  }' | jq .

# Test invalid email format
echo -e "\nTesting invalid email format..."
curl -s -X POST "$BASE_URL/api/users" \
  -H "Content-Type: application/json" \
  -d '{
    "name": "Test User",
    "email": "invalid-email",
    "age": 25
  }' | jq .

# Test 404 endpoint
echo -e "\nTesting 404 endpoint..."
curl -s -X GET "$BASE_URL/nonexistent" | jq .

echo -e "\nAPI testing completed!"