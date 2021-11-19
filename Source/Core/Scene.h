#pragma once

#include "Core/SceneFile.h"

#include <QObject>

namespace Slick {

    class Scene : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(HipHop::Game game READ game WRITE setGame)
        Q_PROPERTY(HipHop::Platform platform READ platform WRITE setPlatform)
        Q_PROPERTY(HipHop::Language language READ language WRITE setLanguage)
        Q_PROPERTY(HipHop::Region region READ region WRITE setRegion)

    public:
        Scene(QObject* parent = nullptr);

        HipHop::Game game() const { return m_game; }
        void setGame(HipHop::Game game) { m_game = game; }

        HipHop::Platform platform() const { return m_platform; }
        void setPlatform(HipHop::Platform platform) { m_platform = platform; }

        HipHop::Language language() const { return m_language; }
        void setLanguage(HipHop::Language language) { m_language = language; }

        HipHop::Region region() const { return m_region; }
        void setRegion(HipHop::Region region) { m_region = region; }

        int fileCount() const { return m_files.size(); }
        SceneFile* file(int index) { return m_files[index]; }
        void addFile(SceneFile* file);

        bool load();

    private:
        QList<SceneFile*> m_files;
        HipHop::Game m_game;
        HipHop::Platform m_platform;
        HipHop::Language m_language;
        HipHop::Region m_region;
    };

}
