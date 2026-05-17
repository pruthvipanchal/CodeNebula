// CodeNebula - C++98 Example: Encapsulation
// Compile: g++ -std=c++98 -Wall -Wextra -o example encapsulation.cpp
//
// This example demonstrates:
// - Private data members hidden from outside access
// - Public getter/setter methods as the controlled interface
// - Validation in setters to enforce invariants
// - Why encapsulation matters: data integrity and flexibility

#include <iostream>
#include <cstring>

// ============================================================
// 1. BankAccount: encapsulated balance with validation
// ============================================================
class BankAccount {
private:
    // --- Hidden internal state ---
    char owner[64];
    double balance;
    int    accountNumber;

    // Private helper
    static int nextAccountNumber;

public:
    BankAccount(const char* name, double initialDeposit) : balance(0.0) {
        std::strncpy(owner, name, 63);
        owner[63] = '\0';
        accountNumber = ++nextAccountNumber;

        // Validate initial deposit
        if (initialDeposit > 0.0) {
            balance = initialDeposit;
        }
        std::cout << "  Account #" << accountNumber
                  << " created for " << owner << std::endl;
    }

    // --- Getters (read-only access) ---
    const char* getOwner() const { return owner; }
    double getBalance() const { return balance; }
    int getAccountNumber() const { return accountNumber; }

    // --- Setters with validation ---
    bool deposit(double amount) {
        if (amount <= 0.0) {
            std::cout << "  ERROR: deposit amount must be positive" << std::endl;
            return false;
        }
        balance += amount;
        std::cout << "  Deposited $" << amount
                  << " -> Balance: $" << balance << std::endl;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0.0) {
            std::cout << "  ERROR: withdrawal amount must be positive" << std::endl;
            return false;
        }
        if (amount > balance) {
            std::cout << "  ERROR: insufficient funds (need $" << amount
                      << ", have $" << balance << ")" << std::endl;
            return false;
        }
        balance -= amount;
        std::cout << "  Withdrew $" << amount
                  << " -> Balance: $" << balance << std::endl;
        return true;
    }

    void printStatement() const {
        std::cout << "  +--------------------------+" << std::endl;
        std::cout << "  | Account #" << accountNumber << std::endl;
        std::cout << "  | Owner: " << owner << std::endl;
        std::cout << "  | Balance: $" << balance << std::endl;
        std::cout << "  +--------------------------+" << std::endl;
    }
};

int BankAccount::nextAccountNumber = 1000;

// ============================================================
// 2. Temperature sensor with read-only external access
// ============================================================
class TemperatureSensor {
private:
    double currentTemp;
    double minTemp;
    double maxTemp;
    int    readingCount;

public:
    TemperatureSensor()
        : currentTemp(0.0), minTemp(999.0), maxTemp(-999.0), readingCount(0) {}

    // Only the sensor itself can record readings (simulating hardware input)
    void recordReading(double temp) {
        if (temp < -273.15) {
            std::cout << "  ERROR: temperature below absolute zero!" << std::endl;
            return;
        }
        currentTemp = temp;
        ++readingCount;
        if (temp < minTemp) minTemp = temp;
        if (temp > maxTemp) maxTemp = temp;
    }

    // Public read-only access
    double getCurrent() const { return currentTemp; }
    double getMin() const { return minTemp; }
    double getMax() const { return maxTemp; }
    int    getReadingCount() const { return readingCount; }

    void printStats() const {
        std::cout << "  Readings: " << readingCount
                  << ", Current: " << currentTemp
                  << ", Min: " << minTemp
                  << ", Max: " << maxTemp << std::endl;
    }
};

// ============================================================
// 3. EmailValidator: internal logic hidden, clean interface
// ============================================================
class EmailValidator {
private:
    char email[128];
    bool valid;

    // Private validation logic -- implementation can change
    // without affecting the public interface
    bool hasAtSign() const {
        for (int i = 0; email[i] != '\0'; ++i) {
            if (email[i] == '@') return true;
        }
        return false;
    }

    bool hasDot() const {
        for (int i = 0; email[i] != '\0'; ++i) {
            if (email[i] == '.') return true;
        }
        return false;
    }

    bool isLongEnough() const {
        return std::strlen(email) >= 5;  // a@b.c
    }

    void validate() {
        valid = hasAtSign() && hasDot() && isLongEnough();
    }

public:
    EmailValidator(const char* e) : valid(false) {
        std::strncpy(email, e, 127);
        email[127] = '\0';
        validate();
    }

    // Simple public interface
    bool isValid() const { return valid; }
    const char* getEmail() const { return email; }

    void setEmail(const char* e) {
        std::strncpy(email, e, 127);
        email[127] = '\0';
        validate();  // re-validate on change
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. BANK ACCOUNT (validated operations)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        BankAccount acc("Alice", 1000.0);
        acc.printStatement();

        std::cout << std::endl;
        acc.deposit(500.0);
        acc.withdraw(200.0);

        std::cout << "\n  Attempting invalid operations:" << std::endl;
        acc.deposit(-50.0);      // rejected
        acc.withdraw(5000.0);    // rejected: insufficient funds
        acc.withdraw(-10.0);     // rejected

        std::cout << std::endl;
        acc.printStatement();

        // acc.balance = 999999;  // COMPILE ERROR: balance is private!
        std::cout << "\n  acc.balance = 999999;  // COMPILE ERROR: private!" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. TEMPERATURE SENSOR (read-only stats)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        TemperatureSensor sensor;

        double readings[] = { 22.5, 23.1, 19.8, 25.0, 21.3 };
        int count = 5;

        for (int i = 0; i < count; ++i) {
            sensor.recordReading(readings[i]);
        }

        // Invalid reading rejected
        sensor.recordReading(-300.0);

        sensor.printStats();

        // sensor.currentTemp = 100;  // COMPILE ERROR: private!
        std::cout << "  sensor.currentTemp = 100;  // COMPILE ERROR: private!" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. EMAIL VALIDATOR (hidden logic)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        const char* emails[] = {
            "user@example.com",
            "invalid",
            "no@dot",
            "a@b.c",
            ""
        };
        int count = 5;

        for (int i = 0; i < count; ++i) {
            EmailValidator ev(emails[i]);
            std::cout << "  \"" << ev.getEmail() << "\" -> "
                      << (ev.isValid() ? "VALID" : "INVALID") << std::endl;
        }

        std::cout << "\n  Changing email via setter:" << std::endl;
        EmailValidator ev("bad");
        std::cout << "  \"" << ev.getEmail() << "\" -> "
                  << (ev.isValid() ? "VALID" : "INVALID") << std::endl;

        ev.setEmail("now.valid@email.com");
        std::cout << "  \"" << ev.getEmail() << "\" -> "
                  << (ev.isValid() ? "VALID" : "INVALID") << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. WHY ENCAPSULATION MATTERS" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  - Data integrity: setters enforce valid states" << std::endl;
    std::cout << "  - Flexibility: internal representation can change" << std::endl;
    std::cout << "    without breaking client code" << std::endl;
    std::cout << "  - Debugging: all changes go through known entry points" << std::endl;
    std::cout << "  - Security: sensitive data cannot be tampered with directly" << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. BANK ACCOUNT (validated operations)
// ========================================
//   Account #1001 created for Alice
//   +--------------------------+
//   | Account #1001
//   | Owner: Alice
//   | Balance: $1000
//   +--------------------------+
//
//   Deposited $500 -> Balance: $1500
//   Withdrew $200 -> Balance: $1300
//
//   Attempting invalid operations:
//   ERROR: deposit amount must be positive
//   ERROR: insufficient funds (need $5000, have $1300)
//   ERROR: withdrawal amount must be positive
//
//   +--------------------------+
//   | Account #1001
//   | Owner: Alice
//   | Balance: $1300
//   +--------------------------+
//
//   acc.balance = 999999;  // COMPILE ERROR: private!
//
// ========================================
// 2. TEMPERATURE SENSOR (read-only stats)
// ========================================
//   ERROR: temperature below absolute zero!
//   Readings: 5, Current: 21.3, Min: 19.8, Max: 25
//   sensor.currentTemp = 100;  // COMPILE ERROR: private!
//
// ========================================
// 3. EMAIL VALIDATOR (hidden logic)
// ========================================
//   "user@example.com" -> VALID
//   "invalid" -> INVALID
//   "no@dot" -> INVALID
//   "a@b.c" -> VALID
//   "" -> INVALID
//   ...
//
// ========================================
// 4. WHY ENCAPSULATION MATTERS
// ========================================
//   ...summary...
