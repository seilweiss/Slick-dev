#pragma once

#include "inspector/listsource.h"

#include <vector>

namespace Slick {

    namespace Inspector {

        template <class T>
        class STLListSource : public ListSource
        {
        public:
            STLListSource(T& list) : m_list(list) {}

            virtual T& list() const { return m_list; }
            virtual int size() const override { return (int)m_list.size(); }
            virtual void add() { m_list.push_back({}); }
            virtual void remove(int index) { m_list.erase(m_list.begin() + index); }
            virtual void createGroupItem(Group* group, int index) = 0;

        private:
            T& m_list;
        };

    }

}
