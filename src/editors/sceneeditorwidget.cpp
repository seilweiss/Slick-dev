#include "editors/sceneeditorwidget.h"

#include "editors/sceneeditorviewport.h"

#include "assets/cameraasset.h"
#include "core/scrfxmanager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>

namespace Slick {

    namespace Editors {

        SceneEditorWidget::SceneEditorWidget(QWidget* parent) :
            EditorWidget(parent),
            m_scene(nullptr),
            m_viewport(new SceneEditorViewport),
            m_statsLabel(new QLabel),
            m_letterBoxCheckBox(new QCheckBox),
            m_aspectRatioComboBox(new QComboBox),
            m_previewCamComboBox(new QComboBox),
            m_previewCamChangedByMe(false)
        {
            m_letterBoxCheckBox->setChecked(false);

            m_aspectRatioComboBox->addItem(tr("Auto"), 0.0f);
            m_aspectRatioComboBox->addItem(tr("3:2"), 3.0f / 2.0f);
            m_aspectRatioComboBox->addItem(tr("4:3"), 4.0f / 3.0f);
            m_aspectRatioComboBox->addItem(tr("16:9"), 16.0f / 9.0f);

            QVBoxLayout* mainLayout = new QVBoxLayout;

            QHBoxLayout* toolbar = new QHBoxLayout;

            toolbar->addStretch(1);
            toolbar->addWidget(new QLabel(tr("Aspect Ratio:")));
            toolbar->addWidget(m_aspectRatioComboBox);
            toolbar->addWidget(new QLabel(tr("Letterbox:")));
            toolbar->addWidget(m_letterBoxCheckBox);
            toolbar->addWidget(new QLabel(tr("Preview Camera:")));
            toolbar->addWidget(m_previewCamComboBox);
            toolbar->addWidget(m_statsLabel);

            mainLayout->setContentsMargins(0, 0, 0, 0);
            mainLayout->addLayout(toolbar);
            mainLayout->addWidget(QWidget::createWindowContainer(m_viewport), 1);

            setLayout(mainLayout);

            connect(m_viewport, &SceneEditorViewport::doneRendering, this, &SceneEditorWidget::updateStats);

            connect(m_letterBoxCheckBox, &QCheckBox::toggled, this, [=](bool checked)
            {
                m_scene->scrFxManager()->setLetterBoxEnabled(checked);
            });

            connect(m_aspectRatioComboBox, &QComboBox::currentIndexChanged, this, [=](int index)
            {
                m_viewport->setAspectOverride(m_aspectRatioComboBox->itemData(index).toFloat());
            });

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
                    m_scene->cameraManager()->setPreviewCamera((Assets::CameraAsset*)m_scene->assetById(id));
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

            m_statsLabel->setText(tr("Atomics: %1 Triangles: %2 FPS: %3")
                                  .arg(stats->atomicCount)
                                  .arg(stats->triangleCount)
                                  .arg(stats->fps));
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
