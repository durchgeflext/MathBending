#include <catch2/catch_test_macros.hpp>

#include <MathBending/util/Integer128.hpp>

TEST_CASE("Integer128 basic assignment functions", "[Integer128 assign]") {
    Integer128 a{0x1234567890abcdef, 0xfedcba0987654321};
    Integer128 b = a;
    Integer128 c = a;

    REQUIRE(a == b);
    REQUIRE(a == c);
}

TEST_CASE("UnsignedInteger128 basic assignment functions", "[UnsignedInteger128 assign]") {
    UnsignedInteger128 a{0x1234567890abcdef, 0xfedcba0987654321};
    UnsignedInteger128 b = a;
    UnsignedInteger128 c = a;

    REQUIRE(a == b);
    REQUIRE(a == c);
}

TEST_CASE("Integer128 constructors", "[Integer128 constructor]") {
    // Copy constructor
    const Integer128 a{0x1234567890abcdef, 0xfedcba0987654321};
    const Integer128 b(a);
    REQUIRE(a == b);

    // Move constructor
    Integer128 c{0x1234567890abcdef, 0xfedcba0987654321};
    const Integer128 d(std::move(c));
    REQUIRE(d == Integer128{0x1234567890abcdef, 0xfedcba0987654321});

    // Single-argument constructor
    const Integer128 e(0x1234567890abcdef);
    const Integer128 f(-0x1234567890abcdef);
    REQUIRE(e == Integer128{0, 0x1234567890abcdef});
    REQUIRE(f == Integer128{-1, 0xedcba9876f543211});
}

TEST_CASE("UnsignedInteger128 constructors", "[UnsignedInteger128 constructor]") {
    // Copy constructor
    const UnsignedInteger128 a{0x1234567890abcdef, 0xfedcba0987654321};
    const UnsignedInteger128 b(a);
    REQUIRE(a == b);

    // Move constructor
    UnsignedInteger128 c{0x1234567890abcdef, 0xfedcba0987654321};
    const UnsignedInteger128 d(std::move(c));
    REQUIRE(d == UnsignedInteger128{0x1234567890abcdef, 0xfedcba0987654321});

    // Single-argument constructor
    const UnsignedInteger128 e(0x1234567890abcdef);
    REQUIRE(e == UnsignedInteger128{0, 0x1234567890abcdef});
}

TEST_CASE("Integer128 copy assignment operator", "[Integer128 copy assignment]") {
    Integer128 a{0x1234567890abcdef, 0xfedcba0987654321};
    Integer128 b;
    b = a;

    REQUIRE(a == b);
}

TEST_CASE("UnsignedInteger128 copy assignment operator", "[UnsignedInteger128 copy assignment]") {
    UnsignedInteger128 a{0x1234567890abcdef, 0xfedcba0987654321};
    UnsignedInteger128 b;
    b = a;

    REQUIRE(a == b);
}

TEST_CASE("Integer128 basic shift functions", "[Integer128 shift]") {
    const Integer128 a{0x1234567890abcdef, 0xfedcba0987654321};

    REQUIRE((a << 4) == Integer128{0x234567890abcdeff, 0xedcba09876543210});
    REQUIRE((a >> 4) == Integer128{0x01234567890abcde, 0xffedcba098765432});

    const Integer128 b{static_cast<int64_t>(0xfedcba0987654321), 0x1234567890abcdef};
    REQUIRE((b >> 4) == Integer128{static_cast<int64_t>(0xffedcba098765432), 0x11234567890abcde});
}

TEST_CASE("UnsignedInteger128 basic shift functions", "[UnsignedInteger128 shift]") {
    const UnsignedInteger128 a{0x1234567890abcdef, 0xfedcba0987654321};

    REQUIRE((a << 4) == UnsignedInteger128{0x234567890abcdeff, 0xedcba09876543210});
    REQUIRE((a >> 4) == UnsignedInteger128{0x01234567890abcde, 0xffedcba098765432});
}

TEST_CASE("Integer128 basic logic functions", "[Integer128 logic]") {
    const Integer128 a{0x1234567890abcdef, 0xfedcba0987654321};
    const Integer128 b{0x0f0f0f0f0f0f0f0f, 0xf0f0f0f0f0f0f0f0};

    REQUIRE((a & b) == Integer128{0x02040608000b0d0f, 0xf0d0b00080604020});
    REQUIRE((a | b) == Integer128{0x1f3f5f7f9fafcfef, 0xfefcfaf9f7f5f3f1});
    REQUIRE((a ^ b) == Integer128{0x1d3b59779fa4c2e0, 0x0e2c4af97795b3d1});
    REQUIRE((~a)    == Integer128{static_cast<int64_t>(0xedcba9876f543210), 0x012345f6789abcde});
}

TEST_CASE("UnsignedInteger128 basic logic functions", "[UnsignedInteger128 logic]") {
    const UnsignedInteger128 a{0x1234567890abcdef, 0xfedcba0987654321};
    const UnsignedInteger128 b{0x0f0f0f0f0f0f0f0f, 0xf0f0f0f0f0f0f0f0};

    REQUIRE((a & b) == UnsignedInteger128{0x02040608000b0d0f, 0xf0d0b00080604020});
    REQUIRE((a | b) == UnsignedInteger128{0x1f3f5f7f9fafcfef, 0xfefcfaf9f7f5f3f1});
    REQUIRE((a ^ b) == UnsignedInteger128{0x1d3b59779fa4c2e0, 0x0e2c4af97795b3d1});
    REQUIRE((~a)    == UnsignedInteger128{0xedcba9876f543210, 0x012345f6789abcde});
}

TEST_CASE("Integer128 basic comparison functions", "[Integer128 comparison]") {
    const Integer128 a{0x1234567890abcdef, 0xfedcba0987654321};
    const Integer128 b{0x1234567890abcdef, 0xfedcba0987654321};
    const Integer128 c{0x1234567890abcdef, 0xfedcba0987654322};
    const Integer128 d{0x1234567890abcdee, 0xfedcba0987654321};

    REQUIRE(a == b);

    REQUIRE(a != c);
    REQUIRE(a != d);

    REQUIRE(a < c);
    REQUIRE(d < a);
    REQUIRE(!(a < d));

    REQUIRE(a > d);
    REQUIRE(c > a);
    REQUIRE(!(d > a));

    REQUIRE(a <= b);
    REQUIRE(a <= c);

    REQUIRE(a >= b);
    REQUIRE(a >= d);
}

TEST_CASE("UnsignedInteger128 basic comparison functions", "[UnsignedInteger128 comparison]") {
    const UnsignedInteger128 a{0x1234567890abcdef, 0xfedcba0987654321};
    const UnsignedInteger128 b{0x1234567890abcdef, 0xfedcba0987654321};
    const UnsignedInteger128 c{0x1234567890abcdef, 0xfedcba0987654322};
    const UnsignedInteger128 d{0x1234567890abcdee, 0xfedcba0987654321};

    REQUIRE(a == b);

    REQUIRE(a != c);
    REQUIRE(a != d);

    REQUIRE(a < c);
    REQUIRE(d < a);
    REQUIRE(!(a < d));

    REQUIRE(a > d);
    REQUIRE(c > a);
    REQUIRE(!(d > a));

    REQUIRE(a <= b);
    REQUIRE(a <= c);

    REQUIRE(a >= b);
    REQUIRE(a >= d);
}

TEST_CASE("Integer128 basic arithmetic functions", "[Integer128 arithmetic]") {
    const Integer128 a{0x1234567890abcdef, 0xfedcba0987654321};
    const Integer128 b{0x0f0f0f0f0f0f0f0f, 0xf0f0f0f0f0f0f0f0};

    //TODO: Make sure this is defined behaviour and it is actually correct
    REQUIRE((a + b) == Integer128{0x213546798fafcfef, 0xfefcfaf9f7f5f3f1});
    REQUIRE((a - b) == Integer128{0x01345678900abcde, 0x000cba0987654321});
    REQUIRE((a * b) == Integer128{static_cast<int64_t>(-0x1e1e1e1e1e1e1e1e), 0x1e1e1e1e1e1e1e10});
    REQUIRE((a / b) == Integer128{static_cast<int64_t>(-2), 2});
    REQUIRE((a % b) == Integer128{static_cast<int64_t>(-2), 2});
}

TEST_CASE("UnsignedInteger128 basic arithmetic functions", "[UnsignedInteger128 arithmetic]") {
    const UnsignedInteger128 a{0x1234567890abcdef, 0xfedcba0987654321};
    const UnsignedInteger128 b{0x0f0f0f0f0f0f0f0f, 0xf0f0f0f0f0f0f0f0};

    //TODO: Repair this
    REQUIRE((a + b) == UnsignedInteger128{0x213546798fafcfef, 0xfefcfaf9f7f5f3f1});
    REQUIRE((a - b) == UnsignedInteger128{0x01345678900abcde, 0x000cba0987654321});
    REQUIRE((a * b) == UnsignedInteger128{static_cast<uint64_t>(-0x1e1e1e1e1e1e1e1e), 0x1e1e1e1e1e1e1e10});
    REQUIRE((a / b) == UnsignedInteger128{2});
    REQUIRE((a % b) == UnsignedInteger128{2});
}