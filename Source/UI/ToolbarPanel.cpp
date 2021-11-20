#include "UI/ToolbarPanel.h"

#include <QHBoxLayout>
#include <QPushButton>

namespace Slick {

    ToolbarPanel::ToolbarPanel(QWidget* parent) :
        QWidget(parent),
        //m_playButton(new QPushButton("▶"))
        m_playButton(new QPushButton(tr("Play")))
    {
        //m_playButton->setStyleSheet("QPushButton { font-size: 16px; }");

        QHBoxLayout* mainLayout = new QHBoxLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->addStretch(1);
        mainLayout->addWidget(m_playButton);
        mainLayout->addStretch(1);

        setLayout(mainLayout);
    }

}
