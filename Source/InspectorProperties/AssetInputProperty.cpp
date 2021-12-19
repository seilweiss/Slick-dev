#include "InspectorProperties/AssetInputProperty.h"

#include "Core/Scene.h"

#include <QLineEdit>

namespace Slick {

    namespace {

        QWidget* createAssetInput(const QList<InspectorProperty*>& props)
        {
            QLineEdit* lineEdit = new QLineEdit;
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

            lineEdit->setReadOnly(true);

            if (match)
            {
                Asset* asset = ((AssetInputProperty*)props[0])->scene()->asset(assetID);

                if (asset)
                {
                    lineEdit->setText(asset->name());
                }
            }

            return lineEdit;
        }

    }

    QWidget* AssetInputProperty::createWidget(const QList<InspectorProperty*>& props)
    {
        return createAssetInput(props);
    }

}
