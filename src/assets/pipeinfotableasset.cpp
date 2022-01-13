#include "assets/pipeinfotableasset.h"

#include "core/scene.h"
#include "assets/modelasset.h"

#include <QCoreApplication>

namespace Slick {

    namespace Assets {

        namespace {

            class Unk0Proxy : public Inspector::Proxy<uint8_t>
            {
            public:
                Unk0Proxy(HipHop::PipeInfo* info) : Inspector::Proxy<uint8_t>(nullptr), m_info(info) {}

                virtual uint8_t data() const override { return m_info->Unk0; }
                virtual void setData(const uint8_t& data) const override { m_info->Unk0 = data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class ZWriteProxy : public Inspector::Proxy<uint8_t>
            {
            public:
                ZWriteProxy(HipHop::PipeInfo* info) : Inspector::Proxy<uint8_t>(nullptr), m_info(info) {}

                virtual uint8_t data() const override { return (uint8_t)m_info->ZWrite; }
                virtual void setData(const uint8_t& data) const override { m_info->ZWrite = (HipHop::PipeInfo::ZWriteMode)data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class CullProxy : public Inspector::Proxy<uint8_t>
            {
            public:
                CullProxy(HipHop::PipeInfo* info) : Inspector::Proxy<uint8_t>(nullptr), m_info(info) {}

                virtual uint8_t data() const override { return (uint8_t)m_info->Cull; }
                virtual void setData(const uint8_t& data) const override { m_info->Cull = (HipHop::PipeInfo::CullMode)data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class LightingProxy : public Inspector::Proxy<uint8_t>
            {
            public:
                LightingProxy(HipHop::PipeInfo* info) : Inspector::Proxy<uint8_t>(nullptr), m_info(info) {}

                virtual uint8_t data() const override { return (uint8_t)m_info->Lighting; }
                virtual void setData(const uint8_t& data) const override { m_info->Lighting = (HipHop::PipeInfo::LightingMode)data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class BlendSrcProxy : public Inspector::Proxy<uint8_t>
            {
            public:
                BlendSrcProxy(HipHop::PipeInfo* info) : Inspector::Proxy<uint8_t>(nullptr), m_info(info) {}

                virtual uint8_t data() const override { return (uint8_t)m_info->BlendSrc; }
                virtual void setData(const uint8_t& data) const override { m_info->BlendSrc = (HipHop::PipeInfo::BlendFunction)data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class BlendDstProxy : public Inspector::Proxy<uint8_t>
            {
            public:
                BlendDstProxy(HipHop::PipeInfo* info) : Inspector::Proxy<uint8_t>(nullptr), m_info(info) {}

                virtual uint8_t data() const override { return (uint8_t)m_info->BlendDst; }
                virtual void setData(const uint8_t& data) const override { m_info->BlendDst = (HipHop::PipeInfo::BlendFunction)data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class EnableFogProxy : public Inspector::Proxy<bool>
            {
            public:
                EnableFogProxy(HipHop::PipeInfo* info) : Inspector::Proxy<bool>(nullptr), m_info(info) {}

                virtual bool data() const override { return !m_info->DisableFog; }
                virtual void setData(const bool& data) const override { m_info->DisableFog = !data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class Unk1Proxy : public Inspector::Proxy<uint8_t>
            {
            public:
                Unk1Proxy(HipHop::PipeInfo* info) : Inspector::Proxy<uint8_t>(nullptr), m_info(info) {}

                virtual uint8_t data() const override { return m_info->Unk1; }
                virtual void setData(const uint8_t& data) const override { m_info->Unk1 = data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class AlphaLayerProxy : public Inspector::Proxy<uint8_t>
            {
            public:
                AlphaLayerProxy(HipHop::PipeInfo* info) : Inspector::Proxy<uint8_t>(nullptr), m_info(info) {}

                virtual uint8_t data() const override { return m_info->AlphaLayer; }
                virtual void setData(const uint8_t& data) const override { m_info->AlphaLayer = data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class AlphaCompareProxy : public Inspector::Proxy<uint8_t>
            {
            public:
                AlphaCompareProxy(HipHop::PipeInfo* info) : Inspector::Proxy<uint8_t>(nullptr), m_info(info) {}

                virtual uint8_t data() const override { return m_info->AlphaCompare; }
                virtual void setData(const uint8_t& data) const override { m_info->AlphaCompare = data; }

            private:
                HipHop::PipeInfo* m_info;
            };

            class PipeInfoListSource : public Inspector::ListSource<std::vector<HipHop::PipeInfo>>
            {
                Q_DECLARE_TR_FUNCTIONS(LightListSource)

            public:
                PipeInfoListSource(PipeInfoTableAsset* asset, std::vector<HipHop::PipeInfo>& list) : Inspector::ListSource<std::vector<HipHop::PipeInfo>>(list), m_asset(asset) {}

                virtual void createGroupItem(Inspector::Group* group, int index) override
                {
                    static const QStringList zwriteItems = {
                        tr("Enabled"),
                        tr("Disabled"),
                        tr("Depth Pre-Pass")
                    };

                    static const QStringList cullItems = {
                        tr("Auto"),
                        tr("Disabled"),
                        tr("Back"),
                        tr("Front then Back")
                    };

                    static const QStringList lightingItems = {
                        tr("Enabled"),
                        tr("Disabled"),
                        tr("Enabled + Vertex Colors")
                    };

                    static const QStringList blendItems = {
                        tr("N/A"),
                        tr("Zero"),
                        tr("One"),
                        tr("Src Color"),
                        tr("Inv Src Color"),
                        tr("Src Alpha"),
                        tr("Inv Src Alpha"),
                        tr("Dst Alpha"),
                        tr("Inv Dst Alpha"),
                        tr("Dst Color"),
                        tr("Inv Dst Color"),
                        tr("Src Alpha Sat")
                    };

                    auto* info = &list()[index];
                    auto infoGroup = group->addGroup();

                    infoGroup->setExpanded(false);

                    Core::Asset* modelAsset = m_asset->scene()->assetById(info->ModelHashID);

                    if (modelAsset)
                    {
                        infoGroup->setDisplayName(modelAsset->name());
                    }

                    auto modelProp = infoGroup->addAssetInput("model", tr("Model"), &info->ModelHashID, m_asset->scene());
                    auto subObjectBitsProp = infoGroup->addNumberInput("subObjectBits", tr("Sub Object Bits"), &info->SubObjectBits);
                    //auto pipeFlagsProp = infoGroup->addNumberInput("pipeFlags", tr("Pipe Flags"), &info->PipeFlags);
                    //auto unk0Prop = infoGroup->addNumberInput("unk0", tr("Unknown 0"), new Unk0Proxy(info));
                    auto zwriteProp = infoGroup->addComboBox("zwriteMode", tr("Z-Write Mode"), new ZWriteProxy(info), zwriteItems);
                    auto cullProp = infoGroup->addComboBox("cullMode", tr("Cull Mode"), new CullProxy(info), cullItems);
                    auto lightingProp = infoGroup->addComboBox("lightingMode", tr("Lighting Mode"), new LightingProxy(info), lightingItems);
                    auto blendSrcProp = infoGroup->addComboBox("blendSrc", tr("Blend Src"), new BlendSrcProxy(info), blendItems);
                    auto blendDstProp = infoGroup->addComboBox("blendDst", tr("Blend Dst"), new BlendDstProxy(info), blendItems);
                    auto enableFogProp = infoGroup->addCheckBox("fog", tr("Fog"), new EnableFogProxy(info));
                    //auto unk1Prop = infoGroup->addNumberInput("unk1", tr("Unknown 1"), new Unk1Proxy(info));
                    auto alphaLayerProp = infoGroup->addNumberInput("alphaLayer", tr("Alpha Layer"), new AlphaLayerProxy(info));
                    auto alphaCompareProp = infoGroup->addNumberInput("alphaThreshold", tr("Alpha Threshold"), new AlphaCompareProxy(info));

                    QObject::connect(modelProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    QObject::connect(subObjectBitsProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(pipeFlagsProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);

                    //QObject::connect(unk0Prop, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(unk0Prop, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);

                    QObject::connect(zwriteProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(zwriteProp, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);

                    QObject::connect(cullProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(cullProp, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);

                    QObject::connect(lightingProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(lightingProp, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);

                    QObject::connect(blendSrcProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(blendSrcProp, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);

                    QObject::connect(blendDstProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(blendDstProp, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);

                    QObject::connect(enableFogProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(enableFogProp, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);

                    //QObject::connect(unk1Prop, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(unk1Prop, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);

                    QObject::connect(alphaLayerProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(alphaLayerProp, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);

                    QObject::connect(alphaCompareProp, &Inspector::Property::dataChanged, m_asset, &PipeInfoTableAsset::makeDirty);
                    //QObject::connect(alphaCompareProp, &Inspector::Property::dataChanged, pipeFlagsProp, &Inspector::Property::requestRefresh);
                }

            private:
                PipeInfoTableAsset* m_asset;
            };

        }

        PipeInfoTableAsset::PipeInfoTableAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_pipt(asset)
        {
            setEditor(&m_pipt);
        }

        void PipeInfoTableAsset::inspect(Inspector::Root* root)
        {
            auto piptGroup = root->addGroup("pipeInfoTable", tr("Pipe Info Table"));

            piptGroup->setListSource(new PipeInfoListSource(this, m_pipt.pipeInfo));

            connect(piptGroup, &Inspector::Group::listItemAdded, this, &PipeInfoTableAsset::makeDirty);
            connect(piptGroup, &Inspector::Group::listItemRemoved, this, &PipeInfoTableAsset::makeDirty);
        }

    }

}
