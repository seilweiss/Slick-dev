#include "Editors/HipHopEditor.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>

#include <algorithm>

namespace Slick {

    namespace {

        inline QString layerTypeToString(HipHop::LayerType type)
        {
            switch (type)
            {
            case HipHop::LayerType::DEFAULT: return "DEFAULT";
            case HipHop::LayerType::TEXTURE: return "TEXTURE";
            case HipHop::LayerType::TEXTURE_STRM: return "TEXTURE_STRM";
            case HipHop::LayerType::BSP: return "BSP";
            case HipHop::LayerType::MODEL: return "MODEL";
            case HipHop::LayerType::ANIMATION: return "ANIMATION";
            case HipHop::LayerType::VRAM: return "VRAM";
            case HipHop::LayerType::SRAM: return "SRAM";
            case HipHop::LayerType::SNDTOC: return "SNDTOC";
            case HipHop::LayerType::CUTSCENE: return "CUTSCENE";
            case HipHop::LayerType::CUTSCENETOC: return "CUTSCENETOC";
            case HipHop::LayerType::JSPINFO: return "JSPINFO";
            default: return "<unknown>";
            }
        }

        inline QString assetTypeToString(HipHop::AssetType type)
        {
            uint32_t t = (uint32_t)type;
            HipHop::Util::Swap32(&t, sizeof(uint32_t));

            return QString::fromUtf8((char*)&t, sizeof(uint32_t));
        }

    }

    HipHopEditor::HipHopEditor(QObject* parent) :
        IEditor(parent),
        m_file(),
        m_stream(),
        m_widget(nullptr)
    {
        setTitle("Untitled.HIP");
        setDirty(true);

        panelLayout().sceneVisible = false;

        connect(this, &HipHopEditor::pathChanged, this, [=](const QString& path)
        {
            setTitle(QFileInfo(path).fileName());
            setTooltip(path);
        });
    }

    IEditorWidget* HipHopEditor::createWidget()
    {
        m_widget = new HipHopEditorWidget(this);
        m_widget->load();

        return m_widget;
    }

    IEditor::SaveResult HipHopEditor::save()
    {
        if (m_path.isEmpty())
        {
            return saveAs();
        }

        setDirty(false);

        return SaveSuccessful;
    }

    IEditor::SaveResult HipHopEditor::saveAs()
    {
        QString path = getSaveFileName(this);

        if (path.isEmpty())
        {
            return SaveCancelled;
        }

        setPath(path);
        setDirty(false);

        return SaveSuccessful;
    }

    IEditor::OpenResult HipHopEditor::open()
    {
        if (m_path.isEmpty())
        {
            QString path = getOpenFileName();

            if (path.isEmpty())
            {
                return OpenCancelled;
            }

            setPath(path);
        }

        if (!m_stream.Open(m_path.toStdString()))
        {
            return OpenFailed;
        }

        m_file.SetStream(&m_stream);

        if (!m_file.Read())
        {
            return OpenFailed;
        }

        m_stream.Close();

        setDirty(false);

        return OpenSuccessful;
    }

    QString HipHopEditor::filter()
    {
        return "HIP/HOP files (*.hip *.hop);;All files (*.*)";
    }

    QString HipHopEditor::getOpenFileName()
    {
        return QFileDialog::getOpenFileName(nullptr, tr("Open HIP/HOP File"), QString(), filter());
    }

    QString HipHopEditor::getSaveFileName(HipHopEditor* editor)
    {
        QString path;

        if (editor)
        {
            if (!editor->path().isEmpty())
            {
                path = editor->path();
            }
            else
            {
                path = editor->title();

                if (QFileInfo(path).suffix().isEmpty())
                {
                    path += ".HIP";
                }
            }
        }

        return QFileDialog::getSaveFileName(nullptr, tr("Save HIP/HOP File"), path, filter());
    }

    HipHopEditorWidget::HipHopEditorWidget(HipHopEditor* editor, QWidget* parent) :
        IEditorWidget(parent),
        m_editor(editor),
        m_layerComboBox(new QComboBox),
        m_layerTypeComboBox(new QComboBox),
        m_assetTypeComboBox(new QComboBox),
        m_assetSearchLineEdit(new QLineEdit),
        m_assetTableWidget(new QTableWidget)
    {
        QVBoxLayout* mainLayout = new QVBoxLayout;
        QGroupBox* layerGroupBox = new QGroupBox(tr("Layer"));
        QGroupBox* assetGroupBox = new QGroupBox(tr("Assets"));
        QHBoxLayout* layerGroupBoxLayout = new QHBoxLayout;
        QVBoxLayout* assetGroupBoxLayout = new QVBoxLayout;
        QHBoxLayout* assetToolbarLayout = new QHBoxLayout;
        QHBoxLayout* assetTableLayout = new QHBoxLayout;
        QPushButton* layerAddButton = new QPushButton(tr("Add"));
        QPushButton* layerRemoveButton = new QPushButton(tr("Remove"));
        QPushButton* layerMoveUpButton = new QPushButton(tr("Move Up"));
        QPushButton* layerMoveDownButton = new QPushButton(tr("Move Down"));

        connect(m_layerComboBox, &QComboBox::currentTextChanged, this, &HipHopEditorWidget::refresh);
        connect(m_assetTypeComboBox, &QComboBox::currentTextChanged, this, &HipHopEditorWidget::refresh);
        connect(m_assetSearchLineEdit, &QLineEdit::textEdited, this, &HipHopEditorWidget::refresh);

        resetTable();

        m_assetTableWidget->verticalHeader()->hide();
        m_assetTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        m_assetTableWidget->setShowGrid(false);
        m_assetTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_assetTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        m_assetTableWidget->setSortingEnabled(true);
        m_assetTableWidget->sortByColumn(1, Qt::AscendingOrder);

        layerGroupBoxLayout->addWidget(m_layerComboBox, 2);
        layerGroupBoxLayout->addWidget(new QLabel(tr("Type:")));
        layerGroupBoxLayout->addWidget(m_layerTypeComboBox, 1);
        layerGroupBoxLayout->addWidget(layerAddButton);
        layerGroupBoxLayout->addWidget(layerRemoveButton);
        layerGroupBoxLayout->addWidget(layerMoveUpButton);
        layerGroupBoxLayout->addWidget(layerMoveDownButton);

        layerGroupBox->setLayout(layerGroupBoxLayout);

        assetToolbarLayout->addWidget(new QLabel(tr("Type:")));
        assetToolbarLayout->addWidget(m_assetTypeComboBox, 1);
        assetToolbarLayout->addWidget(new QLabel(tr("Find:")));
        assetToolbarLayout->addWidget(m_assetSearchLineEdit, 3);

        assetTableLayout->addWidget(m_assetTableWidget, 1);

        assetGroupBoxLayout->addLayout(assetToolbarLayout, 1);
        assetGroupBoxLayout->addLayout(assetTableLayout, 1);

        assetGroupBox->setLayout(assetGroupBoxLayout);

        mainLayout->addWidget(layerGroupBox);
        mainLayout->addWidget(assetGroupBox, 1);

        setLayout(mainLayout);
    }

    void HipHopEditorWidget::load()
    {
        HipHop::File& file = m_editor->file();

        m_layerComboBox->clear();
        m_layerTypeComboBox->clear();

        for (int i = 0; i < file.GetLayerCount(); i++)
        {
            HipHop::Layer layer = file.GetLayerAt(i);

            m_layerComboBox->addItem(QString("Layer %1: %2 [%3]").arg(i).arg(layerTypeToString(layer.GetType())).arg(layer.GetAssetCount()));
        }

        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::DEFAULT));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::TEXTURE));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::TEXTURE_STRM));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::BSP));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::MODEL));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::ANIMATION));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::VRAM));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::SRAM));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::SNDTOC));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::CUTSCENE));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::CUTSCENETOC));
        m_layerTypeComboBox->addItem(layerTypeToString(HipHop::LayerType::JSPINFO));

        m_layerComboBox->setCurrentIndex(0);

        struct AssetType
        {
            HipHop::AssetType type;
            QString str;
        };

        QVector<AssetType> assetTypes;

        for (int i = 0; i < file.GetAssetCount(); i++)
        {
            HipHop::Asset asset = file.GetAssetAt(i);
            HipHop::AssetType type = asset.GetType();
            bool found = false;

            for (const AssetType& t : assetTypes)
            {
                if (t.type == type)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                assetTypes.append({ type, assetTypeToString(type) });
            }
        }

        std::sort(assetTypes.begin(), assetTypes.end(), [](const AssetType& a, const AssetType& b) { return a.type < b.type; });

        m_assetTypeComboBox->addItem("All", (uint32_t)HipHop::AssetType::Default);

        for (const AssetType& t : assetTypes)
        {
            m_assetTypeComboBox->addItem(t.str, (uint32_t)t.type);
        }

        m_assetSearchLineEdit->clear();
    }

    void HipHopEditorWidget::resetTable()
    {
        m_assetTableWidget->clear();
        m_assetTableWidget->setColumnCount(3);
        m_assetTableWidget->setHorizontalHeaderLabels({ "Asset ID", "Name", "Type" });
    }

    void HipHopEditorWidget::refresh()
    {
        resetTable();

        const HipHop::Layer& layer = m_editor->file().GetLayerAt(m_layerComboBox->currentIndex());
        int assetCount = layer.GetAssetCount();
        QVector<HipHop::Asset> filteredAssets;
        HipHop::AssetType typeFilter = (HipHop::AssetType)m_assetTypeComboBox->currentData().toUInt();
        QString searchFilter = m_assetSearchLineEdit->text();

        m_layerTypeComboBox->setCurrentIndex((int)layer.GetType());

        for (int i = 0; i < assetCount; i++)
        {
            HipHop::Asset asset = layer.GetAsset(i);

            if ((typeFilter == HipHop::AssetType::Default || asset.GetType() == typeFilter) &&
                (searchFilter.isEmpty() || QString::fromStdString(asset.GetName()).contains(searchFilter, Qt::CaseInsensitive)))
            {
                filteredAssets.append(asset);
            }
        }

        int filteredAssetCount = filteredAssets.size();

        m_assetTableWidget->setRowCount(filteredAssetCount);
        m_assetTableWidget->setSortingEnabled(false);
        m_assetTableWidget->setUpdatesEnabled(false);

        for (int i = 0; i < filteredAssetCount; i++)
        {
            HipHop::Asset asset = filteredAssets[i];

            QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(asset.GetID(), 16).toUpper());
            QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(asset.GetName()));
            QTableWidgetItem* typeItem = new QTableWidgetItem(assetTypeToString(asset.GetType()));

            m_assetTableWidget->setItem(i, 0, idItem);
            m_assetTableWidget->setItem(i, 1, nameItem);
            m_assetTableWidget->setItem(i, 2, typeItem);
        }

        m_assetTableWidget->setSortingEnabled(true);
        m_assetTableWidget->setUpdatesEnabled(true);
    }

}
