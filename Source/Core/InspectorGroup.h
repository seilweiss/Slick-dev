#pragma once

#include "Core/InspectorProperty.h"

#include "InspectorProperties/Int8InspectorProperty.h"
#include "InspectorProperties/Int16InspectorProperty.h"
#include "InspectorProperties/Int32InspectorProperty.h"
#include "InspectorProperties/UInt8InspectorProperty.h"
#include "InspectorProperties/UInt16InspectorProperty.h"
#include "InspectorProperties/UInt32InspectorProperty.h"
#include "InspectorProperties/FloatInspectorProperty.h"
#include "InspectorProperties/DoubleInspectorProperty.h"
#include "InspectorProperties/QStringInspectorProperty.h"
#include "InspectorProperties/StdStringInspectorProperty.h"
#include "InspectorProperties/Color8InspectorProperty.h"

namespace Slick {

    class InspectorGroup;

    class InspectorGroupItem
    {
    public:
        InspectorGroupItem(InspectorProperty* property) :
            m_type(Property),
            m_property(property)
        {
        }

        InspectorGroupItem(InspectorGroup* group) :
            m_type(Group),
            m_group(group)
        {
        }

        bool isProperty() const { return m_type == Property; }
        bool isGroup() const { return m_type == Group; }
        InspectorProperty* property() const { return isProperty() ? m_property : nullptr; }
        InspectorGroup* group() const { return isGroup() ? m_group : nullptr; }

        QString name() const;

    private:
        enum Type
        {
            Property,
            Group
        } m_type;

        union
        {
            InspectorProperty* m_property;
            InspectorGroup* m_group;
        };
    };

    class InspectorGroup : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName)
        Q_PROPERTY(bool nameVisible READ nameVisible WRITE setNameVisible)
        Q_PROPERTY(int itemCount READ itemCount)
        Q_PROPERTY(QVector<InspectorGroupItem*> items READ items)
        Q_PROPERTY(int propertyCount READ propertyCount)
        Q_PROPERTY(QVector<InspectorProperty*> properties READ properties)
        Q_PROPERTY(int groupCount READ groupCount)
        Q_PROPERTY(QVector<InspectorGroup*> groups READ groups)

    public:
        InspectorGroup(const QString& name, QObject* parent = nullptr);
        virtual ~InspectorGroup();

        QString name() const { return m_name; }
        void setName(const QString& name) { m_name = name; }

        QString displayName() const { return m_displayName; }
        void setDisplayName(const QString& displayName) { m_displayName = displayName; }

        bool nameVisible() const { return m_nameVisible; }
        void setNameVisible(bool visible) { m_nameVisible = visible; }

        void clear();

        int itemCount() const { return m_items.size(); }
        InspectorGroupItem* item(int index) const { return m_items[index]; }
        InspectorGroupItem* item(const QString& name) const;
        QVector<InspectorGroupItem*> items() const { return m_items; }
        bool hasItem(const QString& name) const { return item(name) != nullptr; }

        int propertyCount() const;
        InspectorProperty* property(int index) const;
        InspectorProperty* property(const QString& name) const;
        QVector<InspectorProperty*> properties() const;
        bool hasProperty(const QString& name) const { return property(name) != nullptr; }

        int groupCount() const;
        InspectorGroup* group(int index) const;
        InspectorGroup* group(const QString& name) const;
        QVector<InspectorGroup*> groups() const;
        bool hasGroup(const QString& name) const { return group(name) != nullptr; }

        InspectorProperty* addProperty(InspectorProperty* prop);
        InspectorGroup* addGroup(InspectorGroup* group);
        InspectorGroup* addGroup(const QString& name);

        Int8InspectorProperty* addNumber(const QString& name, int8_t* dataSource);
        Int16InspectorProperty* addNumber(const QString& name, int16_t* dataSource);
        Int32InspectorProperty* addNumber(const QString& name, int32_t* dataSource);
        UInt8InspectorProperty* addNumber(const QString& name, uint8_t* dataSource);
        UInt16InspectorProperty* addNumber(const QString& name, uint16_t* dataSource);
        UInt32InspectorProperty* addNumber(const QString& name, uint32_t* dataSource);
        FloatInspectorProperty* addNumber(const QString& name, float* dataSource);
        DoubleInspectorProperty* addNumber(const QString& name, double* dataSource);
        QStringInspectorProperty* addString(const QString& name, QString* dataSource);
        StdStringInspectorProperty* addString(const QString& name, std::string* dataSource);
        Color8InspectorProperty* addColor(const QString& name, uint8_t(*dataSource)[4]);

    private:
        QString m_name;
        QString m_displayName;
        bool m_nameVisible;
        QVector<InspectorGroupItem*> m_items;
    };

}
