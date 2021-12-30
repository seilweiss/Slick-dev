#pragma once

#include "inspector/property.h"

Q_MOC_INCLUDE("core/scene.h")

namespace Slick {

    namespace Core { class Scene; }

    namespace Inspector {

        class EventInputProperty : public Property
        {
            Q_OBJECT
            Q_PROPERTY(Core::Scene* scene READ scene WRITE setScene)

        public:
            EventInputProperty(const QString& name, const QString& displayName, const DataSource& dataSource, Core::Scene* scene, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent), m_scene(scene) { Q_ASSERT(scene); }

            Core::Scene* scene() const { return m_scene; }
            void setScene(Core::Scene* scene) { Q_ASSERT(scene); m_scene = scene; }

            virtual QWidget* createWidget(const QList<Property*>& props) override;

        private:
            Core::Scene* m_scene;
        };

    }

}
