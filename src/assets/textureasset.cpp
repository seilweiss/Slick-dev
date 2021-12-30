#include "assets/textureasset.h"

#include "core/scene.h"

namespace Slick {

    namespace Assets {

        TextureAsset::TextureAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Core::Asset(asset, sceneFile),
            m_textureAsset(asset),
            m_texture(Render::Texture(scene()->renderContext()))
        {
            setEditor(&m_textureAsset);
        }

        void TextureAsset::setup()
        {
            Rws::TexDictionary* texDict = m_textureAsset.GetTexDictionary();

            if (texDict)
            {
                m_texture.setData(texDict->GetTextureNative(0));
            }
        }

        void TextureAsset::bind()
        {
            m_texture.bind();
        }

        void TextureAsset::unbind()
        {
            m_texture.unbind();
        }

        void TextureAsset::inspect(Inspector::Root* root)
        {
            Asset::inspect(root);

            root->addGroup("texture", tr("Texture"));
        }

        void TextureManager::setup()
        {
            for (auto asset : assets())
            {
                ((TextureAsset*)asset)->setup();
            }
        }

    }

}
