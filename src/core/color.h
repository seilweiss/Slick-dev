#pragma once

#include <QColor>
#include <QString>

namespace Slick {

    namespace Core {

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

    }

}
