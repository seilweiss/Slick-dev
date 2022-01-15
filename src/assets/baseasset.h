#pragma once

#include "core/asset.h"

#include "hiphop/core/base_asset.h"

namespace Slick {

    namespace Assets {

        class BaseAsset : public Core::Asset
        {
            Q_OBJECT

        public:
            BaseAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::BaseAsset* serializer() const { return m_base; }
            void setSerializer(HipHop::BaseAsset* serializer) { Core::Asset::setSerializer(serializer); m_base = serializer; }

            virtual void inspect(Inspector::Root* root) override;

        protected:
            void inspectLinks(Inspector::Root* root);

        private:
            HipHop::BaseAsset m_baseDefault;
            HipHop::BaseAsset* m_base;
        };

    }

}
