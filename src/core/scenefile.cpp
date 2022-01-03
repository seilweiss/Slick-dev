#include "core/scenefile.h"

#include "core/scene.h"

namespace Slick {

    namespace Core {

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

        void SceneFile::addAsset(Asset* asset)
        {
            asset->setParent(this);
            m_assetMap[asset->id()] = asset;
        }

        Asset* SceneFile::assetByType(HipHop::AssetType type, int index)
        {
            int assetIndex = m_file.GetAssetIndex(type, index);

            if (assetIndex != -1)
            {
                return assetById(m_file.GetAssetAt(assetIndex).GetID());
            }

            return nullptr;
        }

        QList<Asset*> SceneFile::assets(HipHop::AssetType type)
        {
            QList<Asset*> assets;
            std::vector<HipHop::Asset> hipAssets = m_file.GetAssets(type);

            for (HipHop::Asset a : hipAssets)
            {
                assets.append(assetById(a.GetID()));
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

            return true;
        }

    }

}
