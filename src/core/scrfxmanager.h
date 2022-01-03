#pragma once

#include <QObject>

namespace Slick {

    namespace Core {

        class Scene;

        class ScrFxManager : public QObject
        {
            Q_OBJECT

        public:
            ScrFxManager(Scene* scene);

            bool letterBoxEnabled() const { return m_letterBoxEnabled; }
            void setLetterBoxEnabled(bool enabled) { m_letterBoxEnabled = enabled; }

            uint8_t letterBoxAlpha() const { return m_letterBoxAlpha; }
            void setLetterBoxAlpha(uint8_t alpha) { m_letterBoxAlpha = alpha; }

            void render();

        private:
            Scene* m_scene;
            bool m_letterBoxEnabled;
            float m_letterBoxSize;
            uint8_t m_letterBoxAlpha;
            float m_letterBoxCurSize;

            void renderLetterBox();
        };

    }

}
