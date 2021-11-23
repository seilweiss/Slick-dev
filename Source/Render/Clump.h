#pragma once

#include "Render/Geometry.h"

#include <QObject>

namespace Rws {

    class Clump;

}

namespace Slick {

    namespace Render {

        class Clump : public QObject
        {
            Q_OBJECT

        public:
            Clump(QObject* parent = nullptr);

            Rws::Clump* data() const { return m_data; }
            void setData(Rws::Clump* data);

            QVector<Geometry*>& geometryList() { return m_geomList; }

            void render(Context& context);

        private:
            Rws::Clump* m_data;
            QVector<Geometry*> m_geomList;
        };

    }

}
