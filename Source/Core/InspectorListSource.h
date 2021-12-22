#pragma once

#include <vector>

namespace Slick {

    class InspectorGroup;

    class AbstractInspectorListSource
    {
    public:
        virtual int size() const = 0;
        virtual int max() const { return -1; }
        virtual void add() = 0;
        virtual void remove(int index) = 0;
        virtual void createGroupItem(InspectorGroup* group, int index) = 0;
    };

    template <class T>
    class InspectorListSource : public AbstractInspectorListSource
    {
    public:
        InspectorListSource(T& list) : m_list(list) {}

        virtual T& list() const { return m_list; }
        virtual int size() const override { return (int)m_list.size(); }
        virtual void add() { m_list.push_back({}); }
        virtual void remove(int index) { m_list.erase(m_list.begin() + index); }
        virtual void createGroupItem(InspectorGroup* group, int index) = 0;

    private:
        T& m_list;
    };

}
