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
            if (item->isProperty())
            {
                delete item->property();
            }
            else
            {
                delete item->group();
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

    QVector<InspectorProperty*> InspectorGroup::properties() const
    {
        QVector<InspectorProperty*> props;

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

    QVector<InspectorGroup*> InspectorGroup::groups() const
    {
        QVector<InspectorGroup*> props;

        for (InspectorGroupItem* item : m_items)
        {
            if (item->isGroup())
            {
                props.append(item->group());
            }
        }

        return props;
    }

    InspectorProperty* InspectorGroup::addProperty(InspectorProperty* prop)
    {
        prop->setParent(this);

        m_items.append(new InspectorGroupItem(prop));

        return prop;
    }

    InspectorGroup* InspectorGroup::addGroup(InspectorGroup* group)
    {
        group->setParent(this);

        m_items.append(new InspectorGroupItem(group));

        return group;
    }

    InspectorGroup* InspectorGroup::addGroup(const QString& name)
    {
        return addGroup(new InspectorGroup(name));
    }

    Int8InspectorProperty* InspectorGroup::addNumber(const QString& name, int8_t* dataSource)
    {
        return (Int8InspectorProperty*)addProperty(new Int8InspectorProperty(name, dataSource));
    }

    Int16InspectorProperty* InspectorGroup::addNumber(const QString& name, int16_t* dataSource)
    {
        return (Int16InspectorProperty*)addProperty(new Int16InspectorProperty(name, dataSource));
    }

    Int32InspectorProperty* InspectorGroup::addNumber(const QString& name, int32_t* dataSource)
    {
        return (Int32InspectorProperty*)addProperty(new Int32InspectorProperty(name, dataSource));
    }

    UInt8InspectorProperty* InspectorGroup::addNumber(const QString& name, uint8_t* dataSource)
    {
        return (UInt8InspectorProperty*)addProperty(new UInt8InspectorProperty(name, dataSource));
    }

    UInt16InspectorProperty* InspectorGroup::addNumber(const QString& name, uint16_t* dataSource)
    {
        return (UInt16InspectorProperty*)addProperty(new UInt16InspectorProperty(name, dataSource));
    }

    UInt32InspectorProperty* InspectorGroup::addNumber(const QString& name, uint32_t* dataSource)
    {
        return (UInt32InspectorProperty*)addProperty(new UInt32InspectorProperty(name, dataSource));
    }

    FloatInspectorProperty* InspectorGroup::addNumber(const QString& name, float* dataSource)
    {
        return (FloatInspectorProperty*)addProperty(new FloatInspectorProperty(name, dataSource));
    }

    DoubleInspectorProperty* InspectorGroup::addNumber(const QString& name, double* dataSource)
    {
        return (DoubleInspectorProperty*)addProperty(new DoubleInspectorProperty(name, dataSource));
    }

    QStringInspectorProperty* InspectorGroup::addString(const QString& name, QString* dataSource)
    {
        return (QStringInspectorProperty*)addProperty(new QStringInspectorProperty(name, dataSource));
    }

    StdStringInspectorProperty* InspectorGroup::addString(const QString& name, std::string* dataSource)
    {
        return (StdStringInspectorProperty*)addProperty(new StdStringInspectorProperty(name, dataSource));
    }

    Color8InspectorProperty* InspectorGroup::addColor(const QString& name, uint8_t(*dataSource)[4])
    {
        return (Color8InspectorProperty*)addProperty(new Color8InspectorProperty(name, dataSource));
    }

}
