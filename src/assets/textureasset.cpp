#include "assets/textureasset.h"

#include "assets/texturepreview.h"
#include "core/scene.h"

namespace Slick {

    namespace Assets {

        TextureAsset::TextureAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Core::Asset(asset, sceneFile),
            m_textureAsset(asset),
            m_texture(Render::Texture(scene()->renderContext())),
            m_info()
        {
            setEditor(&m_textureAsset);
        }

        void TextureAsset::setup()
        {
            Rws::TexDictionary* texDict = m_textureAsset.GetTexDictionary();

            if (texDict)
            {
                m_texture.setData(texDict->GetTextureNative(0));
                //m_texture.setFilterMode(Rws::FILTER_LINEARMIPLINEAR);
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

            Rws::TextureNative* data = m_texture.data();

            if (data && m_info.isEmpty())
            {
                QString format;
                QString palette;
                QString mipmapLevels;

                switch (data->rasterFormat & Rws::RASTERFORMAT_PIXELFORMATMASK)
                {
                case Rws::RASTERFORMAT_DEFAULT: format = "Default"; break;
                case Rws::RASTERFORMAT_1555: format = "1555"; break;
                case Rws::RASTERFORMAT_565: format = "565"; break;
                case Rws::RASTERFORMAT_4444: format = "4444"; break;
                case Rws::RASTERFORMAT_LUM8: format = "LUM8"; break;
                case Rws::RASTERFORMAT_8888: format = "8888"; break;
                case Rws::RASTERFORMAT_888: format = "888"; break;
                case Rws::RASTERFORMAT_16: format = "16"; break;
                case Rws::RASTERFORMAT_24: format = "24"; break;
                case Rws::RASTERFORMAT_32: format = "32"; break;
                case Rws::RASTERFORMAT_555: format = "555"; break;
                default: format = "Unknown"; break;
                }

                if (data->rasterFormat & Rws::RASTERFORMAT_PAL8)
                {
                    palette = "PAL8";
                }
                else if (data->rasterFormat & Rws::RASTERFORMAT_PAL4)
                {
                    palette = "PAL4";
                }
                else
                {
                    palette = "None";
                }

                if (data->rasterFormat & Rws::RASTERFORMAT_AUTOMIPMAP)
                {
                    mipmapLevels = "Auto";
                }
                else if (data->rasterFormat & Rws::RASTERFORMAT_MIPMAP)
                {
                    mipmapLevels = "Unknown"; // TODO: Replace with actual mipmap count
                }
                else
                {
                    mipmapLevels = "None";
                }

                m_info = tr("Size: %1x%2\n"
                            "Depth: %3\n"
                            "Format: %4\n"
                            "Palette: %5\n"
                            "Mipmap Levels: %6")
                         .arg(data->width)
                         .arg(data->height)
                         .arg(data->depth)
                         .arg(format)
                         .arg(palette)
                         .arg(mipmapLevels);
            }

            auto textureGroup = root->addGroup("texture", tr("Texture"));
            auto infoProp = textureGroup->addLabel("info", tr("Info"), &m_info);

            infoProp->setNameVisible(false);
            infoProp->setExclusive(true);

            if (data)
            {
                auto filterModeProp = textureGroup->addComboBox("filterMode", tr("Filter Mode"), (int32_t*)&data->filtering, {
                                                                   tr("N/A"),
                                                                   tr("Nearest"),
                                                                   tr("Linear"),
                                                                   tr("Mip Nearest"),
                                                                   tr("Mip Linear"),
                                                                   tr("Linear Mip Nearest"),
                                                                   tr("Linear Mip Linear")
                                                               });
                auto addressUProp = textureGroup->addComboBox("addressModeU", tr("Address Mode (U)"), (int32_t*)&data->addressingU, {
                                                                 tr("N/A"),
                                                                 tr("Wrap"),
                                                                 tr("Mirror"),
                                                                 tr("Clamp"),
                                                                 tr("Border")
                                                             });
                auto addressVProp = textureGroup->addComboBox("addressModeV", tr("Address Mode (V)"), (int32_t*)&data->addressingV, {
                                                                 tr("N/A"),
                                                                 tr("Wrap"),
                                                                 tr("Mirror"),
                                                                 tr("Clamp"),
                                                                 tr("Border")
                                                             });

                connect(filterModeProp, &Inspector::Property::dataChanged, this, [=]
                {
                    m_texture.setFilterMode(data->filtering);
                    makeDirty();
                });

                connect(addressUProp, &Inspector::Property::dataChanged, this, [=]
                {
                    m_texture.setAddressingU(data->addressingU);
                    makeDirty();
                });

                connect(addressVProp, &Inspector::Property::dataChanged, this, [=]
                {
                    m_texture.setAddressingV(data->addressingV);
                    makeDirty();
                });
            }
        }

        QWidget* TextureAsset::createPreview()
        {
            TexturePreview* preview = new TexturePreview(this);
            QWidget* container = QWidget::createWindowContainer(preview);
            container->setMinimumHeight(256);

            return container;
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
