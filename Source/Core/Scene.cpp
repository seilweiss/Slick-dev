#include "Core/Scene.h"

#include "Render/Camera.h"

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
            }
        }

        if (m_fogAsset)
        {
            m_fogAsset.Load();
        }

        return success;
    }

    void Scene::update(float dt)
    {
        for (SceneFile* file : m_files)
        {
            for (HipHop::Asset hipAsset : file->hipHopFile().GetAssets())
            {
                Asset* asset = file->getAsset(hipAsset);

                if (asset)
                {
                    asset->update(dt);
                }
            }
        }
    }

    void Scene::render(Render::Context& context)
    {
        if (m_fogAsset)
        {
            //context.camera->setFogEnabled(true);
            context.camera->setFogType(Render::FogLinear);
            context.camera->setFogDensity(m_fogAsset.fogDensity);
            context.camera->setFogStart(m_fogAsset.fogStart);
            context.camera->setFogEnd(m_fogAsset.fogStop);
            context.camera->setFogColor(QColor(m_fogAsset.fogColor[0], m_fogAsset.fogColor[1], m_fogAsset.fogColor[2], m_fogAsset.fogColor[3]));
            context.camera->setClearColor(QColor(m_fogAsset.bkgndColor[0], m_fogAsset.bkgndColor[1], m_fogAsset.bkgndColor[2], m_fogAsset.bkgndColor[3]));
        }
        else
        {
            context.camera->setFogEnabled(false);
            context.camera->setClearColor(QColor(0, 0, 0));
        }

        context.camera->clear(Render::AllBuffers);

        for (SceneFile* file : m_files)
        {
            auto jsps = file->hipHopFile().GetAssets(HipHop::AssetType::JSP);

            for (auto jsp : jsps)
            {
                Asset* jspAsset = file->getAsset(jsp);

                if (jspAsset)
                {
                    jspAsset->render(context);
                }
            }
        }
    }

}
