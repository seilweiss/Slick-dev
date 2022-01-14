#include "assets/egenasset.h"

#include "core/scene.h"

#include <glm/glm.hpp>

namespace Slick {

    namespace Assets {

        EGenAsset::EGenAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_egen(asset)
        {
            setEditor(&m_egen);
        }

        void EGenAsset::setup()
        {
            EntAsset::setup();
        }

        void EGenAsset::update()
        {
            EntAsset::update();
        }

        void EGenAsset::render()
        {
            EntAsset::render();
        }

        void EGenAsset::inspect(Inspector::Root* root)
        {
            EntAsset::inspect(root);

            auto egenGroup = root->addGroup("electricArcGenerator", tr("Electric Arc Generator"));
            auto sourceOffsetProp = egenGroup->addVectorInput("sourceOffset", tr("Source Offset"), (Core::Vector3*)&m_egen.src_dpos);
            auto damageTypeProp = egenGroup->addNumberInput("damageType", tr("Damage Type"), &m_egen.damage_type);
            auto flagsProp = egenGroup->addNumberInput("flags", tr("Flags"), &m_egen.flags);
            auto onTimeProp = egenGroup->addNumberInput("onTime", tr("On Time"), &m_egen.ontime);
            auto onAnimProp = egenGroup->addAssetInput("onAnim", tr("On Anim"), &m_egen.onAnimID, scene());

            connect(sourceOffsetProp, &Inspector::Property::dataChanged, this, &EGenAsset::makeDirty);
            connect(damageTypeProp, &Inspector::Property::dataChanged, this, &EGenAsset::makeDirty);
            connect(flagsProp, &Inspector::Property::dataChanged, this, &EGenAsset::makeDirty);
            connect(onTimeProp, &Inspector::Property::dataChanged, this, &EGenAsset::makeDirty);
            connect(onAnimProp, &Inspector::Property::dataChanged, this, &EGenAsset::makeDirty);

            inspectEntity(root);
            inspectLinks(root);
        }

        void EGenManager::setup()
        {
            for (auto asset : assets())
            {
                ((EGenAsset*)asset)->setup();
            }
        }

        void EGenManager::update()
        {
            for (auto asset : assets())
            {
                ((EGenAsset*)asset)->update();
            }
        }

        void EGenManager::render()
        {
            for (auto asset : assets())
            {
                ((EGenAsset*)asset)->render();
            }
        }

    }

}
