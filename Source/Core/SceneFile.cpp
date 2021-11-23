#include "Core/SceneFile.h"

#include "Assets/JSPAsset.h"

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

        for (Asset* asset : m_assetMap)
        {
            asset->deleteLater();
        }

        m_assetMap.clear();

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

        for (HipHop::Asset hipAsset : m_file.GetAssets())
        {
            Asset* asset = nullptr;

            switch (hipAsset.GetType())
            {
            case HipHop::AssetType::JSP:
                asset = new Assets::JSPAsset(hipAsset, this);
                break;
            default:
                break;
            }

            if (asset)
            {
                asset->setSceneFile(this);

                m_assetMap[hipAsset.GetID()] = asset;
            }
        }

        return true;
    }

}
