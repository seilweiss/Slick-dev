#include "Core/Asset.h"

#include "Core/SceneFile.h"

namespace Slick {

    Asset::Asset(HipHop::Asset asset, SceneFile* sceneFile) :
        QObject(sceneFile),
        m_file(sceneFile),
        m_asset(asset)
    {
    }

}
