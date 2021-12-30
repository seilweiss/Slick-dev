#include "panels/scenepanel.h"

#include "util/hiphoputils.h"

#include <QTabWidget>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QStackedLayout>
#include <QLabel>

#include <map>

namespace Slick {

    namespace Panels {

        using namespace ScenePanelPrivate;

        namespace {

            inline QString getAssetTypeName(HipHop::Asset asset)
            {
                static std::map<HipHop::AssetType, const char*> typeMap =
                {
                    { HipHop::AssetType::ALST, "AnimList" },
                    { HipHop::AssetType::ANIM, "Animation" },
                    { HipHop::AssetType::ATBL, "AnimTable" },
                    { HipHop::AssetType::ATKT, "Attack Table" },
                    { HipHop::AssetType::BINK, "Bink" },
                    { HipHop::AssetType::BOUL, "Boulder" },
                    { HipHop::AssetType::BSP,  "BSP" },
                    { HipHop::AssetType::BUTN, "Button" },
                    { HipHop::AssetType::CAM,  "Camera" },
                    { HipHop::AssetType::CCRV, "Camera Curve" },
                    { HipHop::AssetType::CNTR, "Counter" },
                    { HipHop::AssetType::COLL, "Collision Table" },
                    { HipHop::AssetType::COND, "Conditional" },
                    { HipHop::AssetType::CRDT, "Credits" },
                    { HipHop::AssetType::CSN,  "Cutscene" },
                    { HipHop::AssetType::CSNM, "Cutscene Mgr" },
                    { HipHop::AssetType::CSSS, "Cutscene Streaming Sound" },
                    { HipHop::AssetType::CTOC, "Cutscene TOC" },
                    { HipHop::AssetType::DEST, "Destructible" },
                    { HipHop::AssetType::DPAT, "Dispatcher" },
                    { HipHop::AssetType::DSCO, "Disco Floor" },
                    { HipHop::AssetType::DSTR, "Destructible Object" },
                    { HipHop::AssetType::DTRK, "Dash Track" },
                    { HipHop::AssetType::DUPC, "Duplicator" },
                    { HipHop::AssetType::DYNA, "Dynamic" },
                    { HipHop::AssetType::EGEN, "Electric Arc Generator" },
                    { HipHop::AssetType::ENV,  "Environment" },
                    { HipHop::AssetType::FLY,  "Flythrough" },
                    { HipHop::AssetType::FOG,  "Fog" },
                    { HipHop::AssetType::GRSM, "Grass Mesh" },
                    { HipHop::AssetType::GRUP, "Group" },
                    { HipHop::AssetType::GUST, "Gust" },
                    { HipHop::AssetType::HANG, "Hangable" },
                    { HipHop::AssetType::JAW,  "Jaw Data Table" },
                    { HipHop::AssetType::JSP,  "JSP" },
                    { HipHop::AssetType::LITE, "Light" },
                    { HipHop::AssetType::LKIT, "LightKit" },
                    { HipHop::AssetType::LOBM, "LobMaster" },
                    { HipHop::AssetType::LODT, "LOD Table" },
                    { HipHop::AssetType::MAPR, "Material Map" },
                    { HipHop::AssetType::MINF, "Model Info" },
                    { HipHop::AssetType::MODL, "Model" },
                    { HipHop::AssetType::MPHT, "Morph Target" },
                    { HipHop::AssetType::MRKR, "Marker" },
                    { HipHop::AssetType::MVPT, "Move Point" },
                    { HipHop::AssetType::NGMS, "NavMesh" },
                    { HipHop::AssetType::NPC,  "Villain" },
                    { HipHop::AssetType::NPCS, "NPC Settings" },
                    { HipHop::AssetType::ONEL, "OneLiner" },
                    { HipHop::AssetType::PARE, "Particle Emitter" },
                    { HipHop::AssetType::PARP, "Particle Emitter Props" },
                    { HipHop::AssetType::PARS, "Particle System" },
                    { HipHop::AssetType::PEND, "Pendulum" },
                    { HipHop::AssetType::PGRS, "Progress Script" },
                    { HipHop::AssetType::PICK, "Pickup Table" },
                    { HipHop::AssetType::PIPT, "Pipe Info Table" },
                    { HipHop::AssetType::PKUP, "Pickup" },
                    { HipHop::AssetType::PLAT, "Platform" },
                    { HipHop::AssetType::PLYR, "Player" },
                    { HipHop::AssetType::PORT, "Portal" },
                    { HipHop::AssetType::PRJT, "Projectile" },
                    { HipHop::AssetType::RANM, "Reactive Anim Table" },
                    { HipHop::AssetType::RAW,  "Raw" },
                    { HipHop::AssetType::RWTX, "Texture" },
                    { HipHop::AssetType::SCRP, "Script" },
                    { HipHop::AssetType::SDFX, "Sound FX" },
                    { HipHop::AssetType::SFX,  "SFX" },
                    { HipHop::AssetType::SGRP, "Sound Group" },
                    { HipHop::AssetType::SHDW, "Simple Shadow Table" },
                    { HipHop::AssetType::SHRP, "Shrapnel" },
                    { HipHop::AssetType::SIMP, "Simple Object" },
                    { HipHop::AssetType::SLID, "Slide Props" },
                    { HipHop::AssetType::SND,  "Sound" },
                    { HipHop::AssetType::SNDI, "Sound Info" },
                    { HipHop::AssetType::SNDS, "Streaming Sound" },
                    { HipHop::AssetType::SPLN, "Spline" },
                    { HipHop::AssetType::SPLP, "Spline Path" },
                    { HipHop::AssetType::SSET, "Scene Settings" },
                    { HipHop::AssetType::SUBT, "Subtitles" },
                    { HipHop::AssetType::SURF, "Surface" },
                    { HipHop::AssetType::TEXS, "Streaming Texture" },
                    { HipHop::AssetType::TEXT, "Text" },
                    { HipHop::AssetType::TIMR, "Timer" },
                    { HipHop::AssetType::TPIK, "Pickup Table" },
                    { HipHop::AssetType::TRIG, "Trigger" },
                    { HipHop::AssetType::TRWT, "Throwable Table" },
                    { HipHop::AssetType::UI,   "UI" },
                    { HipHop::AssetType::UIFT, "UI Font" },
                    { HipHop::AssetType::UIM,  "UI Motion" },
                    { HipHop::AssetType::VIL,  "NPC" },
                    { HipHop::AssetType::VILP, "NPC Properties" },
                    { HipHop::AssetType::VOLU, "Volume" },
                    { HipHop::AssetType::WIRE, "Wireframe" },
                    { HipHop::AssetType::ZLIN, "ZipLine" }
                };

                static std::map<uint32_t, const char*> dynaMap =
                {
                    { 0x3A335FCF, "audio:conversation" },
                    { 0xFA0E4015, "camera:binary_poi" },
                    { 0xCDAB9190, "camera:preset" },
                    { 0xBBA5036A, "camera:transition_path" },
                    { 0xBC304E86, "camera:transition_time" },
                    { 0x2DE7AB98, "Checkpoint" },
                    { 0xDEC6DFF0, "effect:Boss Brain" },
                    { 0xFB1179F5, "effect:Flamethrower" },
                    { 0x081A3629, "effect:grass" },
                    { 0x2CD29541, "effect:Lens Flare Element" },
                    { 0x5EAB97E1, "effect:light" },
                    { 0x53CE3CA4, "effect:Light Effect Flicker" },
                    { 0x96727F69, "effect:Light Effect Strobe" },
                    { 0x94B8EF2D, "effect:Lightning" },
                    { 0x4AF4ABC7, "effect:particle_generator" },
                    { 0x2A59443A, "effect:Rumble" },
                    { 0x56F5D96F, "effect:Rumble Box Emitter" },
                    { 0x1337E641, "effect:Rumble Spherical Emitter" },
                    { 0x9535DB9D, "effect:ScreenFade" },
                    { 0xC2783A7F, "effect:Screen Warp" },
                    { 0x0903FBB9, "effect:smoke_emitter" },
                    { 0xA7039867, "effect:spark_emitter" },
                    { 0xCDF6730C, "effect:Splash" },
                    { 0x6AA8BF67, "effect:spotlight" },
                    { 0xA866726F, "effect:uber_laser" },
                    { 0x90D4BA5B, "effect:water_body" },
                    { 0x03E64AEB, "effect:Waterhose" },
                    { 0x5B1CC119, "Enemy:SB" },
                    { 0xD2D6A1E5, "Enemy:SB:BucketOTron" },
                    { 0x1F9D54BB, "Enemy:SB:CastNCrew" },
                    { 0x45B73B62, "Enemy:SB:Critter" },
                    { 0xCE41C144, "Enemy:SB:Dennis" },
                    { 0x11FCF451, "Enemy:SB:FrogFish" },
                    { 0xC92170B2, "Enemy:SB:Mindy" },
                    { 0xBE8C5CAC, "Enemy:SB:Neptune" },
                    { 0x44EA147A, "Enemy:SB:Standard" },
                    { 0x495BFF9B, "Enemy:SB:SupplyCrate" },
                    { 0x9FEC1E09, "Enemy:SB:Turret" },
                    { 0xBB4864D8, "game_object:BoulderGenerator" },
                    { 0x381232B4, "game_object:bullet_mark" },
                    { 0x390467A4, "game_object:bullet_time" },
                    { 0x574749A4, "game_object:bungee_drop" },
                    { 0x57CFB6F0, "game_object:bungee_hook" },
                    { 0x8F012778, "game_object:BusStop" },
                    { 0xE44DCEBA, "game_object:camera_param_asset" },
                    { 0x9092FB14, "game_object:Camera_Tweak" },
                    { 0x571A5DBC, "game_object:dash_camera_spline" },
                    { 0xE6120704, "game_object:flame_emitter" },
                    { 0x85BFDF34, "game_object:Flythrough" },
                    { 0x35D19631, "game_object:FreezableObject" },
                    { 0xE7928821, "game_object:Grapple" },
                    { 0x1D3C54EE, "game_object:Hangable" },
                    { 0x832E4208, "game_object:IN_Pickup" },
                    { 0xBBCB17C1, "game_object:laser_beam" },
                    { 0x8768334A, "game_object:NPCSettings" },
                    { 0x844BCF76, "game_object:RaceTimer" },
                    { 0x945F2E84, "game_object:rband_camera_asset" },
                    { 0x4D81C1EE, "game_object:Ring" },
                    { 0x18028CA7, "game_object:RingControl" },
                    { 0x3D0D5121, "game_object:RubbleGenerator" },
                    { 0x0934B196, "game_object:talk_box" },
                    { 0xE9D2C1BB, "game_object:task_box" },
                    { 0x4DC449FC, "game_object:Taxi" },
                    { 0x70ADB7F9, "game_object:Teleport" },
                    { 0x442E1337, "game_object:text_box" },
                    { 0xC279D693, "game_object:train_car" },
                    { 0xEA7B28D9, "game_object:train_junction" },
                    { 0x798A7982, "game_object:Turret" },
                    { 0x4E09EC43, "game_object:Vent" },
                    { 0x5E5B5165, "game_object:VentType" },
                    { 0xB8DA553C, "hud:image" },
                    { 0x8B3E732F, "hud:meter:font" },
                    { 0x8D40B9AC, "hud:meter:unit" },
                    { 0xFF5691D2, "hud:model" },
                    { 0x687ED0B0, "hud:text" },
                    { 0xD6093241, "Incredibles:Icon" },
                    { 0xF7E8697A, "interaction:Ice Bridge" },
                    { 0x4B03B4F7, "interaction:Launch" },
                    { 0x4C1F2B57, "interaction:Lift" },
                    { 0x28478E46, "interaction:SwitchLever" },
                    { 0x4D34C2B9, "interaction:Turn" },
                    { 0x1F662B3C, "Interest_Pointer" },
                    { 0x204D6ADB, "JSP Extra Data" },
                    { 0x4494F483, "logic:Function Generator" },
                    { 0xF98698FF, "logic:reference" },
                    { 0x48C0D3A6, "npc:CoverPoint" },
                    { 0x2326640A, "npc:group" },
                    { 0xFF7E4CFC, "npc:NPC_Custom_AV" },
                    { 0x2196C135, "pointer" },
                    { 0x8C2D107D, "ui:box" },
                    { 0xE8753BAE, "ui:controller" },
                    { 0x337BCB31, "ui:image" },
                    { 0x79F807C7, "ui:model" },
                    { 0xBD7646D7, "ui:text" },
                    { 0xFB50BACB, "ui:text:user string" },

                    { 0xFABDB3B3, "Scene Properties" }
                };

                HipHop::AssetType type = asset.GetType();

                if (typeMap.find(type) != typeMap.end())
                {
                    if (type == HipHop::AssetType::DYNA)
                    {
                        HipHop::DynaAsset dyna(asset);
                        dyna.Load();

                        if (dynaMap.find(dyna.type) != dynaMap.end())
                        {
                            return dynaMap[dyna.type];
                        }
                        else
                        {
                            qDebug() << QString("Asset %1 has unknown DYNA type 0x%2").arg(QString::fromStdString(asset.GetName())).arg(dyna.type, 0, 16);
                        }
                    }

                    return typeMap[type];
                }
                else
                {
                    qDebug() << QString("Asset %1 has unknown type %2").arg(QString::fromStdString(asset.GetName())).arg(Util::assetTypeToString(type));
                }

                return QObject::tr("Unknown");
            }

        }

        ScenePanel::ScenePanel(QWidget* parent) :
            QWidget(parent)
        {
            QStackedLayout* mainLayout = new QStackedLayout;

            setLayout(mainLayout);
        }

        Core::Scene* ScenePanel::scene() const
        {
            QStackedLayout* stack = (QStackedLayout*)layout();
            SceneWidget* widget = (SceneWidget*)stack->currentWidget();

            if (widget)
            {
                return widget->scene();
            }

            return nullptr;
        }

        void ScenePanel::setScene(Core::Scene* scene)
        {
            QStackedLayout* stack = (QStackedLayout*)layout();
            bool widgetFound = false;

            for (int i = 0; i < stack->count(); i++)
            {
                SceneWidget* widget = (SceneWidget*)stack->widget(i);

                if (widget->scene() == scene)
                {
                    stack->setCurrentWidget(widget);
                    widgetFound = true;
                    break;
                }
            }

            if (!widgetFound)
            {
                SceneWidget* widget = new SceneWidget;

                widget->setScene(scene);

                connect(widget, &SceneWidget::assetsSelected, this, &ScenePanel::assetsSelected);

                stack->addWidget(widget);
                stack->setCurrentWidget(widget);
            }

            emit sceneChanged(scene);
            emit assetsSelected(selectedAssets());
        }

        QList<Core::Asset*> ScenePanel::selectedAssets() const
        {
            QStackedLayout* stack = (QStackedLayout*)layout();
            SceneWidget* widget = (SceneWidget*)stack->currentWidget();

            if (widget)
            {
                return widget->selectedAssets();
            }

            return {};
        }

        SceneWidget::SceneWidget(QWidget* parent) :
            QWidget(parent),
            m_scene(nullptr),
            m_fileTabWidget(new QTabWidget)
        {
            m_fileTabWidget->setDocumentMode(true);

            QVBoxLayout* mainLayout = new QVBoxLayout;

            mainLayout->addWidget(m_fileTabWidget, 1);

            setLayout(mainLayout);

            connect(m_fileTabWidget, &QTabWidget::currentChanged, this, [=] { emit assetsSelected(selectedAssets()); });
        }

        void SceneWidget::setScene(Core::Scene* scene)
        {
            m_scene = scene;

            for (int i = 0; i < m_fileTabWidget->count(); i++)
            {
                m_fileTabWidget->widget(i)->deleteLater();
            }

            m_fileTabWidget->clear();

            if (scene)
            {
                for (int i = 0; i < scene->fileCount(); i++)
                {
                    SceneFileWidget* widget = new SceneFileWidget;
                    Core::SceneFile* file = scene->file(i);
                    QString title = QFileInfo(file->path()).fileName();

                    widget->setFile(file);

                    connect(widget, &SceneFileWidget::assetsSelected, this, &SceneWidget::assetsSelected);

                    m_fileTabWidget->addTab(widget, title);
                }
            }
        }

        QList<Core::Asset*> SceneWidget::selectedAssets() const
        {
            SceneFileWidget* widget = (SceneFileWidget*)m_fileTabWidget->currentWidget();

            if (widget)
            {
                return widget->selectedAssets();
            }

            return {};
        }

        SceneFileWidget::SceneFileWidget(QWidget* parent) :
            QWidget(parent),
            m_file(nullptr),
            m_createAssetButton(new QPushButton(QIcon(":/icons/list-add.svg"), QString())),
            m_filterAssetsLineEdit(new QLineEdit),
            m_filterTypesComboBox(new QComboBox),
            m_assetsTableWidget(new QTableWidget(0, 2))
        {
            //m_createAssetButton->setFlat(true);

            m_filterAssetsLineEdit->setPlaceholderText(tr("Search assets..."));

            m_assetsTableWidget->setHorizontalHeaderLabels({ tr("Name"), tr("Type") });
            m_assetsTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
            m_assetsTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
            m_assetsTableWidget->horizontalHeader()->setDefaultSectionSize(80);
            m_assetsTableWidget->verticalHeader()->hide();
            m_assetsTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            m_assetsTableWidget->verticalHeader()->setMinimumSectionSize(20);
            m_assetsTableWidget->verticalHeader()->setDefaultSectionSize(20);
            m_assetsTableWidget->setShowGrid(false);
            m_assetsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            m_assetsTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

            connect(m_filterAssetsLineEdit, &QLineEdit::textChanged, this, &SceneFileWidget::updateFilter);
            connect(m_filterTypesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SceneFileWidget::updateFilter);
            connect(m_assetsTableWidget, &QTableWidget::itemSelectionChanged, this, &SceneFileWidget::onItemSelectionChanged);

            QVBoxLayout* mainLayout = new QVBoxLayout;

            QHBoxLayout* hbox1 = new QHBoxLayout;
            hbox1->addWidget(m_createAssetButton);
            hbox1->addWidget(m_filterAssetsLineEdit, 1);

            QHBoxLayout* hbox2 = new QHBoxLayout;
            hbox2->addWidget(new QLabel("Filter by type:"));
            hbox2->addWidget(m_filterTypesComboBox, 1);

            //mainLayout->setContentsMargins(0, 0, 0, 0);
            mainLayout->addLayout(hbox1);
            mainLayout->addLayout(hbox2);
            mainLayout->addWidget(m_assetsTableWidget, 1);

            setLayout(mainLayout);
        }

        void SceneFileWidget::setFile(Core::SceneFile* file)
        {
            m_file = file;

            m_filterAssetsLineEdit->clear();
            m_filterTypesComboBox->clear();
            m_assetsTableWidget->clearContents();

            if (file)
            {
                HipHop::File& hiphop = file->hipHopFile();
                auto assets = hiphop.GetAssets();
                QStringList assetTypes;

                for (auto asset : assets)
                {
                    QString type = getAssetTypeName(asset);

                    if (!assetTypes.contains(type))
                    {
                        assetTypes.append(type);
                    }
                }

                assetTypes.sort(Qt::CaseInsensitive);

                m_filterTypesComboBox->addItem("All");
                m_filterTypesComboBox->addItems(assetTypes);

                m_assetsTableWidget->setSortingEnabled(false);
                m_assetsTableWidget->setUpdatesEnabled(false);

                m_assetsTableWidget->setRowCount(hiphop.GetAssetCount());

                for (int i = 0; i < (int)assets.size(); i++)
                {
                    auto asset = assets[i];

                    QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(asset.GetName()));
                    QTableWidgetItem* typeItem = new QTableWidgetItem(getAssetTypeName(asset));

                    nameItem->setData(Qt::UserRole, (uint32_t)asset.GetID());
                    typeItem->setData(Qt::UserRole, (uint32_t)asset.GetType());

                    m_assetsTableWidget->setItem(i, 0, nameItem);
                    m_assetsTableWidget->setItem(i, 1, typeItem);
                }

                m_assetsTableWidget->setSortingEnabled(true);
                m_assetsTableWidget->setUpdatesEnabled(true);
            }

            m_assetsTableWidget->sortItems(0);
            m_assetsTableWidget->sortItems(1);
        }

        void SceneFileWidget::updateFilter()
        {
            QString nameFilter = m_filterAssetsLineEdit->text();
            QString typeFilter = m_filterTypesComboBox->currentText();
            bool shouldFilterName = (!nameFilter.isEmpty());
            bool shouldFilterTypes = (m_filterTypesComboBox->currentIndex() != 0);

            for (int i = 0; i < m_assetsTableWidget->rowCount(); i++)
            {
                QTableWidgetItem* nameItem = m_assetsTableWidget->item(i, 0);
                QTableWidgetItem* typeItem = m_assetsTableWidget->item(i, 1);
                bool filtered = false;

                if (shouldFilterName && !nameItem->text().contains(nameFilter, Qt::CaseInsensitive))
                {
                    filtered = true;
                }

                if (shouldFilterTypes && typeItem->text() != typeFilter)
                {
                    filtered = true;
                }

                m_assetsTableWidget->setRowHidden(i, filtered);
            }
        }

        void SceneFileWidget::onItemSelectionChanged()
        {
            m_selectedAssets.clear();

            auto items = m_assetsTableWidget->selectedItems();

            for (auto item : items)
            {
                if (item->column() == 0)
                {
                    uint32_t assetID = item->data(Qt::UserRole).toUInt();
                    Core::Asset* asset = m_file->asset(assetID);

                    m_selectedAssets.append(asset);
                }
            }

            emit assetsSelected(m_selectedAssets);
        }

    }

}
