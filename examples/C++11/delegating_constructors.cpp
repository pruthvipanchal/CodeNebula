// CodeNebula - C++11 Example: Delegating Constructors
// Compile: g++ -std=c++11 -Wall -Wextra -o example delegating_constructors.cpp

// Demonstrates delegating constructors: one constructor calling another
// to share initialization logic. This eliminates duplicated code that
// previously required a separate init() helper method.

#include <iostream>
#include <string>
#include <ctime>

// Real-world scenario: a database connection class with multiple constructors
class DbConnection {
    std::string host_;
    int port_;
    std::string user_;
    std::string database_;
    bool connected_;

public:
    // Primary constructor (most parameters)
    DbConnection(const std::string& host, int port,
                 const std::string& user, const std::string& database)
        : host_(host), port_(port), user_(user),
          database_(database), connected_(false)
    {
        std::cout << "  [Primary ctor] " << user_ << "@" << host_
                  << ":" << port_ << "/" << database_ << std::endl;
    }

    // Delegate: default port
    DbConnection(const std::string& host, const std::string& user,
                 const std::string& database)
        : DbConnection(host, 5432, user, database)    // delegate!
    {
        std::cout << "  [Default port ctor]" << std::endl;
    }

    // Delegate: localhost defaults
    DbConnection(const std::string& database)
        : DbConnection("localhost", 5432, "admin", database)  // delegate!
    {
        std::cout << "  [Local ctor]" << std::endl;
    }

    // Delegate: default everything
    DbConnection()
        : DbConnection("test_db")  // delegate!
    {
        std::cout << "  [Default ctor]" << std::endl;
    }

    void print() const
    {
        std::cout << "  Connection: " << user_ << "@" << host_
                  << ":" << port_ << "/" << database_ << std::endl;
    }
};

// Another example: a Log entry with timestamps
class LogEntry {
    std::string level_;
    std::string message_;
    std::string timestamp_;

    static std::string currentTime()
    {
        return "2026-03-23 10:30:00";  // simplified for reproducible output
    }

public:
    // Primary constructor
    LogEntry(const std::string& level, const std::string& msg,
             const std::string& time)
        : level_(level), message_(msg), timestamp_(time) {}

    // Delegate: auto-timestamp
    LogEntry(const std::string& level, const std::string& msg)
        : LogEntry(level, msg, currentTime()) {}

    // Delegate: info-level shorthand
    explicit LogEntry(const std::string& msg)
        : LogEntry("INFO", msg) {}

    void print() const
    {
        std::cout << "  [" << timestamp_ << "] " << level_
                  << ": " << message_ << std::endl;
    }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. DbConnection delegation chain
    // ------------------------------------------------------------------
    std::cout << "=== Full parameters ===" << std::endl;
    DbConnection db1("db.example.com", 3306, "root", "production");
    db1.print();
    std::cout << std::endl;

    std::cout << "=== Default port ===" << std::endl;
    DbConnection db2("staging.local", "dev", "staging_db");
    db2.print();
    std::cout << std::endl;

    std::cout << "=== Local shorthand ===" << std::endl;
    DbConnection db3("my_app");
    db3.print();
    std::cout << std::endl;

    std::cout << "=== Full defaults ===" << std::endl;
    DbConnection db4;
    db4.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. LogEntry delegation
    // ------------------------------------------------------------------
    std::cout << "=== Log entries ===" << std::endl;
    LogEntry log1("ERROR", "Disk full", "2026-03-23 09:00:00");
    LogEntry log2("WARN", "High memory usage");
    LogEntry log3("Server started");

    log1.print();
    log2.print();
    log3.print();

    return 0;
}

/*
Expected output:

=== Full parameters ===
  [Primary ctor] root@db.example.com:3306/production
  Connection: root@db.example.com:3306/production

=== Default port ===
  [Primary ctor] dev@staging.local:5432/staging_db
  [Default port ctor]
  Connection: dev@staging.local:5432/staging_db

=== Local shorthand ===
  [Primary ctor] admin@localhost:5432/my_app
  [Local ctor]
  Connection: admin@localhost:5432/my_app

=== Full defaults ===
  [Primary ctor] admin@localhost:5432/test_db
  [Local ctor]
  [Default ctor]
  Connection: admin@localhost:5432/test_db

=== Log entries ===
  [2026-03-23 09:00:00] ERROR: Disk full
  [2026-03-23 10:30:00] WARN: High memory usage
  [2026-03-23 10:30:00] INFO: Server started
*/
