# VS Code C++ Dev Container Sample

## Purpose
This repo is a small C++ sample project configured with CMake and GoogleTest. It is meant to demonstrate a clean CMake-based workflow that works in GitHub Codespaces or locally using VS Code Dev Containers.

## Use in GitHub Codespaces
1. Open this repo on GitHub.
2. Click Code -> Codespaces -> Create codespace on main.
3. When the Codespace opens in VS Code (web), wait for the container to finish building.
4. Build and test using the CMake Tools extension:
   - Select the CMake preset: dev-debug.
   - Build the default target.
   - Run tests from the Testing view or with the CMake Tools test action.

## Use locally with VS Code + Dev Containers
### Requirements
- Docker Desktop (or another Docker engine compatible with Dev Containers)
- Visual Studio Code
- VS Code Dev Containers extension
- Git

### Steps
1. Clone the repo locally.
2. Open the repo folder in VS Code.
3. Run the command: Dev Containers: Reopen in Container.
4. Wait for the container to build and the tools to install.
5. Build and test using CMake Tools (select the dev-debug preset).

## Build and Test via CLI
If you prefer the command line, you can build and test the project without opening VS Code:

```bash
cmake -B build
cmake --build build
ctest --test-dir build --verbose
```

## GitHub Actions Pipeline
This repo includes a GitHub Actions workflow ([.github/workflows/build-and-test.yml](.github/workflows/build-and-test.yml)) that automatically builds and tests the project on every push and pull request to the `main` branch. The workflow:

1. Installs CMake, GCC, and GoogleTest
2. Configures and builds the project
3. Runs all tests with CTest

This ensures code quality and catches regressions before merging.

## Notes
- The sample code lives in src and include.
- Tests are in test and run with GoogleTest.
