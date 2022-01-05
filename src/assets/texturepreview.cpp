#include "assets/texturepreview.h"

#include "core/scene.h"

namespace Slick {

    namespace Assets {

        TexturePreview::TexturePreview(TextureAsset* asset, QWindow* parent) :
            Render::Viewport(parent),
            m_asset(asset)
        {
            setContext(asset->scene()->renderContext());
        }

        void TexturePreview::render()
        {
            if (!m_asset->texture() || !m_asset->texture()->data())
            {
                return;
            }

            context()->glPushAttrib(GL_ALL_ATTRIB_BITS);

            context()->glDisable(GL_FOG);
            context()->glDisable(GL_DEPTH_TEST);
            context()->glDepthMask(GL_FALSE);
            context()->glEnable(GL_BLEND);
            context()->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            context()->glMatrixMode(GL_PROJECTION);
            context()->glPushMatrix();
            context()->glLoadIdentity();
            context()->glOrtho(0.0f, width(), height(), 0.0f, -1.0f, 1.0f);

            context()->glMatrixMode(GL_MODELVIEW);
            context()->glPushMatrix();
            context()->glLoadIdentity();

            m_asset->texture()->bind();

            QRectF rect(QPointF(0.0f, 0.0f), QSize(m_asset->texture()->data()->width, m_asset->texture()->data()->height).scaled(width(), height(), Qt::KeepAspectRatio));
            rect.translate((width() - rect.width()) / 2.0f, (height() - rect.height()) / 2.0f);

            context()->glBegin(GL_QUADS);

            context()->glTexCoord2f(0.0f, 0.0f);
            context()->glVertex2f(rect.left(), rect.top());

            context()->glTexCoord2f(1.0f, 0.0f);
            context()->glVertex2f(rect.right(), rect.top());

            context()->glTexCoord2f(1.0f, 1.0f);
            context()->glVertex2f(rect.right(), rect.bottom());

            context()->glTexCoord2f(0.0f, 1.0f);
            context()->glVertex2f(rect.left(), rect.bottom());

            context()->glEnd();

            m_asset->texture()->unbind();

            context()->glMatrixMode(GL_PROJECTION);
            context()->glPopMatrix();

            context()->glMatrixMode(GL_MODELVIEW);
            context()->glPopMatrix();

            context()->glPopAttrib();
        }

    }

}
