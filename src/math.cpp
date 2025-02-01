#include <math.hpp>

using namespace Math;

//ructors
Vec3::Vec3() : data(0.0f) {}
Vec3::Vec3(float x, float y, float z) : data(x, y, z) {}
Vec3::Vec3(const glm::vec3& vec) : data(vec) {}

// Accessors
float Vec3::x() { return data.x; }
float Vec3::y() { return data.y; }
float Vec3::z() { return data.z; }

void Vec3::setX(float x) { data.x = x; }
void Vec3::setY(float y) { data.y = y; }
void Vec3::setZ(float z) { data.z = z; }

// Operators
Vec3 Vec3::operator+(const Vec3& other) { return Vec3(data + other.data); }
Vec3 Vec3::operator-(const Vec3& other) { return Vec3(data - other.data); }
Vec3 Vec3::operator*(float scalar) { return Vec3(data * scalar); }
Vec3 Vec3::operator/(float scalar) { return Vec3(data / scalar); }
Vec3& Vec3::operator+=(const Vec3& other) { data += other.data; return *this; }
Vec3& Vec3::operator-=(const Vec3& other) { data -= other.data; return *this; }
Vec3& Vec3::operator*=(float scalar) { data *= scalar; return *this; }
Vec3& Vec3::operator/=(float scalar) { data /= scalar; return *this; }
bool Vec3::operator==(const Vec3& other) { return data == other.data; }
bool Vec3::operator!=(const Vec3& other) { return data != other.data; }

// Conversions
Vec3::operator glm::vec3() { return data; }
float* Vec3::toFloat() {return glm::value_ptr(data);}

// Magnitude and normalization
float Vec3::length() { return glm::length(data); }
Vec3 Vec3::normalize() { return Vec3(glm::normalize(data)); }

// Dot product
float Vec3::dot(const Vec3& other) { return glm::dot(data, other.data); }

// Stream operator
std::ostream& operator<<(std::ostream& os, Vec3& vec) {
    os << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
    return os;
}

// Constructors
Vec2::Vec2() : data(0.0f, 0.0f) {}
Vec2::Vec2(float x, float y) : data(x, y) {}
Vec2::Vec2(const glm::vec2& vec) : data(vec) {}

// Getters
float Vec2::x() { return data.x; }
float Vec2::y() { return data.y; }

// Setters
void Vec2::setX(float x) { data.x = x; }
void Vec2::setY(float y) { data.y = y; }

// Operators
Vec2 Vec2::operator+(const Vec2& other) { return Vec2(data + other.data); }
Vec2 Vec2::operator-(const Vec2& other) { return Vec2(data - other.data); }
Vec2 Vec2::operator*(float scalar) { return Vec2(data * scalar); }
Vec2 Vec2::operator/(float scalar) { return Vec2(data / scalar); }
Vec2& Vec2::operator+=(const Vec2& other) { data += other.data; return *this; }
Vec2& Vec2::operator-=(const Vec2& other) { data -= other.data; return *this; }
Vec2& Vec2::operator*=(float scalar) { data *= scalar; return *this; }
Vec2& Vec2::operator/=(float scalar) { data /= scalar; return *this; }
bool Vec2::operator==(const Vec2& other) { return data == other.data; }
bool Vec2::operator!=(const Vec2& other) { return data != other.data; }

// Utility Methods
float Vec2::length() { return glm::length(data); }
Vec2 Vec2::normalize() { return Vec2(glm::normalize(data)); }

// Conversion
Vec2::operator glm::vec2() { return data; }
float* Vec2::toFloat() {return glm::value_ptr(data);}

// Friend functions
std::ostream& operator<<(std::ostream& os, Vec2& vec) {
    os << "Vec2(" << vec.x() << ", " << vec.y() << ")";
    return os;
}
