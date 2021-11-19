#pragma once

#include "hiphop.h"

#include <QObject>

namespace Slick {

    class SceneFile : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString path READ path WRITE setPath)
        Q_PROPERTY(HipHop::File hipHopFile READ hipHopFile)
        Q_PROPERTY(HipHop::FileStream hipHopStream READ hipHopStream)
        Q_PROPERTY(HipHop::Game game READ game WRITE setGame)
        Q_PROPERTY(HipHop::Platform platform READ platform WRITE setPlatform)
        Q_PROPERTY(HipHop::Language language READ language WRITE setLanguage)
        Q_PROPERTY(HipHop::Region region READ region WRITE setRegion)

    public:
        SceneFile(QObject* parent = nullptr);

        QString path() const { return m_path; }
        void setPath(const QString& path) { m_path = path; }

        HipHop::File& hipHopFile() { return m_file; };
        HipHop::FileStream& hipHopStream() { return m_stream; }

        HipHop::Game game() const { return m_game; }
        void setGame(HipHop::Game game) { m_game = game; }

        HipHop::Platform platform() const { return m_platform; }
        void setPlatform(HipHop::Platform platform) { m_platform = platform; }

        HipHop::Language language() const { return m_language; }
        void setLanguage(HipHop::Language language) { m_language = language; }

        HipHop::Region region() const { return m_region; }
        void setRegion(HipHop::Region region) { m_region = region; }

        bool load();

    private:
        QString m_path;
        HipHop::File m_file;
        HipHop::FileStream m_stream;
        HipHop::Game m_game;
        HipHop::Platform m_platform;
        HipHop::Language m_language;
        HipHop::Region m_region;
    };

}
