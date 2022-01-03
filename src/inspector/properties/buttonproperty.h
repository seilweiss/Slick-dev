#pragma once

#include "inspector/property.h"

namespace Slick {

    namespace Inspector {

        class ButtonProperty : public Property
        {
            Q_OBJECT

        public:
            ButtonProperty(const QString& name, const QString& displayName, const DataSource& dataSource, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent) {}

            virtual QWidget* createWidget(const QList<Property*>& props) override;

            void notifyClicked() { emit clicked(); }

        signals:
            void clicked();
        };

    }

}
