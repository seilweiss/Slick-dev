#pragma once

#include <QWidget>

namespace Slick {

    class IEditorWidget;

    class IEditor : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(IEditorWidget* widget READ widget)
        Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
        Q_PROPERTY(QString tooltip READ tooltip WRITE setTooltip NOTIFY tooltipChanged)
        Q_PROPERTY(bool dirty READ dirty WRITE setDirty NOTIFY dirtyChanged)

    public:
        enum SaveResult
        {
            SaveSuccessful,
            SaveFailed,
            SaveCancelled
        };

        enum OpenResult
        {
            OpenSuccessful,
            OpenFailed,
            OpenCancelled
        };

        IEditor(QObject* parent = nullptr);

        virtual IEditorWidget* createWidget() = 0;
        virtual SaveResult save() = 0;
        virtual SaveResult saveAs() = 0;
        virtual OpenResult open() = 0;

        IEditorWidget* widget();

        QString title() const { return m_title; }
        void setTitle(const QString& title) { m_title = title; emit titleChanged(title); }

        QString tooltip() const { return m_tooltip; }
        void setTooltip(const QString& tooltip) { m_tooltip = tooltip; emit tooltipChanged(tooltip); }

        bool dirty() const { return m_dirty; }
        void setDirty(bool dirty) { m_dirty = dirty; emit dirtyChanged(dirty); }

    signals:
        void titleChanged(const QString& title);
        void tooltipChanged(const QString& tooltip);
        void dirtyChanged(bool dirty);

    private:
        IEditorWidget* m_widget;
        QString m_title;
        QString m_tooltip;
        bool m_dirty;
    };

    class IEditorWidget : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(IEditor* editor READ editor WRITE setEditor)

    public:
        IEditorWidget(QWidget* parent = nullptr);

        IEditor* editor() const { return m_editor; }
        void setEditor(IEditor* editor) { m_editor = editor; }

    private:
        IEditor* m_editor;
    };

}
