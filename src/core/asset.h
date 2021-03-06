#pragma once

#include "inspector/object.h"
#include "render/context.h"

#include "hiphop.h"

#include <QObject>

Q_MOC_INCLUDE("core/scenefile.h")
Q_MOC_INCLUDE("core/scene.h")

namespace Slick {

    namespace Core {

        class SceneFile;
        class Scene;

        class Asset : public QObject, public Inspector::Object
        {
            Q_OBJECT
            Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
            Q_PROPERTY(uint32_t id READ id)
            Q_PROPERTY(SceneFile* sceneFile READ sceneFile)
            Q_PROPERTY(Scene* scene READ scene)
            Q_PROPERTY(HipHop::Asset hipHopAsset READ hipHopAsset)
            Q_PROPERTY(bool isDirty READ isDirty)
            Q_PROPERTY(HipHop::AssetSerializer* serializer READ serializer WRITE setSerializer)

        public:
            Asset(HipHop::Asset asset, SceneFile* sceneFile);
            virtual ~Asset() {}

            QString name() const { return QString::fromStdString(m_asset.GetName()); }
            void setName(const QString& name) { m_asset.SetName(name.toStdString()); emit nameChanged(name); }

            uint32_t id() const { return m_asset.GetID(); }

            SceneFile* sceneFile() const { return m_file; }
            Scene* scene() const { return m_scene; }
            HipHop::Asset hipHopAsset() const { return m_asset; }

            bool isDirty() const { return m_dirty; }
            void makeDirty();

            HipHop::AssetSerializer* serializer() const { return m_serializer; }
            void setSerializer(HipHop::AssetSerializer* serializer) { m_serializer = serializer; }

            void load();
            void save();

            virtual void inspect(Inspector::Root* root) override;

        signals:
            void dirty();

            void nameChanged(const QString& name);

        private:
            SceneFile* m_file;
            Scene* m_scene;
            HipHop::Asset m_asset;
            HipHop::AssetSerializer* m_serializer;
            bool m_dirty;
        };

    }

}
