#include "render/cameracontroller.h"

namespace Slick {

    namespace Render {

        CameraController::CameraController(Context* context, QObject* parent) :
            QObject(parent),
            m_context(context)
        {
            Q_ASSERT(context);
        }

    }

}
