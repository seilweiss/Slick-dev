#include "Core/InspectorGroup.h"

#include <QDebug>

namespace Slick {

    InspectorGroup::InspectorGroup(const QString& name, const QString& displayName, QObject* parent) :
        QObject(parent),
        m_parentGroup(qobject_cast<InspectorGroup*>(parent)),
        m_name(name),
        m_displayName(displayName),
        m_visible(true),
        m_nameVisible(true),
        m_expanded(true),
        m_listSource(nullptr),
        m_items()
    {
    }

    InspectorGroup::~InspectorGroup()
    {
        clear();

        if (m_listSource)
        {
            delete m_listSource;
        }
    }

    QString InspectorGroup::id() const
    {
        return m_parentGroup ? (m_parentGroup->id() + "." + m_name) : m_name;
    }

    void InspectorGroup::setListSource(AbstractInspectorListSource* listSource)
    {
        m_listSource = listSource;
        refreshListItems();
        emit listSourceChanged(listSource);
    }

    void InspectorGroup::refreshListItems()
    {
        clear();

        for (int i = 0; i < m_listSource->size(); i++)
        {
            m_listSource->createGroupItem(this, i);
        }
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

    InspectorGroup* InspectorGroup::group(const QString& name)
    {
        InspectorGroup* g = ((const InspectorGroup*)this)->group(name);

        return g ? g : addGroup(name, QString());
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
        if (m_listSource)
        {
            item->setName(QString::number(m_items.size()));
        }

        switch (item->type())
        {
        case InspectorGroupItem::Property:
            item->property()->setParent(this);
            item->property()->setParentGroup(this);
            break;
        case InspectorGroupItem::Group:
            item->group()->setParent(this);
            item->group()->setParentGroup(this);
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

    InspectorGroup* InspectorGroup::addGroup(const QString& name, const QString& displayName)
    {
        return addGroup(new InspectorGroup(name, displayName));
    }

    InspectorGroup* InspectorGroup::addGroup()
    {
        return addGroup(new InspectorGroup(QString(), QString()));
    }

    void InspectorGroup::removeItem(InspectorGroupItem* item)
    {
        Q_ASSERT(item);
        Q_ASSERT(m_items.contains(item));

        switch (item->type())
        {
        case InspectorGroupItem::Property:
            item->property()->setParent(nullptr);
            item->property()->setParentGroup(nullptr);
            break;
        case InspectorGroupItem::Group:
            item->group()->setParent(nullptr);
            item->group()->setParentGroup(nullptr);
            break;
        }

        m_items.removeOne(item);
    }

    void InspectorGroup::removeItem(int index)
    {
        removeItem(item(index));
    }

    void InspectorGroup::removeItem(const QString& name)
    {
        removeItem(item(name));
    }

    void InspectorGroup::removeProperty(InspectorProperty* prop)
    {
        Q_ASSERT(prop);

        bool found = false;

        for (InspectorGroupItem* item : m_items)
        {
            if (item->property() == prop)
            {
                found = true;
                removeItem(item);
                break;
            }
        }

        Q_ASSERT(found);
        Q_UNUSED(found);
    }

    void InspectorGroup::removeProperty(int index)
    {
        removeProperty(property(index));
    }

    void InspectorGroup::removeProperty(const QString& name)
    {
        removeProperty(property(name));
    }

    void InspectorGroup::removeGroup(InspectorGroup* group)
    {
        Q_ASSERT(group);

        bool found = false;

        for (InspectorGroupItem* item : m_items)
        {
            if (item->group() == group)
            {
                found = true;
                removeItem(item);
                break;
            }
        }

        Q_ASSERT(found);
        Q_UNUSED(found);
    }

    void InspectorGroup::removeGroup(int index)
    {
        removeGroup(group(index));
    }

    void InspectorGroup::removeGroup(const QString& name)
    {
        removeGroup(group(name));
    }

    void InspectorGroup::addListItem()
    {
        Q_ASSERT(m_listSource);

        if (m_listSource->size() < m_listSource->max())
        {
            m_listSource->add();
            refreshListItems();

            emit listItemAdded();
        }
    }

    void InspectorGroup::removeListItem(int index)
    {
        Q_ASSERT(m_listSource);

        m_listSource->remove(index);
        refreshListItems();

        emit listItemRemoved(index);
    }

    AssetInputProperty* InspectorGroup::addAssetInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, Scene* scene)
    {
        return (AssetInputProperty*)addProperty(new AssetInputProperty(name, displayName, dataSource, scene));
    }

    AssetInputProperty* InspectorGroup::addAssetInput(const InspectorDataSource& dataSource, Scene* scene)
    {
        return (AssetInputProperty*)addProperty(new AssetInputProperty(QString(), QString(), dataSource, scene));
    }

    CheckBoxProperty* InspectorGroup::addCheckBox(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, uint32_t mask)
    {
        return (CheckBoxProperty*)addProperty(new CheckBoxProperty(name, displayName, dataSource, mask));
    }

    CheckBoxProperty* InspectorGroup::addCheckBox(const InspectorDataSource& dataSource, uint32_t mask)
    {
        return (CheckBoxProperty*)addProperty(new CheckBoxProperty(QString(), QString(), dataSource, mask));
    }

    ColorInputProperty* InspectorGroup::addColorInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource)
    {
        return (ColorInputProperty*)addProperty(new ColorInputProperty(name, displayName, dataSource));
    }

    ColorInputProperty* InspectorGroup::addColorInput(const InspectorDataSource& dataSource)
    {
        return (ColorInputProperty*)addProperty(new ColorInputProperty(QString(), QString(), dataSource));
    }

    ComboBoxProperty* InspectorGroup::addComboBox(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, const QStringList& items)
    {
        return (ComboBoxProperty*)addProperty(new ComboBoxProperty(name, displayName, dataSource, items));
    }

    ComboBoxProperty* InspectorGroup::addComboBox(const InspectorDataSource& dataSource, const QStringList& items)
    {
        return (ComboBoxProperty*)addProperty(new ComboBoxProperty(QString(), QString(), dataSource, items));
    }

    EventInputProperty* InspectorGroup::addEventInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, Scene* scene)
    {
        return (EventInputProperty*)addProperty(new EventInputProperty(name, displayName, dataSource, scene));
    }

    EventInputProperty* InspectorGroup::addEventInput(const InspectorDataSource& dataSource, Scene* scene)
    {
        return (EventInputProperty*)addProperty(new EventInputProperty(QString(), QString(), dataSource, scene));
    }

    NumberInputProperty* InspectorGroup::addNumberInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource)
    {
        return (NumberInputProperty*)addProperty(new NumberInputProperty(name, displayName, dataSource));
    }

    NumberInputProperty* InspectorGroup::addNumberInput(const InspectorDataSource& dataSource)
    {
        return (NumberInputProperty*)addProperty(new NumberInputProperty(QString(), QString(), dataSource));
    }

    TextInputProperty* InspectorGroup::addTextInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource)
    {
        return (TextInputProperty*)addProperty(new TextInputProperty(name, displayName, dataSource));
    }

    TextInputProperty* InspectorGroup::addTextInput(const InspectorDataSource& dataSource)
    {
        return (TextInputProperty*)addProperty(new TextInputProperty(QString(), QString(), dataSource));
    }

    VectorInputProperty* InspectorGroup::addVectorInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource)
    {
        return (VectorInputProperty*)addProperty(new VectorInputProperty(name, displayName, dataSource));
    }

    VectorInputProperty* InspectorGroup::addVectorInput(const InspectorDataSource& dataSource)
    {
        return (VectorInputProperty*)addProperty(new VectorInputProperty(QString(), QString(), dataSource));
    }

}
