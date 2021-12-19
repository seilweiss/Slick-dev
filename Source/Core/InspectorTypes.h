#pragma once

#include <QString>
#include <QColor>

#include <cstdint>

namespace Slick {

    struct Color
    {
        uint8_t r, g, b, a;

        Color() : r(0), g(0), b(0), a(0) {}
        Color(uint8_t rgb, uint8_t a = 255) : r(rgb), g(rgb), b(rgb), a(a) {}
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r(r), g(g), b(b), a(a) {}
        Color(const QColor& qc) : r(qc.red()), g(qc.green()), b(qc.blue()), a(qc.alpha()) {}

        QString toString() const { return QString("(%1, %2, %3, %4)").arg(r).arg(g).arg(b).arg(a); }
        QColor toQColor() const { return QColor::fromRgb(r, g, b, a); }

        bool operator==(const Color& other) { return r == other.r && g == other.g && b == other.b && a == other.a; }
        bool operator!=(const Color& other) { return !operator==(other); }
    };

    struct ColorF
    {
        float r, g, b, a;

        ColorF() : r(0), g(0), b(0), a(0) {}
        ColorF(float rgb, float a = 1.0f) : r(rgb), g(rgb), b(rgb), a(a) {}
        ColorF(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
        ColorF(const QColor& qc) : r(qc.redF()), g(qc.greenF()), b(qc.blueF()), a(qc.alphaF()) {}

        QString toString() const { return QString("(%1, %2, %3, %4)").arg(r).arg(g).arg(b).arg(a); }
        QColor toQColor() const { return QColor::fromRgbF(r, g, b, a); }

        bool operator==(const ColorF& other) { return r == other.r && g == other.g && b == other.b && a == other.a; }
        bool operator!=(const ColorF& other) { return !operator==(other); }
    };

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
