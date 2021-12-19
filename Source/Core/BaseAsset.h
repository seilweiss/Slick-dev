#pragma once

#include "Core/Asset.h"

#include "hiphop/core/base_asset.h"

namespace Slick {

    class BaseAsset : public Asset
    {
        Q_OBJECT

    public:
        BaseAsset(HipHop::Asset asset, SceneFile* sceneFile);

        HipHop::BaseAsset* editor() const { return m_base; }
        void setEditor(HipHop::BaseAsset* editor) { Asset::setEditor(editor); m_base = editor; }

        virtual void inspect(Inspector* inspector) override;

    protected:
        void inspectLinks(Inspector* inspector);

    private:
        HipHop::BaseAsset m_baseDefault;
        HipHop::BaseAsset* m_base;
    };

}
