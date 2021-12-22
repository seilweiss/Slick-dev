#include "Assets/JSPAsset.h"

#include "Core/Scene.h"

namespace Slick {

    namespace Assets {

        JSPAsset::JSPAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_jsp(asset),
            m_clumpRenderer(nullptr),
            m_jspAssets()
        {
            setEditor(&m_jsp);
        }

        void JSPAsset::inspect(Inspector* inspector)
        {
            Asset::inspect(inspector);

            auto jspGroup = inspector->addGroup("jsp", tr("JSP"));

            Q_UNUSED(jspGroup);
        }

        void JSPAsset::setup()
        {
            switch (m_jsp.type)
            {
            case HipHop::JSPAsset::JSPClump:
            {
                m_clumpRenderer = new ClumpRenderer(this);
                m_clumpRenderer->setClump(m_jsp.clump);
                break;
            }
            case HipHop::JSPAsset::JSPInfo:
            {
                uint32_t id = m_jsp.GetAsset().GetID();

                for (int i = 0; i < 3; i++)
                {
                    uint32_t jspID = HipHop::Util::Hash(std::to_string(i), id);
                    JSPAsset* jspAsset = qobject_cast<JSPAsset*>(scene()->asset(jspID));

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

        void JSPAsset::render(RenderContext* context)
        {
            context->glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);
            context->glEnable(GL_DEPTH_TEST);

            if (m_jsp.type == HipHop::JSPAsset::JSPClump)
            {
                m_clumpRenderer->render(context);
            }
            else if (m_jsp.type == HipHop::JSPAsset::JSPInfo)
            {
                int nodeIndex = 0;
                bool zwrite = true;
                bool cullback = true;

                for (JSPAsset* jspAsset : m_jspAssets)
                {
                    for (AtomicRenderer* atomRenderer : jspAsset->m_clumpRenderer->atomicRenderers())
                    {
                        Q_ASSERT(nodeIndex < m_jsp.jspNodeList.size());

                        const auto& node = m_jsp.jspNodeList[nodeIndex];

                        if (node.nodeFlags & HipHop::JSPAsset::NodeInfo::ToggleZWrite)
                        {
                            zwrite = !zwrite;
                        }

                        if (node.nodeFlags & HipHop::JSPAsset::NodeInfo::ToggleCullMode)
                        {
                            cullback = !cullback;
                        }

                        context->glDepthMask(zwrite ? GL_TRUE : GL_FALSE);
                        context->glCullFace(cullback ? GL_BACK : GL_FRONT);

                        atomRenderer->render(context);

                        nodeIndex++;
                    }
                }
            }

            context->glPopAttrib();
        }

    }

}
