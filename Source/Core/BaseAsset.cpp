#include "Core/BaseAsset.h"

#include "Core/BaseAssetPrivate.h"
#include "Core/Scene.h"
#include "Core/Util.h"

#include <QCoreApplication>

namespace Slick {

    namespace {

        class LinkListSource : public InspectorListSource<std::vector<HipHop::LinkAsset>>
        {
            Q_DECLARE_TR_FUNCTIONS(LinkListSource)

        public:
            LinkListSource(BaseAsset* asset, std::vector<HipHop::LinkAsset>& list) : InspectorListSource(list), m_asset(asset) {}

            void LinkListSource::createGroupItem(InspectorGroup* group, int index)
            {
                HipHop::LinkAsset* link = &list()[index];
                auto linkGroup = group->addGroup(new LinkGroup(link));

                linkGroup->setExpanded(false);

                QStringList eventNames = Util::eventNames(m_asset->scene()->game());

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

                QObject::connect(srcEventProp, &InspectorProperty::dataChanged, m_asset, &Asset::makeDirty);
                QObject::connect(srcAssetProp, &InspectorProperty::dataChanged, m_asset, &Asset::makeDirty);
                QObject::connect(dstEventProp, &InspectorProperty::dataChanged, m_asset, &Asset::makeDirty);
                QObject::connect(dstAssetProp, &InspectorProperty::dataChanged, m_asset, &Asset::makeDirty);
                QObject::connect(paramAssetProp, &InspectorProperty::dataChanged, m_asset, &Asset::makeDirty);

                auto updateDisplayName = [=]
                {
                    HipHop::Game game = m_asset->scene()->game();
                    QString srcEventName = QString::fromStdString(HipHop::EventToString(link->srcEvent, game));
                    QString dstEventName = QString::fromStdString(HipHop::EventToString(link->dstEvent, game));
                    Asset* dstAsset = m_asset->scene()->asset(link->dstAssetID);
                    QString dstAssetName = dstAsset ? dstAsset->name() : Util::hexToString(link->dstAssetID);

                    linkGroup->setDisplayName(QString("%1 => %2 => %3").arg(srcEventName, dstEventName, dstAssetName));
                };

                QObject::connect(srcEventProp, &InspectorProperty::dataChanged, updateDisplayName);
                QObject::connect(dstEventProp, &InspectorProperty::dataChanged, updateDisplayName);
                QObject::connect(dstAssetProp, &InspectorProperty::dataChanged, updateDisplayName);

                updateDisplayName();
            }

        private:
            BaseAsset* m_asset;
        };

    }

    BaseAsset::BaseAsset(HipHop::Asset asset, SceneFile* sceneFile) :
        Asset(asset, sceneFile),
        m_baseDefault(asset)
    {
        setEditor(&m_baseDefault);
    }

    void BaseAsset::inspect(Inspector* inspector)
    {
        Asset::inspect(inspector);

        auto flagsGroup = inspector->addGroup("flags", tr("Flags"));
        auto enabledProp = flagsGroup->addCheckBox("enabled", tr("Enabled"), &m_base->baseFlags, HipHop::BaseAsset::Enabled);
        auto persistentProp = flagsGroup->addCheckBox("persistent", tr("Persistent"), &m_base->baseFlags, HipHop::BaseAsset::Persistent);
        //auto validProp = flagsGroup->addCheckBox("valid", tr("Valid"), &m_base->baseFlags, HipHop::BaseAsset::Valid);

        enabledProp->setHelpText(tr("Whether the object is enabled or not.\n"
                                    "Enabled means the object will be active (which can mean different\n"
                                    "things depending on the asset type) and able to receive events."));
        persistentProp->setHelpText(tr("Whether the object is persistent or not.\n"
                                       "Persistent means the object will save its current state upon\n"
                                       "leaving the level and load it when re-entering the level."));

        connect(enabledProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);
        connect(persistentProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);
    }

    void BaseAsset::inspectLinks(Inspector* inspector)
    {
        auto linksGroup = inspector->addGroup("links", tr("Links"));
        linksGroup->setListSource(new LinkListSource(this, m_base->links));
    }

}
