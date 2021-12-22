#include "InspectorProperties/EventInputProperty.h"

#include "Core/Scene.h"
#include "Core/Util.h"

#include <QHBoxLayout>
#include <QFrame>
#include <QToolButton>

namespace Slick {

    namespace {

        QWidget* createEventInput(const QList<InspectorProperty*>& props)
        {
            QFrame* frame = new QFrame;
            QHBoxLayout* layout = new QHBoxLayout;
            QToolButton* eventButton = new QToolButton;
            QToolButton* selectButton = new QToolButton;

            frame->setFrameStyle(QFrame::StyledPanel);
            frame->setStyleSheet("QFrame { background-color: white; }");
            frame->setLayout(layout);

            layout->setContentsMargins(0, 0, 0, 0);
            layout->setSpacing(0);

            layout->addWidget(eventButton, 1);
            layout->addWidget(selectButton);

            eventButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
            eventButton->setStyleSheet("QToolButton:!hover:!pressed { border: 0; background-color: transparent; }");

            selectButton->setText("...");

            int eventID = props[0]->dataSource().data<int>();
            bool match = true;

            for (int i = 1; i < props.size(); i++)
            {
                int data = props[i]->dataSource().data<int>();

                if (data != eventID)
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                QString eventName = QString::fromStdString(HipHop::EventToString(eventID, ((EventInputProperty*)props[0])->scene()->game()));

                eventButton->setText(eventName);
            }

            return frame;
        }

    }

    QWidget* EventInputProperty::createWidget(const QList<InspectorProperty*>& props)
    {
        return createEventInput(props);
    }

}
