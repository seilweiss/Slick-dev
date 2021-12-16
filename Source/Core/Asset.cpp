#include "Core/Asset.h"

#include "Core/SceneFile.h"

namespace Slick {

    Asset::Asset(HipHop::Asset asset, SceneFile* sceneFile) :
        QObject(sceneFile),
        m_file(sceneFile),
        m_scene(sceneFile->scene()),
        m_asset(asset),
        m_inspector(new Inspector(this)),
        m_dirty(false),
        m_name(asset.GetName())
    {
        auto assetGroup = m_inspector->addGroup("asset");
        auto nameProp = assetGroup->addString("name", &m_name);

        assetGroup->setNameVisible(false);
        nameProp->setNameVisible(false);

        connect(nameProp, &InspectorProperty::dataChanged, this, [=]
        {
            m_asset.SetName(m_name);
            makeDirty();
        });
    }

    void Asset::makeDirty()
    {
        m_dirty = true;
        emit dirty();
    }

    void Asset::save()
    {
        doSave();
        m_dirty = false;
    }

}
