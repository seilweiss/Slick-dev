#pragma once

#include "Core/Editor.h"

#include "hiphop.h"

namespace Slick {

    class HipHopEditor : public Editor
    {
        Q_OBJECT
        Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
        Q_PROPERTY(HipHop::File file READ file)

    public:
        HipHopEditor(QObject* parent = nullptr);

        virtual EditorWidget* createWidget() override;
        virtual SaveResult save(bool saveAs) override;
        virtual OpenResult open() override;

        QString path() const { return m_path; }
        void setPath(const QString& path) { m_path = path; emit pathChanged(path); }

        HipHop::File& file() { return m_file; }

    signals:
        void pathChanged(const QString& path);

    private:
        QString m_path;
        HipHop::File m_file;
        HipHop::FileStream m_stream;

        QString getOpenFileName();
        QString getSaveFileName();
    };

}
