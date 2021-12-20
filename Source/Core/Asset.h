#pragma once

#include "Core/Inspectable.h"

#include "hiphop.h"

#include <QObject>

Q_MOC_INCLUDE("Core/SceneFile.h")
Q_MOC_INCLUDE("Core/Scene.h")

namespace Slick {

    class SceneFile;
    class Scene;

    class Asset : public QObject, public Inspectable
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(SceneFile* sceneFile READ sceneFile)
        Q_PROPERTY(Scene* scene READ scene)
        Q_PROPERTY(HipHop::Asset hipHopAsset READ hipHopAsset)
        Q_PROPERTY(bool isDirty READ isDirty)
        Q_PROPERTY(HipHop::AssetEditor* editor READ editor WRITE setEditor)

    public:
        Asset(HipHop::Asset asset, SceneFile* sceneFile);

        QString name() const { return QString::fromStdString(m_asset.GetName()); }
        void setName(const QString& name) { m_asset.SetName(name.toStdString()); emit nameChanged(name); }

        SceneFile* sceneFile() const { return m_file; }
        Scene* scene() const { return m_scene; }
        HipHop::Asset hipHopAsset() const { return m_asset; }

        bool isDirty() const { return m_dirty; }
        void makeDirty();

        HipHop::AssetEditor* editor() const { return m_editor; }
        void setEditor(HipHop::AssetEditor* editor) { m_editor = editor; }

        void load();
        void save();

        virtual void inspect(Inspector* inspector) override;
        virtual void setup() {}

    signals:
        void dirty();

        void nameChanged(const QString& name);

    protected:
        virtual void preLoad() {}
        virtual void postLoad() {}
        virtual void preSave() {}
        virtual void postSave() {}

    private:
        SceneFile* m_file;
        Scene* m_scene;
        HipHop::Asset m_asset;
        HipHop::AssetEditor* m_editor;
        bool m_dirty;
        std::string m_name;
    };

}
