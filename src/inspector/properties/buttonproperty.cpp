#include "inspector/properties/buttonproperty.h"

#include <QPushButton>

namespace Slick {

    namespace Inspector {

        namespace {

            QWidget* createButton(const QList<Property*>& props)
            {
                QPushButton* button = new QPushButton;
                QString text = props[0]->dataSource().data<QString>();
                bool match = true;

                for (int i = 1; i < props.size(); i++)
                {
                    QString data = props[i]->dataSource().data<QString>();

                    if (data != text)
                    {
                        match = false;
                        break;
                    }
                }

                button->setText(match ? text : QString());

                QObject::connect(button, &QPushButton::clicked, [=]
                {
                    for (Property* prop : props)
                    {
                        ((ButtonProperty*)prop)->notifyClicked();
                    }
                });

                return button;
            }

        }

        QWidget* ButtonProperty::createWidget(const QList<Property*>& props)
        {
            return createButton(props);
        }

    }

}
