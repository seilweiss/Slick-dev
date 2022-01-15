#include "core/asset.h"

#include "core/scenefile.h"

#include <QDebug>

namespace Slick {

    namespace Core {

        namespace {

            class AssetNameProxy : public Inspector::Proxy<QString>
            {
            public:
                AssetNameProxy(HipHop::Asset& asset) : m_asset(asset) {}

                virtual QString data() const override { return QString::fromStdString(m_asset.GetName()); }
                virtual void setData(const QString& data) const override { m_asset.SetName(data.toStdString()); }

            private:
                HipHop::Asset& m_asset;
            };

        }

        Asset::Asset(HipHop::Asset asset, SceneFile* sceneFile) :
            QObject(sceneFile),
            Inspector::Object(),
            m_file(sceneFile),
            m_scene(sceneFile->scene()),
            m_asset(asset),
            m_serializer(nullptr),
            m_dirty(false)
        {
        }

        void Asset::makeDirty()
        {
            m_dirty = true;
            emit dirty();
            qDebug().noquote() << QString("%1 dirty").arg(name());
        }

        void Asset::load()
        {
            if (m_serializer)
            {
                m_serializer->Load();
            }

            m_dirty = false;
        }

        void Asset::save()
        {
            if (m_serializer)
            {
                m_serializer->Save();
            }

            m_dirty = false;
        }

        void Asset::inspect(Inspector::Root* root)
        {
            auto assetGroup = root->addGroup("asset", tr("Asset"));
            auto nameProp = assetGroup->addTextInput("name", tr("Name"), new AssetNameProxy(m_asset));

            assetGroup->setNameVisible(false);
            nameProp->setNameVisible(false);

            connect(nameProp, &Inspector::Property::dataChanged, this, &Asset::makeDirty);
        }

    }

}
