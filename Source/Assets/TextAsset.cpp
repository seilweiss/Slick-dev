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

            auto textGroup = inspector->addGroup("text");
            auto textProp = textGroup->addTextInput("text", &m_text.text);

            textProp->setNameVisible(false);
            textProp->setMultiline(true);
            textProp->setMonospace(true);

            connect(textProp, &InspectorProperty::dataChanged, this, &TextAsset::makeDirty);
        }

    }

}
