#pragma once

#include <QObject>

namespace Slick {

    class InspectorCategory : public QObject
    {
        Q_OBJECT

    public:
        InspectorCategory(const QString& name, QObject* parent = nullptr) :
            QObject(parent),
            m_name(name),
            m_displayName(),
            m_headerVisible(true)
        {
        }

        QString name() const { return m_name; }
        void setName(const QString& name) { m_name = name; }

        QString displayName() const { return m_displayName; }
        void setDisplayName(const QString& displayName) { m_displayName = displayName; }

        bool headerVisible() const { return m_headerVisible; }
        void setHeaderVisible(bool visible) { m_headerVisible = visible; }

    private:
        QString m_name;
        QString m_displayName;
        bool m_headerVisible;
    };

}
