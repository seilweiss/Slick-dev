#include "assets/groupasset.h"

namespace Slick {

    namespace Assets {

        namespace {

            class ItemListSource : public Inspector::ListSource<std::vector<uint32_t>>
            {
            public:
                ItemListSource(GroupAsset* asset, std::vector<uint32_t>& list) : Inspector::ListSource<std::vector<uint32_t>>(list), m_asset(asset) {}

                virtual void createGroupItem(Inspector::Group* group, int index) override
                {
                    auto itemProp = group->addAssetInput(&list()[index], m_asset->scene());

                    QObject::connect(itemProp, &Inspector::Property::dataChanged, m_asset, &GroupAsset::makeDirty);
                }

            private:
                GroupAsset* m_asset;
            };

        }

        GroupAsset::GroupAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_group(asset)
        {
            setEditor(&m_group);
        }

        void GroupAsset::inspect(Inspector::Root* root)
        {
            BaseAsset::inspect(root);

            auto groupGroup = root->addGroup("group", tr("Group")); // lol
            auto eventBehaviorProp = groupGroup->addComboBox("sendEventsTo", tr("Send Events to"), &m_group.groupFlags, { tr("All Items"), tr("Random Item"), tr("Next Item in Group") });

            eventBehaviorProp->setHelpText(tr("Which item(s) to send incoming events to.\n"
                                              "All Items - Send event to all items at once.\n"
                                              "Random Item - Send event to a single random item.\n"
                                              "Next Item in Group - Send event to items in order. After the last item\n"
                                              "is sent an event, loop back to the first item."));

            auto itemsGroup = groupGroup->addGroup("items", tr("Items"));

            itemsGroup->setListSource(new ItemListSource(this, m_group.items));

            connect(eventBehaviorProp, &Inspector::Property::dataChanged, this, &GroupAsset::makeDirty);
            connect(itemsGroup, &Inspector::Group::listItemAdded, this, &GroupAsset::makeDirty);
            connect(itemsGroup, &Inspector::Group::listItemRemoved, this, &GroupAsset::makeDirty);

            inspectLinks(root);
        }

    }

}
