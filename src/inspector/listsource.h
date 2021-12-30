#pragma once

#include <vector>

namespace Slick {

    namespace Inspector {

        class Group;

        class AbstractListSource
        {
        public:
            virtual int size() const = 0;
            virtual int max() const { return -1; }
            bool full() const { return max() != -1 && size() >= max(); }
            virtual void add() = 0;
            virtual void remove(int index) = 0;
            virtual void createGroupItem(Group* group, int index) = 0;
        };

        template <class T>
        class ListSource : public AbstractListSource
        {
        public:
            ListSource(T& list) : m_list(list) {}

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
