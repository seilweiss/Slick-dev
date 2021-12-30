#pragma once

#include "inspector/property.h"

namespace Slick {

    namespace Inspector {

        class ColorInputProperty : public Property
        {
            Q_OBJECT

        public:
            ColorInputProperty(const QString& name, const QString& displayName, const DataSource& dataSource, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent) {}

            virtual QWidget* createWidget(const QList<Property*>& props) override;
        };

    }

}
