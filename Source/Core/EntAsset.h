#pragma once

#include "Core/BaseAsset.h"
#include "Core/RenderContext.h"

#include "hiphop/core/ent_asset.h"

namespace Slick {

    namespace Assets {

        class ModelAsset;
        class EnvAsset;
        class LightKitAsset;

    }

    class EntAsset : public BaseAsset
    {
        Q_OBJECT

    public:
        EntAsset(HipHop::Asset asset, SceneFile* sceneFile);

        HipHop::EntAsset* editor() const { return m_ent; }
        void setEditor(HipHop::EntAsset* editor) { BaseAsset::setEditor(editor); m_ent = editor; }

        virtual void update(RenderContext* context);
        virtual void render(RenderContext* context);

        virtual void setup() override;
        virtual void inspect(Inspector* inspector) override;

    protected:
        void inspectEntity(Inspector* inspector);
        void setLightKit(Assets::LightKitAsset* lightKit) { m_lightKit = lightKit; }

    private:
        HipHop::EntAsset m_entDefault;
        HipHop::EntAsset* m_ent;
        Assets::ModelAsset* m_model;
        Assets::EnvAsset* m_env;
        Assets::LightKitAsset* m_lightKit;
    };

}
