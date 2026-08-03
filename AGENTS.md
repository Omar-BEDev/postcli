# AGENTS.md — Development Guidelines & Code Standards

This document establishes the mandatory coding standards, quality gates, and architectural rules required for any contributor or AI agent working on the `postcli` project.

---

## 1. Code Style & Formatting

- **Indentation:**
  - Using **Tabs (`\t`) is strictly prohibited**.
  - Use **4 spaces** per indentation level.
- **Braces Style:**
  - Strictly follow **K&R style**:
    - Place the opening brace `{` on the same line as the statement, loop, condition, or function definition.
    - Place the closing brace `}` on a new, separate line.
  - **Example:**
    ```c
    if (condition) {
        do_something();
    } else {
        do_other_thing();
    }
    ```

---

## 2. Code Comments & Rationale

- Comments must be added for any technical or design decision made in the code.
- The purpose of these comments is to **justify the implementation choices** and explain the reasoning to facilitate understanding for future reviewers and maintainers.

---

## 3. Testing & Quality Gate

- **100% Pass Rate Requirement:** All tests must pass successfully. **No code will be accepted or merged if any test fails.**
- Always run the complete test suite (`make test`) and ensure all tests pass before submitting any code changes.

---

## 4. Directory & Module Architecture

- **Modular Directory Organization:** Assign one dedicated directory per module according to the project's modular architecture.
- Avoid dumping unrelated files directly into root or flat folders to prevent file clutter and maintain clean project structure.

---

## 5. Libraries & Performance in C

- **Pure / Native C:** Do not import or depend on external C libraries for trivial or standard tasks.
- The codebase must rely on standard native C to ensure maximum execution speed, minimal overhead, and small binary size.
- **Exception:** External libraries are only allowed if there is a **well-documented and compelling performance or technical justification**.

---

## 6. Contribution Workflow

- Thoroughly read and strictly adhere to all contribution guidelines, commit conventions, and Pull Request (PR) templates specified for the repository.
