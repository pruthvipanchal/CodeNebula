// CodeNebula - C++98 Example: Bitfields
// Compile: g++ -std=c++98 -Wall -Wextra -o example bitfields.cpp

// Demonstrates bitfield members in structs: packing multiple values into
// minimal bits, flag fields, practical use cases, and size comparisons.

#include <iostream>
#include <cstring>

// ------------------------------------------------------------------
// 1. Basic bitfield struct - packs flags into a single byte (or few bytes)
// ------------------------------------------------------------------
struct FilePermissions {
    unsigned int read    : 1;   // 1 bit: 0 or 1
    unsigned int write   : 1;   // 1 bit: 0 or 1
    unsigned int execute : 1;   // 1 bit: 0 or 1
    unsigned int hidden  : 1;   // 1 bit: 0 or 1
};

// ------------------------------------------------------------------
// 2. Bitfield with multi-bit fields
// ------------------------------------------------------------------
struct DatePacked {
    unsigned int day   : 5;     // 1-31  (needs 5 bits)
    unsigned int month : 4;     // 1-12  (needs 4 bits)
    unsigned int year  : 12;    // 0-4095 (needs 12 bits)
};

// Equivalent without bitfields for size comparison
struct DateNormal {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

// ------------------------------------------------------------------
// 3. Bitfield for a color value (RGB565 format, common in embedded)
// ------------------------------------------------------------------
struct RGB565 {
    unsigned short red   : 5;   // 0-31
    unsigned short green : 6;   // 0-63
    unsigned short blue  : 5;   // 0-31
};

// ------------------------------------------------------------------
// 4. Bitfield with signed fields
// ------------------------------------------------------------------
struct SmallInts {
    signed int a : 4;    // -8 to 7
    signed int b : 4;    // -8 to 7
    signed int c : 8;    // -128 to 127
};

// ------------------------------------------------------------------
// 5. TCP-like header flags (practical networking example)
// ------------------------------------------------------------------
struct TcpFlags {
    unsigned int fin : 1;
    unsigned int syn : 1;
    unsigned int rst : 1;
    unsigned int psh : 1;
    unsigned int ack : 1;
    unsigned int urg : 1;
    unsigned int reserved : 2;  // padding / reserved bits
};

void printPermissions(const FilePermissions& p)
{
    std::cout << (p.read    ? "r" : "-")
              << (p.write   ? "w" : "-")
              << (p.execute ? "x" : "-")
              << (p.hidden  ? "h" : "-");
}

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: File permission flags
    // ------------------------------------------------------------------
    std::cout << "=== File Permission Bitfields ===" << std::endl;

    FilePermissions fp;
    std::memset(&fp, 0, sizeof(fp));    // zero all bits

    fp.read = 1;
    fp.write = 1;
    fp.execute = 0;
    fp.hidden = 0;

    std::cout << "  Permissions: ";
    printPermissions(fp);
    std::cout << std::endl;
    std::cout << "  sizeof(FilePermissions): " << sizeof(FilePermissions)
              << " byte(s) (4 flags in ~1 byte, but may be padded to int)"
              << std::endl;
    std::cout << std::endl;

    // Modify individual flags
    fp.execute = 1;
    fp.hidden = 1;
    std::cout << "  After adding execute and hidden: ";
    printPermissions(fp);
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: Packed date vs. normal struct
    // ------------------------------------------------------------------
    std::cout << "=== Packed Date ===" << std::endl;

    DatePacked dp;
    std::memset(&dp, 0, sizeof(dp));
    dp.day   = 22;
    dp.month = 3;
    dp.year  = 2026;

    std::cout << "  Date: " << dp.year << "-"
              << dp.month << "-" << dp.day << std::endl;
    std::cout << "  sizeof(DatePacked)  : " << sizeof(DatePacked)
              << " byte(s)" << std::endl;
    std::cout << "  sizeof(DateNormal)  : " << sizeof(DateNormal)
              << " byte(s)" << std::endl;
    std::cout << "  Space saved: " << sizeof(DateNormal) - sizeof(DatePacked)
              << " byte(s)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: RGB565 color packing
    // ------------------------------------------------------------------
    std::cout << "=== RGB565 Color ===" << std::endl;

    RGB565 color;
    std::memset(&color, 0, sizeof(color));
    color.red   = 31;   // max red
    color.green = 0;
    color.blue  = 0;

    std::cout << "  Pure red:   R=" << color.red
              << " G=" << color.green
              << " B=" << color.blue << std::endl;

    color.red   = 0;
    color.green = 63;   // max green
    color.blue  = 0;
    std::cout << "  Pure green: R=" << color.red
              << " G=" << color.green
              << " B=" << color.blue << std::endl;

    color.red   = 31;
    color.green = 63;
    color.blue  = 31;
    std::cout << "  White:      R=" << color.red
              << " G=" << color.green
              << " B=" << color.blue << std::endl;

    std::cout << "  sizeof(RGB565): " << sizeof(RGB565)
              << " byte(s) (16 bits packed into 2 bytes)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: Signed bitfields
    // ------------------------------------------------------------------
    std::cout << "=== Signed Bitfields ===" << std::endl;

    SmallInts si;
    std::memset(&si, 0, sizeof(si));
    si.a = 5;
    si.b = -3;
    si.c = -100;

    std::cout << "  a (4-bit signed) = " << si.a << "  (range: -8 to 7)" << std::endl;
    std::cout << "  b (4-bit signed) = " << si.b << "  (range: -8 to 7)" << std::endl;
    std::cout << "  c (8-bit signed) = " << si.c << "  (range: -128 to 127)" << std::endl;

    // Show overflow behavior: 4-bit signed can only hold -8..7
    si.a = 7;
    std::cout << "  a set to 7       = " << si.a << "  (max for 4-bit signed)" << std::endl;
    std::cout << "  sizeof(SmallInts): " << sizeof(SmallInts) << " byte(s)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: TCP flags
    // ------------------------------------------------------------------
    std::cout << "=== TCP-like Flags ===" << std::endl;

    TcpFlags tcp;
    std::memset(&tcp, 0, sizeof(tcp));

    // SYN packet
    tcp.syn = 1;
    std::cout << "  SYN packet:     "
              << "FIN=" << tcp.fin << " SYN=" << tcp.syn
              << " RST=" << tcp.rst << " PSH=" << tcp.psh
              << " ACK=" << tcp.ack << " URG=" << tcp.urg << std::endl;

    // SYN-ACK packet
    tcp.ack = 1;
    std::cout << "  SYN-ACK packet: "
              << "FIN=" << tcp.fin << " SYN=" << tcp.syn
              << " RST=" << tcp.rst << " PSH=" << tcp.psh
              << " ACK=" << tcp.ack << " URG=" << tcp.urg << std::endl;

    // ACK + PSH (data packet)
    tcp.syn = 0;
    tcp.psh = 1;
    std::cout << "  Data packet:    "
              << "FIN=" << tcp.fin << " SYN=" << tcp.syn
              << " RST=" << tcp.rst << " PSH=" << tcp.psh
              << " ACK=" << tcp.ack << " URG=" << tcp.urg << std::endl;

    std::cout << "  sizeof(TcpFlags): " << sizeof(TcpFlags) << " byte(s)" << std::endl;

    return 0;
}

/*
Expected output:

=== File Permission Bitfields ===
  Permissions: rw--
  sizeof(FilePermissions): 4 byte(s) (4 flags in ~1 byte, but may be padded to int)

  After adding execute and hidden: rwxh

=== Packed Date ===
  Date: 2026-3-22
  sizeof(DatePacked)  : 4 byte(s)
  sizeof(DateNormal)  : 12 byte(s)
  Space saved: 8 byte(s)

=== RGB565 Color ===
  Pure red:   R=31 G=0 B=0
  Pure green: R=0 G=63 B=0
  White:      R=31 G=63 B=31
  sizeof(RGB565): 2 byte(s) (16 bits packed into 2 bytes)

=== Signed Bitfields ===
  a (4-bit signed) = 5  (range: -8 to 7)
  b (4-bit signed) = -3  (range: -8 to 7)
  c (8-bit signed) = -100  (range: -128 to 127)
  a set to 7       = 7  (max for 4-bit signed)
  sizeof(SmallInts): 4 byte(s)

=== TCP-like Flags ===
  SYN packet:     FIN=0 SYN=1 RST=0 PSH=0 ACK=0 URG=0
  SYN-ACK packet: FIN=0 SYN=1 RST=0 PSH=0 ACK=1 URG=0
  Data packet:    FIN=0 SYN=0 RST=0 PSH=1 ACK=1 URG=0
  sizeof(TcpFlags): 4 byte(s)
*/
