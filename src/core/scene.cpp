#include "core/scene.h"

#include "assets/animlistasset.h"
#include "assets/boulderasset.h"
#include "assets/buttonasset.h"
#include "assets/cameraasset.h"
#include "assets/conditionalasset.h"
#include "assets/counterasset.h"
#include "assets/dispatcherasset.h"
#include "assets/envasset.h"
#include "assets/fogasset.h"
#include "assets/groupasset.h"
#include "assets/lightkitasset.h"
#include "assets/jspasset.h"
#include "assets/markerasset.h"
#include "assets/modelasset.h"
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
            m_animListManager(new Assets::AnimListManager(this)),
            m_boulderManager(new Assets::BoulderManager(this)),
            m_buttonManager(new Assets::ButtonManager(this)),
            m_cameraManager(new Assets::CameraManager(this)),
            m_condManager(new Assets::ConditionalManager(this)),
            m_counterManager(new Assets::CounterManager(this)),
            m_dpatManager(new Assets::DispatcherManager(this)),
            m_envManager(new Assets::EnvManager(this)),
            m_fogManager(new Assets::FogManager(this)),
            m_groupManager(new Assets::GroupManager(this)),
            m_jspManager(new Assets::JSPManager(this)),
            m_lightKitManager(new Assets::LightKitManager(this)),
            m_markerManager(new Assets::MarkerManager(this)),
            m_modelManager(new Assets::ModelManager(this)),
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
            m_assetManagers.append(m_dpatManager);
            m_assetManagers.append(m_envManager);
            m_assetManagers.append(m_fogManager);
            m_assetManagers.append(m_groupManager);
            m_assetManagers.append(m_jspManager);
            m_assetManagers.append(m_lightKitManager);
            m_assetManagers.append(m_markerManager);
            m_assetManagers.append(m_modelManager);
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

        Asset* Scene::asset(quint32 id) const
        {
            for (SceneFile* file : m_files)
            {
                Asset* asset = file->asset(id);

                if (asset)
                {
                    return asset;
                }
            }

            return nullptr;
        }

        Asset* Scene::asset(const QString& name) const
        {
            for (SceneFile* file : m_files)
            {
                Asset* asset = file->asset(name);

                if (asset)
                {
                    return asset;
                }
            }

            return nullptr;
        }

        Asset* Scene::asset(HipHop::AssetType type, int index) const
        {
            for (SceneFile* file : m_files)
            {
                Asset* asset = file->asset(type, index);

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
            m_simpManager->setup();

            m_playerManager->setup();
        }

        void Scene::update()
        {
            m_cameraManager->update();

            m_boulderManager->update();
            m_buttonManager->update();
            m_simpManager->update();

            m_playerManager->update();
        }

        void Scene::render()
        {
            m_context->camera()->begin();

            m_fogManager->apply();

            m_context->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            m_envManager->render();

            m_boulderManager->render();
            m_buttonManager->render();
            m_simpManager->render();

            m_playerManager->render();

            m_context->camera()->end();
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
                        Assets::TextureAsset* textureAsset = qobject_cast<Assets::TextureAsset*>(asset(QString("%1.RW3").arg(rwtex->GetTextureName()->string)));

                        if (textureAsset)
                        {
                            material->setTexture(textureAsset->texture());
                        }
                    }
                }
            }
        }

    }

}
