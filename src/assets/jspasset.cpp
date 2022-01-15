#include "assets/jspasset.h"

#include "core/scene.h"

namespace Slick {

    namespace Assets {

        JSPAsset::JSPAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_jsp(asset),
            m_clump(scene()->renderContext()),
            m_jspAssets()
        {
            setSerializer(&m_jsp);
        }

        void JSPAsset::setup()
        {
            switch (m_jsp.type)
            {
            case HipHop::JSPAsset::JSPClump:
            {
                m_clump.setData(m_jsp.clump);

                scene()->setupClump(&m_clump);

                break;
            }
            case HipHop::JSPAsset::JSPInfo:
            {
                uint32_t id = m_jsp.GetAsset().GetID();

                for (int i = 0; i < 3; i++)
                {
                    uint32_t jspID = HipHop::Util::Hash(std::to_string(i), id);
                    JSPAsset* jspAsset = qobject_cast<JSPAsset*>(scene()->assetById(jspID));

                    if (jspAsset && jspAsset->m_jsp.type == HipHop::JSPAsset::JSPClump)
                    {
                        m_jspAssets.append(jspAsset);
                    }
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }

        void JSPAsset::render()
        {
            Render::Context* context = scene()->renderContext();

            context->glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_POLYGON_BIT);

            context->glEnable(GL_CULL_FACE);
            context->glCullFace(GL_BACK);
            context->glDepthMask(GL_TRUE);
            context->glEnable(GL_DEPTH_TEST);

            if (m_jsp.type == HipHop::JSPAsset::JSPClump)
            {
                m_clump.render();
            }
            else if (m_jsp.type == HipHop::JSPAsset::JSPInfo)
            {
                int nodeIndex = 0;
                bool cull = true;
                bool zwrite = true;

                for (auto jspIt = m_jspAssets.rbegin(); jspIt != m_jspAssets.rend(); jspIt++)
                {
                    JSPAsset* jspAsset = *jspIt;
                    auto& atomics = jspAsset->m_clump.atomics();

                    for (auto atomicIt = atomics.rbegin(); atomicIt != atomics.rend(); atomicIt++)
                    {
                        Render::Atomic& atomic = *atomicIt;

                        Q_ASSERT(nodeIndex < m_jsp.jspNodeList.size());

                        const auto& node = m_jsp.jspNodeList[nodeIndex];

                        if (cull)
                        {
                            if (node.nodeFlags & HipHop::JSPAsset::NodeInfo::ToggleCullMode)
                            {
                                cull = false;
                                context->glDisable(GL_CULL_FACE);
                            }
                        }
                        else
                        {
                            if (!(node.nodeFlags & HipHop::JSPAsset::NodeInfo::ToggleCullMode))
                            {
                                cull = true;
                                context->glEnable(GL_CULL_FACE);
                                context->glCullFace(GL_BACK);
                            }
                        }

                        if (zwrite)
                        {
                            if (node.nodeFlags & HipHop::JSPAsset::NodeInfo::ToggleZWrite)
                            {
                                zwrite = false;
                                context->glDepthMask(GL_FALSE);
                            }
                        }
                        else
                        {
                            if (!(node.nodeFlags & HipHop::JSPAsset::NodeInfo::ToggleZWrite))
                            {
                                zwrite = true;
                                context->glDepthMask(GL_TRUE);
                            }
                        }

                        if (!atomic.cull())
                        {
                            atomic.render();
                        }

                        nodeIndex++;
                    }
                }
            }

            context->glPopAttrib();
        }

        void JSPAsset::inspect(Inspector::Root* root)
        {
            Core::Asset::inspect(root);

            auto jspGroup = root->addGroup("jsp", tr("JSP"));

            Q_UNUSED(jspGroup);
        }

        void JSPManager::setup()
        {
            for (auto asset : assets())
            {
                ((JSPAsset*)asset)->setup();
            }
        }

    }

}
