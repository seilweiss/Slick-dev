#include "inspector/groupitem.h"

#include "inspector/property.h"
#include "inspector/group.h"

#include <QDebug>

namespace Slick {

    namespace Inspector {

        Property* GroupItem::property() const
        {
            Q_ASSERT(isProperty());

            if (isProperty())
            {
                return m_property;
            }
            else
            {
                qDebug().noquote() << "WARNING: tried to get non-property from item " << id();
                return nullptr;
            }
        }

        Group* GroupItem::group() const
        {
            Q_ASSERT(isGroup());

            if (isGroup())
            {
                return m_group;
            }
            else
            {
                qDebug().noquote() << "WARNING: tried to get non-group from item " << id();
                return nullptr;
            }
        }

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
