#include "Core/Scene.h"

#include "Core/Camera.h"

#include "Assets/EnvAsset.h"
#include "Assets/FogAsset.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Slick {

    Scene::Scene(QObject* parent) :
        QObject(parent),
        m_files(),
        m_game(HipHop::Game::Unknown),
        m_platform(HipHop::Platform::Unknown),
        m_language(HipHop::Language::Unknown),
        m_region(HipHop::Region::Unknown),
        m_envAsset(nullptr),
        m_fogAsset(nullptr)
    {
    }

    void Scene::addFile(SceneFile* file)
    {
        file->setParent(this);

        m_files.append(file);
    }

    Asset* Scene::asset(quint32 id) const
    {
        for (SceneFile* file : m_files)
        {
            Asset* asset = file->asset(id);

            if (asset)
            {
                return asset;
            }
        }

        return nullptr;
    }

    Asset* Scene::asset(const QString& name) const
    {
        for (SceneFile* file : m_files)
        {
            Asset* asset = file->asset(name);

            if (asset)
            {
                return asset;
            }
        }

        return nullptr;
    }

    Asset* Scene::asset(HipHop::AssetType type, int index) const
    {
        for (SceneFile* file : m_files)
        {
            Asset* asset = file->asset(type, index);

            if (asset)
            {
                return asset;
            }

            index -= file->assetCount(type);
        }

        return nullptr;
    }

    QVector<Asset*> Scene::assets() const
    {
        QVector<Asset*> assets;

        for (SceneFile* file : m_files)
        {
            assets.append(file->assets());
        }

        return assets;
    }

    QVector<Asset*> Scene::assets(HipHop::AssetType type) const
    {
        QVector<Asset*> assets;

        for (SceneFile* file : m_files)
        {
            assets.append(file->assets(type));
        }

        return assets;
    }

    int Scene::assetCount() const
    {
        int count = 0;

        for (SceneFile* file : m_files)
        {
            count += file->assetCount();
        }

        return count;
    }

    int Scene::assetCount(HipHop::AssetType type) const
    {
        int count = 0;

        for (SceneFile* file : m_files)
        {
            count += file->assetCount(type);
        }

        return count;
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
        }

        return success;
    }

    void Scene::setup()
    {
        m_envAsset = (Assets::EnvAsset*)asset(HipHop::AssetType::ENV);
        m_fogAsset = (Assets::FogAsset*)asset(HipHop::AssetType::FOG);
    }

    void Scene::update(RenderContext* context)
    {
    }

    void Scene::render(RenderContext* context)
    {
        context->camera()->begin();

        if (m_fogAsset)
        {
            m_fogAsset->apply(context);
        }
        else
        {
            context->glDisable(GL_FOG);
            context->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

            Projection proj = context->camera()->projection();
            proj.farClip = 1000.0f;
            context->camera()->setProjection(proj);
        }

        context->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (m_envAsset)
        {
            m_envAsset->render(context);
        }

        context->camera()->end();
    }

}
