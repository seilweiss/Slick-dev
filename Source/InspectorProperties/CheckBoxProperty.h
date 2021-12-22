#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class CheckBoxProperty : public InspectorProperty
    {
        Q_OBJECT
        Q_PROPERTY(uint32_t mask READ mask WRITE setMask)

    public:
        CheckBoxProperty(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, displayName, dataSource, parent), m_mask(0xFFFFFFFF) {}

        CheckBoxProperty(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, uint32_t mask, QObject* parent = nullptr) :
            InspectorProperty(name, displayName, dataSource, parent), m_mask(mask) {}

        uint32_t mask() const { return m_mask; }
        void setMask(uint32_t mask) { m_mask = mask; }

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) override;

    private:
        uint32_t m_mask;
    };

}
