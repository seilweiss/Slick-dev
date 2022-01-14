#include "panels/debugpanel.h"

#include "render/context.h"

#include <QVBoxLayout>
#include <QLabel>

namespace Slick {

    namespace Panels {

        DebugPanel::DebugPanel(QWidget* parent) :
            QWidget(parent),
            m_context(nullptr),
            m_debugLabel(new QLabel)
        {
            QVBoxLayout* mainLayout = new QVBoxLayout;

            mainLayout->addWidget(m_debugLabel, 0, Qt::AlignTop);

            setLayout(mainLayout);

            refresh();
        }

        void DebugPanel::setRenderContext(Render::Context* context)
        {
            if (m_context)
            {
                m_context->disconnect(this);
            }

            if (context)
            {
                connect(context, &Render::Context::frameEnded, this, &DebugPanel::refresh);
            }

            m_context = context;

            refresh();
        }

        void DebugPanel::refresh()
        {
            QString debugText;

            if (m_context)
            {
                Render::Stats* stats = m_context->stats();

                debugText += tr("FPS: %1\n"
                                "Atomics: %2\n"
                                "Triangles: %3\n")
                             .arg(stats->atomicCount)
                             .arg(stats->triangleCount)
                             .arg(stats->fps);
            }

            m_debugLabel->setText(debugText);
        }

    }

}
