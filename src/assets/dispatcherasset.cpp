#include "assets/dispatcherasset.h"

namespace Slick {

    namespace Assets {

        DispatcherAsset::DispatcherAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_dispatcher(asset)
        {
            setSerializer(&m_dispatcher);
        }

        void DispatcherAsset::inspect(Inspector::Root* root)
        {
            BaseAsset::inspect(root);

            inspectLinks(root);
        }

    }

}
