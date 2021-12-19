#include "Core/Asset.h"

#include "Core/SceneFile.h"

namespace Slick {

    Asset::Asset(HipHop::Asset asset, SceneFile* sceneFile) :
        QObject(sceneFile),
        m_file(sceneFile),
        m_scene(sceneFile->scene()),
        m_asset(asset),
        m_editor(nullptr),
        m_dirty(false),
        m_name(asset.GetName())
    {
    }

    void Asset::makeDirty()
    {
        m_dirty = true;
        emit dirty();
    }

    void Asset::load()
    {
        preLoad();

        if (m_editor)
        {
            m_editor->Load();
        }

        postLoad();

        m_dirty = false;
    }

    void Asset::save()
    {
        preSave();

        if (m_editor)
        {
            m_editor->Save();
        }

        postSave();

        m_dirty = false;
    }

    void Asset::inspect(Inspector* inspector)
    {
        auto assetGroup = inspector->addGroup("asset");
        auto nameProp = assetGroup->addTextInput("name", &m_name);

        assetGroup->setNameVisible(false);
        nameProp->setNameVisible(false);

        connect(nameProp, &InspectorProperty::dataChanged, this, [=]
        {
            m_asset.SetName(m_name);
            makeDirty();
        });
    }

}
