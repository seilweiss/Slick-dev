#include "assets/animlistasset.h"

namespace Slick {

    namespace Assets {

        namespace {

            class AnimListSource : public Inspector::AbstractListSource
            {
            public:
                AnimListSource(AnimListAsset* asset, uint32_t* list) :
                    m_asset(asset),
                    m_list(list),
                    m_count(0)
                {
                    while (m_count < 10 && m_list[m_count] != 0)
                    {
                        m_count++;
                    }
                }

                virtual int size() const override { return m_count; }
                virtual int max() const override { return 10; }

                virtual void add()
                {
                    if (m_count < max())
                    {
                        m_list[m_count++] = 0;
                    }
                }

                virtual void remove(int index)
                {
                    if (m_count > 0)
                    {
                        while (index < m_count - 1)
                        {
                            m_list[index] = m_list[index + 1];
                            index++;
                        }

                        m_list[m_count - 1] = 0;
                        m_count--;
                    }
                }

                virtual void createGroupItem(Inspector::Group* group, int index) override
                {
                    auto itemProp = group->addAssetInput(&m_list[index], m_asset->scene());

                    QObject::connect(itemProp, &Inspector::Property::dataChanged, m_asset, &AnimListAsset::makeDirty);
                }

            private:
                AnimListAsset* m_asset;
                uint32_t* m_list;
                int m_count;
            };

        }

        AnimListAsset::AnimListAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_animList(asset)
        {
            setEditor(&m_animList);
        }

        void AnimListAsset::inspect(Inspector::Root* root)
        {
            auto animListGroup = root->addGroup("animList", tr("Anim List"));
            auto animsGroup = animListGroup->addGroup("animations", tr("Animations"));

            animsGroup->setListSource(new AnimListSource(this, m_animList.ids));
        }

    }

}
