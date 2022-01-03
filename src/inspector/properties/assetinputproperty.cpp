#include "inspector/properties/assetinputproperty.h"

#include "core/scene.h"
#include "util/stringutils.h"

#include <QHBoxLayout>
#include <QFrame>
#include <QToolButton>

namespace Slick {

    namespace Inspector {

        namespace {

            QWidget* createAssetInput(const QList<Property*>& props)
            {
                QFrame* frame = new QFrame;
                QHBoxLayout* layout = new QHBoxLayout;
                QToolButton* assetButton = new QToolButton;
                QToolButton* selectButton = new QToolButton;

                frame->setFrameStyle(QFrame::StyledPanel);
                frame->setStyleSheet("QFrame { background-color: white; }");
                frame->setLayout(layout);

                layout->setContentsMargins(0, 0, 0, 0);
                layout->setSpacing(0);

                layout->addWidget(assetButton, 1);
                layout->addWidget(selectButton);

                assetButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
                assetButton->setStyleSheet("QToolButton:!hover:!pressed { border: 0; background-color: transparent; }");

                selectButton->setText("...");

                uint32_t assetID = props[0]->dataSource().data<uint32_t>();
                bool match = true;

                for (int i = 1; i < props.size(); i++)
                {
                    uint32_t data = props[i]->dataSource().data<uint32_t>();

                    if (data != assetID)
                    {
                        match = false;
                        break;
                    }
                }

                if (match)
                {
                    if (assetID == 0)
                    {
                        assetButton->setText(QObject::tr("<None>"));
                    }
                    else
                    {
                        Core::Asset* asset = ((AssetInputProperty*)props[0])->scene()->assetById(assetID);

                        assetButton->setText(asset ? asset->name() : Util::hexToString(assetID));
                    }
                }

                return frame;
            }

        }

        QWidget* AssetInputProperty::createWidget(const QList<Property*>& props)
        {
            return createAssetInput(props);
        }

    }

}
