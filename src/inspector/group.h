#pragma once

#include "inspector/property.h"
#include "inspector/groupitem.h"
#include "inspector/listsource.h"

#include "inspector/properties/assetinputproperty.h"
#include "inspector/properties/buttonproperty.h"
#include "inspector/properties/checkboxproperty.h"
#include "inspector/properties/colorinputproperty.h"
#include "inspector/properties/comboboxproperty.h"
#include "inspector/properties/eventinputproperty.h"
#include "inspector/properties/numberinputproperty.h"
#include "inspector/properties/textinputproperty.h"
#include "inspector/properties/vectorinputproperty.h"

#include <QObject>

namespace Slick {

    namespace Inspector {

        class Group : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(Group* parentGroup READ parentGroup WRITE setParentGroup NOTIFY parentGroupChanged)
            Q_PROPERTY(QString id READ id CONSTANT)
            Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
            Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
            Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibilityChanged)
            Q_PROPERTY(bool nameVisible READ nameVisible WRITE setNameVisible NOTIFY nameVisibilityChanged)
            Q_PROPERTY(bool expanded READ expanded WRITE setExpanded NOTIFY expansionChanged)
            Q_PROPERTY(QString helpText READ helpText WRITE setHelpText NOTIFY helpTextChanged)
            Q_PROPERTY(AbstractListSource* listSource READ listSource WRITE setListSource)
            Q_PROPERTY(bool isList READ isList)
            Q_PROPERTY(int itemCount READ itemCount)
            Q_PROPERTY(QList<GroupItem*> items READ items)
            Q_PROPERTY(int propertyCount READ propertyCount)
            Q_PROPERTY(QList<Property*> properties READ properties)
            Q_PROPERTY(int groupCount READ groupCount)
            Q_PROPERTY(QList<Group*> groups READ groups)

        public:
            Group(const QString& name, const QString& displayName, QObject* parent = nullptr);
            virtual ~Group();

            Group* parentGroup() const { return m_parentGroup; }
            void setParentGroup(Group* group) { m_parentGroup = group; emit parentGroupChanged(group); }

            QString id() const;

            QString name() const { return m_name; }
            void setName(const QString& name) { m_name = name; emit nameChanged(name); }

            QString displayName() const { return m_displayName; }
            void setDisplayName(const QString& displayName) { m_displayName = displayName; emit displayNameChanged(displayName); }

            bool visible() const { return m_visible; }
            void setVisible(bool visible) { m_visible = visible; emit visibilityChanged(visible); }

            bool nameVisible() const { return m_nameVisible; }
            void setNameVisible(bool visible) { m_nameVisible = visible; emit nameVisibilityChanged(visible); }

            bool expanded() const { return m_expanded; }
            void setExpanded(bool expanded) { m_expanded = expanded; emit expansionChanged(expanded); }

            QString helpText() const { return m_helpText; }
            void setHelpText(const QString& helpText) { m_helpText = helpText; emit helpTextChanged(helpText); }

            AbstractListSource* listSource() const { return m_listSource; }
            void setListSource(AbstractListSource* listSource);

            bool isList() const { return m_listSource != nullptr; }

            void clear();

            int itemCount() const { return m_items.size(); }
            GroupItem* item(int index) const { return m_items[index]; }
            GroupItem* item(const QString& name) const;
            QList<GroupItem*> items() const { return m_items; }
            bool hasItem(const QString& name) const { return item(name) != nullptr; }

            int propertyCount() const;
            Property* property(int index) const;
            Property* property(const QString& name) const;
            QList<Property*> properties() const;
            bool hasProperty(const QString& name) const { return property(name) != nullptr; }

            int groupCount() const;
            Group* group(int index) const;
            Group* group(const QString& name) const;
            Group* group(const QString& name); // creates group if none exists
            QList<Group*> groups() const;
            bool hasGroup(const QString& name) const { return group(name) != nullptr; }

            GroupItem* addItem(GroupItem* item);
            Property* addProperty(Property* prop);
            Group* addGroup(Group* group);
            Group* addGroup(const QString& name, const QString& displayName);
            Group* addGroup();

            void removeItem(GroupItem* item);
            void removeItem(int index);
            void removeItem(const QString& name);
            void removeProperty(Property* prop);
            void removeProperty(int index);
            void removeProperty(const QString& name);
            void removeGroup(Group* group);
            void removeGroup(int index);
            void removeGroup(const QString& name);

            AssetInputProperty* addAssetInput(const QString& name, const QString& displayName, const DataSource& dataSource, Core::Scene* scene);
            AssetInputProperty* addAssetInput(const DataSource& dataSource, Core::Scene* scene);
            ButtonProperty* addButton(const QString& name, const QString& displayName, const DataSource& dataSource);
            ButtonProperty* addButton(const DataSource& dataSource);
            CheckBoxProperty* addCheckBox(const QString& name, const QString& displayName, const DataSource& dataSource, uint32_t mask = 0xFFFFFFFF);
            CheckBoxProperty* addCheckBox(const DataSource& dataSource, uint32_t mask = 0xFFFFFFFF);
            ColorInputProperty* addColorInput(const QString& name, const QString& displayName, const DataSource& dataSource);
            ColorInputProperty* addColorInput(const DataSource& dataSource);
            ComboBoxProperty* addComboBox(const QString& name, const QString& displayName, const DataSource& dataSource, const QStringList& items = QStringList());
            ComboBoxProperty* addComboBox(const DataSource& dataSource, const QStringList& items = QStringList());
            EventInputProperty* addEventInput(const QString& name, const QString& displayName, const DataSource& dataSource, Core::Scene* scene);
            EventInputProperty* addEventInput(const DataSource& dataSource, Core::Scene* scene);
            NumberInputProperty* addNumberInput(const QString& name, const QString& displayName, const DataSource& dataSource);
            NumberInputProperty* addNumberInput(const DataSource& dataSource);
            TextInputProperty* addTextInput(const QString& name, const QString& displayName, const DataSource& dataSource);
            TextInputProperty* addTextInput(const DataSource& dataSource);
            VectorInputProperty* addVectorInput(const QString& name, const QString& displayName, const DataSource& dataSource);
            VectorInputProperty* addVectorInput(const DataSource& dataSource);

            void addListItem();
            void removeListItem(int index);

            virtual bool equals(Group* other) const
            {
                return m_name == other->m_name;
            }

            void requestRefresh() { emit refreshRequested(); }

        signals:
            void refreshRequested();
            void parentGroupChanged(Slick::Inspector::Group* group);
            void nameChanged(const QString& name);
            void displayNameChanged(const QString& displayName);
            void visibilityChanged(bool visible);
            void nameVisibilityChanged(bool visible);
            void expansionChanged(bool expanded);
            void helpTextChanged(const QString& helpText);
            void listSourceChanged(Slick::Inspector::AbstractListSource* listSource);
            void listItemAdded();
            void listItemRemoved(int index);

        private:
            Group* m_parentGroup;
            QString m_name;
            QString m_displayName;
            bool m_visible;
            bool m_nameVisible;
            bool m_expanded;
            QString m_helpText;
            AbstractListSource* m_listSource;
            QList<GroupItem*> m_items;

            void refreshListItems();
        };

    }

}
