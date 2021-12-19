#pragma once

#include "Core/InspectorTypes.h"

#include <QString>

namespace Slick {

    class InspectorDataSource
    {
    public:
        enum Type
        {
            Null,
            Int8,
            Int16,
            Int32,
            UInt8,
            UInt16,
            UInt32,
            Float,
            Double,
            Bool,
            String,
            StdString,
            Color,
            ColorF,
            Vector2,
            Vector3,
            Vector4
        };

        InspectorDataSource() : m_type(Null), m_sourceVoid(nullptr) {}
        InspectorDataSource(int8_t* source) : m_type(Int8), m_sourceInt8(source) { Q_ASSERT(source); }
        InspectorDataSource(int16_t* source) : m_type(Int16), m_sourceInt16(source) { Q_ASSERT(source); }
        InspectorDataSource(int32_t* source) : m_type(Int32), m_sourceInt32(source) { Q_ASSERT(source); }
        InspectorDataSource(uint8_t* source) : m_type(UInt8), m_sourceUInt8(source) { Q_ASSERT(source); }
        InspectorDataSource(uint16_t* source) : m_type(UInt16), m_sourceUInt16(source) { Q_ASSERT(source); }
        InspectorDataSource(uint32_t* source) : m_type(UInt32), m_sourceUInt32(source) { Q_ASSERT(source); }
        InspectorDataSource(float* source) : m_type(Float), m_sourceFloat(source) { Q_ASSERT(source); }
        InspectorDataSource(double* source) : m_type(Double), m_sourceDouble(source) { Q_ASSERT(source); }
        InspectorDataSource(bool* source) : m_type(Bool), m_sourceBool(source) { Q_ASSERT(source); }
        InspectorDataSource(QString* source) : m_type(String), m_sourceQString(source) { Q_ASSERT(source); }
        InspectorDataSource(std::string* source) : m_type(StdString), m_sourceStdString(source) { Q_ASSERT(source); }
        InspectorDataSource(Slick::Color* source) : m_type(Color), m_sourceColor(source) { Q_ASSERT(source); }
        InspectorDataSource(Slick::ColorF* source) : m_type(ColorF), m_sourceColorF(source) { Q_ASSERT(source); }
        InspectorDataSource(Slick::Vector2* source) : m_type(Vector2), m_sourceVector2(source) { Q_ASSERT(source); }
        InspectorDataSource(Slick::Vector3* source) : m_type(Vector3), m_sourceVector3(source) { Q_ASSERT(source); }
        InspectorDataSource(Slick::Vector4* source) : m_type(Vector4), m_sourceVector4(source) { Q_ASSERT(source); }

        Type type() const { return m_type; }

        bool isNull() const { return m_type == Null; }
        bool isInt8() const { return m_type == Int8; }
        bool isInt16() const { return m_type == Int16; }
        bool isInt32() const { return m_type == Int32; }
        bool isUInt8() const { return m_type == UInt8; }
        bool isUInt16() const { return m_type == UInt16; }
        bool isUInt32() const { return m_type == UInt32; }
        bool isFloat() const { return m_type == Float; }
        bool isDouble() const { return m_type == Double; }
        bool isBool() const { return m_type == Bool; }
        bool isString() const { return m_type == String; }
        bool isStdString() const { return m_type == StdString; }
        bool isColor() const { return m_type == Color; }
        bool isColorF() const { return m_type == ColorF; }
        bool isVector2() const { return m_type == Vector2; }
        bool isVector3() const { return m_type == Vector3; }
        bool isVector4() const { return m_type == Vector4; }

        int8_t toInt8() const { return data<int8_t>(); }
        int16_t toInt16() const { return data<int16_t>(); }
        int32_t toInt32() const { return data<int32_t>(); }
        uint8_t toUInt8() const { return data<uint8_t>(); }
        uint16_t toUInt16() const { return data<uint16_t>(); }
        uint32_t toUInt32() const { return data<uint32_t>(); }
        float toFloat() const { return data<float>(); }
        double toDouble() const { return data<double>(); }
        bool toBool() const { return data<bool>(); }
        QString toString() const { return data<QString>(); }
        std::string toStdString() const { return data<std::string>(); }
        Slick::Color toColor() const { return data<Slick::Color>(); }
        Slick::ColorF toColorF() const { return data<Slick::ColorF>(); }
        Slick::Vector2 toVector2() const { return data<Slick::Vector2>(); }
        Slick::Vector3 toVector3() const { return data<Slick::Vector3>(); }
        Slick::Vector4 toVector4() const { return data<Slick::Vector4>(); }

        void setInt8(int8_t data) const { setData<int8_t>(data); }
        void setInt16(int16_t data) const { setData<int16_t>(data); }
        void setInt32(int32_t data) const { setData<int32_t>(data); }
        void setUInt8(uint8_t data) const { setData<uint8_t>(data); }
        void setUInt16(uint16_t data) const { setData<uint16_t>(data); }
        void setUInt32(uint32_t data) const { setData<uint32_t>(data); }
        void setFloat(float data) const { setData<float>(data); }
        void setDouble(double data) const { setData<double>(data); }
        void setBool(bool data) const { setData<bool>(data); }
        void setString(const QString& data) const { setData<QString>(data); }
        void setStdString(const std::string& data) const { setData<std::string>(data); }
        void setColor(const Slick::Color& data) const { setData<Slick::Color>(data); }
        void setColorF(const Slick::ColorF& data) const { setData<Slick::ColorF>(data); }
        void setVector2(const Slick::Vector2& data) const { setData<Slick::Vector2>(data); }
        void setVector3(const Slick::Vector3& data) const { setData<Slick::Vector3>(data); }
        void setVector4(const Slick::Vector4& data) const { setData<Slick::Vector4>(data); }

        template <class T> T data() const
        {
            switch (m_type)
            {
            case Int8: return convert<T>(*m_sourceInt8); break;
            case Int16: return convert<T>(*m_sourceInt16); break;
            case Int32: return convert<T>(*m_sourceInt32); break;
            case UInt8: return convert<T>(*m_sourceUInt8); break;
            case UInt16: return convert<T>(*m_sourceUInt16); break;
            case UInt32: return convert<T>(*m_sourceUInt32); break;
            case Float: return convert<T>(*m_sourceFloat); break;
            case Double: return convert<T>(*m_sourceDouble); break;
            case Bool: return convert<T>(*m_sourceDouble); break;
            case String: return convert<T>(*m_sourceQString); break;
            case StdString: return convert<T>(*m_sourceStdString); break;
            case Color: return convert<T>(*m_sourceColor); break;
            case ColorF: return convert<T>(*m_sourceColorF); break;
            case Vector2: return convert<T>(*m_sourceVector2); break;
            case Vector3: return convert<T>(*m_sourceVector3); break;
            case Vector4: return convert<T>(*m_sourceVector4); break;
            default: Q_ASSERT(false); return T();
            }
        }

        template <class T> void setData(const T& data) const
        {
            switch (m_type)
            {
            case Int8: *m_sourceInt8 = convert<int8_t>(data); break;
            case Int16: *m_sourceInt16 = convert<int16_t>(data); break;
            case Int32: *m_sourceInt32 = convert<int32_t>(data); break;
            case UInt8: *m_sourceUInt8 = convert<uint8_t>(data); break;
            case UInt16: *m_sourceUInt16 = convert<uint16_t>(data); break;
            case UInt32: *m_sourceUInt32 = convert<uint32_t>(data); break;
            case Float: *m_sourceFloat = convert<float>(data); break;
            case Double: *m_sourceDouble = convert<double>(data); break;
            case Bool: *m_sourceBool = convert<bool>(data); break;
            case String: *m_sourceQString = convert<QString>(data); break;
            case StdString: *m_sourceStdString = convert<std::string>(data); break;
            case Color: *m_sourceColor = convert<Slick::Color>(data); break;
            case ColorF: *m_sourceColorF = convert<Slick::ColorF>(data); break;
            case Vector2: *m_sourceVector2 = convert<Slick::Vector2>(data); break;
            case Vector3: *m_sourceVector3 = convert<Slick::Vector3>(data); break;
            case Vector4: *m_sourceVector4 = convert<Slick::Vector4>(data); break;
            default: Q_ASSERT(false); break;
            }
        }

        template <class T> T* source() const;
        template <> int8_t* source() const { return m_type == Int8 ? m_sourceInt8 : nullptr; }
        template <> int16_t* source() const { return m_type == Int16 ? m_sourceInt16 : nullptr; }
        template <> int32_t* source() const { return m_type == Int32 ? m_sourceInt32 : nullptr; }
        template <> uint8_t* source() const { return m_type == UInt8 ? m_sourceUInt8 : nullptr; }
        template <> uint16_t* source() const { return m_type == UInt16 ? m_sourceUInt16 : nullptr; }
        template <> uint32_t* source() const { return m_type == UInt32 ? m_sourceUInt32 : nullptr; }
        template <> float* source() const { return m_type == Float ? m_sourceFloat : nullptr; }
        template <> double* source() const { return m_type == Double ? m_sourceDouble : nullptr; }
        template <> bool* source() const { return m_type == Bool ? m_sourceBool : nullptr; }
        template <> QString* source() const { return m_type == String ? m_sourceQString : nullptr; }
        template <> std::string* source() const { return m_type == StdString ? m_sourceStdString : nullptr; }
        template <> Slick::Color* source() const { return m_type == Color ? m_sourceColor : nullptr; }
        template <> Slick::ColorF* source() const { return m_type == ColorF ? m_sourceColorF : nullptr; }
        template <> Slick::Vector2* source() const { return m_type == Vector2 ? m_sourceVector2 : nullptr; }
        template <> Slick::Vector3* source() const { return m_type == Vector3 ? m_sourceVector3 : nullptr; }
        template <> Slick::Vector4* source() const { return m_type == Vector4 ? m_sourceVector4 : nullptr; }

    private:
        Type m_type;

        union
        {
            void* m_sourceVoid;
            int8_t* m_sourceInt8;
            int16_t* m_sourceInt16;
            int32_t* m_sourceInt32;
            uint8_t* m_sourceUInt8;
            uint16_t* m_sourceUInt16;
            uint32_t* m_sourceUInt32;
            float* m_sourceFloat;
            double* m_sourceDouble;
            bool* m_sourceBool;
            QString* m_sourceQString;
            std::string* m_sourceStdString;
            Slick::Color* m_sourceColor;
            Slick::ColorF* m_sourceColorF;
            Slick::Vector2* m_sourceVector2;
            Slick::Vector3* m_sourceVector3;
            Slick::Vector4* m_sourceVector4;
        };

        template <class A, class B> A convert(const B& b) const;

        template <> int8_t convert(const int8_t& b) const { return b; }
        template <> int8_t convert(const int16_t& b) const { return b; }
        template <> int8_t convert(const int32_t& b) const { return b; }
        template <> int8_t convert(const uint8_t& b) const { return b; }
        template <> int8_t convert(const uint16_t& b) const { return b; }
        template <> int8_t convert(const uint32_t& b) const { return b; }
        template <> int8_t convert(const float& b) const { return b; }
        template <> int8_t convert(const double& b) const { return b; }
        template <> int8_t convert(const bool& b) const { return b; }
        template <> int8_t convert(const QString& b) const { return b.toInt(); }
        template <> int8_t convert(const std::string& b) const { return std::stoi(b); }
        template <> int8_t convert(const Slick::Color& b) const { return b.r; }
        template <> int8_t convert(const Slick::ColorF& b) const { return b.r * 255.0f; }
        template <> int8_t convert(const Slick::Vector2& b) const { return b.x; }
        template <> int8_t convert(const Slick::Vector3& b) const { return b.x; }
        template <> int8_t convert(const Slick::Vector4& b) const { return b.x; }

        template <> int16_t convert(const int8_t& b) const { return b; }
        template <> int16_t convert(const int16_t& b) const { return b; }
        template <> int16_t convert(const int32_t& b) const { return b; }
        template <> int16_t convert(const uint8_t& b) const { return b; }
        template <> int16_t convert(const uint16_t& b) const { return b; }
        template <> int16_t convert(const uint32_t& b) const { return b; }
        template <> int16_t convert(const float& b) const { return b; }
        template <> int16_t convert(const double& b) const { return b; }
        template <> int16_t convert(const bool& b) const { return b; }
        template <> int16_t convert(const QString& b) const { return b.toInt(); }
        template <> int16_t convert(const std::string& b) const { return std::stoi(b); }
        template <> int16_t convert(const Slick::Color& b) const { return b.r; }
        template <> int16_t convert(const Slick::ColorF& b) const { return b.r * 255.0f; }
        template <> int16_t convert(const Slick::Vector2& b) const { return b.x; }
        template <> int16_t convert(const Slick::Vector3& b) const { return b.x; }
        template <> int16_t convert(const Slick::Vector4& b) const { return b.x; }

        template <> int32_t convert(const int8_t& b) const { return b; }
        template <> int32_t convert(const int16_t& b) const { return b; }
        template <> int32_t convert(const int32_t& b) const { return b; }
        template <> int32_t convert(const uint8_t& b) const { return b; }
        template <> int32_t convert(const uint16_t& b) const { return b; }
        template <> int32_t convert(const uint32_t& b) const { return b; }
        template <> int32_t convert(const float& b) const { return b; }
        template <> int32_t convert(const double& b) const { return b; }
        template <> int32_t convert(const bool& b) const { return b; }
        template <> int32_t convert(const QString& b) const { return b.toInt(); }
        template <> int32_t convert(const std::string& b) const { return std::stoi(b); }
        template <> int32_t convert(const Slick::Color& b) const { return b.r; }
        template <> int32_t convert(const Slick::ColorF& b) const { return b.r * 255.0f; }
        template <> int32_t convert(const Slick::Vector2& b) const { return b.x; }
        template <> int32_t convert(const Slick::Vector3& b) const { return b.x; }
        template <> int32_t convert(const Slick::Vector4& b) const { return b.x; }

        template <> uint8_t convert(const int8_t& b) const { return b; }
        template <> uint8_t convert(const int16_t& b) const { return b; }
        template <> uint8_t convert(const int32_t& b) const { return b; }
        template <> uint8_t convert(const uint8_t& b) const { return b; }
        template <> uint8_t convert(const uint16_t& b) const { return b; }
        template <> uint8_t convert(const uint32_t& b) const { return b; }
        template <> uint8_t convert(const float& b) const { return b; }
        template <> uint8_t convert(const double& b) const { return b; }
        template <> uint8_t convert(const bool& b) const { return b; }
        template <> uint8_t convert(const QString& b) const { return b.toUInt(); }
        template <> uint8_t convert(const std::string& b) const { return std::stoul(b); }
        template <> uint8_t convert(const Slick::Color& b) const { return b.r; }
        template <> uint8_t convert(const Slick::ColorF& b) const { return b.r * 255.0f; }
        template <> uint8_t convert(const Slick::Vector2& b) const { return b.x; }
        template <> uint8_t convert(const Slick::Vector3& b) const { return b.x; }
        template <> uint8_t convert(const Slick::Vector4& b) const { return b.x; }

        template <> uint16_t convert(const int8_t& b) const { return b; }
        template <> uint16_t convert(const int16_t& b) const { return b; }
        template <> uint16_t convert(const int32_t& b) const { return b; }
        template <> uint16_t convert(const uint8_t& b) const { return b; }
        template <> uint16_t convert(const uint16_t& b) const { return b; }
        template <> uint16_t convert(const uint32_t& b) const { return b; }
        template <> uint16_t convert(const float& b) const { return b; }
        template <> uint16_t convert(const double& b) const { return b; }
        template <> uint16_t convert(const bool& b) const { return b; }
        template <> uint16_t convert(const QString& b) const { return b.toUInt(); }
        template <> uint16_t convert(const std::string& b) const { return std::stoul(b); }
        template <> uint16_t convert(const Slick::Color& b) const { return b.r; }
        template <> uint16_t convert(const Slick::ColorF& b) const { return b.r * 255.0f; }
        template <> uint16_t convert(const Slick::Vector2& b) const { return b.x; }
        template <> uint16_t convert(const Slick::Vector3& b) const { return b.x; }
        template <> uint16_t convert(const Slick::Vector4& b) const { return b.x; }

        template <> uint32_t convert(const int8_t& b) const { return b; }
        template <> uint32_t convert(const int16_t& b) const { return b; }
        template <> uint32_t convert(const int32_t& b) const { return b; }
        template <> uint32_t convert(const uint8_t& b) const { return b; }
        template <> uint32_t convert(const uint16_t& b) const { return b; }
        template <> uint32_t convert(const uint32_t& b) const { return b; }
        template <> uint32_t convert(const float& b) const { return b; }
        template <> uint32_t convert(const double& b) const { return b; }
        template <> uint32_t convert(const bool& b) const { return b; }
        template <> uint32_t convert(const QString& b) const { return b.toUInt(); }
        template <> uint32_t convert(const std::string& b) const { return std::stoul(b); }
        template <> uint32_t convert(const Slick::Color& b) const { return b.r; }
        template <> uint32_t convert(const Slick::ColorF& b) const { return b.r * 255.0f; }
        template <> uint32_t convert(const Slick::Vector2& b) const { return b.x; }
        template <> uint32_t convert(const Slick::Vector3& b) const { return b.x; }
        template <> uint32_t convert(const Slick::Vector4& b) const { return b.x; }

        template <> float convert(const int8_t& b) const { return b; }
        template <> float convert(const int16_t& b) const { return b; }
        template <> float convert(const int32_t& b) const { return b; }
        template <> float convert(const uint8_t& b) const { return b; }
        template <> float convert(const uint16_t& b) const { return b; }
        template <> float convert(const uint32_t& b) const { return b; }
        template <> float convert(const float& b) const { return b; }
        template <> float convert(const double& b) const { return b; }
        template <> float convert(const bool& b) const { return b; }
        template <> float convert(const QString& b) const { return b.toFloat(); }
        template <> float convert(const std::string& b) const { return std::stof(b); }
        template <> float convert(const Slick::Color& b) const { return b.r / 255.0f; }
        template <> float convert(const Slick::ColorF& b) const { return b.r; }
        template <> float convert(const Slick::Vector2& b) const { return b.x; }
        template <> float convert(const Slick::Vector3& b) const { return b.x; }
        template <> float convert(const Slick::Vector4& b) const { return b.x; }

        template <> double convert(const int8_t& b) const { return b; }
        template <> double convert(const int16_t& b) const { return b; }
        template <> double convert(const int32_t& b) const { return b; }
        template <> double convert(const uint8_t& b) const { return b; }
        template <> double convert(const uint16_t& b) const { return b; }
        template <> double convert(const uint32_t& b) const { return b; }
        template <> double convert(const float& b) const { return b; }
        template <> double convert(const double& b) const { return b; }
        template <> double convert(const bool& b) const { return b; }
        template <> double convert(const QString& b) const { return b.toDouble(); }
        template <> double convert(const std::string& b) const { return std::stod(b); }
        template <> double convert(const Slick::Color& b) const { return b.r / 255.0; }
        template <> double convert(const Slick::ColorF& b) const { return b.r; }
        template <> double convert(const Slick::Vector2& b) const { return b.x; }
        template <> double convert(const Slick::Vector3& b) const { return b.x; }
        template <> double convert(const Slick::Vector4& b) const { return b.x; }

        template <> bool convert(const int8_t& b) const { return b; }
        template <> bool convert(const int16_t& b) const { return b; }
        template <> bool convert(const int32_t& b) const { return b; }
        template <> bool convert(const uint8_t& b) const { return b; }
        template <> bool convert(const uint16_t& b) const { return b; }
        template <> bool convert(const uint32_t& b) const { return b; }
        template <> bool convert(const float& b) const { return b; }
        template <> bool convert(const double& b) const { return b; }
        template <> bool convert(const bool& b) const { return b; }
        template <> bool convert(const QString& b) const { return stringToBool(b); }
        template <> bool convert(const std::string& b) const { return stringToBool(QString::fromStdString(b)); }
        template <> bool convert(const Slick::Color& b) const { return b.r; }
        template <> bool convert(const Slick::ColorF& b) const { return b.r; }
        template <> bool convert(const Slick::Vector2& b) const { return b.x; }
        template <> bool convert(const Slick::Vector3& b) const { return b.x; }
        template <> bool convert(const Slick::Vector4& b) const { return b.x; }

        template <> QString convert(const int8_t& b) const { return QString::number(b); }
        template <> QString convert(const int16_t& b) const { return QString::number(b); }
        template <> QString convert(const int32_t& b) const { return QString::number(b); }
        template <> QString convert(const uint8_t& b) const { return QString::number(b); }
        template <> QString convert(const uint16_t& b) const { return QString::number(b); }
        template <> QString convert(const uint32_t& b) const { return QString::number(b); }
        template <> QString convert(const float& b) const { return QString::number(b); }
        template <> QString convert(const double& b) const { return QString::number(b); }
        template <> QString convert(const bool& b) const { return b ? "true" : "false"; }
        template <> QString convert(const QString& b) const { return b; }
        template <> QString convert(const std::string& b) const { return QString::fromStdString(b); }
        template <> QString convert(const Slick::Color& b) const { return b.toString(); }
        template <> QString convert(const Slick::ColorF& b) const { return b.toString(); }
        template <> QString convert(const Slick::Vector2& b) const { return b.toString(); }
        template <> QString convert(const Slick::Vector3& b) const { return b.toString(); }
        template <> QString convert(const Slick::Vector4& b) const { return b.toString(); }

        template <> std::string convert(const int8_t& b) const { return std::to_string(b); }
        template <> std::string convert(const int16_t& b) const { return std::to_string(b); }
        template <> std::string convert(const int32_t& b) const { return std::to_string(b); }
        template <> std::string convert(const uint8_t& b) const { return std::to_string(b); }
        template <> std::string convert(const uint16_t& b) const { return std::to_string(b); }
        template <> std::string convert(const uint32_t& b) const { return std::to_string(b); }
        template <> std::string convert(const float& b) const { return std::to_string(b); }
        template <> std::string convert(const double& b) const { return std::to_string(b); }
        template <> std::string convert(const bool& b) const { return b ? "true" : "false"; }
        template <> std::string convert(const QString& b) const { return b.toStdString(); }
        template <> std::string convert(const std::string& b) const { return b; }
        template <> std::string convert(const Slick::Color& b) const { return b.toString().toStdString(); }
        template <> std::string convert(const Slick::ColorF& b) const { return b.toString().toStdString(); }
        template <> std::string convert(const Slick::Vector2& b) const { return b.toString().toStdString(); }
        template <> std::string convert(const Slick::Vector3& b) const { return b.toString().toStdString(); }
        template <> std::string convert(const Slick::Vector4& b) const { return b.toString().toStdString(); }

        template <> Slick::Color convert(const int8_t& b) const { return Slick::Color(b); }
        template <> Slick::Color convert(const int16_t& b) const { return Slick::Color(b); }
        template <> Slick::Color convert(const int32_t& b) const { return Slick::Color(b); }
        template <> Slick::Color convert(const uint8_t& b) const { return Slick::Color(b); }
        template <> Slick::Color convert(const uint16_t& b) const { return Slick::Color(b); }
        template <> Slick::Color convert(const uint32_t& b) const { return Slick::Color(b); }
        template <> Slick::Color convert(const float& b) const { return Slick::Color(b * 255.0f); }
        template <> Slick::Color convert(const double& b) const { return Slick::Color(b * 255.0); }
        template <> Slick::Color convert(const bool& b) const { return Slick::Color(b ? 255 : 0); }
        template <> Slick::Color convert(const QString& b) const { Q_UNUSED(b); return Slick::Color(); }
        template <> Slick::Color convert(const std::string& b) const { Q_UNUSED(b); return Slick::Color(); }
        template <> Slick::Color convert(const Slick::Color& b) const { return b; }
        template <> Slick::Color convert(const Slick::ColorF& b) const { return Slick::Color(b.r * 255.0f, b.g * 255.0f, b.b * 255.0f, b.a * 255.0f); }
        template <> Slick::Color convert(const Slick::Vector2& b) const { return Slick::Color(b.x * 255.0f, b.y * 255.0f, 0); }
        template <> Slick::Color convert(const Slick::Vector3& b) const { return Slick::Color(b.x * 255.0f, b.y * 255.0f, b.z * 255.0f); }
        template <> Slick::Color convert(const Slick::Vector4& b) const { return Slick::Color(b.x * 255.0f, b.y * 255.0f, b.z * 255.0f, b.w * 255.0f); }

        template <> Slick::ColorF convert(const int8_t& b) const { return Slick::ColorF(b / 255.0f); }
        template <> Slick::ColorF convert(const int16_t& b) const { return Slick::ColorF(b / 255.0f); }
        template <> Slick::ColorF convert(const int32_t& b) const { return Slick::ColorF(b / 255.0f); }
        template <> Slick::ColorF convert(const uint8_t& b) const { return Slick::ColorF(b / 255.0f); }
        template <> Slick::ColorF convert(const uint16_t& b) const { return Slick::ColorF(b / 255.0f); }
        template <> Slick::ColorF convert(const uint32_t& b) const { return Slick::ColorF(b / 255.0f); }
        template <> Slick::ColorF convert(const float& b) const { return Slick::ColorF(b); }
        template <> Slick::ColorF convert(const double& b) const { return Slick::ColorF(b); }
        template <> Slick::ColorF convert(const bool& b) const { return Slick::ColorF(b ? 1.0f : 0.0f); }
        template <> Slick::ColorF convert(const QString& b) const { Q_UNUSED(b); return Slick::ColorF(); }
        template <> Slick::ColorF convert(const std::string& b) const { Q_UNUSED(b); return Slick::ColorF(); }
        template <> Slick::ColorF convert(const Slick::Color& b) const { return Slick::ColorF(b.r / 255.0f, b.g / 255.0f, b.b / 255.0f, b.a / 255.0f); }
        template <> Slick::ColorF convert(const Slick::ColorF& b) const { return b; }
        template <> Slick::ColorF convert(const Slick::Vector2& b) const { return Slick::ColorF(b.x, b.y, 0.0f); }
        template <> Slick::ColorF convert(const Slick::Vector3& b) const { return Slick::ColorF(b.x, b.y, b.z); }
        template <> Slick::ColorF convert(const Slick::Vector4& b) const { return Slick::ColorF(b.x, b.y, b.z, b.w); }

        template <> Slick::Vector2 convert(const int8_t& b) const { return Slick::Vector2(b); }
        template <> Slick::Vector2 convert(const int16_t& b) const { return Slick::Vector2(b); }
        template <> Slick::Vector2 convert(const int32_t& b) const { return Slick::Vector2(b); }
        template <> Slick::Vector2 convert(const uint8_t& b) const { return Slick::Vector2(b); }
        template <> Slick::Vector2 convert(const uint16_t& b) const { return Slick::Vector2(b); }
        template <> Slick::Vector2 convert(const uint32_t& b) const { return Slick::Vector2(b); }
        template <> Slick::Vector2 convert(const float& b) const { return Slick::Vector2(b); }
        template <> Slick::Vector2 convert(const double& b) const { return Slick::Vector2(b); }
        template <> Slick::Vector2 convert(const bool& b) const { return Slick::Vector2(b ? 1.0f : 0.0f); }
        template <> Slick::Vector2 convert(const QString& b) const { Q_UNUSED(b); return Slick::Vector2(); }
        template <> Slick::Vector2 convert(const std::string& b) const { Q_UNUSED(b); return Slick::Vector2(); }
        template <> Slick::Vector2 convert(const Slick::Color& b) const { return Slick::Vector2(b.r / 255.0f, b.g / 255.0f); }
        template <> Slick::Vector2 convert(const Slick::ColorF& b) const { return Slick::Vector2(b.r, b.g); }
        template <> Slick::Vector2 convert(const Slick::Vector2& b) const { return b; }
        template <> Slick::Vector2 convert(const Slick::Vector3& b) const { return Slick::Vector2(b.x, b.y); }
        template <> Slick::Vector2 convert(const Slick::Vector4& b) const { return Slick::Vector2(b.x, b.y); }

        template <> Slick::Vector3 convert(const int8_t& b) const { return Slick::Vector3(b); }
        template <> Slick::Vector3 convert(const int16_t& b) const { return Slick::Vector3(b); }
        template <> Slick::Vector3 convert(const int32_t& b) const { return Slick::Vector3(b); }
        template <> Slick::Vector3 convert(const uint8_t& b) const { return Slick::Vector3(b); }
        template <> Slick::Vector3 convert(const uint16_t& b) const { return Slick::Vector3(b); }
        template <> Slick::Vector3 convert(const uint32_t& b) const { return Slick::Vector3(b); }
        template <> Slick::Vector3 convert(const float& b) const { return Slick::Vector3(b); }
        template <> Slick::Vector3 convert(const double& b) const { return Slick::Vector3(b); }
        template <> Slick::Vector3 convert(const bool& b) const { return Slick::Vector3(b ? 1.0f : 0.0f); }
        template <> Slick::Vector3 convert(const QString& b) const { Q_UNUSED(b); return Slick::Vector3(); }
        template <> Slick::Vector3 convert(const std::string& b) const { Q_UNUSED(b); return Slick::Vector3(); }
        template <> Slick::Vector3 convert(const Slick::Color& b) const { return Slick::Vector3(b.r / 255.0f, b.g / 255.0f, b.b / 255.0f); }
        template <> Slick::Vector3 convert(const Slick::ColorF& b) const { return Slick::Vector3(b.r, b.g, b.b); }
        template <> Slick::Vector3 convert(const Slick::Vector2& b) const { return Slick::Vector3(b.x, b.y, 0.0f); }
        template <> Slick::Vector3 convert(const Slick::Vector3& b) const { return b; }
        template <> Slick::Vector3 convert(const Slick::Vector4& b) const { return Slick::Vector3(b.x, b.y, b.z); }

        template <> Slick::Vector4 convert(const int8_t& b) const { return Slick::Vector4(b); }
        template <> Slick::Vector4 convert(const int16_t& b) const { return Slick::Vector4(b); }
        template <> Slick::Vector4 convert(const int32_t& b) const { return Slick::Vector4(b); }
        template <> Slick::Vector4 convert(const uint8_t& b) const { return Slick::Vector4(b); }
        template <> Slick::Vector4 convert(const uint16_t& b) const { return Slick::Vector4(b); }
        template <> Slick::Vector4 convert(const uint32_t& b) const { return Slick::Vector4(b); }
        template <> Slick::Vector4 convert(const float& b) const { return Slick::Vector4(b); }
        template <> Slick::Vector4 convert(const double& b) const { return Slick::Vector4(b); }
        template <> Slick::Vector4 convert(const bool& b) const { return Slick::Vector4(b ? 1.0f : 0.0f); }
        template <> Slick::Vector4 convert(const QString& b) const { Q_UNUSED(b); return Slick::Vector4(); }
        template <> Slick::Vector4 convert(const std::string& b) const { Q_UNUSED(b); return Slick::Vector4(); }
        template <> Slick::Vector4 convert(const Slick::Color& b) const { return Slick::Vector4(b.r / 255.0f, b.g / 255.0f, b.b / 255.0f, b.a / 255.0f); }
        template <> Slick::Vector4 convert(const Slick::ColorF& b) const { return Slick::Vector4(b.r, b.g, b.b, b.a); }
        template <> Slick::Vector4 convert(const Slick::Vector2& b) const { return Slick::Vector4(b.x, b.y, 0.0f); }
        template <> Slick::Vector4 convert(const Slick::Vector3& b) const { return Slick::Vector4(b.x, b.y, b.z); }
        template <> Slick::Vector4 convert(const Slick::Vector4& b) const { return b; }

        static bool stringToBool(const QString& str) { return (str.toLower() == "true" || str.toInt() != 0); }
    };

}
