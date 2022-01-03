#pragma once

#include "assets/entasset.h"

#include <QObject>

namespace Slick {

    namespace Core {

        class SkyDomeManager : public QObject
        {
            Q_OBJECT

        public:
            SkyDomeManager(Scene* scene);

            void setup();
            void render();

        private:
            struct SkyDomeInfo
            {
                Assets::EntAsset* ent;
                int sortorder;
                bool lockY;
            };

            Scene* m_scene;
            QList<SkyDomeInfo> m_info;
        };

    }

}
