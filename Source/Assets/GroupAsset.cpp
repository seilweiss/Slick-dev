#include "Assets/GroupAsset.h"

namespace Slick {

    namespace Assets {

        GroupAsset::GroupAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_group(asset)
        {
            setEditor(&m_group);
        }

        void GroupAsset::inspect(Inspector* inspector)
        {
            BaseAsset::inspect(inspector);

            auto groupGroup = inspector->addGroup("group"); // lol
            auto eventBehaviorProp = groupGroup->addComboBox("sendEventsTo", &m_group.groupFlags, { "All Items", "Random Item", "Next Item in Group" });

            connect(eventBehaviorProp, &InspectorProperty::dataChanged, this, &GroupAsset::makeDirty);

            auto itemsGroup = groupGroup->addGroup("items");
            itemsGroup->setDisplayName(QString("Items (%1)").arg(m_group.items.size()));

            for (int i = 0; i < m_group.items.size(); i++)
            {
                itemsGroup->addAssetInput(QString::number(i), &m_group.items[i], scene());
            }

            inspectLinks(inspector);
        }

    }

}
