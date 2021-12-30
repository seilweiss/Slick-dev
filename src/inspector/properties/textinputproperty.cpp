#include "inspector/properties/textinputproperty.h"

#include "util/stringutils.h"

#include <QLineEdit>
#include <QPlainTextEdit>

namespace Slick {

    namespace Inspector {

        namespace {

            template <class W> QString getTextInputText(W* widget);

            template <> QString getTextInputText(QLineEdit* lineEdit)
            {
                return lineEdit->text();
            }

            template <> QString getTextInputText(QPlainTextEdit* textEdit)
            {
                return textEdit->toPlainText();
            }

            template <class W> void setTextInputText(W* widget, const QString& text);

            template <> void setTextInputText(QLineEdit* lineEdit, const QString& text)
            {
                lineEdit->setText(text);
            }

            template <> void setTextInputText(QPlainTextEdit* textEdit, const QString& text)
            {
                textEdit->setPlainText(text);
            }

            template <class W> using TextInputSignal = void(W::*)();

            template <class W> TextInputSignal<W> getTextInputSignal();
            template <> TextInputSignal<QLineEdit> getTextInputSignal() { return &QLineEdit::editingFinished; }
            template <> TextInputSignal<QPlainTextEdit> getTextInputSignal() { return &QPlainTextEdit::textChanged; }

            template <class T, class W> QWidget* createTextInputInternal(const QList<Property*>& props)
            {
                W* widget = new W;
                T text = props[0]->dataSource().data<T>();
                bool match = true;

                for (int i = 1; i < props.size(); i++)
                {
                    T data = props[i]->dataSource().data<T>();

                    if (data != text)
                    {
                        match = false;
                        break;
                    }
                }

                widget->setFont(QFontDatabase::systemFont(((TextInputProperty*)props[0])->monospace() ? QFontDatabase::FixedFont : QFontDatabase::GeneralFont));

                setTextInputText(widget, match ? Util::convertString<QString>(text) : QString());

                QObject::connect(widget, getTextInputSignal<W>(), [=]
                {
                    for (Property* prop : props)
                    {
                        prop->dataSource().setData(Util::convertString<T>(getTextInputText(widget)));
                        prop->notifyDataChanged();
                    }
                });

                return widget;
            }

            template <class T> QWidget* createTextInput(const QList<Property*>& props)
            {
                return ((TextInputProperty*)props[0])->multiline() ?
                            createTextInputInternal<T, QPlainTextEdit>(props) :
                            createTextInputInternal<T, QLineEdit>(props);
            }

        }

        QWidget* TextInputProperty::createWidget(const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::StdString: return createTextInput<std::string>(props);
            default: return createTextInput<QString>(props);
            }
        }

    }

}
