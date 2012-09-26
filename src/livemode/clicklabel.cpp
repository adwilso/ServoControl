#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent) :
    QLabel(parent)
{
}
void ClickLabel::mouseDoubleClickEvent(QMouseEvent *ev)
{
    emit this->clicked();
}
