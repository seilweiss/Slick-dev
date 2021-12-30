#include "inspector/property.h"

#include "inspector/group.h"

namespace Slick {

    namespace Inspector {

        Property::Property(const QString& name, const QString& displayName, const DataSource& dataSource, QObject* parent) :
            QObject(parent),
            m_parentGroup(qobject_cast<Group*>(parent)),
            m_name(name),
            m_displayName(displayName),
            m_dataSource(dataSource),
            m_visible(true),
            m_nameVisible(true),
            m_orientation(Qt::Horizontal),
            m_nameStretch(1),
            m_widgetStretch(1)
        {
        }

        Property::~Property()
        {
            if (m_dataSource.isProxy())
            {
                m_dataSource.freeProxy();
            }
        }

        QString Property::id() const
        {
            return m_parentGroup ? (m_parentGroup->id() + "." + m_name) : m_name;
        }

    }

}
