#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent) :
    QLabel(parent)
{
}
void ClickLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    emit this->clicked();
}
