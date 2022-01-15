#pragma once

namespace Slick {

    namespace Inspector {

        template <class T> class Proxy
        {
        public:
            virtual T data() const = 0;
            virtual void setData(const T& data) const = 0;
        };

    }

}
