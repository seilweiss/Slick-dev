#include "InspectorProperties/CheckBoxProperty.h"

#include <QCheckBox>

namespace Slick {

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

        template <class T> QWidget* createCheckBox(const QList<InspectorProperty*>& props)
        {
            QCheckBox* checkBox = new QCheckBox;
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

            checkBox->setChecked(match && value);

            QObject::connect(checkBox, &QCheckBox::stateChanged, [=](int state)
            {
                for (InspectorProperty* prop : props)
                {
                    setCheckBoxData<T>((CheckBoxProperty*)prop, state == Qt::Checked);
                    prop->notifyDataChanged();
                }
            });

            return checkBox;
        }

    }

    QWidget* CheckBoxProperty::createWidget(const QList<InspectorProperty*>& props)
    {
        switch (props[0]->dataSource().type())
        {
        case InspectorDataSource::Bool: return createCheckBox<bool>(props);
        default: return createCheckBox<uint32_t>(props);
        }
    }

}
