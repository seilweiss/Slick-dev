#include "Assets/TextAsset.h"

namespace Slick {

    namespace Assets {

        TextAsset::TextAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_text(asset)
        {
            m_text.Load();

            auto textGroup = inspector()->addGroup("text");
            auto textProp = textGroup->addString("text", &m_text.text);

            textProp->setNameVisible(false);
            textProp->setMultiline(true);
            textProp->setMonospace(true);

            connect(textProp, &InspectorProperty::dataChanged, this, &TextAsset::makeDirty);
        }

        void TextAsset::doSave()
        {
            m_text.Save();
        }

    }

}
