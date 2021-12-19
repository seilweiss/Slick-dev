#pragma once

#include "Core/InspectorGroup.h"

#include "hiphop/core/link_asset.h"

namespace Slick {

    class LinkGroup : public InspectorGroup
    {
        Q_OBJECT

    public:
        LinkGroup(HipHop::LinkAsset& link, const QString& name, QObject* parent = nullptr) :
            InspectorGroup(name, parent), m_link(link) {}

        HipHop::LinkAsset& link() const { return m_link; }

        virtual bool equals(InspectorGroup* o) const override
        {
            LinkGroup* other = qobject_cast<LinkGroup*>(o);

            if (!other)
            {
                return false;
            }

            return (m_link.srcEvent == other->m_link.srcEvent && m_link.dstEvent == other->m_link.dstEvent);
        }

    private:
        HipHop::LinkAsset& m_link;
    };

}
