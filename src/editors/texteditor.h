#pragma once

#include "core/editor.h"

class QTextEdit;

namespace Slick {

    namespace Editors {

        class TextEditorWidget;

        class TextEditor : public Core::Editor
        {
            Q_OBJECT
            Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)

        public:
            TextEditor(QObject* parent = nullptr);

            virtual Core::EditorWidget* createWidget() override;
            virtual OpenResult open() override;
            virtual SaveResult save(bool saveAs) override;

            QString path() const { return m_path; }
            void setPath(const QString& path) { m_path = path; emit pathChanged(path); }

        signals:
            void pathChanged(const QString& path);

        private:
            QString m_path;
            QString m_readText;

            QString getOpenFileName();
            QString getSaveFileName();
        };

    }

}
