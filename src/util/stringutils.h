#pragma once

#include <QString>

namespace Slick {

    namespace Util {

        inline QString hexToString(uint32_t hex)
        {
            return QString("0x") + QString("%1").arg(hex, 8, 16, QLatin1Char('0')).toUpper();
        }

        template <class A, class B> A convertString(const B& s);
        template <> inline QString convertString(const QString& s) { return s; }
        template <> inline QString convertString(const std::string& s) { return QString::fromStdString(s); }
        template <> inline std::string convertString(const std::string& s) { return s; }
        template <> inline std::string convertString(const QString& s) { return s.toStdString(); }

    }

}
