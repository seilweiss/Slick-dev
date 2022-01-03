#pragma once

#include "core/scenefile.h"
#include "core/assetmanager.h"
#include "render/context.h"

#include <QObject>

namespace Slick {

    namespace Assets {

        class AnimListManager;
        class BoulderManager;
        class ButtonManager;
        class CameraManager;
        class ConditionalManager;
        class CounterManager;
        class DispatcherManager;
        class EnvManager;
        class FogManager;
        class GroupManager;
        class JSPManager;
        class LightKitManager;
        class MarkerManager;
        class ModelManager;
        class PlayerManager;
        class SimpleObjectManager;
        class TextManager;
        class TextureManager;
        class TimerManager;

    }

    namespace Render { class Clump; }

    // _SDRenderState
    enum RenderState
    {
        RenderState_Unknown,
        RenderState_Default,
        RenderState_OpaqueModels,
        RenderState_AlphaModels,
        RenderState_Bubble,
        RenderState_Projectile,
        RenderState_Font,
        RenderState_HUD,
        RenderState_Particles,
        RenderState_Lightning,
        RenderState_Streak,
        RenderState_SkyBack,
        RenderState_Environment,
        RenderState_Fill,
        RenderState_NPCVisual,
        RenderState_OOBFade,
        RenderState_OOBPlayerZ,
        RenderState_OOBPlayerAlpha,
        RenderState_OOBHand,
        RenderState_Glare,
        RenderState_Newsfish,
        RenderState_CruiseHUD,
        RenderState_DiscoFloorGlow
    };

    namespace Core {

        class SkyDomeManager;
        class ScrFxManager;

        class Scene : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(Render::Context* renderContext READ renderContext)
            Q_PROPERTY(HipHop::Game game READ game WRITE setGame)
            Q_PROPERTY(HipHop::Platform platform READ platform WRITE setPlatform)
            Q_PROPERTY(HipHop::Language language READ language WRITE setLanguage)
            Q_PROPERTY(HipHop::Region region READ region WRITE setRegion)

        public:
            Scene(QObject* parent = nullptr);

            Render::Context* renderContext() const { return m_context; }

            HipHop::Game game() const { return m_game; }
            void setGame(HipHop::Game game) { m_game = game; }

            HipHop::Platform platform() const { return m_platform; }
            void setPlatform(HipHop::Platform platform) { m_platform = platform; }

            HipHop::Language language() const { return m_language; }
            void setLanguage(HipHop::Language language) { m_language = language; }

            HipHop::Region region() const { return m_region; }
            void setRegion(HipHop::Region region) { m_region = region; }

            int fileCount() const { return m_files.size(); }
            SceneFile* file(int index) { return m_files[index]; }
            void addFile(SceneFile* file);

            Asset* assetById(quint32 id) const;
            Asset* assetByName(const QString& name) const;
            Asset* assetByType(HipHop::AssetType type, int index = 0) const;
            QList<Asset*> assets() const;
            QList<Asset*> assets(HipHop::AssetType type) const;

            template <class T> QList<T*> assets(HipHop::AssetType type) const
            {
                QList<T*> result;
                QList<Asset*> a = assets(type);

                for (Asset* asset : a)
                {
                    result.append(qobject_cast<T*>(asset));
                }

                return result;
            }

            int assetCount() const;
            int assetCount(HipHop::AssetType type) const;

            bool load();
            void setup();

            void update();
            void render();

            void setupClump(Render::Clump* clump);

            void setRenderState(RenderState state);

            SkyDomeManager* skyDomeManager() const { return m_skyDomeManager; }
            ScrFxManager* scrFxManager() const { return m_scrFxManager; }

            Assets::AnimListManager* animListManager() const { return m_animListManager; }
            Assets::BoulderManager* boulderManager() const { return m_boulderManager; }
            Assets::ButtonManager* buttonManager() const { return m_buttonManager; }
            Assets::CameraManager* cameraManager() const { return m_cameraManager; }
            Assets::ConditionalManager* conditionalManager() const { return m_condManager; }
            Assets::CounterManager* counterManager() const { return m_counterManager; }
            Assets::DispatcherManager* dispatcherManager() const { return m_dpatManager; }
            Assets::EnvManager* envManager() const { return m_envManager; }
            Assets::FogManager* fogManager() const { return m_fogManager; }
            Assets::GroupManager* groupManager() const { return m_groupManager; }
            Assets::JSPManager* jspManager() const { return m_jspManager; }
            Assets::LightKitManager* lightKitManager() const { return m_lightKitManager; }
            Assets::MarkerManager* markerManager() const { return m_markerManager; }
            Assets::ModelManager* modelManager() const { return m_modelManager; }
            Assets::PlayerManager* playerManager() const { return m_playerManager; }
            Assets::SimpleObjectManager* simpleObjectManager() const { return m_simpManager; }
            Assets::TextManager* textManager() const { return m_textManager; }
            Assets::TextureManager* textureManager() const { return m_textureManager; }
            Assets::TimerManager* timerManager() const { return m_timerManager; }

        private:
            Render::Context* m_context;
            QList<SceneFile*> m_files;
            HipHop::Game m_game;
            HipHop::Platform m_platform;
            HipHop::Language m_language;
            HipHop::Region m_region;

            SkyDomeManager* m_skyDomeManager;
            ScrFxManager* m_scrFxManager;

            QList<AssetManager*> m_assetManagers;
            Assets::AnimListManager* m_animListManager;
            Assets::BoulderManager* m_boulderManager;
            Assets::ButtonManager* m_buttonManager;
            Assets::CameraManager* m_cameraManager;
            Assets::ConditionalManager* m_condManager;
            Assets::CounterManager* m_counterManager;
            Assets::DispatcherManager* m_dpatManager;
            Assets::EnvManager* m_envManager;
            Assets::FogManager* m_fogManager;
            Assets::GroupManager* m_groupManager;
            Assets::JSPManager* m_jspManager;
            Assets::LightKitManager* m_lightKitManager;
            Assets::MarkerManager* m_markerManager;
            Assets::ModelManager* m_modelManager;
            Assets::PlayerManager* m_playerManager;
            Assets::SimpleObjectManager* m_simpManager;
            Assets::TextManager* m_textManager;
            Assets::TextureManager* m_textureManager;
            Assets::TimerManager* m_timerManager;
        };

    }

}
