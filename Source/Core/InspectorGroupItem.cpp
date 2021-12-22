#include "Core/InspectorGroupItem.h"

#include "Core/InspectorProperty.h"
#include "Core/InspectorGroup.h"

namespace Slick {

    QString InspectorGroupItem::name() const
    {
        switch (m_type)
        {
        case Property: return m_property->name();
        case Group: return m_group->name();
        default: return QString();
        }
    }

    void InspectorGroupItem::setName(const QString& name)
    {
        switch (m_type)
        {
        case Property: m_property->setName(name);
        case Group: m_group->setName(name);
        default: break;
        }
    }

    QString InspectorGroupItem::id() const
    {
        switch (m_type)
        {
        case Property: return m_property->id();
        case Group: return m_group->id();
        default: return QString();
        }
    }

}
