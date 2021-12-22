#pragma once

#include "Core/InspectorProperty.h"
#include "Core/InspectorGroupItem.h"
#include "Core/InspectorListSource.h"

#include "InspectorProperties/AssetInputProperty.h"
#include "InspectorProperties/CheckBoxProperty.h"
#include "InspectorProperties/ColorInputProperty.h"
#include "InspectorProperties/ComboBoxProperty.h"
#include "InspectorProperties/EventInputProperty.h"
#include "InspectorProperties/NumberInputProperty.h"
#include "InspectorProperties/TextInputProperty.h"
#include "InspectorProperties/VectorInputProperty.h"

namespace Slick {

    class InspectorGroup : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(InspectorGroup* parentGroup READ parentGroup WRITE setParentGroup NOTIFY parentGroupChanged)
        Q_PROPERTY(QString id READ id CONSTANT)
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
        Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibilityChanged)
        Q_PROPERTY(bool nameVisible READ nameVisible WRITE setNameVisible NOTIFY nameVisibilityChanged)
        Q_PROPERTY(bool expanded READ expanded WRITE setExpanded NOTIFY expansionChanged)
        Q_PROPERTY(QString helpText READ helpText WRITE setHelpText NOTIFY helpTextChanged)
        Q_PROPERTY(AbstractInspectorListSource* listSource READ listSource WRITE setListSource)
        Q_PROPERTY(bool isList READ isList)
        Q_PROPERTY(int itemCount READ itemCount)
        Q_PROPERTY(QList<InspectorGroupItem*> items READ items)
        Q_PROPERTY(int propertyCount READ propertyCount)
        Q_PROPERTY(QList<InspectorProperty*> properties READ properties)
        Q_PROPERTY(int groupCount READ groupCount)
        Q_PROPERTY(QList<InspectorGroup*> groups READ groups)

    public:
        InspectorGroup(const QString& name, const QString& displayName, QObject* parent = nullptr);
        virtual ~InspectorGroup();

        InspectorGroup* parentGroup() const { return m_parentGroup; }
        void setParentGroup(InspectorGroup* group) { m_parentGroup = group; emit parentGroupChanged(group); }

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

        AbstractInspectorListSource* listSource() const { return m_listSource; }
        void setListSource(AbstractInspectorListSource* listSource);

        bool isList() const { return m_listSource != nullptr; }

        void clear();

        int itemCount() const { return m_items.size(); }
        InspectorGroupItem* item(int index) const { return m_items[index]; }
        InspectorGroupItem* item(const QString& name) const;
        QList<InspectorGroupItem*> items() const { return m_items; }
        bool hasItem(const QString& name) const { return item(name) != nullptr; }

        int propertyCount() const;
        InspectorProperty* property(int index) const;
        InspectorProperty* property(const QString& name) const;
        QList<InspectorProperty*> properties() const;
        bool hasProperty(const QString& name) const { return property(name) != nullptr; }

        int groupCount() const;
        InspectorGroup* group(int index) const;
        InspectorGroup* group(const QString& name) const;
        InspectorGroup* group(const QString& name); // creates group if none exists
        QList<InspectorGroup*> groups() const;
        bool hasGroup(const QString& name) const { return group(name) != nullptr; }

        InspectorGroupItem* addItem(InspectorGroupItem* item);
        InspectorProperty* addProperty(InspectorProperty* prop);
        InspectorGroup* addGroup(InspectorGroup* group);
        InspectorGroup* addGroup(const QString& name, const QString& displayName);
        InspectorGroup* addGroup();

        void removeItem(InspectorGroupItem* item);
        void removeItem(int index);
        void removeItem(const QString& name);
        void removeProperty(InspectorProperty* prop);
        void removeProperty(int index);
        void removeProperty(const QString& name);
        void removeGroup(InspectorGroup* group);
        void removeGroup(int index);
        void removeGroup(const QString& name);

        AssetInputProperty* addAssetInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, Scene* scene);
        AssetInputProperty* addAssetInput(const InspectorDataSource& dataSource, Scene* scene);
        CheckBoxProperty* addCheckBox(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, uint32_t mask = 0xFFFFFFFF);
        CheckBoxProperty* addCheckBox(const InspectorDataSource& dataSource, uint32_t mask = 0xFFFFFFFF);
        ColorInputProperty* addColorInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource);
        ColorInputProperty* addColorInput(const InspectorDataSource& dataSource);
        ComboBoxProperty* addComboBox(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, const QStringList& items = QStringList());
        ComboBoxProperty* addComboBox(const InspectorDataSource& dataSource, const QStringList& items = QStringList());
        EventInputProperty* addEventInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, Scene* scene);
        EventInputProperty* addEventInput(const InspectorDataSource& dataSource, Scene* scene);
        NumberInputProperty* addNumberInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource);
        NumberInputProperty* addNumberInput(const InspectorDataSource& dataSource);
        TextInputProperty* addTextInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource);
        TextInputProperty* addTextInput(const InspectorDataSource& dataSource);
        VectorInputProperty* addVectorInput(const QString& name, const QString& displayName, const InspectorDataSource& dataSource);
        VectorInputProperty* addVectorInput(const InspectorDataSource& dataSource);

        void addListItem();
        void removeListItem(int index);

        virtual bool equals(InspectorGroup* other) const
        {
            return m_name == other->m_name;
        }

    signals:
        void parentGroupChanged(Slick::InspectorGroup* group);
        void nameChanged(const QString& name);
        void displayNameChanged(const QString& displayName);
        void visibilityChanged(bool visible);
        void nameVisibilityChanged(bool visible);
        void expansionChanged(bool expanded);
        void helpTextChanged(const QString& helpText);
        void listSourceChanged(Slick::AbstractInspectorListSource* listSource);
        void listItemAdded();
        void listItemRemoved(int index);

    private:
        InspectorGroup* m_parentGroup;
        QString m_name;
        QString m_displayName;
        bool m_visible;
        bool m_nameVisible;
        bool m_expanded;
        QString m_helpText;
        AbstractInspectorListSource* m_listSource;
        QList<InspectorGroupItem*> m_items;

        void refreshListItems();
    };

}
