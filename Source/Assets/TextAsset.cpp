#include "Assets/TextAsset.h"

namespace Slick {

    namespace Assets {

        TextAsset::TextAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_text(asset)
        {
            setEditor(&m_text);
        }

        void TextAsset::inspect(Inspector* inspector)
        {
            Asset::inspect(inspector);

            auto textGroup = inspector->addGroup("text", tr("Text"));
            auto textProp = textGroup->addTextInput("text", tr("Text"), &m_text.text);

            textProp->setNameVisible(false);
            textProp->setMultiline(true);
            textProp->setMonospace(true);
            textProp->setHelpText(tr("The text."));

            connect(textProp, &InspectorProperty::dataChanged, this, &TextAsset::makeDirty);
        }

    }

}
