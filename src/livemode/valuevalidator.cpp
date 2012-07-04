#include "valuevalidator.h"

ValueValidator::ValueValidator(QObject *parent) :
    QValidator(parent)
{
}
void ValueValidator::fixup(QString &input) const
{
    input = input.trimmed();
}
QValidator::State ValueValidator::validate(QString &input, int &pos) const
{
    if (input.isEmpty())
    {
        return QValidator::Intermediate;
    }
    bool ok = false;
    int test = input.toInt(&ok);
    if (test < 1 || test > 97 || !ok)
    {
        return QValidator::Invalid;
    }
    return QValidator::Acceptable;
}
