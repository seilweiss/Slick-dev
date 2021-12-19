#pragma once

#include "Core/Inspector.h"
#include "Core/InspectorState.h"

namespace Slick {

    class Inspectable
    {
    public:
        InspectorState& inspectorState() { return m_state; }
        const InspectorState& inspectorState() const { return m_state; }

        virtual void inspect(Inspector* inspector) = 0;

    private:
        InspectorState m_state;
    };

}
