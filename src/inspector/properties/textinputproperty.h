#pragma once

#include "inspector/property.h"

namespace Slick {

    namespace Inspector {

        class TextInputProperty : public Property
        {
            Q_OBJECT

        public:
            TextInputProperty(const QString& name, const QString& displayName, const DataSource& dataSource, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent), m_multiline(false), m_monospace(false) {}

            bool multiline() const { return m_multiline; }
            void setMultiline(bool multiline) { m_multiline = multiline; setOrientation(multiline ? Qt::Vertical : Qt::Horizontal); }

            bool monospace() const { return m_monospace; }
            void setMonospace(bool monospace) { m_monospace = monospace; }

            virtual QWidget* createWidget(const QList<Property*>& props) override;

        private:
            bool m_multiline;
            bool m_monospace;
        };

    }

}
