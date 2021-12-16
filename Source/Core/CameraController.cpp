#include "Core/CameraController.h"

#include "Core/Viewport.h"

namespace Slick {

    CameraController::CameraController(RenderContext* context) :
        QObject(context),
        m_context(context)
    {
        Q_ASSERT(context);
    }

}
