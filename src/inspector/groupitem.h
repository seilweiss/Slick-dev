#pragma once

#include <QString>

namespace Slick {

    namespace Inspector {

        class Property;
        class Group;

        class GroupItem
        {
        public:
            enum Type
            {
                Property,
                Group
            };

            GroupItem(Inspector::Property* property) : m_type(Property), m_property(property) {}
            GroupItem(Inspector::Group* group) : m_type(Group), m_group(group) {}

            Type type() const { return m_type; }
            bool isProperty() const { return m_type == Property; }
            bool isGroup() const { return m_type == Group; }
            Inspector::Property* property() const;
            Inspector::Group* group() const;

            QString name() const;
            void setName(const QString& name);

            QString id() const;

        private:
            Type m_type;

            union
            {
                void* m_data;
                Inspector::Property* m_property;
                Inspector::Group* m_group;
            };
        };

    }

}
