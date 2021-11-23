#pragma once

#include "Render/Context.h"

#include "hiphop.h"

#include <QObject>

Q_MOC_INCLUDE("Core/SceneFile.h")

namespace Slick {

    class SceneFile;

    class Asset : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(SceneFile* sceneFile READ sceneFile WRITE setSceneFile)
        Q_PROPERTY(HipHop::Asset hipHopAsset READ hipHopAsset)

    public:
        Asset(HipHop::Asset asset, SceneFile* sceneFile);

        SceneFile* sceneFile() const { return m_file; }
        void setSceneFile(SceneFile* file) { m_file = file; }

        HipHop::Asset hipHopAsset() const { return m_asset; }

        virtual void update(float dt) { Q_UNUSED(dt); }
        virtual void render(Render::Context& context) { Q_UNUSED(context); }

    private:
        SceneFile* m_file;
        HipHop::Asset m_asset;
    };

}
