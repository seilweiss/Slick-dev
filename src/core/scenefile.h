#pragma once

#include "core/asset.h"

#include "hiphop.h"

#include <QObject>
#include <QMap>

Q_MOC_INCLUDE("core/scene.h")

namespace Slick {

    namespace Core {

        class Scene;

        class SceneFile : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString path READ path WRITE setPath)
            Q_PROPERTY(Scene* scene READ scene)
            Q_PROPERTY(HipHop::File hipHopFile READ hipHopFile)
            Q_PROPERTY(HipHop::FileStream hipHopStream READ hipHopStream)
            Q_PROPERTY(HipHop::Game game READ game WRITE setGame)
            Q_PROPERTY(HipHop::Platform platform READ platform WRITE setPlatform)
            Q_PROPERTY(HipHop::Language language READ language WRITE setLanguage)
            Q_PROPERTY(HipHop::Region region READ region WRITE setRegion)

        public:
            SceneFile(Scene* scene);

            Scene* scene() const { return m_scene; }

            QString path() const { return m_path; }
            void setPath(const QString& path) { m_path = path; }

            HipHop::File& hipHopFile() { return m_file; }
            HipHop::FileStream& hipHopStream() { return m_stream; }

            HipHop::Game game() const { return m_game; }
            void setGame(HipHop::Game game) { m_game = game; }

            HipHop::Platform platform() const { return m_platform; }
            void setPlatform(HipHop::Platform platform) { m_platform = platform; }

            HipHop::Language language() const { return m_language; }
            void setLanguage(HipHop::Language language) { m_language = language; }

            HipHop::Region region() const { return m_region; }
            void setRegion(HipHop::Region region) { m_region = region; }

            void addAsset(Asset* asset);

            Asset* assetById(uint32_t id) const { return m_assetMap.contains(id) ? m_assetMap[id] : nullptr; }
            Asset* assetByName(const QString& name) const { return assetById(HipHop::Util::Hash(name.toStdString())); }
            Asset* assetByType(HipHop::AssetType type, int index = 0);
            QList<Asset*> assets() const { return m_assetMap.values(); }
            QList<Asset*> assets(HipHop::AssetType type);

            template <class T> QList<T*> assets(HipHop::AssetType type)
            {
                QList<T*> result;
                QList<Asset*> a = assets(type);

                for (Asset* asset : a)
                {
                    result.append(qobject_cast<T*>(asset));
                }

                return result;
            }

            int assetCount() const { return m_assetMap.size(); }
            int assetCount(HipHop::AssetType type) const;

            bool load();

        private:
            Scene* m_scene;
            QString m_path;
            HipHop::File m_file;
            HipHop::FileStream m_stream;
            HipHop::Game m_game;
            HipHop::Platform m_platform;
            HipHop::Language m_language;
            HipHop::Region m_region;
            QMap<uint32_t, Asset*> m_assetMap;
        };

    }

}
