#include "core/skydomemanager.h"

#include "core/scene.h"

#include <glm/glm.hpp>

namespace Slick {

    namespace Core {

        SkyDomeManager::SkyDomeManager(Scene* scene) :
            QObject(scene),
            m_scene(scene)
        {
        }

        void SkyDomeManager::setup()
        {
            m_info.clear();

            for (Asset* asset : m_scene->assets())
            {
                Assets::BaseAsset* base = qobject_cast<Assets::BaseAsset*>(asset);

                if (base)
                {
                    for (const HipHop::LinkAsset& link : base->editor()->links)
                    {
                        if (link.dstEvent == HipHop::Event::SetSkyDome)
                        {
                            Assets::EntAsset* ent = qobject_cast<Assets::EntAsset*>(m_scene->assetById(link.dstAssetID));

                            if (ent)
                            {
                                bool alreadyAdded = false;

                                for (const auto& info : m_info)
                                {
                                    if (info.ent == ent)
                                    {
                                        alreadyAdded = true;
                                        break;
                                    }
                                }

                                if (!alreadyAdded)
                                {
                                    SkyDomeInfo info;
                                    info.ent = ent;
                                    info.sortorder = (int)link.param[0].f;
                                    info.lockY = (bool)link.param[1].f;

                                    ent->setRenderEnabled(false);

                                    int index = -1;

                                    for (int i = 0; i < m_info.size(); i++)
                                    {
                                        if (info.sortorder < m_info[i].sortorder)
                                        {
                                            index = i;
                                            break;
                                        }
                                    }

                                    if (index == -1)
                                    {
                                        m_info.append(info);
                                    }
                                    else
                                    {
                                        m_info.insert(index, info);
                                    }

                                    qDebug().noquote() << "Added skydome " << ent->name();
                                }
                            }
                        }
                    }
                }
            }
        }

        void SkyDomeManager::render()
        {
            for (const auto& info : m_info)
            {
                Render::Clump* clump = info.ent->clump();

                if (clump)
                {
                    glm::mat mat = clump->frame()->matrix();
                    glm::mat cammat = m_scene->renderContext()->camera()->viewMatrix();

                    mat[3][0] = cammat[3][0];
                    mat[3][2] = cammat[3][2];

                    if (info.lockY)
                    {
                        mat[3][1] = cammat[3][1];
                    }

                    clump->frame()->setMatrix(mat);
                    clump->render();
                }
            }
        }

    }

}
