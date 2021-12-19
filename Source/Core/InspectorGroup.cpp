#include "Core/InspectorGroup.h"

namespace Slick {

    QString InspectorGroupItem::name() const
    {
        return m_type == Property ? m_property->name() : m_group->name();
    }

    InspectorGroup::InspectorGroup(const QString& name, QObject* parent) :
        QObject(parent),
        m_name(name),
        m_displayName(),
        m_nameVisible(true),
        m_expanded(true),
        m_items()
    {
    }

    InspectorGroup::~InspectorGroup()
    {
        clear();
    }

    void InspectorGroup::clear()
    {
        for (InspectorGroupItem* item : m_items)
        {
            switch (item->type())
            {
            case InspectorGroupItem::Property:
                delete item->property();
                break;
            case InspectorGroupItem::Group:
                delete item->group();
                break;
            }

            delete item;
        }

        m_items.clear();
    }

    InspectorGroupItem* InspectorGroup::item(const QString& name) const
    {
        for (InspectorGroupItem* item : m_items)
        {
            if (item->name() == name)
            {
                return item;
            }
        }

        return nullptr;
    }

    int InspectorGroup::propertyCount() const
    {
        int count = 0;

        for (InspectorGroupItem* item : m_items)
        {
            if (item->isProperty())
            {
                count++;
            }
        }

        return count;
    }

    InspectorProperty* InspectorGroup::property(int index) const
    {
        for (InspectorGroupItem* item : m_items)
        {
            if (item->isProperty())
            {
                if (index == 0)
                {
                    return item->property();
                }

                index--;
            }
        }

        return nullptr;
    }

    InspectorProperty* InspectorGroup::property(const QString& name) const
    {
        for (InspectorGroupItem* item : m_items)
        {
            if (item->isProperty() && item->name() == name)
            {
                return item->property();
            }
        }

        return nullptr;
    }

    QList<InspectorProperty*> InspectorGroup::properties() const
    {
        QList<InspectorProperty*> props;

        for (InspectorGroupItem* item : m_items)
        {
            if (item->isProperty())
            {
                props.append(item->property());
            }
        }

        return props;
    }

    int InspectorGroup::groupCount() const
    {
        int count = 0;

        for (InspectorGroupItem* item : m_items)
        {
            if (item->isGroup())
            {
                count++;
            }
        }

        return count;
    }

    InspectorGroup* InspectorGroup::group(int index) const
    {
        for (InspectorGroupItem* item : m_items)
        {
            if (item->isGroup())
            {
                if (index == 0)
                {
                    return item->group();
                }

                index--;
            }
        }

        return nullptr;
    }

    InspectorGroup* InspectorGroup::group(const QString& name) const
    {
        for (InspectorGroupItem* item : m_items)
        {
            if (item->isGroup() && item->name() == name)
            {
                return item->group();
            }
        }

        return nullptr;
    }

    QList<InspectorGroup*> InspectorGroup::groups() const
    {
        QList<InspectorGroup*> props;

        for (InspectorGroupItem* item : m_items)
        {
            if (item->isGroup())
            {
                props.append(item->group());
            }
        }

        return props;
    }

    InspectorGroupItem* InspectorGroup::addItem(InspectorGroupItem* item)
    {
        switch (item->type())
        {
        case InspectorGroupItem::Property:
            item->property()->setParent(this);
            break;
        case InspectorGroupItem::Group:
            item->group()->setParent(this);
            break;
        }

        m_items.append(item);

        return item;
    }

    InspectorProperty* InspectorGroup::addProperty(InspectorProperty* prop)
    {
        addItem(new InspectorGroupItem(prop));
        return prop;
    }

    InspectorGroup* InspectorGroup::addGroup(InspectorGroup* group)
    {
        addItem(new InspectorGroupItem(group));
        return group;
    }

    InspectorGroup* InspectorGroup::addGroup(const QString& name)
    {
        return addGroup(new InspectorGroup(name));
    }

}
