#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class AbstractStringInspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        AbstractStringInspectorProperty(const QString& name, void* dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent),
            m_multiline(false),
            m_monospace(false) {}

        bool multiline() const { return m_multiline; }
        void setMultiline(bool multiline) { m_multiline = multiline; setOrientation(multiline ? Qt::Vertical : Qt::Horizontal); }

        bool monospace() const { return m_monospace; }
        void setMonospace(bool monospace) { m_monospace = monospace; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override = 0;

    private:
        bool m_multiline;
        bool m_monospace;
    };

}
