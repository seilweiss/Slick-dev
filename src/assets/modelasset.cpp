#include "assets/modelasset.h"

#include "assets/pipeinfotableasset.h"

#include "core/scene.h"

#include <memory>

namespace Slick {

    namespace Assets {

        ModelAsset::ModelAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_model(asset),
            m_clump(Render::Clump(scene()->renderContext())),
            m_instances()
        {
            setEditor(&m_model);
        }

        ModelAsset::~ModelAsset()
        {
            for (Core::ModelInstance* minst : m_instances)
            {
                free(minst);
            }
        }

        Core::ModelInstance* ModelAsset::createInstance()
        {
            auto& atomics = m_clump.atomics();
            Core::ModelInstance* minst = (Core::ModelInstance*)malloc(sizeof(Core::ModelInstance) * atomics.size());

            for (int i = 0; i < atomics.size(); i++)
            {
                new (&minst[i]) Core::ModelInstance(scene());

                minst[i].setData(&atomics[atomics.size() - 1 - i]);

                if (i < atomics.size() - 1)
                {
                    minst[i].setNext(&minst[i + 1]);
                }
            }

            uint32_t remainSubObjBits = (1 << atomics.size()) - 1;

            if (remainSubObjBits)
            {
                auto pipts = scene()->assets<Assets::PipeInfoTableAsset>(HipHop::AssetType::PIPT);

                for (auto pipt : pipts)
                {
                    for (HipHop::PipeInfo& info : pipt->data()->pipeInfo)
                    {
                        if (info.ModelHashID == id())
                        {
                            uint32_t currSubObjBits = remainSubObjBits & info.SubObjectBits;

                            if (currSubObjBits)
                            {
                                for (int i = 0; i < atomics.size(); i++)
                                {
                                    if (currSubObjBits & (1 << i))
                                    {
                                        minst[i].setPipeInfo(&info);
                                    }
                                }
                            }

                            remainSubObjBits &= ~currSubObjBits;

                            if (!remainSubObjBits)
                            {
                                break;
                            }
                        }
                    }

                    if (!remainSubObjBits)
                    {
                        break;
                    }
                }
            }

            m_instances.append(minst);

            return minst;
        }

        void ModelAsset::setup()
        {
            m_clump.setData(m_model.GetClump());

            scene()->setupClump(&m_clump);
        }

        void ModelAsset::inspect(Inspector::Root* root)
        {
            Core::Asset::inspect(root);

            root->addGroup("model", tr("Model"));
        }

        void ModelManager::setup()
        {
            for (auto asset : assets())
            {
                ((ModelAsset*)asset)->setup();
            }
        }

    }

}
