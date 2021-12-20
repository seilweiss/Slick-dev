#include "Core/BaseAsset.h"

#include "Core/BaseAssetPrivate.h"
#include "Core/Scene.h"
#include "Core/Util.h"

namespace Slick {

    BaseAsset::BaseAsset(HipHop::Asset asset, SceneFile* sceneFile) :
        Asset(asset, sceneFile),
        m_baseDefault(asset)
    {
        setEditor(&m_baseDefault);
    }

    void BaseAsset::inspect(Inspector* inspector)
    {
        Asset::inspect(inspector);

        auto flagsGroup = inspector->addGroup("flags");
        auto enabledProp = flagsGroup->addCheckBox("enabled", &m_base->baseFlags, HipHop::BaseAsset::Enabled);
        auto persistentProp = flagsGroup->addCheckBox("persistent", &m_base->baseFlags, HipHop::BaseAsset::Persistent);
        //auto validProp = flagsGroup->addCheckBox("valid", &m_base->baseFlags, HipHop::BaseAsset::Valid);

        connect(enabledProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);
        connect(persistentProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);
        //connect(validProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);
    }

    void BaseAsset::inspectLinks(Inspector* inspector)
    {
        auto linksGroup = inspector->addGroup("links");
        linksGroup->setDisplayName(QString("Links (%1)").arg(m_base->links.size()));

        HipHop::Game game = hipHopAsset().GetFile()->GetGame();
        QStringList eventNames = Util::eventNames(game);

        for (int i = 0; i < m_base->links.size(); i++)
        {
            HipHop::LinkAsset& link = m_base->links[i];
            auto linkGroup = linksGroup->addGroup(new LinkGroup(link, QString::number(i)));

            linkGroup->setExpanded(false);

            auto srcAssetProp = linkGroup->addAssetInput("srcAsset", &link.chkAssetID, scene());
            auto srcEventProp = linkGroup->addComboBox("srcEvent", &link.srcEvent, eventNames);
            auto dstEventProp = linkGroup->addComboBox("dstEvent", &link.dstEvent, eventNames);
            auto dstAssetProp = linkGroup->addAssetInput("dstAsset", &link.dstAssetID, scene());
            auto paramAssetProp = linkGroup->addAssetInput("paramAsset", &link.paramWidgetAssetID, scene());

            auto updateDisplayName = [=]
            {
                QString srcEventName = QString::fromStdString(HipHop::EventToString(m_base->links[i].srcEvent, game));
                QString dstEventName = QString::fromStdString(HipHop::EventToString(m_base->links[i].dstEvent, game));
                Asset* dstAsset = scene()->asset(m_base->links[i].dstAssetID);
                QString dstAssetName = dstAsset ? dstAsset->name() : Util::hexToString(m_base->links[i].dstAssetID);

                linkGroup->setDisplayName(QString("%1 => %2 => %3").arg(srcEventName, dstEventName, dstAssetName));
            };

            connect(srcAssetProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);

            connect(srcEventProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);
            connect(srcEventProp, &InspectorProperty::dataChanged, updateDisplayName);

            connect(dstEventProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);
            connect(dstEventProp, &InspectorProperty::dataChanged, updateDisplayName);

            connect(dstAssetProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);
            connect(dstAssetProp, &InspectorProperty::dataChanged, updateDisplayName);

            connect(paramAssetProp, &InspectorProperty::dataChanged, this, &BaseAsset::makeDirty);

            updateDisplayName();
        }
    }

}
