// CodeNebula - C++98 Example: Multiple Inheritance
// Compile: g++ -std=c++98 -Wall -Wextra -o example multiple_inheritance.cpp
//
// This example demonstrates:
// - A class inheriting from two (or more) base classes
// - Constructor/destructor order with multiple bases
// - Ambiguity when two bases have identically named members
// - Resolving ambiguity with scope resolution (Base::member)
// - Practical use case: combining capabilities from multiple bases

#include <iostream>
#include <cstring>

// ============================================================
// Base class 1: Printer
// ============================================================
class Printer {
private:
    char model[64];

public:
    Printer(const char* m) {
        std::strncpy(model, m, 63);
        model[63] = '\0';
        std::cout << "  Printer constructed: " << model << std::endl;
    }

    ~Printer() {
        std::cout << "  Printer destructor: " << model << std::endl;
    }

    void printDocument(const char* doc) const {
        std::cout << "  [Printer:" << model << "] Printing: " << doc << std::endl;
    }

    // This method name also exists in Scanner -- causes ambiguity
    void status() const {
        std::cout << "  [Printer:" << model << "] Status: Ready to print" << std::endl;
    }

    void info() const {
        std::cout << "  Printer model: " << model << std::endl;
    }
};

// ============================================================
// Base class 2: Scanner
// ============================================================
class Scanner {
private:
    int resolution;  // DPI

public:
    Scanner(int dpi) : resolution(dpi) {
        std::cout << "  Scanner constructed: " << resolution << " DPI" << std::endl;
    }

    ~Scanner() {
        std::cout << "  Scanner destructor: " << resolution << " DPI" << std::endl;
    }

    void scanDocument(const char* doc) const {
        std::cout << "  [Scanner:" << resolution << "DPI] Scanning: " << doc << std::endl;
    }

    // Same name as Printer::status() -- ambiguous in MultiFunctionDevice
    void status() const {
        std::cout << "  [Scanner:" << resolution << "DPI] Status: Ready to scan" << std::endl;
    }

    void info() const {
        std::cout << "  Scanner resolution: " << resolution << " DPI" << std::endl;
    }
};

// ============================================================
// Derived class: MultiFunctionDevice (inherits from BOTH)
// ============================================================
class MultiFunctionDevice : public Printer, public Scanner {
private:
    char deviceName[64];

public:
    // Constructors for both bases are called in declaration order:
    // Printer first (listed first in inheritance), then Scanner
    MultiFunctionDevice(const char* name, const char* printerModel, int scanDPI)
        : Printer(printerModel), Scanner(scanDPI)
    {
        std::strncpy(deviceName, name, 63);
        deviceName[63] = '\0';
        std::cout << "  MultiFunctionDevice constructed: " << deviceName << std::endl;
    }

    ~MultiFunctionDevice() {
        std::cout << "  MultiFunctionDevice destructor: " << deviceName << std::endl;
    }

    // Resolve the ambiguity by providing a unified status()
    void status() const {
        std::cout << "  [" << deviceName << "] Combined status:" << std::endl;
        Printer::status();    // explicitly call Printer's version
        Scanner::status();    // explicitly call Scanner's version
    }

    void copyDocument(const char* doc) const {
        std::cout << "  [" << deviceName << "] Copying: " << doc << std::endl;
        Scanner::scanDocument(doc);
        Printer::printDocument(doc);
    }
};

// ============================================================
// Another example: Amphibious vehicle
// ============================================================
class LandVehicle {
protected:
    int wheels;
public:
    LandVehicle(int w) : wheels(w) {
        std::cout << "  LandVehicle(" << wheels << " wheels)" << std::endl;
    }
    ~LandVehicle() {
        std::cout << "  ~LandVehicle" << std::endl;
    }
    void drive() const {
        std::cout << "  Driving on " << wheels << " wheels" << std::endl;
    }
};

class WaterVehicle {
protected:
    int hulls;
public:
    WaterVehicle(int h) : hulls(h) {
        std::cout << "  WaterVehicle(" << hulls << " hulls)" << std::endl;
    }
    ~WaterVehicle() {
        std::cout << "  ~WaterVehicle" << std::endl;
    }
    void sail() const {
        std::cout << "  Sailing with " << hulls << " hull(s)" << std::endl;
    }
};

class AmphibiousVehicle : public LandVehicle, public WaterVehicle {
public:
    AmphibiousVehicle()
        : LandVehicle(4), WaterVehicle(1)
    {
        std::cout << "  AmphibiousVehicle constructed" << std::endl;
    }
    ~AmphibiousVehicle() {
        std::cout << "  ~AmphibiousVehicle" << std::endl;
    }
    void describe() const {
        std::cout << "  I have " << wheels << " wheels and "
                  << hulls << " hull(s)" << std::endl;
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. CONSTRUCTOR ORDER (multiple bases)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        MultiFunctionDevice mfd("OfficeJet", "HP-3000", 600);
        std::cout << "\n  -- leaving scope --" << std::endl;
    }
    std::cout << "  (Destructors: derived first, then bases in reverse)\n" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "2. USING CAPABILITIES FROM BOTH BASES" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        MultiFunctionDevice mfd("AllInOne", "Canon-500", 1200);
        std::cout << std::endl;

        mfd.printDocument("report.pdf");    // from Printer
        mfd.scanDocument("photo.jpg");      // from Scanner
        mfd.copyDocument("letter.doc");     // combines both
        std::cout << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. AMBIGUITY RESOLUTION" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        MultiFunctionDevice mfd("MFD-Pro", "Epson-200", 300);
        std::cout << std::endl;

        // mfd.info();  // ERROR: ambiguous -- both Printer and Scanner have info()

        // Solution 1: Use scope resolution
        std::cout << "  Calling Printer::info() explicitly:" << std::endl;
        mfd.Printer::info();

        std::cout << "  Calling Scanner::info() explicitly:" << std::endl;
        mfd.Scanner::info();

        // Solution 2: The derived class overrides with its own version
        std::cout << "\n  Calling overridden status():" << std::endl;
        mfd.status();  // calls MultiFunctionDevice::status()

        // Can still call specific base versions
        std::cout << "\n  Calling Printer::status() directly:" << std::endl;
        mfd.Printer::status();
        std::cout << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. AMPHIBIOUS VEHICLE (practical example)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        AmphibiousVehicle av;
        std::cout << std::endl;

        av.describe();
        av.drive();   // from LandVehicle
        av.sail();    // from WaterVehicle
        std::cout << std::endl;
    }

    return 0;
}

// Expected output:
// ========================================
// 1. CONSTRUCTOR ORDER (multiple bases)
// ========================================
//   Printer constructed: HP-3000
//   Scanner constructed: 600 DPI
//   MultiFunctionDevice constructed: OfficeJet
//
//   -- leaving scope --
//   MultiFunctionDevice destructor: OfficeJet
//   Scanner destructor: 600 DPI
//   Printer destructor: HP-3000
//   (Destructors: derived first, then bases in reverse)
//
// ========================================
// 2. USING CAPABILITIES FROM BOTH BASES
// ========================================
//   ...constructor output...
//   [Printer:Canon-500] Printing: report.pdf
//   [Scanner:1200DPI] Scanning: photo.jpg
//   [AllInOne] Copying: letter.doc
//   [Scanner:1200DPI] Scanning: letter.doc
//   [Printer:Canon-500] Printing: letter.doc
//   ...destructor output...
//
// ========================================
// 3. AMBIGUITY RESOLUTION
// ========================================
//   ...resolving with Printer:: and Scanner:: scope...
//
// ========================================
// 4. AMPHIBIOUS VEHICLE (practical example)
// ========================================
//   LandVehicle(4 wheels)
//   WaterVehicle(1 hulls)
//   AmphibiousVehicle constructed
//   I have 4 wheels and 1 hull(s)
//   Driving on 4 wheels
//   Sailing with 1 hull(s)
//   ...destructor output...
