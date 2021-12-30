#include "inspector/groupitem.h"

#include "inspector/property.h"
#include "inspector/group.h"

namespace Slick {

    namespace Inspector {

        QString GroupItem::name() const
        {
            switch (m_type)
            {
            case Property: return m_property->name();
            case Group: return m_group->name();
            default: return QString();
            }
        }

        void GroupItem::setName(const QString& name)
        {
            switch (m_type)
            {
            case Property: m_property->setName(name);
            case Group: m_group->setName(name);
            default: break;
            }
        }

        QString GroupItem::id() const
        {
            switch (m_type)
            {
            case Property: return m_property->id();
            case Group: return m_group->id();
            default: return QString();
            }
        }

    }

}
