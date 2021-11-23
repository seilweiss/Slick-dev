#include "Render/Clump.h"

#include "rws_core.h"
#include "rws_world.h"

namespace Slick {

    namespace Render {

        Clump::Clump(QObject* parent) :
            QObject(parent),
            m_data(nullptr)
        {
        }

        void Clump::setData(Rws::Clump* data)
        {
            m_data = data;

            if (data)
            {
                Rws::GeometryList* rwGeomList = data->GetGeometryList();

                for (Rws::Geometry* rwGeom : rwGeomList->GetGeometries())
                {
                    Geometry* geom = new Geometry(this);

                    geom->setData(rwGeom);

                    m_geomList.append(geom);
                }
            }
        }

        void Clump::render(Context& context)
        {
            for (Geometry* geom : m_geomList)
            {
                geom->render(context);
            }
        }

    }

}
