#pragma once

#include "UI/IEditorWidget.h"
#include "UI/PanelLayout.h"

#include <QObject>

namespace Slick {

    class IEditor : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(IEditorWidget* widget READ widget)
        Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
        Q_PROPERTY(QString tooltip READ tooltip WRITE setTooltip NOTIFY tooltipChanged)
        Q_PROPERTY(bool dirty READ dirty WRITE setDirty NOTIFY dirtyChanged)

    public:
        enum OpenResult
        {
            OpenSuccessful,
            OpenFailed,
            OpenCancelled
        };

        enum SaveResult
        {
            SaveSuccessful,
            SaveFailed,
            SaveCancelled
        };

        IEditor(QObject* parent = nullptr);

        virtual IEditorWidget* createWidget() = 0;
        virtual OpenResult open() = 0;
        virtual SaveResult save(bool saveAs) = 0;
        virtual void enter() {}
        virtual void exit() {}

        IEditorWidget* widget();

        QString title() const { return m_title; }
        void setTitle(const QString& title) { m_title = title; emit titleChanged(title); }

        QString tooltip() const { return m_tooltip; }
        void setTooltip(const QString& tooltip) { m_tooltip = tooltip; emit tooltipChanged(tooltip); }

        bool dirty() const { return m_dirty; }
        void setDirty(bool dirty) { m_dirty = dirty; emit dirtyChanged(dirty); }

        PanelLayout& panelLayout() { return m_panelLayout; }

    signals:
        void titleChanged(const QString& title);
        void tooltipChanged(const QString& tooltip);
        void dirtyChanged(bool dirty);

    private:
        IEditorWidget* m_widget;
        QString m_title;
        QString m_tooltip;
        bool m_dirty;
        PanelLayout m_panelLayout;
    };

}
