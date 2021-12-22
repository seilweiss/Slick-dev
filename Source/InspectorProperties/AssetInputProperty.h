#pragma once

#include "Core/InspectorProperty.h"

Q_MOC_INCLUDE("Core/Scene.h")

namespace Slick {

    class Scene;

    class AssetInputProperty : public InspectorProperty
    {
        Q_OBJECT
        Q_PROPERTY(Scene* scene READ scene WRITE setScene)

    public:
        AssetInputProperty(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, Scene* scene, QObject* parent = nullptr) :
            InspectorProperty(name, displayName, dataSource, parent), m_scene(scene) { Q_ASSERT(scene); }

        Scene* scene() const { return m_scene; }
        void setScene(Scene* scene) { Q_ASSERT(scene); m_scene = scene; }

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) override;

    private:
        Scene* m_scene;
    };

}
