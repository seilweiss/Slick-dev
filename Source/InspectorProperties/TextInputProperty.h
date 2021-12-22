#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class TextInputProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        TextInputProperty(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, displayName, dataSource, parent), m_multiline(false), m_monospace(false) {}

        bool multiline() const { return m_multiline; }
        void setMultiline(bool multiline) { m_multiline = multiline; setOrientation(multiline ? Qt::Vertical : Qt::Horizontal); }

        bool monospace() const { return m_monospace; }
        void setMonospace(bool monospace) { m_monospace = monospace; }

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) override;

    private:
        bool m_multiline;
        bool m_monospace;
    };

}
