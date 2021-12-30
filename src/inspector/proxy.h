#pragma once

namespace Slick {

    namespace Inspector {

        template <class T>
        class ProxyBase
        {
        public:
            ProxyBase(void* source = nullptr) : m_source(source) {}

            void* source() const { return m_source; }

            virtual T data() const = 0;
            virtual void setData(const T& data) const = 0;

        private:
            void* m_source;
        };

        template<class T, class S = void>
        class Proxy : public ProxyBase<T>
        {
        public:
            Proxy(S* source = nullptr) : ProxyBase<T>(source) {}

            S* source() const { return (S*)ProxyBase<T>::source(); }

            virtual T data() const = 0;
            virtual void setData(const T& data) const = 0;
        };

    }

}
