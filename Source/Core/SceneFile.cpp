#include "Core/SceneFile.h"

#include "Core/Scene.h"

#include "Assets/CounterAsset.h"
#include "Assets/EnvAsset.h"
#include "Assets/FogAsset.h"
#include "Assets/JSPAsset.h"
#include "Assets/TextAsset.h"
#include "Assets/TimerAsset.h"

namespace Slick {

    SceneFile::SceneFile(Scene* scene) :
        QObject(scene),
        m_scene(scene),
        m_path(),
        m_file(),
        m_stream(),
        m_game(HipHop::Game::Unknown),
        m_platform(HipHop::Platform::Unknown),
        m_language(HipHop::Language::Unknown),
        m_region(HipHop::Region::Unknown)
    {
    }

    Asset* SceneFile::asset(HipHop::AssetType type, int index)
    {
        int assetIndex = m_file.GetAssetIndex(type, index);

        if (assetIndex != -1)
        {
            return asset(m_file.GetAssetAt(assetIndex).GetID());
        }

        return nullptr;
    }

    QVector<Asset*> SceneFile::assets(HipHop::AssetType type)
    {
        QVector<Asset*> assets;
        std::vector<HipHop::Asset> hipAssets = m_file.GetAssets(type);

        for (HipHop::Asset a : hipAssets)
        {
            assets.append(asset(a.GetID()));
        }

        return assets;
    }

    int SceneFile::assetCount(HipHop::AssetType type) const
    {
        return m_file.GetAssetCount(type);
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

        loadAssets();

        return true;
    }

    void SceneFile::loadAssets()
    {
        for (HipHop::Asset hipAsset : m_file.GetAssets())
        {
            Asset* asset = nullptr;

            switch (hipAsset.GetType())
            {
            case HipHop::AssetType::CNTR:
                asset = new Assets::CounterAsset(hipAsset, this);
                break;
            case HipHop::AssetType::ENV:
                asset = new Assets::EnvAsset(hipAsset, this);
                break;
            case HipHop::AssetType::FOG:
                asset = new Assets::FogAsset(hipAsset, this);
                break;
            case HipHop::AssetType::JSP:
                asset = new Assets::JSPAsset(hipAsset, this);
                break;
            case HipHop::AssetType::TIMR:
                asset = new Assets::TimerAsset(hipAsset, this);
                break;
            case HipHop::AssetType::TEXT:
                asset = new Assets::TextAsset(hipAsset, this);
                break;
            default:
                asset = new Asset(hipAsset, this);
                break;
            }

            if (asset)
            {
                m_assetMap[hipAsset.GetID()] = asset;
            }
        }
    }

}
