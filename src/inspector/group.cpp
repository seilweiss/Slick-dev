#include "inspector/group.h"

#include <QDebug>

namespace Slick {

    namespace Inspector {

        Group::Group(const QString& name, const QString& displayName, QObject* parent) :
            QObject(parent),
            m_parentGroup(qobject_cast<Group*>(parent)),
            m_name(name),
            m_displayName(displayName),
            m_visible(true),
            m_nameVisible(true),
            m_expanded(true),
            m_listSource(nullptr),
            m_items()
        {
        }

        Group::~Group()
        {
            clear();

            if (m_listSource)
            {
                delete m_listSource;
            }
        }

        QString Group::id() const
        {
            return m_parentGroup ? (m_parentGroup->id() + "." + m_name) : m_name;
        }

        void Group::setListSource(AbstractListSource* listSource)
        {
            m_listSource = listSource;
            refreshListItems();
            emit listSourceChanged(listSource);
        }

        void Group::refreshListItems()
        {
            clear();

            for (int i = 0; i < m_listSource->size(); i++)
            {
                m_listSource->createGroupItem(this, i);
            }
        }

        void Group::clear()
        {
            for (GroupItem* item : m_items)
            {
                switch (item->type())
                {
                case GroupItem::Property:
                    delete item->property();
                    break;
                case GroupItem::Group:
                    delete item->group();
                    break;
                }

                delete item;
            }

            m_items.clear();
        }

        GroupItem* Group::item(const QString& name) const
        {
            for (GroupItem* item : m_items)
            {
                if (item->name() == name)
                {
                    return item;
                }
            }

            return nullptr;
        }

        int Group::propertyCount() const
        {
            int count = 0;

            for (GroupItem* item : m_items)
            {
                if (item->isProperty())
                {
                    count++;
                }
            }

            return count;
        }

        Property* Group::property(int index) const
        {
            for (GroupItem* item : m_items)
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

        Property* Group::property(const QString& name) const
        {
            for (GroupItem* item : m_items)
            {
                if (item->isProperty() && item->name() == name)
                {
                    return item->property();
                }
            }

            return nullptr;
        }

        QList<Property*> Group::properties() const
        {
            QList<Property*> props;

            for (GroupItem* item : m_items)
            {
                if (item->isProperty())
                {
                    props.append(item->property());
                }
            }

            return props;
        }

        int Group::groupCount() const
        {
            int count = 0;

            for (GroupItem* item : m_items)
            {
                if (item->isGroup())
                {
                    count++;
                }
            }

            return count;
        }

        Group* Group::group(int index) const
        {
            for (GroupItem* item : m_items)
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

        Group* Group::group(const QString& name) const
        {
            for (GroupItem* item : m_items)
            {
                if (item->isGroup() && item->name() == name)
                {
                    return item->group();
                }
            }

            return nullptr;
        }

        Group* Group::group(const QString& name)
        {
            Group* g = ((const Group*)this)->group(name);

            return g ? g : addGroup(name, QString());
        }

        QList<Group*> Group::groups() const
        {
            QList<Group*> props;

            for (GroupItem* item : m_items)
            {
                if (item->isGroup())
                {
                    props.append(item->group());
                }
            }

            return props;
        }

        GroupItem* Group::addItem(GroupItem* item)
        {
            if (m_listSource)
            {
                item->setName(QString::number(m_items.size()));
            }

            switch (item->type())
            {
            case GroupItem::Property:
                item->property()->setParent(this);
                item->property()->setParentGroup(this);
                break;
            case GroupItem::Group:
                item->group()->setParent(this);
                item->group()->setParentGroup(this);
                break;
            }

            m_items.append(item);

            return item;
        }

        Property* Group::addProperty(Property* prop)
        {
            addItem(new GroupItem(prop));
            return prop;
        }

        Group* Group::addGroup(Group* group)
        {
            addItem(new GroupItem(group));
            return group;
        }

        Group* Group::addGroup(const QString& name, const QString& displayName)
        {
            return addGroup(new Group(name, displayName));
        }

        Group* Group::addGroup()
        {
            return addGroup(new Group(QString(), QString()));
        }

        void Group::removeItem(GroupItem* item)
        {
            Q_ASSERT(item);
            Q_ASSERT(m_items.contains(item));

            switch (item->type())
            {
            case GroupItem::Property:
                item->property()->setParent(nullptr);
                item->property()->setParentGroup(nullptr);
                break;
            case GroupItem::Group:
                item->group()->setParent(nullptr);
                item->group()->setParentGroup(nullptr);
                break;
            }

            m_items.removeOne(item);
        }

        void Group::removeItem(int index)
        {
            removeItem(item(index));
        }

        void Group::removeItem(const QString& name)
        {
            removeItem(item(name));
        }

        void Group::removeProperty(Property* prop)
        {
            Q_ASSERT(prop);

            bool found = false;

            for (GroupItem* item : m_items)
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

        void Group::removeProperty(int index)
        {
            removeProperty(property(index));
        }

        void Group::removeProperty(const QString& name)
        {
            removeProperty(property(name));
        }

        void Group::removeGroup(Group* group)
        {
            Q_ASSERT(group);

            bool found = false;

            for (GroupItem* item : m_items)
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

        void Group::removeGroup(int index)
        {
            removeGroup(group(index));
        }

        void Group::removeGroup(const QString& name)
        {
            removeGroup(group(name));
        }

        void Group::addListItem()
        {
            Q_ASSERT(m_listSource);

            if (!m_listSource->full())
            {
                m_listSource->add();
                refreshListItems();

                emit listItemAdded();
            }
        }

        void Group::removeListItem(int index)
        {
            Q_ASSERT(m_listSource);

            m_listSource->remove(index);
            refreshListItems();

            emit listItemRemoved(index);
        }

        AssetInputProperty* Group::addAssetInput(const QString& name, const QString& displayName, const DataSource& dataSource, Core::Scene* scene)
        {
            return (AssetInputProperty*)addProperty(new AssetInputProperty(name, displayName, dataSource, scene));
        }

        AssetInputProperty* Group::addAssetInput(const DataSource& dataSource, Core::Scene* scene)
        {
            return (AssetInputProperty*)addProperty(new AssetInputProperty(QString(), QString(), dataSource, scene));
        }

        CheckBoxProperty* Group::addCheckBox(const QString& name, const QString& displayName, const DataSource& dataSource, uint32_t mask)
        {
            return (CheckBoxProperty*)addProperty(new CheckBoxProperty(name, displayName, dataSource, mask));
        }

        CheckBoxProperty* Group::addCheckBox(const DataSource& dataSource, uint32_t mask)
        {
            return (CheckBoxProperty*)addProperty(new CheckBoxProperty(QString(), QString(), dataSource, mask));
        }

        ColorInputProperty* Group::addColorInput(const QString& name, const QString& displayName, const DataSource& dataSource)
        {
            return (ColorInputProperty*)addProperty(new ColorInputProperty(name, displayName, dataSource));
        }

        ColorInputProperty* Group::addColorInput(const DataSource& dataSource)
        {
            return (ColorInputProperty*)addProperty(new ColorInputProperty(QString(), QString(), dataSource));
        }

        ComboBoxProperty* Group::addComboBox(const QString& name, const QString& displayName, const DataSource& dataSource, const QStringList& items)
        {
            return (ComboBoxProperty*)addProperty(new ComboBoxProperty(name, displayName, dataSource, items));
        }

        ComboBoxProperty* Group::addComboBox(const DataSource& dataSource, const QStringList& items)
        {
            return (ComboBoxProperty*)addProperty(new ComboBoxProperty(QString(), QString(), dataSource, items));
        }

        EventInputProperty* Group::addEventInput(const QString& name, const QString& displayName, const DataSource& dataSource, Core::Scene* scene)
        {
            return (EventInputProperty*)addProperty(new EventInputProperty(name, displayName, dataSource, scene));
        }

        EventInputProperty* Group::addEventInput(const DataSource& dataSource, Core::Scene* scene)
        {
            return (EventInputProperty*)addProperty(new EventInputProperty(QString(), QString(), dataSource, scene));
        }

        NumberInputProperty* Group::addNumberInput(const QString& name, const QString& displayName, const DataSource& dataSource)
        {
            return (NumberInputProperty*)addProperty(new NumberInputProperty(name, displayName, dataSource));
        }

        NumberInputProperty* Group::addNumberInput(const DataSource& dataSource)
        {
            return (NumberInputProperty*)addProperty(new NumberInputProperty(QString(), QString(), dataSource));
        }

        TextInputProperty* Group::addTextInput(const QString& name, const QString& displayName, const DataSource& dataSource)
        {
            return (TextInputProperty*)addProperty(new TextInputProperty(name, displayName, dataSource));
        }

        TextInputProperty* Group::addTextInput(const DataSource& dataSource)
        {
            return (TextInputProperty*)addProperty(new TextInputProperty(QString(), QString(), dataSource));
        }

        VectorInputProperty* Group::addVectorInput(const QString& name, const QString& displayName, const DataSource& dataSource)
        {
            return (VectorInputProperty*)addProperty(new VectorInputProperty(name, displayName, dataSource));
        }

        VectorInputProperty* Group::addVectorInput(const DataSource& dataSource)
        {
            return (VectorInputProperty*)addProperty(new VectorInputProperty(QString(), QString(), dataSource));
        }

    }

}
