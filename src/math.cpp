#include <math.hpp>

using namespace Math;

// Constructors
Vec4::Vec4() : data(0.0f) {}
Vec4::Vec4(float x, float y, float z, float w) : data(x, y, z, w) {}
Vec4::Vec4(const glm::vec4& vec) : data(vec) {}

// Accessors
float Vec4::x() { return data.x; }
float Vec4::y() { return data.y; }
float Vec4::z() { return data.z; }
float Vec4::w() { return data.w; }

void Vec4::setX(float x) { data.x = x; }
void Vec4::setY(float y) { data.y = y; }
void Vec4::setZ(float z) { data.z = z; }
void Vec4::setW(float w) { data.w = w; }

// Operators
Vec4 Vec4::operator+(const Vec4& other) { return Vec4(data + other.data); }
Vec4 Vec4::operator-(const Vec4& other) { return Vec4(data - other.data); }
Vec4 Vec4::operator*(float scalar) { return Vec4(data * scalar); }
Vec4 Vec4::operator/(float scalar) { return Vec4(data / scalar); }
Vec4& Vec4::operator+=(const Vec4& other) { data += other.data; return *this; }
Vec4& Vec4::operator-=(const Vec4& other) { data -= other.data; return *this; }
Vec4& Vec4::operator*=(float scalar) { data *= scalar; return *this; }
Vec4& Vec4::operator/=(float scalar) { data /= scalar; return *this; }
bool Vec4::operator==(const Vec4& other) { return data == other.data; }
bool Vec4::operator!=(const Vec4& other) { return data != other.data; }

// Conversions
Vec4::operator glm::vec4() { return data; }
float* Vec4::toFloat() {return glm::value_ptr(data);}

// Magnitude and normalization
float Vec4::length() { return glm::length(data); }
Vec4 Vec4::normalize() { return Vec4(glm::normalize(data)); }

// Dot product
float Vec4::dot(const Vec4& other) { return glm::dot(data, other.data); }
Vec4 Vec4::cross(const Vec4& other) { 
    glm::vec3 result = glm::cross(glm::vec3(data), glm::vec3(other.data));
    return Vec4(result.x, result.y, result.z, 0.0f);
}

// Stream operator
std::ostream& operator<<(std::ostream& os, Vec4& vec) {
    os << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ", " << vec.w() << ")";
    return os;
}

// Constructors
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
Vec3 Vec3::cross(const Vec3& other) { return glm::cross(data, other.data); }

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

float Vec2::dot(const Vec2& other) { return glm::dot(data, other.data); }
float Vec2::cross(const Vec2& other) { 
    return data.x * other.data.y - data.y * other.data.x;
}

// Friend functions
std::ostream& operator<<(std::ostream& os, Vec2& vec) {
    os << "Vec2(" << vec.x() << ", " << vec.y() << ")";
    return os;
}

// Constructors
Mat4::Mat4() : data(1.0f) {}
Mat4::Mat4(const glm::mat4& mat) : data(mat) {}

// Accessors
float* Mat4::toFloat() { return glm::value_ptr(data); }
float& Mat4::operator()(int i, int j) { return data[i][j]; }

// Trastransformations methods
Mat4 Mat4::identity() { return Mat4(glm::mat4(1.0f)); }
Mat4 Mat4::translation(const Mat4& mat, const Vec3& v) { return Mat4(glm::translate(mat.data, v.data)); }
Mat4 Mat4::rotation(const Mat4& mat, float angle, const Vec3& axis) { return Mat4(glm::rotate(mat.data, angle, axis.data)); }
Mat4 Mat4::scale(const Mat4& mat, const Vec3& v) { return Mat4(glm::scale(mat.data, v.data)); }

// operators
Mat4 Mat4::operator+(Mat4& other) { return Mat4(data + other.data); }
Mat4 Mat4::operator-(Mat4& other) { return Mat4(data - other.data); }
Mat4 Mat4::operator*(Mat4& other) { return Mat4(data * other.data); }
Vec4 Mat4::operator*(Vec4& vec) { return Vec4(data * vec.data); }
Mat4 Mat4::operator*(float scalar) { return Mat4(data * scalar); }

// methods
Mat4 Mat4::transpose() { return Mat4(glm::transpose(data)); }
Mat4 Mat4::inverse() { return Mat4(glm::inverse(data)); }

// Print
void Mat4::print() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Constructors
Mat3::Mat3() : data(1.0f) {}
Mat3::Mat3(const glm::mat3& mat) : data(mat) {}

// Accessors
float* Mat3::toFloat() { return glm::value_ptr(data); }
float& Mat3::operator()(int i, int j) { return data[i][j]; }

// Trastransformations methods
Mat3 Mat3::identity() { return Mat3(glm::mat3(1.0f)); }
Mat3 Mat3::translation(const Mat3& mat, Vec2& v) { 
    glm::mat3 translationMat(
            1.0f, 0.0f, v.x(),
            0.0f, 1.0f, v.y(),
            0.0f, 0.0f, 1.0f
        );
    return Mat3(mat.data * translationMat);
 }
Mat3 Mat3::rotation(const Mat3& mat, float angle) { 
    glm::mat3 rotationMat(
            cos(angle), -sin(angle), 0.0f,
            sin(angle), cos(angle), 0.0f,
            0.0f, 0.0f, 1.0f
        );
    return Mat3(mat.data * rotationMat);
 }
Mat3 Mat3::scale(const Mat3& mat, Vec2& v) { 
    glm::mat3 scaleMat(
            v.x(), 0.0f, 0.0f,
            0.0f, v.y(), 0.0f,
            0.0f, 0.0f, 1.0f
        );
    return Mat3(mat.data * scaleMat);
}

// Operators
Mat3 Mat3::operator+(Mat3& other) { return Mat3(data + other.data); }
Mat3 Mat3::operator-(Mat3& other) { return Mat3(data - other.data); }
Mat3 Mat3::operator*(Mat3& other) { return Mat3(data * other.data); }
Vec3 Mat3::operator*(Vec3& vec) { return Vec3(data * vec); }
Mat3 Mat3::operator*(float scalar) { return Mat3(data * scalar); }

// Methods
Mat3 Mat3::transpose() { return Mat3(glm::transpose(data)); }
Mat3 Mat3::inverse() { return Mat3(glm::inverse(data)); }

// Print
void Mat3::print() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Constructors
Mat2::Mat2() : data(1.0f) {}
Mat2::Mat2(const glm::mat2& mat) : data(mat) {}

// Accessors
float* Mat2::toFloat() { return glm::value_ptr(data); }
float& Mat2::operator()(int i, int j) { return data[i][j]; }

// Trastransformations methods
Mat2 Mat2::identity() { return Mat2(glm::mat2(1.0f)); }
Mat2 Mat2::rotation(const Mat2& mat, float angle) { 
    glm::mat2 rotationMat(
            cos(angle), -sin(angle),
            sin(angle), cos(angle)
        );
    return Mat2(mat.data * rotationMat);
 }
 Mat2 Mat2::scale(const Mat2& mat, Vec2& v) { 
    glm::mat2 scaleMat(
            v.x(), 0.0f,
            0.0f, v.y()
        );
    return  Mat2(mat.data * scaleMat);
 }

// Operators
Mat2 Mat2::operator+(Mat2& other) { return Mat2(data + other.data); }
Mat2 Mat2::operator-(Mat2& other) { return Mat2(data - other.data); }
Mat2 Mat2::operator*(Mat2& other) { return Mat2(data * other.data); }
Vec2 Mat2::operator*(Vec2& vec) { return Vec2(data * vec); }
Mat2 Mat2::operator*(float scalar) { return Mat2(data * scalar); }

// Methods
Mat2 Mat2::transpose() { return Mat2(glm::transpose(data)); }
Mat2 Mat2::inverse() { return Mat2(glm::inverse(data)); }

// Print
void Mat2::print() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}