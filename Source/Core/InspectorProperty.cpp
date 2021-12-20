#include "Core/InspectorProperty.h"

#include "Core/InspectorGroup.h"

namespace Slick {

    InspectorProperty::InspectorProperty(const QString& name, const InspectorDataSource& dataSource, QObject* parent) :
        QObject(parent),
        m_parentGroup(qobject_cast<InspectorGroup*>(parent)),
        m_name(name),
        m_displayName(),
        m_dataSource(dataSource),
        m_visible(true),
        m_nameVisible(true),
        m_orientation(Qt::Horizontal),
        m_nameStretch(1),
        m_widgetStretch(1)
    {
    }

    QString InspectorProperty::id() const
    {
        return m_parentGroup ? (m_parentGroup->id() + "." + m_name) : m_name;
    }

}
