#include "assets/baseasset.h"

#include "assets/baseassetprivate.h"
#include "core/scene.h"
#include "util/stringutils.h"
#include "util/hiphoputils.h"

#include <QCoreApplication>

namespace Slick {

    namespace Assets {

        namespace {

            class LinkListSource : public Inspector::ListSource<std::vector<HipHop::LinkAsset>>
            {
                Q_DECLARE_TR_FUNCTIONS(LinkListSource)

            public:
                LinkListSource(BaseAsset* asset, std::vector<HipHop::LinkAsset>& list) : Inspector::ListSource<std::vector<HipHop::LinkAsset>>(list), m_asset(asset) {}

                void createGroupItem(Inspector::Group* group, int index)
                {
                    HipHop::LinkAsset* link = &list()[index];
                    auto linkGroup = group->addGroup(new LinkGroup(link));

                    linkGroup->setExpanded(false);

                    auto srcEventProp = linkGroup->addEventInput("srcEvent", tr("Receive Event"), &link->srcEvent, m_asset->scene());
                    auto srcAssetProp = linkGroup->addAssetInput("srcAsset", tr("From Asset"), &link->chkAssetID, m_asset->scene());
                    auto dstEventProp = linkGroup->addEventInput("dstEvent", tr("Send Event"), &link->dstEvent, m_asset->scene());
                    auto dstAssetProp = linkGroup->addAssetInput("dstAsset", tr("To Asset"), &link->dstAssetID, m_asset->scene());
                    auto paramAssetProp = linkGroup->addAssetInput("paramAsset", tr("Param Asset"), &link->paramWidgetAssetID, m_asset->scene());

                    srcEventProp->setHelpText(tr("Event to receive."));
                    srcAssetProp->setHelpText(tr("Optional asset to receive the event from.\n"
                                                 "This filters out events received from other assets."));
                    dstEventProp->setHelpText(tr("Event to send."));
                    dstAssetProp->setHelpText(tr("Asset to send the event to."));
                    paramAssetProp->setHelpText(tr("Optional parameter asset to send with the event."));

                    QObject::connect(srcEventProp, &Inspector::Property::dataChanged, m_asset, &Core::Asset::makeDirty);
                    QObject::connect(srcAssetProp, &Inspector::Property::dataChanged, m_asset, &Core::Asset::makeDirty);
                    QObject::connect(dstEventProp, &Inspector::Property::dataChanged, m_asset, &Core::Asset::makeDirty);
                    QObject::connect(dstAssetProp, &Inspector::Property::dataChanged, m_asset, &Core::Asset::makeDirty);
                    QObject::connect(paramAssetProp, &Inspector::Property::dataChanged, m_asset, &Core::Asset::makeDirty);

                    auto updateDisplayName = [=]
                    {
                        HipHop::Game game = m_asset->scene()->game();
                        QString srcEventName = QString::fromStdString(HipHop::EventToString(link->srcEvent, game));
                        QString dstEventName = QString::fromStdString(HipHop::EventToString(link->dstEvent, game));
                        Core::Asset* dstAsset = m_asset->scene()->assetById(link->dstAssetID);
                        QString dstAssetName = dstAsset ? dstAsset->name() : Util::hexToString(link->dstAssetID);

                        linkGroup->setDisplayName(QString("%1 => %2 => %3").arg(srcEventName, dstEventName, dstAssetName));
                    };

                    QObject::connect(srcEventProp, &Inspector::Property::dataChanged, updateDisplayName);
                    QObject::connect(dstEventProp, &Inspector::Property::dataChanged, updateDisplayName);
                    QObject::connect(dstAssetProp, &Inspector::Property::dataChanged, updateDisplayName);

                    updateDisplayName();
                }

            private:
                BaseAsset* m_asset;
            };

        }

        BaseAsset::BaseAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Core::Asset(asset, sceneFile),
            m_baseDefault(asset)
        {
            setEditor(&m_baseDefault);
        }

        void BaseAsset::inspect(Inspector::Root* root)
        {
            Core::Asset::inspect(root);

            auto flagsGroup = root->addGroup("flags", tr("Flags"));
            auto enabledProp = flagsGroup->addCheckBox("enabled", tr("Enabled"), &m_base->baseFlags, HipHop::BaseAsset::Enabled);
            auto persistentProp = flagsGroup->addCheckBox("persistent", tr("Persistent"), &m_base->baseFlags, HipHop::BaseAsset::Persistent);
            //auto validProp = flagsGroup->addCheckBox("valid", tr("Valid"), &m_base->baseFlags, HipHop::BaseAsset::Valid);

            enabledProp->setHelpText(tr("Whether the object is enabled or not.\n"
                                        "Enabled means the object will be active (which can mean different\n"
                                        "things depending on the asset type) and able to receive events."));
            persistentProp->setHelpText(tr("Whether the object is persistent or not.\n"
                                           "Persistent means the object will save its current state upon\n"
                                           "leaving the level and load it when re-entering the level."));

            connect(enabledProp, &Inspector::Property::dataChanged, this, &BaseAsset::makeDirty);
            connect(persistentProp, &Inspector::Property::dataChanged, this, &BaseAsset::makeDirty);
        }

        void BaseAsset::inspectLinks(Inspector::Root* root)
        {
            auto linksGroup = root->addGroup("links", tr("Links"));
            linksGroup->setListSource(new LinkListSource(this, m_base->links));
        }

    }

}
