#pragma once

#define GLM_FORCE_CTOR_INIT

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Math {
    class Vec4 {
        public:
            glm::vec4 data;

            // Constructors
            Vec4();
            Vec4(float x, float y, float z, float w);
            Vec4(const glm::vec4& vec);

            // Accessors
            float x();
            float y();
            float z();
            float w();

            // Operators
            Vec4 operator+(const Vec4& other);
            Vec4 operator-(const Vec4& other);
            Vec4 operator*(float scalar);
            Vec4 operator/(float scalar);
            Vec4& operator+=(const Vec4& other);
            Vec4& operator-=(const Vec4& other);
            Vec4& operator*=(float scalar);
            Vec4& operator/=(float scalar);
            bool operator==(const Vec4& other);
            bool operator!=(const Vec4& other);

            // Conversions
            operator glm::vec4();
            float* toFloat();

            // Magnitude and normalization
            float length();
            Vec4 normalize();

            // Dot and cross product
            float dot(const Vec4& other);
            Vec4 cross(const Vec4& other);

            // Stream operator
            friend std::ostream& operator<<(std::ostream& os, Vec4& vec);
    };

    class Vec3 {
        public:
            glm::vec3 data;

            // Constructors
            Vec3();
            Vec3(float x, float y, float z);
            Vec3(const glm::vec3& vec);

            // Accessors
            float x();
            float y();
            float z();

            // Operators
            Vec3 operator+(const Vec3& other);
            Vec3 operator-(const Vec3& other);
            Vec3 operator*(float scalar);
            Vec3 operator/(float scalar);
            Vec3& operator+=(const Vec3& other);
            Vec3& operator-=(const Vec3& other);
            Vec3& operator*=(float scalar);
            Vec3& operator/=(float scalar);
            bool operator==(const Vec3& other);
            bool operator!=(const Vec3& other);

            // Conversions
            operator glm::vec3();
            float* toFloat();

            // Magnitude and normalization
            float length();
            Vec3 normalize();

            // Dot and cross product
            float dot(const Vec3& other);
            Vec3 cross(const Vec3& other);
            
            // Stream operator
            friend std::ostream& operator<<(std::ostream& os, Vec3& vec);
    };

    class Vec2 {
        public:
            glm::vec2 data;

            // Constructors
            Vec2();
            Vec2(float x, float y);
            Vec2(const glm::vec2& vec);

            // Getters
            float x();
            float y();

            // Operators
            Vec2 operator+(const Vec2& other);
            Vec2 operator-(const Vec2& other);
            Vec2 operator*(float scalar);
            Vec2 operator/(float scalar);
            Vec2& operator+=(const Vec2& other);
            Vec2& operator-=(const Vec2& other);
            Vec2& operator*=(float scalar);
            Vec2& operator/=(float scalar);
            bool operator==(const Vec2& other);
            bool operator!=(const Vec2& other);

            // Utility Methods
            float length();
            Vec2 normalize();
            
            // Conversion
            operator glm::vec2();
            float* toFloat();

            // Dot and cross product
            float dot(const Vec2& other);
            float cross(const Vec2& other);

            // Friend functions
            friend std::ostream& operator<<(std::ostream& os, Vec2& vec);
    };
    
    class Mat4 {
        public:
            glm::mat4 data;

            // Constructors
            Mat4();
            Mat4(const glm::mat4& mat);

            // Accessors
            float* toFloat();
            float& operator()(int row, int col); // Allows for modification

            // Transformations methods
            static Mat4 identity();
            static Mat4 translation(const Mat4& mat, const Vec3& v);
            static Mat4 rotation(const Mat4& mat, float angle, const Vec3& axis);
            static Mat4 scale(const Mat4& mat, const Vec3& v);

            // Operators
            Mat4 operator+(Mat4& other);
            Mat4 operator-(Mat4& other);
            Mat4 operator*(Mat4& other);
            Vec4 operator*(Vec4& vec);
            Mat4 operator*(float scalar);

            // Methods
            Mat4 transpose();
            Mat4 inverse();

            // Print
            void print();

    };

    class Mat3 {
        public:
            glm::mat3 data;

            // Constructors
            Mat3();
            Mat3(const glm::mat3& mat);

            // Accessors
            float* toFloat();
            float& operator()(int row, int col); // Allows for modification
            const float& operator()(int row, int col) const; // for read only

            // Transformations methods
            static Mat3 identity();
            static Mat3 translation(const Mat3& mat, Vec2& v);
            static Mat3 rotation(const Mat3& mat, float angle);
            static Mat3 scale(const Mat3& mat, Vec2& v);

            // Operators
            Mat3 operator+(Mat3& other);
            Mat3 operator-(Mat3& other);
            Mat3 operator*(Mat3& other);
            Vec3 operator*(Vec3& vec);
            Mat3 operator*(float scalar);

            //methods
            Mat3 transpose();
            Mat3 inverse();

            // Print
            void print();
    };

    class Mat2 {
        public:
            glm::mat2 data;

            // Constructors
            Mat2();
            Mat2(const glm::mat2& mat);

            // Accessors
            float* toFloat();
            float& operator()(int row, int col); // Allows for modification
            const float& operator()(int row, int col) const; // for read only

            // Transformations methods
            static Mat2 identity();
            static Mat2 rotation(const Mat2& mat, float angle);
            static Mat2 scale(const Mat2& mat, Vec2& v);

            // Operators
            Mat2 operator+(Mat2& other);
            Mat2 operator-(Mat2& other);
            Mat2 operator*(Mat2& other);
            Vec2 operator*(Vec2& vec);
            Mat2 operator*(float scalar);

            //methods
            Mat2 transpose();
            Mat2 inverse();

            // Print
            void print();
    };

    
}   