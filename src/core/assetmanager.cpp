#include "core/assetmanager.h"

#include "core/scene.h"

namespace Slick {

    namespace Core {

        AssetManager::AssetManager(Scene* scene) :
            QObject(scene),
            m_scene(scene)
        {
        }

    }

}
