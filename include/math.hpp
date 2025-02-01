#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Math {
    class Vec3 {
        private:
            glm::vec3 data;

        public:
            // Constructors
            Vec3();
            Vec3(float x, float y, float z);
            Vec3(const glm::vec3& vec);

            // Accessors
            float x();
            float y();
            float z();

            void setX(float x);
            void setY(float y);
            void setZ(float z);

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
            
            // Stream operator
            friend std::ostream& operator<<(std::ostream& os, Vec3& vec);
    };

    class Vec2 {
        private:
            glm::vec2 data;

        public:
            // Constructors
            Vec2();
            Vec2(float x, float y);
            Vec2(const glm::vec2& vec);

            // Getters
            float x();
            float y();

            // Setters
            void setX(float x);
            void setY(float y);

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

            // Friend functions
            friend std::ostream& operator<<(std::ostream& os, Vec2& vec);
    };
}   