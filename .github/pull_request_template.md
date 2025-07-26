## Description

Brief description of the changes made in this pull request.

## Type of Change

Please delete options that are not relevant.

- [ ] Bug fix (non-breaking change which fixes an issue)
- [ ] New feature (non-breaking change which adds functionality)
- [ ] Breaking change (fix or feature that would cause existing functionality to not work as expected)
- [ ] Documentation update
- [ ] Performance improvement
- [ ] Code refactoring
- [ ] Test improvements

## Changes Made

Detailed list of changes:

- [ ] Added/Modified API endpoint: `[METHOD] /api/endpoint`
- [ ] Updated data models
- [ ] Enhanced error handling
- [ ] Improved logging
- [ ] Updated documentation
- [ ] Added tests
- [ ] Other: _describe_

## API Changes (if applicable)

### New Endpoints
```http
GET /api/new-endpoint
```

### Modified Endpoints
```http
PUT /api/existing-endpoint
```

### Deprecated Endpoints
- `DELETE /api/old-endpoint` - Use `DELETE /api/new-endpoint` instead

## Testing

- [ ] All existing tests pass
- [ ] New tests added for new functionality
- [ ] Manual testing completed
- [ ] API endpoints tested with curl/Postman
- [ ] Cross-platform testing (Windows/Linux/macOS)

### Test Results
```bash
# Paste test output here
```

## Checklist

### Code Quality
- [ ] Code follows project style guidelines
- [ ] Self-review of the code completed
- [ ] Code is commented, particularly in hard-to-understand areas
- [ ] No compiler warnings
- [ ] Memory leaks checked (if applicable)

### Documentation
- [ ] Documentation updated (README, API docs, etc.)
- [ ] CHANGELOG.md updated
- [ ] Comments added for complex code
- [ ] Usage examples provided (if new feature)

### Compatibility
- [ ] Changes are backward compatible
- [ ] Dependencies updated in CMakeLists.txt (if applicable)
- [ ] Cross-platform compatibility verified
- [ ] No breaking changes (or clearly documented)

## Performance Impact

- [ ] No performance impact
- [ ] Performance improved
- [ ] Performance impact acceptable
- [ ] Performance benchmarked

## Security Considerations

- [ ] No security implications
- [ ] Security implications reviewed
- [ ] Input validation added/updated
- [ ] No sensitive data exposed

## Related Issues

Fixes #(issue_number)
Closes #(issue_number)
Related to #(issue_number)

## Screenshots (if applicable)

Add screenshots of API responses, logs, or other relevant output.

## Additional Notes

Any additional information that reviewers should know.

## Deployment Notes

Special instructions for deployment (if any):

- [ ] No special deployment requirements
- [ ] Requires configuration changes
- [ ] Requires data migration
- [ ] Requires dependency updates

---

**Reviewer Notes:**
- Please test the API endpoints manually
- Verify cross-platform compatibility
- Check for memory leaks in long-running tests
- Validate error handling with invalid inputs