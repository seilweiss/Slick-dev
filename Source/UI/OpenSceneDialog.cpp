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

#include "hiphop.h"

namespace Slick {

    OpenSceneDialog::OpenSceneDialog(QWidget* parent, Qt::WindowFlags f) :
        QDialog(parent, f),
        m_hipCheckBox(new QCheckBox),
        m_hopCheckBox(new QCheckBox),
        m_hipPathLineEdit(new QLineEdit),
        m_hopPathLineEdit(new QLineEdit),
        m_hipBrowseButton(new QPushButton(tr("Browse..."))),
        m_hopBrowseButton(new QPushButton(tr("Browse..."))),
        m_gameComboBox(new QComboBox),
        m_platformComboBox(new QComboBox),
        m_languageComboBox(new QComboBox),
        m_regionComboBox(new QComboBox),
        m_okButton(new QPushButton(tr("OK"))),
        m_cancelButton(new QPushButton(tr("Cancel")))
    {
        setWindowTitle(tr("Open Scene"));
        setWindowFlag(Qt::WindowContextHelpButtonHint, false);

        resize(600, 0);

        m_hipCheckBox->setChecked(true);
        m_hopCheckBox->setChecked(true);

        connect(m_hipCheckBox, &QCheckBox::stateChanged, this, &OpenSceneDialog::updateWidgets);
        connect(m_hopCheckBox, &QCheckBox::stateChanged, this, &OpenSceneDialog::updateWidgets);
        connect(m_hipPathLineEdit, &QLineEdit::textChanged, this, &OpenSceneDialog::updateWidgets);
        connect(m_hopPathLineEdit, &QLineEdit::textChanged, this, &OpenSceneDialog::updateWidgets);
        connect(m_hipBrowseButton, &QPushButton::clicked, this, &OpenSceneDialog::getHipHopFilename);
        connect(m_hopBrowseButton, &QPushButton::clicked, this, &OpenSceneDialog::getHipHopFilename);

        m_gameComboBox->addItem(tr("Scooby-Doo! Night of 100 Frights"), (int)HipHop::Game::ScoobyNightOf100Frights);
        m_gameComboBox->addItem(tr("SpongeBob SquarePants: Battle for Bikini Bottom"), (int)HipHop::Game::BattleForBikiniBottom);
        m_gameComboBox->addItem(tr("The SpongeBob SquarePants Movie"), (int)HipHop::Game::SpongeBobMovie);
        m_gameComboBox->addItem(tr("The Incredibles"), (int)HipHop::Game::Incredibles);
        m_gameComboBox->addItem(tr("The Incredibles: Rise of the Underminer"), (int)HipHop::Game::RiseOfTheUnderminer);
        m_gameComboBox->setCurrentIndex(0);

        m_platformComboBox->addItem(tr("GameCube"), (int)HipHop::Platform::GameCube);
        m_platformComboBox->addItem(tr("PlayStation 2"), (int)HipHop::Platform::PS2);
        m_platformComboBox->addItem(tr("Xbox"), (int)HipHop::Platform::Xbox);
        m_platformComboBox->setCurrentIndex(0);

        m_languageComboBox->addItem(tr("US Common"), (int)HipHop::Language::USCommon);
        m_languageComboBox->addItem(tr("United Kingdom"), (int)HipHop::Language::UnitedKingdom);
        m_languageComboBox->addItem(tr("French"), (int)HipHop::Language::French);
        m_languageComboBox->addItem(tr("German"), (int)HipHop::Language::German);
        m_languageComboBox->addItem(tr("US"), (int)HipHop::Language::US);
        m_languageComboBox->addItem(tr("BE"), (int)HipHop::Language::BE);
        m_languageComboBox->addItem(tr("CH"), (int)HipHop::Language::CH);
        m_languageComboBox->addItem(tr("CZ"), (int)HipHop::Language::CZ);
        m_languageComboBox->addItem(tr("DE"), (int)HipHop::Language::DE);
        m_languageComboBox->addItem(tr("DK"), (int)HipHop::Language::DK);
        m_languageComboBox->addItem(tr("ES"), (int)HipHop::Language::ES);
        m_languageComboBox->addItem(tr("FI"), (int)HipHop::Language::FI);
        m_languageComboBox->addItem(tr("FR"), (int)HipHop::Language::FR);
        m_languageComboBox->addItem(tr("IT"), (int)HipHop::Language::IT);
        m_languageComboBox->addItem(tr("JP"), (int)HipHop::Language::JP);
        m_languageComboBox->addItem(tr("KR"), (int)HipHop::Language::KR);
        m_languageComboBox->addItem(tr("NL"), (int)HipHop::Language::NL);
        m_languageComboBox->addItem(tr("NO"), (int)HipHop::Language::NO);
        m_languageComboBox->addItem(tr("PL"), (int)HipHop::Language::PL);
        m_languageComboBox->addItem(tr("PT"), (int)HipHop::Language::PT);
        m_languageComboBox->addItem(tr("RU"), (int)HipHop::Language::RU);
        m_languageComboBox->addItem(tr("SE"), (int)HipHop::Language::SE);
        m_languageComboBox->addItem(tr("SK"), (int)HipHop::Language::SK);
        m_languageComboBox->addItem(tr("TW"), (int)HipHop::Language::TW);
        m_languageComboBox->addItem(tr("UK"), (int)HipHop::Language::UK);
        m_languageComboBox->setCurrentIndex(0);

        m_regionComboBox->addItem(tr("NTSC"), (int)HipHop::Region::NTSC);
        m_regionComboBox->addItem(tr("PAL"), (int)HipHop::Region::PAL);
        m_languageComboBox->setCurrentIndex(0);

        QHBoxLayout* hipLayout = new QHBoxLayout;
        hipLayout->addWidget(m_hipCheckBox);
        hipLayout->addWidget(new QLabel(tr(".HIP File:")));
        hipLayout->addWidget(m_hipPathLineEdit, 1);
        hipLayout->addWidget(m_hipBrowseButton);

        QHBoxLayout* hopLayout = new QHBoxLayout;
        hopLayout->addWidget(m_hopCheckBox);
        hopLayout->addWidget(new QLabel(tr(".HOP File:")));
        hopLayout->addWidget(m_hopPathLineEdit, 1);
        hopLayout->addWidget(m_hopBrowseButton);

        QHBoxLayout* gameAndPlatformLayout = new QHBoxLayout;
        gameAndPlatformLayout->addWidget(new QLabel(tr("Game:")));
        gameAndPlatformLayout->addWidget(m_gameComboBox, 2);
        gameAndPlatformLayout->addWidget(new QLabel(tr("Platform:")));
        gameAndPlatformLayout->addWidget(m_platformComboBox, 1);

        QHBoxLayout* languageAndRegionLayout = new QHBoxLayout;
        languageAndRegionLayout->addWidget(new QLabel(tr("Language:")));
        languageAndRegionLayout->addWidget(m_languageComboBox, 2);
        languageAndRegionLayout->addWidget(new QLabel(tr("Region:")));
        languageAndRegionLayout->addWidget(m_regionComboBox, 1);

        QDialogButtonBox* buttonBox = new QDialogButtonBox(Qt::Horizontal);
        buttonBox->addButton(m_okButton, QDialogButtonBox::AcceptRole);
        buttonBox->addButton(m_cancelButton, QDialogButtonBox::RejectRole);

        connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);

        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->addLayout(hipLayout);
        mainLayout->addLayout(hopLayout);
        mainLayout->addSpacing(32);
        mainLayout->addLayout(gameAndPlatformLayout);
        mainLayout->addLayout(languageAndRegionLayout);
        mainLayout->addSpacing(32);
        mainLayout->addStretch(1);
        mainLayout->addWidget(buttonBox);

        setLayout(mainLayout);

        updateWidgets();
    }

    void OpenSceneDialog::updateWidgets()
    {
        m_hipPathLineEdit->setEnabled(m_hipCheckBox->isChecked());
        m_hipBrowseButton->setEnabled(m_hipCheckBox->isChecked());

        m_hopPathLineEdit->setEnabled(m_hopCheckBox->isChecked());
        m_hopBrowseButton->setEnabled(m_hopCheckBox->isChecked());

        if ((m_hipCheckBox->isChecked() && m_hipPathLineEdit->text().isEmpty()) ||
            (m_hopCheckBox->isChecked() && m_hopPathLineEdit->text().isEmpty()) ||
            (!m_hipCheckBox->isChecked() && !m_hopCheckBox->isChecked()))
        {
            m_okButton->setEnabled(false);
        }
        else
        {
            m_okButton->setEnabled(true);
        }
    }

    void OpenSceneDialog::getHipHopFilename()
    {
        QString path = QFileDialog::getOpenFileName(this, tr("Select HIP/HOP file"), QString(), "HIP/HOP files (*.hip *.hop);;All files (*.*)");

        if (!path.isEmpty())
        {
            QFileInfo info(path);
            QString hipPath = info.path() + "/" + info.baseName() + ".HIP";
            QString hopPath = info.path() + "/" + info.baseName() + ".HOP";

            if (QFileInfo::exists(hipPath))
            {
                m_hipCheckBox->setChecked(true);
                m_hipPathLineEdit->setText(hipPath);
            }
            else
            {
                m_hipCheckBox->setChecked(false);
                m_hipPathLineEdit->setText(QString());
            }

            if (QFileInfo::exists(hopPath))
            {
                m_hopCheckBox->setChecked(true);
                m_hopPathLineEdit->setText(hopPath);
            }
            else
            {
                m_hopCheckBox->setChecked(false);
                m_hopPathLineEdit->setText(QString());
            }

            HipHop::File hipHopFile(path.toStdString());

            if (hipHopFile.Read())
            {
                m_gameComboBox->setCurrentIndex(m_gameComboBox->findData((int)hipHopFile.GetGame()));
                m_platformComboBox->setCurrentIndex(m_platformComboBox->findData((int)hipHopFile.GetPlatform()));
                m_languageComboBox->setCurrentIndex(m_languageComboBox->findData((int)hipHopFile.GetLanguage()));
                m_regionComboBox->setCurrentIndex(m_regionComboBox->findData((int)hipHopFile.GetRegion()));
            }
            else
            {
                m_gameComboBox->setCurrentIndex(0);
                m_platformComboBox->setCurrentIndex(0);
                m_languageComboBox->setCurrentIndex(0);
                m_regionComboBox->setCurrentIndex(0);
            }
        }
    }

}
