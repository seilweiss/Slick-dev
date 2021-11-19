#include "Core/SceneFile.h"

namespace Slick {

    SceneFile::SceneFile(QObject* parent) :
        QObject(parent),
        m_path(),
        m_file(),
        m_stream(),
        m_game(HipHop::Game::Unknown),
        m_platform(HipHop::Platform::Unknown),
        m_language(HipHop::Language::Unknown),
        m_region(HipHop::Region::Unknown)
    {
    }

    bool SceneFile::load()
    {
        if (m_game == HipHop::Game::Unknown ||
            m_platform == HipHop::Platform::Unknown ||
            m_language == HipHop::Language::Unknown ||
            m_region == HipHop::Region::Unknown ||
            m_path.isEmpty())
        {
            return false;
        }

        m_file.Destroy();
        m_file.SetStream(&m_stream);

        if (!m_stream.Open(m_path.toStdString()))
        {
            return false;
        }

        if (!m_file.Read())
        {
            return false;
        }

        if (m_file.GetGame() == HipHop::Game::Unknown)
        {
            m_file.SetGame(m_game);
        }

        if (m_file.GetPlatform() == HipHop::Platform::Unknown)
        {
            m_file.SetPlatform(m_platform);
        }

        if (m_file.GetLanguage() == HipHop::Language::Unknown)
        {
            m_file.SetLanguage(m_language);
        }

        if (m_file.GetRegion() == HipHop::Region::Unknown)
        {
            m_file.SetRegion(m_region);
        }

        m_file.InitDefaultSettings();

        if (!m_file.LoadAssets())
        {
            return false;
        }

        return true;
    }

}
