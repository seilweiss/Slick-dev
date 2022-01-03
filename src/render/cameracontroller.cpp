#include "render/cameracontroller.h"

#include "render/context.h"

namespace Slick {

    namespace Render {

        CameraController::CameraController(Context* context, QObject* parent) :
            QObject(parent),
            m_context(context)
        {
            Q_ASSERT(context);
        }

        void CameraController::setViewMatrix(const glm::mat4& mat)
        {
            m_context->camera()->setViewMatrix(mat);
        }

    }

}
