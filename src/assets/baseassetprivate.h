#pragma once

#include "inspector/group.h"

#include "hiphop/core/link_asset.h"

namespace Slick {

    namespace Assets {

        class LinkGroup : public Inspector::Group
        {
            Q_OBJECT

        public:
            LinkGroup(HipHop::LinkAsset* link, Inspector::Group* parent = nullptr) :
                Inspector::Group(QString(), QString(), parent), m_link(link) {}

            HipHop::LinkAsset* link() const { return m_link; }

            virtual bool equals(Inspector::Group* o) const override
            {
                LinkGroup* other = qobject_cast<LinkGroup*>(o);

                if (!other)
                {
                    return false;
                }

                return (m_link->srcEvent == other->m_link->srcEvent && m_link->dstEvent == other->m_link->dstEvent);
            }

        private:
            HipHop::LinkAsset* m_link;
        };

    }

}
