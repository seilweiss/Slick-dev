#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Slick {

    namespace Util {

        inline void decomposeMatrix(const glm::mat4& mat, glm::vec3& pos, glm::vec3& rot, glm::vec3& scale)
        {
            glm::quat r;
            glm::vec3 skew;
            glm::vec4 persp;

            glm::decompose(mat, scale, r, pos, skew, persp);

            //r = glm::conjugate(r);

            rot = glm::eulerAngles(r);
        }

    }

}
