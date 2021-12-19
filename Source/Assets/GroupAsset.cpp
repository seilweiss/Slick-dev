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
            auto eventBehaviorProp = groupGroup->addComboBox("eventBehavior", &m_group.groupFlags, { tr("Send to all items"), tr("Send to random item"), tr("Send to consecutive items") });

            connect(eventBehaviorProp, &InspectorProperty::dataChanged, this, &GroupAsset::makeDirty);

            auto itemsGroup = groupGroup->addGroup("items");
            itemsGroup->setDisplayName(QString("Items (%1)").arg(m_group.items.size()));
            itemsGroup->setExpanded(false);

            for (int i = 0; i < m_group.items.size(); i++)
            {
                itemsGroup->addAssetInput(QString::number(i), &m_group.items[i], scene());
            }

            inspectLinks(inspector);
        }

    }

}
