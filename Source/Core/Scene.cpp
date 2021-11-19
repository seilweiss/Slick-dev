#include "Core/Scene.h"

namespace Slick {

    Scene::Scene(QObject* parent) :
        QObject(parent),
        m_files(),
        m_game(HipHop::Game::Unknown),
        m_platform(HipHop::Platform::Unknown),
        m_language(HipHop::Language::Unknown),
        m_region(HipHop::Region::Unknown)
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
        }

        return success;
    }

}
