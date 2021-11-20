#include "UI/HipHopEditorWidget.h"

#include "Core/Util.h"

#include <QComboBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QHeaderView>

namespace Slick {

    HipHopEditorWidget::HipHopEditorWidget(QWidget* parent) :
        IEditorWidget(parent),
        m_file(nullptr),
        m_layerComboBox(new QComboBox),
        m_layerTypeComboBox(new QComboBox),
        m_assetTypeComboBox(new QComboBox),
        m_assetSearchLineEdit(new QLineEdit),
        m_assetTableWidget(new QTableWidget)
    {
        QVBoxLayout* mainLayout = new QVBoxLayout;
        QGroupBox* layerGroupBox = new QGroupBox(tr("Layer"));
        QGroupBox* assetGroupBox = new QGroupBox(tr("Assets"));

        resetTable();

        // Layers
        {
            connect(m_layerComboBox, &QComboBox::currentTextChanged, this, &HipHopEditorWidget::refresh);

            QPushButton* addButton = new QPushButton(tr("Add"));
            QPushButton* removeButton = new QPushButton(tr("Remove"));
            QPushButton* moveUpButton = new QPushButton(tr("Move Up"));
            QPushButton* moveDownButton = new QPushButton(tr("Move Down"));

            QHBoxLayout* groupBoxLayout = new QHBoxLayout;

            groupBoxLayout->addWidget(m_layerComboBox, 2);
            groupBoxLayout->addWidget(new QLabel(tr("Type:")));
            groupBoxLayout->addWidget(m_layerTypeComboBox, 1);
            groupBoxLayout->addWidget(addButton);
            groupBoxLayout->addWidget(removeButton);
            groupBoxLayout->addWidget(moveUpButton);
            groupBoxLayout->addWidget(moveDownButton);

            layerGroupBox->setLayout(groupBoxLayout);
        }

        // Assets
        {
            // Options
            connect(m_assetTypeComboBox, &QComboBox::currentTextChanged, this, &HipHopEditorWidget::refresh);
            connect(m_assetSearchLineEdit, &QLineEdit::textEdited, this, &HipHopEditorWidget::refresh);

            QHBoxLayout* optionsLayout = new QHBoxLayout;
            optionsLayout->addWidget(new QLabel(tr("Type:")));
            optionsLayout->addWidget(m_assetTypeComboBox, 1);
            optionsLayout->addWidget(new QLabel(tr("Find:")));
            optionsLayout->addWidget(m_assetSearchLineEdit, 3);

            // Table
            m_assetTableWidget->verticalHeader()->hide();
            m_assetTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
            m_assetTableWidget->setShowGrid(false);
            m_assetTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            m_assetTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
            m_assetTableWidget->setSortingEnabled(true);
            m_assetTableWidget->sortByColumn(1, Qt::AscendingOrder);
            m_assetTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

            // Editor
            QGroupBox* editorGroupBox = new QGroupBox;

            {
                QVBoxLayout* editorLayout = new QVBoxLayout;

                QHBoxLayout* nameLayout = new QHBoxLayout;
                nameLayout->addWidget(new QLabel(tr("Name:")));
                nameLayout->addWidget(new QLineEdit, 1);

                editorLayout->addLayout(nameLayout);
                editorLayout->addStretch(1);

                editorGroupBox->setLayout(editorLayout);
            }

            QHBoxLayout* tableLayout = new QHBoxLayout;
            tableLayout->addWidget(m_assetTableWidget, 1);
            tableLayout->addWidget(editorGroupBox);

            QVBoxLayout* groupBoxLayout = new QVBoxLayout;
            groupBoxLayout->addLayout(optionsLayout);
            groupBoxLayout->addLayout(tableLayout, 1);

            assetGroupBox->setLayout(groupBoxLayout);
        }

        mainLayout->addWidget(layerGroupBox);
        mainLayout->addWidget(assetGroupBox, 1);

        setLayout(mainLayout);
    }

    void HipHopEditorWidget::loadFile(HipHop::File* file)
    {
        m_file = file;

        m_layerComboBox->clear();
        m_layerTypeComboBox->clear();

        for (int i = 0; i < file->GetLayerCount(); i++)
        {
            HipHop::Layer layer = file->GetLayerAt(i);

            m_layerComboBox->addItem(QString("Layer %1: %2 [%3]").arg(i).arg(Util::layerTypeToString(layer.GetType())).arg(layer.GetAssetCount()));
        }

        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::DEFAULT));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::TEXTURE));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::TEXTURE_STRM));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::BSP));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::MODEL));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::ANIMATION));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::VRAM));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::SRAM));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::SNDTOC));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::CUTSCENE));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::CUTSCENETOC));
        m_layerTypeComboBox->addItem(Util::layerTypeToString(HipHop::LayerType::JSPINFO));

        m_layerComboBox->setCurrentIndex(0);

        QVector<HipHop::AssetType> assetTypes;

        for (int i = 0; i < file->GetAssetCount(); i++)
        {
            HipHop::Asset asset = file->GetAssetAt(i);
            HipHop::AssetType type = asset.GetType();

            if (!assetTypes.contains(type))
            {
                assetTypes.append(type);
            }
        }

        std::sort(assetTypes.begin(), assetTypes.end(), [](HipHop::AssetType a, HipHop::AssetType b) { return a < b; });

        m_assetTypeComboBox->addItem("All", (uint32_t)HipHop::AssetType::Default);

        for (HipHop::AssetType type : assetTypes)
        {
            m_assetTypeComboBox->addItem(Util::assetTypeToString(type), (uint32_t)type);
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

        int layerIndex = m_layerComboBox->currentIndex();

        if (layerIndex != -1)
        {
            HipHop::Layer layer = m_file->GetLayerAt(layerIndex);
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

            m_assetTableWidget->setSortingEnabled(false);
            m_assetTableWidget->setUpdatesEnabled(false);

            m_assetTableWidget->setRowCount(filteredAssetCount);

            for (int i = 0; i < filteredAssetCount; i++)
            {
                HipHop::Asset asset = filteredAssets[i];

                QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(asset.GetID(), 16).toUpper());
                QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(asset.GetName()));
                QTableWidgetItem* typeItem = new QTableWidgetItem(Util::assetTypeToString(asset.GetType()));

                m_assetTableWidget->setItem(i, 0, idItem);
                m_assetTableWidget->setItem(i, 1, nameItem);
                m_assetTableWidget->setItem(i, 2, typeItem);
            }

            m_assetTableWidget->setSortingEnabled(true);
            m_assetTableWidget->setUpdatesEnabled(true);
        }
    }

}
