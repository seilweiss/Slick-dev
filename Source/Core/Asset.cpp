#include "Core/Asset.h"

#include "Core/SceneFile.h"

#include <QDebug>

namespace Slick {

    namespace {

        class AssetNameProxy : public InspectorProxy<QString>
        {
        public:
            AssetNameProxy(HipHop::Asset& asset) : InspectorProxy(nullptr), m_asset(asset) {}

            virtual QString data() const override { return QString::fromStdString(m_asset.GetName()); }
            virtual void setData(const QString& data) const { m_asset.SetName(data.toStdString()); }

        private:
            HipHop::Asset& m_asset;
        };

    }

    Asset::Asset(HipHop::Asset asset, SceneFile* sceneFile) :
        QObject(sceneFile),
        m_file(sceneFile),
        m_scene(sceneFile->scene()),
        m_asset(asset),
        m_editor(nullptr),
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
        preLoad();

        if (m_editor)
        {
            m_editor->Load();
        }

        postLoad();

        m_dirty = false;
    }

    void Asset::save()
    {
        preSave();

        if (m_editor)
        {
            m_editor->Save();
        }

        postSave();

        m_dirty = false;
    }

    void Asset::inspect(Inspector* inspector)
    {
        auto assetGroup = inspector->addGroup("asset", tr("Asset"));
        auto nameProp = assetGroup->addTextInput("name", tr("Name"), new AssetNameProxy(m_asset));

        assetGroup->setNameVisible(false);
        nameProp->setNameVisible(false);

        connect(nameProp, &InspectorProperty::dataChanged, this, &Asset::makeDirty);
    }

}
