#include "inspector/properties/checkboxproperty.h"

#include <QCheckBox>

namespace Slick {

    namespace Inspector {

        namespace {

            template <class T> bool getCheckBoxData(CheckBoxProperty* prop);

            template <> bool getCheckBoxData<bool>(CheckBoxProperty* prop)
            {
                return prop->dataSource().toBool();
            }

            template <> bool getCheckBoxData<uint32_t>(CheckBoxProperty* prop)
            {
                return (prop->dataSource().toUInt32() & prop->mask()) != 0;
            }

            template <class T> void setCheckBoxData(CheckBoxProperty* prop, bool data);

            template <> void setCheckBoxData<bool>(CheckBoxProperty* prop, bool data)
            {
                prop->dataSource().setBool(data);
            }

            template <> void setCheckBoxData<uint32_t>(CheckBoxProperty* prop, bool data)
            {
                auto source = prop->dataSource();

                if (data)
                {
                    source.setUInt32(source.toUInt32() | prop->mask());
                }
                else
                {
                    source.setUInt32(source.toUInt32() & ~prop->mask());
                }
            }

            template <class T> void updateCheckBox(QWidget* widget, const QList<Property*>& props)
            {
                bool value = getCheckBoxData<T>((CheckBoxProperty*)props[0]);
                bool match = true;

                for (int i = 1; i < props.size(); i++)
                {
                    bool data = getCheckBoxData<T>((CheckBoxProperty*)props[i]);

                    if (data != value)
                    {
                        match = false;
                        break;
                    }
                }

                widget->blockSignals(true);
                ((QCheckBox*)widget)->setChecked(match && value);
                widget->blockSignals(false);
            }

            template <class T> QWidget* createCheckBox(const QList<Property*>& props)
            {
                QCheckBox* checkBox = new QCheckBox;

                QObject::connect(checkBox, &QCheckBox::stateChanged, [=](int state)
                {
                    for (Property* prop : props)
                    {
                        setCheckBoxData<T>((CheckBoxProperty*)prop, state == Qt::Checked);
                        prop->notifyDataChanged();
                    }
                });

                return checkBox;
            }

        }

        QWidget* CheckBoxProperty::createWidget(const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::Bool: return createCheckBox<bool>(props);
            default: return createCheckBox<uint32_t>(props);
            }
        }

        void CheckBoxProperty::updateWidget(QWidget* widget, const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::Bool: updateCheckBox<bool>(widget, props);
            default: updateCheckBox<uint32_t>(widget, props);
            }
        }

    }

}
