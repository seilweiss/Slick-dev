#include "Assets/GroupAsset.h"

namespace Slick {

    namespace Assets {

        namespace {

            class ItemListSource : public InspectorListSource<std::vector<uint32_t>>
            {
            public:
                ItemListSource(GroupAsset* asset, std::vector<uint32_t>& list) : InspectorListSource(list), m_asset(asset) {}

                virtual void createGroupItem(InspectorGroup* group, int index) override
                {
                    auto itemProp = group->addAssetInput(&list()[index], m_asset->scene());

                    QObject::connect(itemProp, &InspectorProperty::dataChanged, m_asset, &GroupAsset::makeDirty);
                }

            private:
                GroupAsset* m_asset;
            };

        }

        GroupAsset::GroupAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_group(asset)
        {
            setEditor(&m_group);
        }

        void GroupAsset::inspect(Inspector* inspector)
        {
            BaseAsset::inspect(inspector);

            auto groupGroup = inspector->addGroup("group", tr("Group")); // lol
            auto eventBehaviorProp = groupGroup->addComboBox("sendEventsTo", tr("Send Events to"), &m_group.groupFlags, { tr("All Items"), tr("Random Item"), tr("Next Item in Group") });

            eventBehaviorProp->setHelpText(tr("Which item(s) to send incoming events to.\n"
                                              "All Items - Send event to all items at once.\n"
                                              "Random Item - Send event to a single random item.\n"
                                              "Next Item in Group - Send event to items in order. After the last item\n"
                                              "is sent an event, loop back to the first item."));

            auto itemsGroup = groupGroup->addGroup("items", tr("Items"));

            itemsGroup->setListSource(new ItemListSource(this, m_group.items));

            connect(eventBehaviorProp, &InspectorProperty::dataChanged, this, &GroupAsset::makeDirty);
            connect(itemsGroup, &InspectorGroup::listItemAdded, this, &GroupAsset::makeDirty);
            connect(itemsGroup, &InspectorGroup::listItemRemoved, this, &GroupAsset::makeDirty);

            inspectLinks(inspector);
        }

    }

}
