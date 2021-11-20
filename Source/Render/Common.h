#pragma once

namespace Slick {

    namespace Render {

        enum ClearBuffer
        {
            ColorBuffer = 0x1,
            DepthBuffer = 0x2,
            StencilBuffer = 0x4,
            AllBuffers = ColorBuffer | DepthBuffer | StencilBuffer
        };

        enum FogType
        {
            FogLinear,
            FogExp,
            FogExp2
        };

    }

}
