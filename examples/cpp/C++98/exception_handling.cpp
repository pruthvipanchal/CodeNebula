// CodeNebula - C++98 Example: Exception Handling
// Compile: g++ -std=c++98 -Wall -Wextra -o example exception_handling.cpp

// Exception handling in C++98 uses try/catch/throw to separate error handling
// from normal logic. This example covers: throwing built-in types, standard
// exceptions, custom exception hierarchies, multiple catch blocks, catch-all,
// and exception propagation through the call stack.

#include <iostream>
#include <string>
#include <stdexcept>   // std::runtime_error, std::out_of_range, etc.
#include <cstdio>     // std::sprintf
#include <cmath>

// ------------------------------------------------------------------
// Custom exception hierarchy
// ------------------------------------------------------------------
class AppException {
private:
    std::string message;
public:
    AppException(const std::string& msg) : message(msg) {}
    virtual ~AppException() {}
    virtual std::string what() const { return message; }
};

class FileException : public AppException {
private:
    std::string filename;
public:
    FileException(const std::string& fname, const std::string& msg)
        : AppException(msg), filename(fname) {}
    std::string getFilename() const { return filename; }
    std::string what() const {
        return "FileException [" + filename + "]: " + AppException::what();
    }
};

class NetworkException : public AppException {
private:
    int errorCode;
public:
    NetworkException(int code, const std::string& msg)
        : AppException(msg), errorCode(code) {}
    int getErrorCode() const { return errorCode; }
    std::string what() const {
        // Build the string manually (no std::to_string in C++98)
        std::string result = "NetworkException (code ";
        // Simple int-to-string for small numbers
        char buf[32];
        std::sprintf(buf, "%d", errorCode);
        result += buf;
        result += "): " + AppException::what();
        return result;
    }
};

// ------------------------------------------------------------------
// Functions that throw exceptions
// ------------------------------------------------------------------
double safeDivide(double a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}

int safeArrayAccess(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Array index out of bounds");
    }
    return arr[index];
}

void openFile(const std::string& name) {
    // Simulate a file not found scenario
    throw FileException(name, "File not found");
}

void connectToServer(const std::string& host) {
    // Simulate a network failure
    throw NetworkException(404, std::string("Cannot reach ") + host);
}

// Function that demonstrates exception propagation
void processData() {
    std::cout << "  processData: calling safeDivide(10, 0)..." << std::endl;
    double result = safeDivide(10, 0);  // This will throw
    std::cout << "  This line never executes. result=" << result << std::endl;
}

int main() {
    std::cout << "=== C++98 Exception Handling ===" << std::endl;

    // --- 1. Basic try/catch with std::runtime_error ---
    std::cout << "\n--- 1. Division by zero ---" << std::endl;
    try {
        double r = safeDivide(10.0, 3.0);
        std::cout << "10 / 3 = " << r << std::endl;
        // Expected: 10 / 3 = 3.33333

        r = safeDivide(10.0, 0.0);  // Throws!
        std::cout << "This won't print: " << r << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught runtime_error: " << e.what() << std::endl;
        // Expected: Caught runtime_error: Division by zero
    }

    // --- 2. std::out_of_range ---
    std::cout << "\n--- 2. Array bounds check ---" << std::endl;
    try {
        int arr[] = {10, 20, 30};
        std::cout << "arr[1] = " << safeArrayAccess(arr, 3, 1) << std::endl;
        // Expected: arr[1] = 20
        std::cout << "arr[5] = " << safeArrayAccess(arr, 3, 5) << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught out_of_range: " << e.what() << std::endl;
        // Expected: Caught out_of_range: Array index out of bounds
    }

    // --- 3. Multiple catch blocks ---
    std::cout << "\n--- 3. Multiple catch blocks ---" << std::endl;
    for (int scenario = 0; scenario < 3; ++scenario) {
        try {
            if (scenario == 0) {
                throw 42;                 // throw an int
            } else if (scenario == 1) {
                throw std::string("string exception");  // throw a string
            } else {
                throw 3.14;              // throw a double
            }
        }
        catch (int val) {
            std::cout << "Caught int: " << val << std::endl;
        }
        catch (const std::string& s) {
            std::cout << "Caught string: " << s << std::endl;
        }
        catch (...) {
            // Catch-all handler
            std::cout << "Caught unknown exception type" << std::endl;
        }
    }
    // Expected:
    // Caught int: 42
    // Caught string: string exception
    // Caught unknown exception type

    // --- 4. Custom exception hierarchy ---
    std::cout << "\n--- 4. Custom exceptions ---" << std::endl;
    try {
        openFile("data.txt");
    }
    catch (const FileException& e) {
        std::cout << e.what() << std::endl;
        std::cout << "File was: " << e.getFilename() << std::endl;
    }
    catch (const AppException& e) {
        std::cout << "AppException: " << e.what() << std::endl;
    }
    // Expected:
    // FileException [data.txt]: File not found
    // File was: data.txt

    try {
        connectToServer("example.com");
    }
    catch (const NetworkException& e) {
        std::cout << e.what() << std::endl;
        std::cout << "Error code: " << e.getErrorCode() << std::endl;
    }
    catch (const AppException& e) {
        std::cout << "AppException: " << e.what() << std::endl;
    }
    // Expected:
    // NetworkException (code 404): Cannot reach example.com
    // Error code: 404

    // --- 5. Exception propagation through the call stack ---
    std::cout << "\n--- 5. Exception propagation ---" << std::endl;
    try {
        std::cout << "main: calling processData()..." << std::endl;
        processData();  // Internally calls safeDivide which throws
    }
    catch (const std::runtime_error& e) {
        std::cout << "main caught propagated exception: " << e.what() << std::endl;
    }
    // Expected:
    // main: calling processData()...
    //   processData: calling safeDivide(10, 0)...
    // main caught propagated exception: Division by zero

    // --- 6. Nested try/catch ---
    std::cout << "\n--- 6. Nested try/catch ---" << std::endl;
    try {
        std::cout << "Outer try block" << std::endl;
        try {
            std::cout << "Inner try block - throwing..." << std::endl;
            throw std::runtime_error("inner error");
        }
        catch (const std::runtime_error& e) {
            std::cout << "Inner catch: " << e.what() << std::endl;
            // Re-throw to outer handler
            throw;
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << "Outer catch (re-thrown): " << e.what() << std::endl;
    }

    std::cout << "\nProgram completed normally." << std::endl;

    return 0;
}

/*
Expected Output:
=== C++98 Exception Handling ===

--- 1. Division by zero ---
10 / 3 = 3.33333
Caught runtime_error: Division by zero

--- 2. Array bounds check ---
arr[1] = 20
Caught out_of_range: Array index out of bounds

--- 3. Multiple catch blocks ---
Caught int: 42
Caught string: string exception
Caught unknown exception type

--- 4. Custom exceptions ---
FileException [data.txt]: File not found
File was: data.txt
NetworkException (code 404): Cannot reach example.com
Error code: 404

--- 5. Exception propagation ---
main: calling processData()...
  processData: calling safeDivide(10, 0)...
main caught propagated exception: Division by zero

--- 6. Nested try/catch ---
Outer try block
Inner try block - throwing...
Inner catch: inner error
Outer catch (re-thrown): inner error

Program completed normally.
*/
