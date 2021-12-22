#pragma once

#include <QString>

namespace Slick {

    class InspectorProperty;
    class InspectorGroup;

    class InspectorGroupItem
    {
    public:
        enum Type
        {
            Property,
            Group
        };

        InspectorGroupItem(InspectorProperty* property) : m_type(Property), m_property(property) {}
        InspectorGroupItem(InspectorGroup* group) : m_type(Group), m_group(group) {}

        Type type() const { return m_type; }
        bool isProperty() const { return m_type == Property; }
        bool isGroup() const { return m_type == Group; }
        InspectorProperty* property() const { return isProperty() ? m_property : nullptr; }
        InspectorGroup* group() const { return isGroup() ? m_group : nullptr; }

        QString name() const;
        void setName(const QString& name);

        QString id() const;

    private:
        Type m_type;

        union
        {
            void* m_data;
            InspectorProperty* m_property;
            InspectorGroup* m_group;
        };
    };

}
