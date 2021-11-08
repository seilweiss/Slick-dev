#include "UI/OpenSceneDialog.h"

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QApplication>

namespace Slick {

    inline static QString getHipHopFilename(OpenSceneDialog* parent)
    {
        return QFileDialog::getOpenFileName(parent, parent->tr("Select HIP/HOP file"), QString(), "HIP/HOP files (*.hip *.hop)");
    }

    OpenSceneDialog::HipHopGroup::HipHopGroup(OpenSceneDialog* dialog, const QString& text) :
        layout(new QHBoxLayout),
        checkBox(new QCheckBox),
        label(new QLabel(text)),
        lineEdit(new QLineEdit),
        browseButton(new QPushButton(tr("Browse..."))),
        valid(true)
    {
        connect(checkBox, &QCheckBox::stateChanged, dialog, &OpenSceneDialog::updateWidgets);
        connect(lineEdit, &QLineEdit::textChanged, dialog, &OpenSceneDialog::updateWidgets);
        connect(browseButton, &QPushButton::clicked, dialog, &OpenSceneDialog::browse);

        layout->addWidget(checkBox);
        layout->addWidget(label);
        layout->addWidget(lineEdit, 1);
        layout->addWidget(browseButton);
    }

    void OpenSceneDialog::HipHopGroup::update()
    {
        lineEdit->setEnabled(checkBox->isChecked());
        browseButton->setEnabled(checkBox->isChecked());

        valid = (!checkBox->isChecked() || (!lineEdit->text().isEmpty() && QFileInfo::exists(lineEdit->text())));

        label->setStyleSheet((valid || lineEdit->text().isEmpty()) ? "" : "QLabel { color: red }");
    }

    void OpenSceneDialog::HipHopGroup::setPath(const QString& path)
    {
        if (QFileInfo::exists(path))
        {
            checkBox->setChecked(true);
            lineEdit->setText(QFileInfo(path).absoluteFilePath());
        }
        else
        {
            checkBox->setChecked(false);
            lineEdit->setText(QString());
        }
    }

    OpenSceneDialog::InfoGroup::InfoGroup(OpenSceneDialog* dialog, const QString& text) :
        layout(new QHBoxLayout),
        label(new QLabel(text)),
        comboBox(new QComboBox),
        valid(true)
    {
        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), dialog, &OpenSceneDialog::updateWidgets);

        layout->addWidget(label);
        layout->addWidget(comboBox, 1);
    }

    void OpenSceneDialog::InfoGroup::update()
    {
        valid = (comboBox->currentIndex() != -1);

        label->setStyleSheet(valid ? "" : "QLabel { color: red }");
    }

    OpenSceneDialog::LocGroup::LocGroup(OpenSceneDialog* dialog, const QString& text) :
        dialog(dialog),
        layout(new QVBoxLayout),
        label(new QLabel(text)),
        tableWidget(new QTableWidget(0, 2)),
        addButton(new QPushButton(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton), QString())),
        removeButton(new QPushButton(QApplication::style()->standardIcon(QStyle::SP_DialogCancelButton), QString())),
        valid(true)
    {
        tableWidget->setMinimumHeight(100);
        tableWidget->horizontalHeader()->hide();
        tableWidget->verticalHeader()->hide();
        tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        tableWidget->verticalHeader()->setMinimumSectionSize(-1);
        tableWidget->verticalHeader()->setDefaultSectionSize(0);
        tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

        connect(tableWidget, &QTableWidget::itemChanged, dialog, &OpenSceneDialog::updateWidgets);

        connect(addButton, &QPushButton::clicked, [=]
        {
            QString path = getHipHopFilename(dialog);

            if (!path.isEmpty())
            {
                addPath(path);
                dialog->updateWidgets();
            }
        });

        connect(removeButton, &QPushButton::clicked, [=]
        {
            for (QTableWidgetItem* item : tableWidget->selectedItems())
            {
                tableWidget->removeRow(item->row());
                dialog->updateWidgets();
            }
        });

        QHBoxLayout* topBar = new QHBoxLayout;

        topBar->addWidget(label, 1);
        topBar->addWidget(addButton);
        topBar->addWidget(removeButton);

        layout->addLayout(topBar);
        layout->addWidget(tableWidget, 1);
    }

    void OpenSceneDialog::LocGroup::update()
    {
        valid = true;

        for (int i = 0; i < tableWidget->rowCount(); i++)
        {
            if (!QFileInfo::exists(tableWidget->item(i, 0)->text()))
            {
                valid = false;
                break;
            }
        }

        label->setStyleSheet(valid ? "" : "QLabel { color: red }");
    }

    void OpenSceneDialog::LocGroup::addPath(const QString& path)
    {
        Item item = createItem(path);
        int end = tableWidget->rowCount();

        tableWidget->insertRow(end);
        tableWidget->setItem(end, 0, item.pathItem);
        tableWidget->setCellWidget(end, 1, item.browseButton);
    }

    void OpenSceneDialog::LocGroup::setPaths(const QStringList& paths)
    {
        tableWidget->clear();
        tableWidget->setRowCount(paths.size());

        for (int i = 0; i < paths.size(); i++)
        {
            Item item = createItem(paths[i]);

            tableWidget->setItem(i, 0, item.pathItem);
            tableWidget->setCellWidget(i, 1, item.browseButton);
        }
    }

    OpenSceneDialog::LocGroup::Item OpenSceneDialog::LocGroup::createItem(const QString& path)
    {
        Item item;
        item.pathItem = new QTableWidgetItem(path);
        item.browseButton = new QPushButton("...");

        connect(item.browseButton, &QPushButton::clicked, [=]
        {
            QString path = getHipHopFilename(dialog);

            if (!path.isEmpty())
            {
                // BUG?: item might get invalidated when new items are added
                item.pathItem->setText(path);
            }
        });

        return item;
    }

    OpenSceneDialog::OpenSceneDialog(QWidget* parent, Qt::WindowFlags f) :
        QDialog(parent, f),
        m_hip(this, tr(".HIP file:")),
        m_hop(this, tr(".HOP file:")),
        m_loc(this, tr("Localization .HIP files:")),
        m_game(this, tr("Game:")),
        m_platform(this, tr("Platform:")),
        m_language(this, tr("Language:")),
        m_region(this, tr("Region")),
        m_sceneName(),
        m_okButton(new QPushButton(tr("OK"))),
        m_cancelButton(new QPushButton(tr("Cancel"))),
        m_dontUpdateWidgets(false)
    {
        setWindowTitle(tr("Open Scene"));
        setWindowFlag(Qt::WindowContextHelpButtonHint, false);

        resize(700, 0);

        m_hip.checkBox->setChecked(true);

        addGame(HipHop::Game::ScoobyNightOf100Frights);
        addGame(HipHop::Game::BattleForBikiniBottom);
        addGame(HipHop::Game::SpongeBobMovie);
        addGame(HipHop::Game::Incredibles);
        addGame(HipHop::Game::RiseOfTheUnderminer);

        addPlatform(HipHop::Platform::GameCube);
        addPlatform(HipHop::Platform::PS2);
        addPlatform(HipHop::Platform::Xbox);

        addLanguage(HipHop::Language::USCommon);
        addLanguage(HipHop::Language::UnitedKingdom);
        addLanguage(HipHop::Language::French);
        addLanguage(HipHop::Language::German);
        addLanguage(HipHop::Language::US);
        addLanguage(HipHop::Language::BE);
        addLanguage(HipHop::Language::CH);
        addLanguage(HipHop::Language::CZ);
        addLanguage(HipHop::Language::DE);
        addLanguage(HipHop::Language::DK);
        addLanguage(HipHop::Language::ES);
        addLanguage(HipHop::Language::FI);
        addLanguage(HipHop::Language::FR);
        addLanguage(HipHop::Language::IT);
        addLanguage(HipHop::Language::JP);
        addLanguage(HipHop::Language::KR);
        addLanguage(HipHop::Language::NL);
        addLanguage(HipHop::Language::NO);
        addLanguage(HipHop::Language::PL);
        addLanguage(HipHop::Language::PT);
        addLanguage(HipHop::Language::RU);
        addLanguage(HipHop::Language::SE);
        addLanguage(HipHop::Language::SK);
        addLanguage(HipHop::Language::TW);
        addLanguage(HipHop::Language::UK);

        addRegion(HipHop::Region::NTSC);
        addRegion(HipHop::Region::PAL);

        QHBoxLayout* gameAndPlatformLayout = new QHBoxLayout;
        gameAndPlatformLayout->addLayout(m_game.layout, 2);
        gameAndPlatformLayout->addLayout(m_platform.layout, 1);

        QHBoxLayout* languageAndRegionLayout = new QHBoxLayout;
        languageAndRegionLayout->addLayout(m_language.layout, 2);
        languageAndRegionLayout->addLayout(m_region.layout, 1);

        QDialogButtonBox* buttonBox = new QDialogButtonBox(Qt::Horizontal);
        buttonBox->addButton(m_okButton, QDialogButtonBox::AcceptRole);
        buttonBox->addButton(m_cancelButton, QDialogButtonBox::RejectRole);

        connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);

        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->setContentsMargins(24, 24, 24, 24);
        //mainLayout->addSpacing(16);
        mainLayout->addLayout(m_hip.layout);
        mainLayout->addLayout(m_hop.layout);
        mainLayout->addSpacing(16);
        mainLayout->addLayout(m_loc.layout);
        mainLayout->addSpacing(32);
        mainLayout->addLayout(gameAndPlatformLayout);
        mainLayout->addLayout(languageAndRegionLayout);
        mainLayout->addSpacing(32);
        mainLayout->addStretch(1);
        mainLayout->addWidget(buttonBox);

        setLayout(mainLayout);

        updateWidgets();
    }

    QString OpenSceneDialog::hipPath() const
    {
        return m_hip.lineEdit->text();
    }

    QString OpenSceneDialog::hopPath() const
    {
        return m_hop.lineEdit->text();
    }

    QStringList OpenSceneDialog::locHipPaths() const
    {
        QStringList paths;

        for (int i = 0; i < m_loc.tableWidget->rowCount(); i++)
        {
            paths.append(m_loc.tableWidget->item(i, 0)->text());
        }

        return paths;
    }

    HipHop::Game OpenSceneDialog::game() const
    {
        return (HipHop::Game)m_game.comboBox->currentData().toInt();
    }

    HipHop::Platform OpenSceneDialog::platform() const
    {
        return (HipHop::Platform)m_platform.comboBox->currentData().toInt();
    }

    HipHop::Language OpenSceneDialog::language() const
    {
        return (HipHop::Language)m_language.comboBox->currentData().toInt();
    }

    HipHop::Region OpenSceneDialog::region() const
    {
        return (HipHop::Region)m_region.comboBox->currentData().toInt();
    }

    void OpenSceneDialog::addGame(HipHop::Game game)
    {
        m_game.comboBox->addItem(tr(HipHop::GameToString(game).c_str()), (int)game);
    }

    void OpenSceneDialog::addPlatform(HipHop::Platform platform)
    {
        m_platform.comboBox->addItem(tr(HipHop::PlatformToString(platform).c_str()), (int)platform);
    }

    void OpenSceneDialog::addLanguage(HipHop::Language language)
    {
        m_language.comboBox->addItem(tr(HipHop::LanguageToString(language).c_str()), (int)language);
    }

    void OpenSceneDialog::addRegion(HipHop::Region region)
    {
        m_region.comboBox->addItem(tr(HipHop::RegionToString(region).c_str()), (int)region);
    }

    void OpenSceneDialog::accept()
    {
        if (m_loc.tableWidget->hasFocus())
        {
            return;
        }

        QDialog::accept();
    }

    void OpenSceneDialog::updateWidgets()
    {
        if (m_dontUpdateWidgets)
        {
            return;
        }

        m_hip.update();
        m_hop.update();
        m_loc.update();
        m_game.update();
        m_platform.update();
        m_language.update();
        m_region.update();

        bool valid =
                (m_hip.valid && m_hop.valid && m_loc.valid &&
                 m_game.valid && m_platform.valid && m_language.valid && m_region.valid &&
                 (m_hip.checkBox->isChecked() || m_hop.checkBox->isChecked()));

        m_okButton->setEnabled(valid);
    }

    void OpenSceneDialog::browse()
    {
        QString path = getHipHopFilename(this);

        if (!path.isEmpty())
        {
            // TODO: Support multiple extensions (e.g. .blah.hip)

            m_dontUpdateWidgets = true;

            QFileInfo info(path);
            QString name = info.completeBaseName();
            QString ext = info.suffix().toUpper();
            QString pathNoExt = info.path() + "/" + name;

            QString hipPath;
            QString hopPath;
            QStringList locHipPaths;

            if (ext == "HIP")
            {
                if (name.size() >= 3 &&
                        name.at(name.size() - 3) == '_' &&
                        HipHop::LanguageFromString(name.right(2).toStdString()) != HipHop::Language::Unknown)
                {
                    locHipPaths.append(path);

                    hipPath = pathNoExt.chopped(3) + ".HIP";
                    hopPath = pathNoExt.chopped(3) + ".HOP";

                    m_sceneName = name.chopped(3).toUpper();
                }
                else
                {
                    hipPath = path;
                    hopPath = pathNoExt + ".HOP";

                    m_sceneName = name.toUpper();
                }
            }
            else if (ext == "HOP")
            {
                hopPath = path;
                hipPath = pathNoExt + ".HIP";

                m_sceneName = name.toUpper();
            }

            if (locHipPaths.isEmpty())
            {
                for (auto i = HipHop::Language::US; i < HipHop::Language::Count; i = (HipHop::Language)((int)i + 1))
                {
                    QString path = pathNoExt + "_" + QString::fromStdString(HipHop::LanguageToString(i)) + ".HIP";

                    if (QFileInfo::exists(path))
                    {
                        locHipPaths.append(path);
                    }
                }
            }

            m_hip.setPath(hipPath);
            m_hop.setPath(hopPath);
            m_loc.setPaths(locHipPaths);

            {
                QString readPath = hipPath;

                if (readPath.isEmpty())
                {
                    readPath = hopPath;

                    if (readPath.isEmpty())
                    {
                        readPath = locHipPaths[0];
                    }
                }

                HipHop::File hipHopFile(readPath.toStdString());

                if (hipHopFile.Read())
                {
                    m_game.comboBox->setCurrentIndex(m_game.comboBox->findData((int)hipHopFile.GetGame()));
                    m_platform.comboBox->setCurrentIndex(m_platform.comboBox->findData((int)hipHopFile.GetPlatform()));
                    m_language.comboBox->setCurrentIndex(m_language.comboBox->findData((int)hipHopFile.GetLanguage()));
                    m_region.comboBox->setCurrentIndex(m_region.comboBox->findData((int)hipHopFile.GetRegion()));
                }
                else
                {
                    m_game.comboBox->setCurrentIndex(-1);
                    m_platform.comboBox->setCurrentIndex(-1);
                    m_language.comboBox->setCurrentIndex(-1);
                    m_region.comboBox->setCurrentIndex(-1);
                }
            }

            m_dontUpdateWidgets = false;
            updateWidgets();
        }
    }

}
