#ifndef EDITAREA_H
#define EDITAREA_H

#include <QFrame>
#include <QDebug>
#include "clicklabel.h"
#include <valuevalidator.h>

namespace Ui {
class EditArea;
}

class EditArea : public QFrame
{
    Q_OBJECT
    
public:
    explicit EditArea(QWidget *parent = 0,int index = 0);
    ~EditArea();

signals:
    void valueEntered(int newValue, int index);
    void gotFocus(int index);

public slots:
    void valueChanged(int newValue);
    void focusShifted(int index);
private slots:
    void labelClicked();
    void editFinished();
    
private:
    Ui::EditArea *ui;
    ClickLabel* label;
    int m_index;
};

#endif // EDITAREA_H
