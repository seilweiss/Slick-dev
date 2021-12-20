#pragma once

#include "Core/InspectorProperty.h"

#include "InspectorProperties/AssetInputProperty.h"
#include "InspectorProperties/CheckBoxProperty.h"
#include "InspectorProperties/ColorInputProperty.h"
#include "InspectorProperties/ComboBoxProperty.h"
#include "InspectorProperties/NumberInputProperty.h"
#include "InspectorProperties/TextInputProperty.h"
#include "InspectorProperties/VectorInputProperty.h"

namespace Slick {

    class InspectorGroup;

    class InspectorGroupItem
    {
    public:
        enum Type
        {
            Property,
            Group
        };

        InspectorGroupItem(InspectorProperty* property) :
            m_type(Property),
            m_property(property)
        {
        }

        InspectorGroupItem(InspectorGroup* group) :
            m_type(Group),
            m_group(group)
        {
        }

        Type type() const { return m_type; }
        bool isProperty() const { return m_type == Property; }
        bool isGroup() const { return m_type == Group; }
        InspectorProperty* property() const { return isProperty() ? m_property : nullptr; }
        InspectorGroup* group() const { return isGroup() ? m_group : nullptr; }

        QString name() const;
        QString id() const;

    private:
        Type m_type;

        union
        {
            InspectorProperty* m_property;
            InspectorGroup* m_group;
        };
    };

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
        Q_PROPERTY(int itemCount READ itemCount)
        Q_PROPERTY(QList<InspectorGroupItem*> items READ items)
        Q_PROPERTY(int propertyCount READ propertyCount)
        Q_PROPERTY(QList<InspectorProperty*> properties READ properties)
        Q_PROPERTY(int groupCount READ groupCount)
        Q_PROPERTY(QList<InspectorGroup*> groups READ groups)

    public:
        InspectorGroup(const QString& name, QObject* parent = nullptr);
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
        InspectorGroup* addGroup(const QString& name);

        AssetInputProperty* addAssetInput(const QString& name, const InspectorDataSource& dataSource, Scene* scene)
        {
            return (AssetInputProperty*)addProperty(new AssetInputProperty(name, dataSource, scene));
        }

        CheckBoxProperty* addCheckBox(const QString& name, const InspectorDataSource& dataSource, uint32_t mask = 0xFFFFFFFF)
        {
            return (CheckBoxProperty*)addProperty(new CheckBoxProperty(name, dataSource, mask));
        }

        ColorInputProperty* addColorInput(const QString& name, const InspectorDataSource& dataSource)
        {
            return (ColorInputProperty*)addProperty(new ColorInputProperty(name, dataSource));
        }

        ComboBoxProperty* addComboBox(const QString& name, const InspectorDataSource& dataSource, const QStringList& items = QStringList())
        {
            return (ComboBoxProperty*)addProperty(new ComboBoxProperty(name, dataSource, items));
        }

        NumberInputProperty* addNumberInput(const QString& name, const InspectorDataSource& dataSource)
        {
            return (NumberInputProperty*)addProperty(new NumberInputProperty(name, dataSource));
        }

        TextInputProperty* addTextInput(const QString& name, const InspectorDataSource& dataSource)
        {
            return (TextInputProperty*)addProperty(new TextInputProperty(name, dataSource));
        }

        VectorInputProperty* addVectorInput(const QString& name, const InspectorDataSource& dataSource)
        {
            return (VectorInputProperty*)addProperty(new VectorInputProperty(name, dataSource));
        }

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

    private:
        InspectorGroup* m_parentGroup;
        QString m_name;
        QString m_displayName;
        bool m_visible;
        bool m_nameVisible;
        bool m_expanded;
        QList<InspectorGroupItem*> m_items;
    };

}
