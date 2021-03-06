#include "tools/hashgenerator.h"

#include "util/stringutils.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>

#include "hiphop.h"

namespace Slick {

    namespace Tools {

        HashGenerator::HashGenerator(QWidget* parent, Qt::WindowFlags f) :
            QDialog(parent, f),
            m_textLineEdit(new QLineEdit),
            m_hashLineEdit(new QLineEdit),
            m_addToLookupTableButton(new QPushButton(tr("Add to Lookup Table...")))
        {
            setWindowTitle(tr("Hash Generator"));
            setWindowFlag(Qt::WindowContextHelpButtonHint, false);

            QLabel* textLabel = new QLabel("Text:");
            QLabel* hashLabel = new QLabel("Hash:");
            QPushButton* hashCopyButton = new QPushButton(tr("Copy"));
            QDialogButtonBox* buttonBox = new QDialogButtonBox;
            QPushButton* closeButton = buttonBox->addButton(tr("Close"), QDialogButtonBox::AcceptRole);
            QVBoxLayout* mainLayout = new QVBoxLayout;
            QHBoxLayout* hashLayout = new QHBoxLayout;

            m_hashLineEdit->setReadOnly(true);

            connect(m_textLineEdit, &QLineEdit::textChanged, this, &HashGenerator::textChanged);
            connect(hashCopyButton, &QPushButton::clicked, this, [=]
            {
                m_hashLineEdit->selectAll();
                m_hashLineEdit->copy();
            });

            connect(closeButton, &QPushButton::clicked, this, [=]
            {
                accept();
            });

            hashLayout->addWidget(m_hashLineEdit, 1);
            hashLayout->addWidget(hashCopyButton, 0);
            //hashLayout->addWidget(m_addToLookupTableButton);

            mainLayout->addWidget(textLabel);
            mainLayout->addWidget(m_textLineEdit);
            mainLayout->addWidget(hashLabel);
            mainLayout->addLayout(hashLayout);
            mainLayout->addSpacing(16);
            mainLayout->addStretch(1);
            mainLayout->addWidget(buttonBox, 0, Qt::AlignBottom);

            setLayout(mainLayout);

            textChanged(m_textLineEdit->text());
        }

        void HashGenerator::textChanged(const QString& text)
        {
            m_hashLineEdit->setText(Util::hexToString(HipHop::Util::Hash(text.toStdString())));
        }

    }

}
