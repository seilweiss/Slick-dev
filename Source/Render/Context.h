#pragma once

namespace Slick {

    namespace Render {

        class Viewport;
        class Camera;

        struct Context
        {
            Viewport* viewport;
            Camera* camera;
        };

    }

}
