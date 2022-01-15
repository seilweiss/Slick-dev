#include "assets/textasset.h"

namespace Slick {

    namespace Assets {

        TextAsset::TextAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_text(asset)
        {
            setSerializer(&m_text);
        }

        void TextAsset::inspect(Inspector::Root* root)
        {
            Core::Asset::inspect(root);

            auto textGroup = root->addGroup("text", tr("Text"));
            auto textProp = textGroup->addTextInput("text", tr("Text"), &m_text.text);

            textProp->setNameVisible(false);
            textProp->setMultiline(true);
            textProp->setMonospace(true);
            textProp->setHelpText(tr("The text."));

            connect(textProp, &Inspector::Property::dataChanged, this, &TextAsset::makeDirty);
        }

    }

}
