#pragma once

namespace Slick {

    namespace Inspector {

        class Group;

        class ListSource
        {
        public:
            virtual int size() const = 0;
            virtual int max() const { return -1; }
            bool full() const { return max() != -1 && size() >= max(); }
            virtual void add() = 0;
            virtual void remove(int index) = 0;
            virtual void createGroupItem(Group* group, int index) = 0;
        };

    }

}
