#include "Core/Scene.h"

namespace Slick {

    Scene::Scene(QObject* parent) :
        QObject(parent),
        m_files(),
        m_game(HipHop::Game::Unknown),
        m_platform(HipHop::Platform::Unknown),
        m_language(HipHop::Language::Unknown),
        m_region(HipHop::Region::Unknown),
        m_fogAsset(HipHop::Asset())
    {
    }

    void Scene::addFile(SceneFile* file)
    {
        file->setParent(this);

        m_files.append(file);
    }

    bool Scene::load()
    {
        if (m_game == HipHop::Game::Unknown ||
            m_platform == HipHop::Platform::Unknown ||
            m_language == HipHop::Language::Unknown ||
            m_region == HipHop::Region::Unknown)
        {
            return false;
        }

        bool success = true;

        for (SceneFile* file : m_files)
        {
            file->setGame(m_game);
            file->setPlatform(m_platform);
            file->setLanguage(m_language);
            file->setRegion(m_region);

            if (!file->load())
            {
                success = false;
                break;
            }

            if (file->hipHopFile().GetAssetCount(HipHop::AssetType::FOG) > 0)
            {
                m_fogAsset = file->hipHopFile().GetAsset(HipHop::AssetType::FOG);
                m_fogAsset.Load();
            }
        }

        return success;
    }

    void Scene::render(Render::Viewport* viewport)
    {
        Render::Camera* camera = viewport->camera();

        if (m_fogAsset)
        {
            camera->setFogEnabled(true);
            camera->setFogType(Render::FogLinear);
            camera->setFogDensity(m_fogAsset.fogDensity);
            camera->setFogStart(m_fogAsset.fogStart);
            camera->setFogEnd(m_fogAsset.fogStop);
            camera->setFogColor(QColor(m_fogAsset.fogColor[0], m_fogAsset.fogColor[1], m_fogAsset.fogColor[2], m_fogAsset.fogColor[3]));
            camera->setClearColor(QColor(m_fogAsset.bkgndColor[0], m_fogAsset.bkgndColor[1], m_fogAsset.bkgndColor[2], m_fogAsset.bkgndColor[3]));
        }
        else
        {
            camera->setFogEnabled(false);
            camera->setClearColor(QColor(0, 0, 0));
        }

        camera->clear(Render::AllBuffers);
    }

}
