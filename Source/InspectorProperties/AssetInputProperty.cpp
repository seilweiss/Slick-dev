#include "InspectorProperties/AssetInputProperty.h"

#include "Core/Scene.h"
#include "Core/Util.h"

#include <QHBoxLayout>
#include <QFrame>
#include <QToolButton>

namespace Slick {

    namespace {

        QWidget* createAssetInput(const QList<InspectorProperty*>& props)
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
                    Asset* asset = ((AssetInputProperty*)props[0])->scene()->asset(assetID);

                    assetButton->setText(asset ? asset->name() : Util::hexToString(assetID));
                }
            }

            return frame;
        }

    }

    QWidget* AssetInputProperty::createWidget(const QList<InspectorProperty*>& props)
    {
        return createAssetInput(props);
    }

}
