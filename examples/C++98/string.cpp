// CodeNebula - C++98 Example: string
// Compile: g++ -std=c++98 -Wall -Wextra -o example string.cpp

// std::string is a dynamic character array providing rich text manipulation.
// It manages its own memory and provides find, substr, append, compare,
// c_str and many other operations.

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>

// C++98-compatible toupper wrapper for std::transform
char to_upper(char c) {
    return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
}

char to_lower(char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

int main() {
    // --- Construction ---
    std::cout << "=== Construction ===" << std::endl;
    std::string s1;                          // empty
    std::string s2("Hello, World!");         // from C-string
    std::string s3(s2);                      // copy
    std::string s4(5, '*');                  // 5 copies of '*'
    std::string s5(s2, 7, 5);               // substring: "World"
    std::string s6(s2.begin(), s2.begin() + 5); // iterator range: "Hello"

    std::cout << "s1 (empty):     \"" << s1 << "\" (size=" << s1.size() << ")" << std::endl;
    std::cout << "s2 (C-string):  \"" << s2 << "\"" << std::endl;
    std::cout << "s3 (copy):      \"" << s3 << "\"" << std::endl;
    std::cout << "s4 (5, '*'):    \"" << s4 << "\"" << std::endl;
    std::cout << "s5 (substr):    \"" << s5 << "\"" << std::endl;
    std::cout << "s6 (iter):      \"" << s6 << "\"" << std::endl;

    // --- find ---
    std::cout << "\n=== find ===" << std::endl;
    std::string text = "The quick brown fox jumps over the lazy dog";
    std::cout << "Text: \"" << text << "\"" << std::endl;

    // Find a substring
    std::string::size_type pos = text.find("fox");
    if (pos != std::string::npos) {
        std::cout << "\"fox\" found at position: " << pos << std::endl;
    }

    pos = text.find("cat");
    if (pos == std::string::npos) {
        std::cout << "\"cat\" not found (npos)" << std::endl;
    }

    // Find a single character
    pos = text.find('q');
    std::cout << "'q' found at position: " << pos << std::endl;

    // Find starting from a position
    pos = text.find("the", 10);
    std::cout << "\"the\" after position 10: " << pos << std::endl;

    // rfind (reverse find)
    pos = text.rfind("the");
    std::cout << "Last \"the\" at position: " << pos << std::endl;

    // find_first_of / find_last_of
    pos = text.find_first_of("aeiou");
    std::cout << "First vowel at position: " << pos
              << " ('" << text[pos] << "')" << std::endl;

    pos = text.find_last_of("aeiou");
    std::cout << "Last vowel at position: " << pos
              << " ('" << text[pos] << "')" << std::endl;

    // find_first_not_of
    std::string padded = "   hello   ";
    pos = padded.find_first_not_of(' ');
    std::cout << "First non-space in \"" << padded << "\": position " << pos << std::endl;

    // --- substr ---
    std::cout << "\n=== substr ===" << std::endl;
    std::string full = "Hello, World!";

    std::string sub1 = full.substr(0, 5);     // "Hello"
    std::string sub2 = full.substr(7);        // "World!" (to end)
    std::string sub3 = full.substr(7, 5);     // "World"

    std::cout << "full:           \"" << full << "\"" << std::endl;
    std::cout << "substr(0, 5):   \"" << sub1 << "\"" << std::endl;
    std::cout << "substr(7):      \"" << sub2 << "\"" << std::endl;
    std::cout << "substr(7, 5):   \"" << sub3 << "\"" << std::endl;

    // --- append ---
    std::cout << "\n=== append ===" << std::endl;
    std::string result = "Hello";
    std::cout << "Start: \"" << result << "\"" << std::endl;

    result.append(", ");
    std::cout << "append(\", \"): \"" << result << "\"" << std::endl;

    result.append("World");
    std::cout << "append(\"World\"): \"" << result << "\"" << std::endl;

    result.append(3, '!');
    std::cout << "append(3, '!'): \"" << result << "\"" << std::endl;

    // Using operator+=
    result += " Bye";
    std::cout << "+= \" Bye\": \"" << result << "\"" << std::endl;

    // Using operator+
    std::string greeting = std::string("Hi") + " " + "there";
    std::cout << "operator+: \"" << greeting << "\"" << std::endl;

    // --- compare ---
    std::cout << "\n=== compare ===" << std::endl;
    std::string a = "apple";
    std::string b = "banana";
    std::string c = "apple";

    int cmp = a.compare(b);
    std::cout << "\"apple\".compare(\"banana\") = " << cmp
              << " (" << (cmp < 0 ? "less" : cmp > 0 ? "greater" : "equal") << ")" << std::endl;

    cmp = b.compare(a);
    std::cout << "\"banana\".compare(\"apple\") = " << cmp
              << " (" << (cmp < 0 ? "less" : cmp > 0 ? "greater" : "equal") << ")" << std::endl;

    cmp = a.compare(c);
    std::cout << "\"apple\".compare(\"apple\") = " << cmp
              << " (" << (cmp < 0 ? "less" : cmp > 0 ? "greater" : "equal") << ")" << std::endl;

    // Comparison operators
    std::cout << "\n\"apple\" == \"apple\": " << (a == c ? "true" : "false") << std::endl;
    std::cout << "\"apple\" != \"banana\": " << (a != b ? "true" : "false") << std::endl;
    std::cout << "\"apple\" < \"banana\": " << (a < b ? "true" : "false") << std::endl;
    std::cout << "\"banana\" > \"apple\": " << (b > a ? "true" : "false") << std::endl;

    // --- c_str ---
    std::cout << "\n=== c_str ===" << std::endl;
    std::string msg = "Hello from C++98";
    const char* cstr = msg.c_str();
    std::cout << "c_str(): " << cstr << std::endl;
    std::cout << "c_str() length (strlen): " << std::strlen(cstr) << std::endl;
    std::cout << "string length: " << msg.length() << std::endl;

    // --- Element access ---
    std::cout << "\n=== Element access ===" << std::endl;
    std::string word = "Hello";
    std::cout << "word[0] = " << word[0] << std::endl;
    std::cout << "word.at(4) = " << word.at(4) << std::endl;
    word[0] = 'J';
    std::cout << "After word[0]='J': " << word << std::endl;

    // --- insert and erase ---
    std::cout << "\n=== insert and erase ===" << std::endl;
    std::string s = "Hello World";
    std::cout << "Original: \"" << s << "\"" << std::endl;

    s.insert(5, ",");
    std::cout << "insert(5, \",\"): \"" << s << "\"" << std::endl;

    s.erase(5, 1);
    std::cout << "erase(5, 1): \"" << s << "\"" << std::endl;

    s.erase(5);
    std::cout << "erase(5): \"" << s << "\"" << std::endl;

    // --- replace ---
    std::cout << "\n=== replace ===" << std::endl;
    std::string rep = "Hello, World!";
    rep.replace(7, 5, "C++98");
    std::cout << "replace \"World\" with \"C++98\": \"" << rep << "\"" << std::endl;

    // --- size, length, empty, clear ---
    std::cout << "\n=== size, length, empty, clear ===" << std::endl;
    std::string info = "test";
    std::cout << "size(): " << info.size() << std::endl;
    std::cout << "length(): " << info.length() << std::endl;
    std::cout << "empty(): " << (info.empty() ? "true" : "false") << std::endl;
    info.clear();
    std::cout << "After clear: empty()=" << (info.empty() ? "true" : "false") << std::endl;

    // --- Iteration ---
    std::cout << "\n=== Iteration ===" << std::endl;
    std::string iter_str = "Hello";
    std::cout << "Forward: ";
    for (std::string::iterator it = iter_str.begin(); it != iter_str.end(); ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;

    std::cout << "Reverse: ";
    for (std::string::reverse_iterator rit = iter_str.rbegin();
         rit != iter_str.rend(); ++rit) {
        std::cout << *rit;
    }
    std::cout << std::endl;

    // --- Case conversion using std::transform ---
    std::cout << "\n=== Case conversion ===" << std::endl;
    std::string mixed = "Hello World";
    std::string upper = mixed;
    std::transform(upper.begin(), upper.end(), upper.begin(), to_upper);
    std::cout << "Upper: " << upper << std::endl;

    std::string lower = mixed;
    std::transform(lower.begin(), lower.end(), lower.begin(), to_lower);
    std::cout << "Lower: " << lower << std::endl;

    // --- swap ---
    std::cout << "\n=== swap ===" << std::endl;
    std::string x = "first";
    std::string y = "second";
    std::cout << "Before: x=\"" << x << "\", y=\"" << y << "\"" << std::endl;
    x.swap(y);
    std::cout << "After:  x=\"" << x << "\", y=\"" << y << "\"" << std::endl;

    return 0;
}

/*
Expected output:
=== Construction ===
s1 (empty):     "" (size=0)
s2 (C-string):  "Hello, World!"
s3 (copy):      "Hello, World!"
s4 (5, '*'):    "*****"
s5 (substr):    "World"
s6 (iter):      "Hello"

=== find ===
Text: "The quick brown fox jumps over the lazy dog"
"fox" found at position: 16
"cat" not found (npos)
'q' found at position: 4
"the" after position 10: 31
Last "the" at position: 31
First vowel at position: 2 ('e')
Last vowel at position: 41 ('o')
First non-space in "   hello   ": position 3

=== substr ===
full:           "Hello, World!"
substr(0, 5):   "Hello"
substr(7):      "World!"
substr(7, 5):   "World"

=== append ===
Start: "Hello"
append(", "): "Hello, "
append("World"): "Hello, World"
append(3, '!'): "Hello, World!!!"
+= " Bye": "Hello, World!!! Bye"
operator+: "Hi there"

=== compare ===
"apple".compare("banana") = -1 (less)
"banana".compare("apple") = 1 (greater)
"apple".compare("apple") = 0 (equal)

"apple" == "apple": true
"apple" != "banana": true
"apple" < "banana": true
"banana" > "apple": true

=== c_str ===
c_str(): Hello from C++98
c_str() length (strlen): 16
string length: 16

=== Element access ===
word[0] = H
word.at(4) = o
After word[0]='J': Jello

=== insert and erase ===
Original: "Hello World"
insert(5, ","): "Hello, World"
erase(5, 1): "Hello World"
erase(5): "Hello"

=== replace ===
replace "World" with "C++98": "Hello, C++98!"

=== size, length, empty, clear ===
size(): 4
length(): 4
empty(): false
After clear: empty()=true

=== Iteration ===
Forward: Hello
Reverse: olleH

=== Case conversion ===
Upper: HELLO WORLD
Lower: hello world

=== swap ===
Before: x="first", y="second"
After:  x="second", y="first"
*/
