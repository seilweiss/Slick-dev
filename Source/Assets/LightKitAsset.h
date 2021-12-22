#pragma once

#include "Core/Asset.h"
#include "Core/RenderContext.h"

#include "hiphop/assets/lightkit_asset.h"

namespace Slick {

    namespace Assets {

        class LightKitAsset : public Asset
        {
            Q_OBJECT

        public:
            LightKitAsset(HipHop::Asset asset, SceneFile* sceneFile);

            void bind(RenderContext* context);
            void unbind(RenderContext* context);

            virtual void inspect(Inspector* inspector) override;

            bool lightPreviewEnabled(int index) const { return m_lightPreviews[index]; }
            void setLightPreviewEnabled(int index, bool enabled) { m_lightPreviews[index] = enabled; }

            Vector3 lightPosition(int index) const { return m_lightPositions[index]; }
            void setLightPosition(int index, const Vector3& pos);

            Vector3 lightRotation(int index) const { return m_lightRotations[index]; }
            void setLightRotation(int index, const Vector3& pos);

            Vector3 lightScale(int index) const { return m_lightScales[index]; }
            void setLightScale(int index, const Vector3& pos);

        protected:
            virtual void postLoad() override;

        private:
            HipHop::LightKitAsset m_lightKit;
            QList<bool> m_lightPreviews;
            QList<Vector3> m_lightPositions;
            QList<Vector3> m_lightRotations;
            QList<Vector3> m_lightScales;

            void updateLightMatrix(int index);
        };

    }

}
