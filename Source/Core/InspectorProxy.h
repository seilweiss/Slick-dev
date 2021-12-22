#pragma once

namespace Slick {

    template <class T>
    class InspectorProxyBase
    {
    public:
        InspectorProxyBase(void* source = nullptr) : m_source(source) {}

        void* source() const { return m_source; }

        virtual T data() const = 0;
        virtual void setData(const T& data) const = 0;

    private:
        void* m_source;
    };

    template<class T, class S = void>
    class InspectorProxy : public InspectorProxyBase<T>
    {
    public:
        InspectorProxy(S* source = nullptr) : InspectorProxyBase<T>(source) {}

        S* source() const { return (S*)InspectorProxyBase<T>::source(); }

        virtual T data() const = 0;
        virtual void setData(const T& data) const = 0;
    };

}
