# PowerShell script to test the C++ REST API
# Run this after starting the server with: build\bin\CppRestAPI.exe

$baseUrl = "http://localhost:8080"

Write-Host "Testing C++ REST API..." -ForegroundColor Green

# Test health check
Write-Host "`n1. Testing health check..." -ForegroundColor Yellow
try {
    $response = Invoke-RestMethod -Uri "$baseUrl/health" -Method GET
    Write-Host "Health check response:" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "Health check failed: $_" -ForegroundColor Red
}

# Test API info
Write-Host "`n2. Testing API info..." -ForegroundColor Yellow
try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api" -Method GET
    Write-Host "API info response:" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "API info failed: $_" -ForegroundColor Red
}

# Test get all users (should be empty initially)
Write-Host "`n3. Testing GET all users..." -ForegroundColor Yellow
try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api/users" -Method GET
    Write-Host "All users response:" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "Get all users failed: $_" -ForegroundColor Red
}

# Test create user
Write-Host "`n4. Testing POST create user..." -ForegroundColor Yellow
$newUser = @{
    name = "John Doe"
    email = "john.doe@example.com"
    age = 30
} | ConvertTo-Json

try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api/users" -Method POST -Body $newUser -ContentType "application/json"
    Write-Host "Create user response:" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
    $userId = $response.data.id
} catch {
    Write-Host "Create user failed: $_" -ForegroundColor Red
    $userId = 1  # Assume user ID for further tests
}

# Test get user by ID
Write-Host "`n5. Testing GET user by ID..." -ForegroundColor Yellow
try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api/users/$userId" -Method GET
    Write-Host "Get user by ID response:" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "Get user by ID failed: $_" -ForegroundColor Red
}

# Test update user
Write-Host "`n6. Testing PUT update user..." -ForegroundColor Yellow
$updatedUser = @{
    name = "John Smith"
    email = "john.smith@example.com"
    age = 31
} | ConvertTo-Json

try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api/users/$userId" -Method PUT -Body $updatedUser -ContentType "application/json"
    Write-Host "Update user response:" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "Update user failed: $_" -ForegroundColor Red
}

# Test get all users again (should show updated user)
Write-Host "`n7. Testing GET all users (after update)..." -ForegroundColor Yellow
try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api/users" -Method GET
    Write-Host "All users response (after update):" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "Get all users failed: $_" -ForegroundColor Red
}

# Test delete user
Write-Host "`n8. Testing DELETE user..." -ForegroundColor Yellow
try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api/users/$userId" -Method DELETE
    Write-Host "Delete user response:" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "Delete user failed: $_" -ForegroundColor Red
}

# Test get all users again (should be empty)
Write-Host "`n9. Testing GET all users (after delete)..." -ForegroundColor Yellow
try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api/users" -Method GET
    Write-Host "All users response (after delete):" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "Get all users failed: $_" -ForegroundColor Red
}

# Test error cases
Write-Host "`n10. Testing error cases..." -ForegroundColor Yellow

# Test invalid user ID
try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api/users/999" -Method GET
    Write-Host "Get non-existent user response:" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "Get non-existent user correctly failed: $_" -ForegroundColor Green
}

# Test invalid JSON
$invalidJson = "{ invalid json }"
try {
    $response = Invoke-RestMethod -Uri "$baseUrl/api/users" -Method POST -Body $invalidJson -ContentType "application/json"
    Write-Host "Invalid JSON response:" -ForegroundColor Cyan
    $response | ConvertTo-Json -Depth 3
} catch {
    Write-Host "Invalid JSON correctly failed: $_" -ForegroundColor Green
}

Write-Host "`nAPI testing completed!" -ForegroundColor Green