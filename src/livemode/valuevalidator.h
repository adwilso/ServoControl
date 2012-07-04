#ifndef VALUEVALIDATOR_H
#define VALUEVALIDATOR_H

#include <QValidator>

class ValueValidator : public QValidator
{
    Q_OBJECT
public:
    explicit ValueValidator(QObject *parent = 0);
    State validate(QString & input, int &pos) const;
    void fixup(QString &input) const;
signals:
    
public slots:
    
};

#endif // VALUEVALIDATOR_H
