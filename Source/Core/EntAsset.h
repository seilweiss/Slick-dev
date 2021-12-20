#pragma once

#include "Core/BaseAsset.h"

#include "hiphop/core/ent_asset.h"

namespace Slick {

    class EntAsset : public BaseAsset
    {
        Q_OBJECT

    public:
        EntAsset(HipHop::Asset asset, SceneFile* sceneFile);

        HipHop::EntAsset* editor() const { return m_ent; }
        void setEditor(HipHop::EntAsset* editor) { BaseAsset::setEditor(editor); m_ent = editor; }

        virtual void inspect(Inspector* inspector) override;

    protected:
        void inspectEntity(Inspector* inspector);

    private:
        HipHop::EntAsset m_entDefault;
        HipHop::EntAsset* m_ent;
        Vector3 m_rotation;
    };

}
