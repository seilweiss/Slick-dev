#pragma once

#include "Core/Inspector.h"

#include "hiphop.h"

#include <QObject>

Q_MOC_INCLUDE("Core/SceneFile.h")
Q_MOC_INCLUDE("Core/Scene.h")

namespace Slick {

    class SceneFile;
    class Scene;

    class Asset : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(SceneFile* sceneFile READ sceneFile)
        Q_PROPERTY(Scene* scene READ scene)
        Q_PROPERTY(HipHop::Asset hipHopAsset READ hipHopAsset)
        Q_PROPERTY(Inspector* inspector READ inspector)
        Q_PROPERTY(bool isDirty READ isDirty)

    public:
        Asset(HipHop::Asset asset, SceneFile* sceneFile);

        SceneFile* sceneFile() const { return m_file; }
        Scene* scene() const { return m_scene; }
        HipHop::Asset hipHopAsset() const { return m_asset; }
        Inspector* inspector() const { return m_inspector; }
        bool isDirty() const { return m_dirty; }

        void save();

    signals:
        void dirty();

    protected:
        void makeDirty();

        virtual void doSave() {}

    private:
        SceneFile* m_file;
        Scene* m_scene;
        HipHop::Asset m_asset;
        Inspector* m_inspector;
        bool m_dirty;
        std::string m_name;
    };

}
