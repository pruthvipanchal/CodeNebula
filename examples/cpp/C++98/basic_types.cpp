// CodeNebula - C++98 Example: Basic Types
// Compile: g++ -std=c++98 -Wall -Wextra -o example basic_types.cpp

// Demonstrates all fundamental types in C++98: int, float, double, char, bool,
// short, long, unsigned variants. Shows sizeof and typical value ranges using
// <climits> and <cfloat> constants.

#include <iostream>
#include <climits>
#include <cfloat>

int main()
{
    // ------------------------------------------------------------------
    // 1. bool  (guaranteed to hold true / false)
    // ------------------------------------------------------------------
    bool flag = true;
    std::cout << "=== bool ===" << std::endl;
    std::cout << "  Value       : " << flag << std::endl;
    std::cout << "  sizeof(bool): " << sizeof(bool) << " byte(s)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. char  (holds a single character or small integer)
    // ------------------------------------------------------------------
    char letter = 'A';
    signed char sc = -42;
    unsigned char uc = 200;

    std::cout << "=== char ===" << std::endl;
    std::cout << "  char   value : " << letter
              << "  (as int: " << static_cast<int>(letter) << ")" << std::endl;
    std::cout << "  sizeof(char) : " << sizeof(char) << " byte(s)" << std::endl;
    std::cout << "  CHAR_MIN     : " << CHAR_MIN << std::endl;
    std::cout << "  CHAR_MAX     : " << CHAR_MAX << std::endl;
    std::cout << "  signed char  : " << static_cast<int>(sc) << std::endl;
    std::cout << "  unsigned char: " << static_cast<int>(uc) << std::endl;
    std::cout << "  UCHAR_MAX    : " << UCHAR_MAX << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. short (at least 16 bits)
    // ------------------------------------------------------------------
    short s = -12345;
    unsigned short us = 50000U;

    std::cout << "=== short ===" << std::endl;
    std::cout << "  short value         : " << s << std::endl;
    std::cout << "  unsigned short value: " << us << std::endl;
    std::cout << "  sizeof(short)       : " << sizeof(short) << " byte(s)" << std::endl;
    std::cout << "  SHRT_MIN            : " << SHRT_MIN << std::endl;
    std::cout << "  SHRT_MAX            : " << SHRT_MAX << std::endl;
    std::cout << "  USHRT_MAX           : " << USHRT_MAX << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. int (at least 16 bits, typically 32 bits on modern platforms)
    // ------------------------------------------------------------------
    int i = -100000;
    unsigned int ui = 3000000000U;

    std::cout << "=== int ===" << std::endl;
    std::cout << "  int value         : " << i << std::endl;
    std::cout << "  unsigned int value: " << ui << std::endl;
    std::cout << "  sizeof(int)       : " << sizeof(int) << " byte(s)" << std::endl;
    std::cout << "  INT_MIN           : " << INT_MIN << std::endl;
    std::cout << "  INT_MAX           : " << INT_MAX << std::endl;
    std::cout << "  UINT_MAX          : " << UINT_MAX << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. long (at least 32 bits)
    // ------------------------------------------------------------------
    long l = -2000000000L;
    unsigned long ul = 4000000000UL;

    std::cout << "=== long ===" << std::endl;
    std::cout << "  long value         : " << l << std::endl;
    std::cout << "  unsigned long value: " << ul << std::endl;
    std::cout << "  sizeof(long)       : " << sizeof(long) << " byte(s)" << std::endl;
    std::cout << "  LONG_MIN           : " << LONG_MIN << std::endl;
    std::cout << "  LONG_MAX           : " << LONG_MAX << std::endl;
    std::cout << "  ULONG_MAX          : " << ULONG_MAX << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. float (single-precision IEEE 754)
    // ------------------------------------------------------------------
    float f = 3.14f;

    std::cout << "=== float ===" << std::endl;
    std::cout << "  float value     : " << f << std::endl;
    std::cout << "  sizeof(float)   : " << sizeof(float) << " byte(s)" << std::endl;
    std::cout << "  FLT_MIN (pos)   : " << FLT_MIN << std::endl;
    std::cout << "  FLT_MAX         : " << FLT_MAX << std::endl;
    std::cout << "  FLT_DIG (digits): " << FLT_DIG << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 7. double (double-precision IEEE 754)
    // ------------------------------------------------------------------
    double d = 2.718281828459045;

    std::cout << "=== double ===" << std::endl;
    std::cout << "  double value     : " << d << std::endl;
    std::cout << "  sizeof(double)   : " << sizeof(double) << " byte(s)" << std::endl;
    std::cout << "  DBL_MIN (pos)    : " << DBL_MIN << std::endl;
    std::cout << "  DBL_MAX          : " << DBL_MAX << std::endl;
    std::cout << "  DBL_DIG (digits) : " << DBL_DIG << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 8. long double (extended precision, platform-dependent)
    // ------------------------------------------------------------------
    long double ld = 1.41421356237309504880L;

    std::cout << "=== long double ===" << std::endl;
    std::cout << "  long double value     : " << static_cast<double>(ld) << std::endl;
    std::cout << "  sizeof(long double)   : " << sizeof(long double) << " byte(s)" << std::endl;
    std::cout << "  LDBL_DIG (digits)     : " << LDBL_DIG << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Summary table
    // ------------------------------------------------------------------
    std::cout << "=== Size summary (bytes) ===" << std::endl;
    std::cout << "  bool       : " << sizeof(bool) << std::endl;
    std::cout << "  char       : " << sizeof(char) << std::endl;
    std::cout << "  short      : " << sizeof(short) << std::endl;
    std::cout << "  int        : " << sizeof(int) << std::endl;
    std::cout << "  long       : " << sizeof(long) << std::endl;
    std::cout << "  float      : " << sizeof(float) << std::endl;
    std::cout << "  double     : " << sizeof(double) << std::endl;
    std::cout << "  long double: " << sizeof(long double) << std::endl;

    return 0;
}

/*
Expected output (typical 64-bit platform, sizes may vary):

=== bool ===
  Value       : 1
  sizeof(bool): 1 byte(s)

=== char ===
  char   value : A  (as int: 65)
  sizeof(char) : 1 byte(s)
  CHAR_MIN     : -128
  CHAR_MAX     : 127
  signed char  : -42
  unsigned char: 200
  UCHAR_MAX    : 255

=== short ===
  short value         : -12345
  unsigned short value: 50000
  sizeof(short)       : 2 byte(s)
  SHRT_MIN            : -32768
  SHRT_MAX            : 32767
  USHRT_MAX           : 65535

=== int ===
  int value         : -100000
  unsigned int value: 3000000000
  sizeof(int)       : 4 byte(s)
  INT_MIN           : -2147483648
  INT_MAX           : 2147483647
  UINT_MAX          : 4294967295

=== long ===
  long value         : -2000000000
  unsigned long value: 4000000000
  sizeof(long)       : 4 byte(s)  (or 8 on some platforms)
  LONG_MIN           : -2147483648
  LONG_MAX           : 2147483647
  ULONG_MAX          : 4294967295

=== float ===
  float value     : 3.14
  sizeof(float)   : 4 byte(s)
  FLT_MIN (pos)   : 1.17549e-38
  FLT_MAX         : 3.40282e+38
  FLT_DIG (digits): 6

=== double ===
  double value     : 2.71828
  sizeof(double)   : 8 byte(s)
  DBL_MIN (pos)    : 2.22507e-308
  DBL_MAX          : 1.79769e+308
  DBL_DIG (digits) : 15

=== long double ===
  long double value     : 1.41421
  sizeof(long double)   : 12 byte(s) (or 8/16 depending on platform)
  LDBL_DIG (digits)     : 18

=== Size summary (bytes) ===
  bool       : 1
  char       : 1
  short      : 2
  int        : 4
  long       : 4
  float      : 4
  double     : 8
  long double: 12
*/
