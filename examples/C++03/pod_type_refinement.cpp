// CodeNebula - C++03 Example: POD (Plain Old Data) Type Definition Refinement
// Compile: g++ -std=c++03 -Wall -Wextra -o pod_type_refinement pod_type_refinement.cpp
//
// C++03 refined the definition of POD types. A POD type:
//   - Has no user-declared constructors, destructor, or copy assignment
//   - Has no virtual functions or virtual base classes
//   - Has no non-static members of non-POD type, reference type, or pointer-to-member type
//   - All non-static data members have the same access control
//
// POD types are safe for: memcpy, memset, binary I/O, C interop

#include <iostream>
#include <cstring>
#include <cstdio>

// ============================================================
// 1. POD struct — safe for low-level operations
// ============================================================
struct PacketHeader {
    unsigned int  srcIP;
    unsigned int  dstIP;
    unsigned short srcPort;
    unsigned short dstPort;
    unsigned char  protocol;
    unsigned char  flags;
    unsigned short checksum;
};

// ============================================================
// 2. Non-POD struct — has constructor (NOT safe for memcpy)
// ============================================================
struct Connection {
    unsigned int ip;
    unsigned short port;
    bool connected;

    Connection() : ip(0), port(0), connected(false) {}
};

// ============================================================
// 3. POD with nested POD — still POD
// ============================================================
struct Vec3 {
    float x, y, z;
};

struct Transform {
    Vec3  position;
    Vec3  rotation;
    Vec3  scale;
    int   entityId;
};

// ============================================================
// 4. Non-POD — has virtual function
// ============================================================
struct Shape {
    int x, y;
    virtual void draw() const {
        std::cout << "  Shape at (" << x << "," << y << ")" << std::endl;
    }
    virtual ~Shape() {}
};

// Helper to print raw memory
void hexDump(const void* ptr, std::size_t size) {
    const unsigned char* bytes = static_cast<const unsigned char*>(ptr);
    for (std::size_t i = 0; i < size && i < 16; ++i) {
        std::printf("%02X ", bytes[i]);
    }
    if (size > 16) std::printf("...");
    std::printf("\n");
}

int main() {
    std::cout << "=== POD Type Definition Refinement ===" << std::endl;

    // --------------------------------------------------------
    // Demo 1: memcpy with POD (safe)
    // --------------------------------------------------------
    std::cout << "\n--- Demo 1: memcpy with POD ---" << std::endl;

    PacketHeader original;
    original.srcIP    = 0xC0A80001;  // 192.168.0.1
    original.dstIP    = 0x0A000001;  // 10.0.0.1
    original.srcPort  = 8080;
    original.dstPort  = 443;
    original.protocol = 6;           // TCP
    original.flags    = 0x02;        // SYN
    original.checksum = 0xABCD;

    PacketHeader copy;
    std::memcpy(&copy, &original, sizeof(PacketHeader));

    std::cout << "  Original srcPort: " << original.srcPort << std::endl;
    std::cout << "  Copy srcPort:     " << copy.srcPort << std::endl;
    std::cout << "  Match: " << (std::memcmp(&original, &copy, sizeof(PacketHeader)) == 0 ? "YES" : "NO") << std::endl;

    // --------------------------------------------------------
    // Demo 2: memset to zero-fill a POD (safe)
    // --------------------------------------------------------
    std::cout << "\n--- Demo 2: memset Zero-Fill ---" << std::endl;

    PacketHeader blank;
    std::memset(&blank, 0, sizeof(PacketHeader));

    std::cout << "  blank.srcIP:    " << blank.srcIP << std::endl;
    std::cout << "  blank.dstPort:  " << blank.dstPort << std::endl;
    std::cout << "  blank.protocol: " << static_cast<int>(blank.protocol) << std::endl;

    // --------------------------------------------------------
    // Demo 3: Nested POD — still safe for memcpy
    // --------------------------------------------------------
    std::cout << "\n--- Demo 3: Nested POD memcpy ---" << std::endl;

    Transform t1;
    t1.position.x = 1.0f; t1.position.y = 2.0f; t1.position.z = 3.0f;
    t1.rotation.x = 0.0f; t1.rotation.y = 90.0f; t1.rotation.z = 0.0f;
    t1.scale.x = 1.0f;    t1.scale.y = 1.0f;    t1.scale.z = 1.0f;
    t1.entityId = 42;

    Transform t2;
    std::memcpy(&t2, &t1, sizeof(Transform));

    std::cout << "  t2.position: (" << t2.position.x << ", "
              << t2.position.y << ", " << t2.position.z << ")" << std::endl;
    std::cout << "  t2.rotation.y: " << t2.rotation.y << std::endl;
    std::cout << "  t2.entityId:   " << t2.entityId << std::endl;

    // --------------------------------------------------------
    // Demo 4: sizeof comparison — POD vs non-POD
    // --------------------------------------------------------
    std::cout << "\n--- Demo 4: Size Comparison ---" << std::endl;

    std::cout << "  sizeof(PacketHeader): " << sizeof(PacketHeader)
              << " bytes (POD, no vtable)" << std::endl;
    std::cout << "  sizeof(Connection):   " << sizeof(Connection)
              << " bytes (non-POD, has constructor)" << std::endl;
    std::cout << "  sizeof(Transform):    " << sizeof(Transform)
              << " bytes (POD, nested PODs)" << std::endl;
    std::cout << "  sizeof(Shape):        " << sizeof(Shape)
              << " bytes (non-POD, has vtable ptr)" << std::endl;

    // --------------------------------------------------------
    // Demo 5: Binary I/O simulation with POD
    // --------------------------------------------------------
    std::cout << "\n--- Demo 5: Binary I/O Pattern ---" << std::endl;

    // Simulate writing POD to a buffer (like a file or network)
    unsigned char buffer[sizeof(PacketHeader)];
    std::memcpy(buffer, &original, sizeof(PacketHeader));

    std::cout << "  Serialized " << sizeof(PacketHeader) << " bytes: ";
    hexDump(buffer, sizeof(PacketHeader));

    // Simulate reading back
    PacketHeader deserialized;
    std::memcpy(&deserialized, buffer, sizeof(PacketHeader));

    std::cout << "  Deserialized srcPort: " << deserialized.srcPort << std::endl;
    std::cout << "  Deserialized dstPort: " << deserialized.dstPort << std::endl;
    std::cout << "  Deserialized protocol: " << static_cast<int>(deserialized.protocol) << std::endl;

    // --------------------------------------------------------
    // Demo 6: Array of PODs — bulk copy
    // --------------------------------------------------------
    std::cout << "\n--- Demo 6: Bulk Array Copy ---" << std::endl;

    Vec3 points[3];
    points[0].x = 1.0f; points[0].y = 0.0f; points[0].z = 0.0f;
    points[1].x = 0.0f; points[1].y = 1.0f; points[1].z = 0.0f;
    points[2].x = 0.0f; points[2].y = 0.0f; points[2].z = 1.0f;

    Vec3 backup[3];
    std::memcpy(backup, points, sizeof(points));

    std::cout << "  Copied " << sizeof(points) << " bytes ("
              << sizeof(points) / sizeof(Vec3) << " Vec3 structs)" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "  backup[" << i << "]: ("
                  << backup[i].x << ", " << backup[i].y << ", "
                  << backup[i].z << ")" << std::endl;
    }

    std::cout << "\n=== POD types: safe for memcpy, memset, and binary I/O ===" << std::endl;

    return 0;
}

// Expected Output:
// === POD Type Definition Refinement ===
//
// --- Demo 1: memcpy with POD ---
//   Original srcPort: 8080
//   Copy srcPort:     8080
//   Match: YES
//
// --- Demo 2: memset Zero-Fill ---
//   blank.srcIP:    0
//   blank.dstPort:  0
//   blank.protocol: 0
//
// --- Demo 3: Nested POD memcpy ---
//   t2.position: (1, 2, 3)
//   t2.rotation.y: 90
//   t2.entityId:   42
//
// --- Demo 4: Size Comparison ---
//   sizeof(PacketHeader): 16 bytes (POD, no vtable)
//   sizeof(Connection):   8 bytes (non-POD, has constructor)
//   sizeof(Transform):    40 bytes (POD, nested PODs)
//   sizeof(Shape):        16 bytes (non-POD, has vtable ptr)
//
// --- Demo 5: Binary I/O Pattern ---
//   Serialized 16 bytes: 01 00 A8 C0 01 00 00 0A 90 1F BB 01 06 02 CD AB
//   Deserialized srcPort: 8080
//   Deserialized dstPort: 443
//   Deserialized protocol: 6
//
// --- Demo 6: Bulk Array Copy ---
//   Copied 36 bytes (3 Vec3 structs)
//   backup[0]: (1, 0, 0)
//   backup[1]: (0, 1, 0)
//   backup[2]: (0, 0, 1)
//
// === POD types: safe for memcpy, memset, and binary I/O ===
