#ifndef NAMEEDITAREA_H
#define NAMEEDITAREA_H

#include <QFrame>
#include <QFont>
#include "clicklabel.h"

namespace Ui {
class NameEditArea;
}

class NameEditArea : public QFrame
{
    Q_OBJECT
    
public:
    explicit NameEditArea(QWidget *parent = 0);
    ~NameEditArea();
    void lostFocus();
    QString getName();
    bool setName(QString name);

signals:
    void valueEntered(QString newValue);
    void focusShifted(int index);

public slots:
    void valueChanged(QString newValue);
private slots:
    void labelClicked();
    void editFinished();
    
private:
    Ui::NameEditArea *ui;
    ClickLabel* label;

};

#endif // NAMEEDITAREA_H
