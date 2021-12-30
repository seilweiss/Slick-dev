#include "editors/sceneeditorwidget.h"

#include "editors/sceneeditorviewport.h"

#include "assets/cameraasset.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

namespace Slick {

    namespace Editors {

        SceneEditorWidget::SceneEditorWidget(QWidget* parent) :
            EditorWidget(parent),
            m_scene(nullptr),
            m_viewport(new SceneEditorViewport),
            m_statsLabel(new QLabel),
            m_previewCamComboBox(new QComboBox),
            m_previewCamChangedByMe(false)
        {
            QVBoxLayout* mainLayout = new QVBoxLayout;

            QHBoxLayout* toolbar = new QHBoxLayout;

            toolbar->addWidget(new QLabel("Placeholder toolbar"));
            toolbar->addWidget(new QPushButton("Test"));
            toolbar->addWidget(new QPushButton("1"));
            toolbar->addWidget(new QPushButton("2"));
            toolbar->addWidget(new QPushButton("3"));
            toolbar->addStretch(1);
            toolbar->addWidget(new QLabel("Preview Camera:"));
            toolbar->addWidget(m_previewCamComboBox);
            toolbar->addWidget(m_statsLabel);

            mainLayout->setContentsMargins(0, 0, 0, 0);
            mainLayout->addLayout(toolbar);
            mainLayout->addWidget(QWidget::createWindowContainer(m_viewport), 1);

            setLayout(mainLayout);

            connect(m_viewport, &SceneEditorViewport::doneRendering, this, &SceneEditorWidget::updateStats);

            connect(m_previewCamComboBox, &QComboBox::currentIndexChanged, this, [=](int index)
            {
                m_previewCamChangedByMe = true;

                uint32_t id = m_previewCamComboBox->itemData(index).toUInt();

                if (id == 0)
                {
                    m_scene->cameraManager()->setPreviewCamera(nullptr);
                }
                else
                {
                    m_scene->cameraManager()->setPreviewCamera((Assets::CameraAsset*)m_scene->asset(id));
                }
            });
        }

        void SceneEditorWidget::setScene(Core::Scene* scene)
        {
            m_scene = scene;

            refreshPreviewCam();

            connect(m_scene->cameraManager(), &Assets::CameraManager::previewCameraChanged, this, [=](Assets::CameraAsset* asset)
            {
                if (m_previewCamChangedByMe)
                {
                    m_previewCamChangedByMe = false;
                    return;
                }

                m_previewCamComboBox->blockSignals(true);

                if (!asset)
                {
                    m_previewCamComboBox->setCurrentIndex(0);
                }
                else
                {
                    m_previewCamComboBox->setCurrentText(asset->name());
                }

                m_previewCamComboBox->blockSignals(false);
            });

            m_viewport->setScene(m_scene);
            m_scene->renderContext()->setViewport(m_viewport);
        }

        void SceneEditorWidget::updateStats()
        {
            Render::Stats* stats = m_viewport->context()->stats();

            m_statsLabel->setText(tr("Atomics: %1 FPS: %2").arg(stats->atomicCount).arg(stats->fps));
        }

        void SceneEditorWidget::refreshPreviewCam()
        {
            m_previewCamComboBox->clear();
            m_previewCamComboBox->addItem(tr("<None>"), 0);

            for (auto asset : m_scene->cameraManager()->assets())
            {
                m_previewCamComboBox->addItem(asset->name(), asset->id());
            }
        }

    }

}
