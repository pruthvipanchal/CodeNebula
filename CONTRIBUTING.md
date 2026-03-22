# Contributing to CodeNebula

Thank you for your interest in contributing! This guide will help you get started.

## Ways to Contribute

- **Add examples** -- Write compilable `.cpp` files for concepts that lack them
- **Improve documentation** -- Clarify explanations, fix typos, or add real-world scenarios
- **Report issues** -- Found an error or a missing concept? Open an issue
- **Suggest improvements** -- Ideas for structure, formatting, or new content are welcome

## Getting Started

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/your-feature-name`
3. Make your changes
4. Commit with a clear message: `git commit -m "Add example for C++17 structured bindings"`
5. Push to your fork: `git push origin feature/your-feature-name`
6. Open a pull request

## Documentation Format

Every concept should follow this four-part structure:

```
## Concept Name
**Explanation**: What it is and why it matters.
**Real-World Scenario**: A practical use case.
**Snippet**:
```cpp
// Minimal code demonstrating the concept
```
**Example**: [filename.cpp](link-to-example)
```

## Example Files

When adding example files:

- Place them in `examples/{standard}/` (e.g., `examples/C++17/structured_bindings.cpp`)
- Include clear comments explaining the code
- Ensure the file compiles cleanly with the appropriate standard flag
- Use `-Wall -Wextra -pedantic` and fix all warnings
- Include expected output in a comment at the top or bottom of the file

## Code Style

- Use descriptive variable names
- Add comments for non-obvious logic
- Follow the style of existing examples (see `examples/C++98/basic_types.cpp`)
- Keep examples focused on one concept

## Commit Messages

- Use present tense: "Add example" not "Added example"
- Be specific: "Add C++17 std::optional example" not "Update examples"
- Reference the standard and concept when applicable

## Questions?

Open an issue if you have questions or need guidance. We are happy to help.
