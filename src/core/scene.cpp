#include "core/scene.h"

#include "core/modelbucketmanager.h"
#include "core/skydomemanager.h"
#include "core/scrfxmanager.h"

#include "assets/animlistasset.h"
#include "assets/boulderasset.h"
#include "assets/buttonasset.h"
#include "assets/cameraasset.h"
#include "assets/conditionalasset.h"
#include "assets/counterasset.h"
#include "assets/destructobjasset.h"
#include "assets/dispatcherasset.h"
#include "assets/envasset.h"
#include "assets/fogasset.h"
#include "assets/groupasset.h"
#include "assets/lightkitasset.h"
#include "assets/jspasset.h"
#include "assets/markerasset.h"
#include "assets/modelasset.h"
#include "assets/pipeinfotableasset.h"
#include "assets/platformasset.h"
#include "assets/playerasset.h"
#include "assets/simpleobjectasset.h"
#include "assets/textasset.h"
#include "assets/textureasset.h"
#include "assets/timerasset.h"

#include "render/context.h"
#include "render/camera.h"
#include "render/clump.h"

#include "rws_core.h"
#include "rws_world.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Slick {

    namespace Core {

        Scene::Scene(QObject* parent) :
            QObject(parent),
            m_context(new Render::Context(/*this*/)),
            m_files(),
            m_game(HipHop::Game::Unknown),
            m_platform(HipHop::Platform::Unknown),
            m_language(HipHop::Language::Unknown),
            m_region(HipHop::Region::Unknown),
            m_modelBucketManager(new ModelBucketManager(this)),
            m_skyDomeManager(new SkyDomeManager(this)),
            m_scrFxManager(new ScrFxManager(this)),
            m_animListManager(new Assets::AnimListManager(this)),
            m_boulderManager(new Assets::BoulderManager(this)),
            m_buttonManager(new Assets::ButtonManager(this)),
            m_cameraManager(new Assets::CameraManager(this)),
            m_condManager(new Assets::ConditionalManager(this)),
            m_counterManager(new Assets::CounterManager(this)),
            m_destructObjManager(new Assets::DestructObjManager(this)),
            m_dpatManager(new Assets::DispatcherManager(this)),
            m_envManager(new Assets::EnvManager(this)),
            m_fogManager(new Assets::FogManager(this)),
            m_groupManager(new Assets::GroupManager(this)),
            m_jspManager(new Assets::JSPManager(this)),
            m_lightKitManager(new Assets::LightKitManager(this)),
            m_markerManager(new Assets::MarkerManager(this)),
            m_modelManager(new Assets::ModelManager(this)),
            m_pipeInfoTableManager(new Assets::PipeInfoTableManager(this)),
            m_platformManager(new Assets::PlatformManager(this)),
            m_playerManager(new Assets::PlayerManager(this)),
            m_simpManager(new Assets::SimpleObjectManager(this)),
            m_textManager(new Assets::TextManager(this)),
            m_textureManager(new Assets::TextureManager(this)),
            m_timerManager(new Assets::TimerManager(this))
        {
            m_assetManagers.append(m_animListManager);
            m_assetManagers.append(m_boulderManager);
            m_assetManagers.append(m_buttonManager);
            m_assetManagers.append(m_cameraManager);
            m_assetManagers.append(m_condManager);
            m_assetManagers.append(m_counterManager);
            m_assetManagers.append(m_destructObjManager);
            m_assetManagers.append(m_dpatManager);
            m_assetManagers.append(m_envManager);
            m_assetManagers.append(m_fogManager);
            m_assetManagers.append(m_groupManager);
            m_assetManagers.append(m_jspManager);
            m_assetManagers.append(m_lightKitManager);
            m_assetManagers.append(m_markerManager);
            m_assetManagers.append(m_modelManager);
            m_assetManagers.append(m_pipeInfoTableManager);
            m_assetManagers.append(m_platformManager);
            m_assetManagers.append(m_playerManager);
            m_assetManagers.append(m_simpManager);
            m_assetManagers.append(m_textManager);
            m_assetManagers.append(m_textureManager);
            m_assetManagers.append(m_timerManager);
        }

        void Scene::addFile(SceneFile* file)
        {
            file->setParent(this);

            m_files.append(file);
        }

        Asset* Scene::assetById(quint32 id) const
        {
            if (id == 0)
            {
                return nullptr;
            }

            for (SceneFile* file : m_files)
            {
                Asset* asset = file->assetById(id);

                if (asset)
                {
                    return asset;
                }
            }

            return nullptr;
        }

        Asset* Scene::assetByName(const QString& name) const
        {
            for (SceneFile* file : m_files)
            {
                Asset* asset = file->assetByName(name);

                if (asset)
                {
                    return asset;
                }
            }

            return nullptr;
        }

        Asset* Scene::assetByType(HipHop::AssetType type, int index) const
        {
            for (SceneFile* file : m_files)
            {
                Asset* asset = file->assetByType(type, index);

                if (asset)
                {
                    return asset;
                }

                index -= file->assetCount(type);
            }

            return nullptr;
        }

        QList<Asset*> Scene::assets() const
        {
            QList<Asset*> assets;

            for (SceneFile* file : m_files)
            {
                assets.append(file->assets());
            }

            return assets;
        }

        QList<Asset*> Scene::assets(HipHop::AssetType type) const
        {
            QList<Asset*> assets;

            for (SceneFile* file : m_files)
            {
                assets.append(file->assets(type));
            }

            return assets;
        }

        int Scene::assetCount() const
        {
            int count = 0;

            for (SceneFile* file : m_files)
            {
                count += file->assetCount();
            }

            return count;
        }

        int Scene::assetCount(HipHop::AssetType type) const
        {
            int count = 0;

            for (SceneFile* file : m_files)
            {
                count += file->assetCount(type);
            }

            return count;
        }

        bool Scene::load()
        {
            if (m_game == HipHop::Game::Unknown ||
                m_platform == HipHop::Platform::Unknown ||
                m_language == HipHop::Language::Unknown ||
                m_region == HipHop::Region::Unknown)
            {
                return false;
            }

            bool success = true;

            for (SceneFile* file : m_files)
            {
                file->setGame(m_game);
                file->setPlatform(m_platform);
                file->setLanguage(m_language);
                file->setRegion(m_region);

                if (!file->load())
                {
                    success = false;
                    break;
                }

                for (HipHop::Asset hipAsset : file->hipHopFile().GetAssets())
                {
                    Asset* asset = nullptr;

                    for (AssetManager* manager : m_assetManagers)
                    {
                        if (manager->supports(hipAsset))
                        {
                            asset = manager->createAsset(hipAsset, file);

                            Q_ASSERT(asset);

                            manager->addAsset(asset);

                            break;
                        }
                    }

                    if (!asset)
                    {
                        asset = new Asset(hipAsset, file);
                    }

                    asset->load();

                    file->addAsset(asset);
                }
            }

            return success;
        }

        void Scene::setup()
        {
            m_textureManager->setup();
            m_modelManager->setup();
            m_jspManager->setup();

            m_envManager->setup();
            m_fogManager->setup();
            m_cameraManager->setup();
            m_lightKitManager->setup();

            m_boulderManager->setup();
            m_buttonManager->setup();
            m_destructObjManager->setup();
            m_platformManager->setup();
            m_simpManager->setup();

            m_playerManager->setup();

            m_skyDomeManager->setup();
        }

        void Scene::update()
        {
            m_boulderManager->update();
            m_buttonManager->update();
            m_destructObjManager->update();
            m_platformManager->update();
            m_simpManager->update();

            m_playerManager->update();
        }

        void Scene::render()
        {
            m_context->beginFrame();
            m_context->camera()->begin();
            m_context->setTextureFilterHackEnabled(true);

            m_fogManager->apply();

            m_context->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            m_lightKitManager->bind(nullptr);

            setRenderState(RenderState_SkyBack);
            m_skyDomeManager->render();

            setRenderState(RenderState_Environment);
            m_envManager->render();

            setRenderState(RenderState_OpaqueModels);

            m_modelBucketManager->begin();

            m_lightKitManager->bind((Assets::LightKitAsset*)assetByType(HipHop::AssetType::LKIT));

            m_boulderManager->render();
            m_buttonManager->render();
            m_destructObjManager->render();
            m_platformManager->render();
            m_simpManager->render();
            m_playerManager->render();

            m_modelBucketManager->renderOpaque();

            m_lightKitManager->bind(nullptr);

            setRenderState(RenderState_AlphaModels);

            m_modelBucketManager->renderAlpha();

            m_lightKitManager->bind(nullptr);

            m_scrFxManager->render();

            m_context->setTextureFilterHackEnabled(false);
            m_context->camera()->end();
            m_context->endFrame();
        }

        void Scene::setupClump(Render::Clump* clump)
        {
            for (Render::Atomic& atomic : clump->atomics())
            {
                for (int i = 0; i < atomic.geometry()->materialCount(); i++)
                {
                    Render::Material* material = atomic.geometry()->material(i);
                    Rws::Texture* rwtex = material->data()->GetTexture();

                    if (rwtex)
                    {
                        Assets::TextureAsset* textureAsset = qobject_cast<Assets::TextureAsset*>(assetByName(QString("%1.RW3").arg(rwtex->GetTextureName()->string)));

                        if (textureAsset)
                        {
                            material->setTexture(textureAsset->texture());
                        }
                    }
                }
            }
        }

        // zRenderState
        void Scene::setRenderState(RenderState state)
        {
            m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            m_fogManager->apply();

            m_context->glDisable(GL_CULL_FACE);
            m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            m_context->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            m_context->glEnable(GL_BLEND);
            m_context->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            m_context->glShadeModel(GL_SMOOTH);
            m_context->glDepthMask(GL_TRUE);
            m_context->glEnable(GL_DEPTH_TEST);

            switch (state)
            {
            case RenderState_Particles:
                m_context->glDepthMask(GL_FALSE);
                m_context->glDisable(GL_FOG);
                m_context->glShadeModel(GL_FLAT);
                break;
            case RenderState_OpaqueModels:
                //m_context->glDisable(GL_BLEND);
                break;
            case RenderState_Environment:
                //m_context->glDisable(GL_BLEND);
                m_context->glBlendFunc(GL_ONE, GL_ZERO);
                m_context->glCullFace(GL_BACK);
                break;
            case RenderState_Lightning:
                m_context->glDepthMask(GL_FALSE);
                m_context->glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                break;
            case RenderState_Streak:
                m_context->glDepthMask(GL_FALSE);
                break;
            case RenderState_NPCVisual:
                m_context->glDepthMask(GL_FALSE);
                break;
            case RenderState_Glare:
                m_context->glDepthMask(GL_FALSE);
                m_context->glDisable(GL_DEPTH_TEST);
                m_context->glDisable(GL_FOG);
                m_context->glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                break;
            case RenderState_Font:
                m_context->glDepthMask(GL_FALSE);
                m_context->glDisable(GL_DEPTH_TEST);
                m_context->glDisable(GL_FOG);
                //m_context->glDisable(GL_BLEND);
                m_context->glBlendFunc(GL_ONE, GL_ZERO);
                break;
            case RenderState_HUD:
                m_context->glDisable(GL_FOG);
                break;
            case RenderState_Bubble:
                m_context->glDisable(GL_FOG);
                //m_context->glDisable(GL_BLEND);
                m_context->glCullFace(GL_BACK);
                break;
            case RenderState_SkyBack:
                m_context->glDepthMask(GL_FALSE);
                m_context->glDisable(GL_DEPTH_TEST);
                m_context->glDisable(GL_FOG);
                break;
            case RenderState_Fill:
                m_context->glDepthMask(GL_FALSE);
                m_context->glDisable(GL_DEPTH_TEST);
                m_context->glDisable(GL_FOG);
                //m_context->glDisable(GL_BLEND);
                m_context->glBlendFunc(GL_ONE, GL_ZERO);
                m_context->glShadeModel(GL_FLAT);
                break;
            case RenderState_OOBFade:
                m_context->glDisable(GL_DEPTH_TEST);
                m_context->glDisable(GL_FOG);
                m_context->glShadeModel(GL_FLAT);
                break;
            case RenderState_OOBPlayerZ:
                //m_context->glDisable(GL_BLEND);
                m_context->glShadeModel(GL_FLAT);
                m_context->glBlendFunc(GL_ONE, GL_ZERO);
                break;
            case RenderState_OOBPlayerAlpha:
                //m_context->glDisable(GL_BLEND);
                m_context->glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                break;
            case RenderState_OOBHand:
                m_context->glDepthMask(GL_FALSE);
                m_context->glDisable(GL_DEPTH_TEST);
                m_context->glDisable(GL_FOG);
                //m_context->glDisable(GL_BLEND);
                m_context->glBlendFunc(GL_ONE, GL_ZERO);
                break;
            case RenderState_Newsfish:
                m_context->glDisable(GL_DEPTH_TEST);
                m_context->glDisable(GL_FOG);
                //m_context->glDisable(GL_BLEND);
                m_context->glBlendFunc(GL_ONE, GL_ZERO);
                break;
            case RenderState_CruiseHUD:
                m_context->glDepthMask(GL_FALSE);
                m_context->glDisable(GL_DEPTH_TEST);
                m_context->glDisable(GL_FOG);
                break;
            case RenderState_DiscoFloorGlow:
                m_context->glDepthMask(GL_FALSE);
                m_context->glDisable(GL_FOG);
                m_context->glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                break;
            default:
                break;
            }
        }

    }

}
