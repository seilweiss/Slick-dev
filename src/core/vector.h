#pragma once

#include <QString>

namespace Slick {

    namespace Core {

        struct Vector2
        {
            float x, y;

            Vector2() : x(0), y(0) {}
            Vector2(float xy) : x(xy), y(xy) {}
            Vector2(float x, float y) : x(x), y(y) {}

            QString toString() const { return QString("(%1, %2)").arg(x).arg(y); }

            bool operator==(const Vector2& other) { return x == other.x && y == other.y; }
            bool operator!=(const Vector2& other) { return !operator==(other); }
        };

        struct Vector3
        {
            float x, y, z;

            Vector3() : x(0), y(0), z(0) {}
            Vector3(float xyz) : x(xyz), y(xyz), z(xyz) {}
            Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

            QString toString() const { return QString("(%1, %2, %3)").arg(x).arg(y).arg(z); }

            bool operator==(const Vector3& other) { return x == other.x && y == other.y && z == other.z; }
            bool operator!=(const Vector3& other) { return !operator==(other); }
        };

        struct Vector4
        {
            float x, y, z, w;

            Vector4() : x(0), y(0), z(0), w(0) {}
            Vector4(float xyz, float w = 1.0f) : x(xyz), y(xyz), z(xyz), w(w) {}
            Vector4(float x, float y, float z, float w = 1.0f) : x(x), y(y), z(z), w(w) {}

            QString toString() const { return QString("(%1, %2, %3, %4)").arg(x).arg(y).arg(z).arg(w); }

            bool operator==(const Vector4& other) { return x == other.x && y == other.y && z == other.z && w == other.w; }
            bool operator!=(const Vector4& other) { return !operator==(other); }
        };

    }

}
