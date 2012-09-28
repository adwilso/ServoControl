#include "positionframe.h"
#include "ui_positionframe.h"

PositionFrame::PositionFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PositionFrame),
    m_position(0),
    active(false)
{
    ui->setupUi(this);
    name = new NameEditArea(this);
    name->move(0,0);
    name->setVisible(true);
    name->setFrameShape(QFrame::Panel);
    name->setLineWidth(1);
    connect(name,SIGNAL(focusShifted(int)),SLOT(focusChanged(int)));
    connect(name, SIGNAL(valueEntered(QString)),SLOT(newName(QString)));
    for (int i(0); i < 12; ++i)
    {
        servoEdits[i] = new EditArea(this,i +1);
        servoEdits[i]->move(i*servoEdits[i]->width() + name->width(),0);
        servoEdits[i]->setVisible(true);
        servoEdits[i]->setFrameShape(QFrame::Panel);
        servoEdits[i]->setLineWidth(1);
        connect(servoEdits[i],SIGNAL(gotFocus(int)),SLOT(focusChanged(int)));
        connect(servoEdits[i],SIGNAL(valueEntered(int,int)),SLOT(dataChanged(int,int)));
        connect(this,SIGNAL(newFocus(int)),servoEdits[i],SLOT(focusShifted(int)));
    }
    this->initalizePosition();
}

PositionFrame::~PositionFrame()
{
    delete ui;
}

QString PositionFrame::getName()
{
    return m_position->getName();
}
bool PositionFrame::setName(QString name)
{
    if (name.length() > 20 || name.isEmpty()) //20 character limit on the position names
    {
        qDebug() << "Name passed is not valid on: " << __LINE__
                 << " in bool PositionFrame::setName(QString name)";
        return false;
    }
    this->m_position->setName(name);
    this->name->setName(name);
    return true;

}
quint8 PositionFrame::getServoData(int servoNumber)
{
    if (servoNumber > 12 || servoNumber < 0)
    {
        return 0;
    }
    return m_position->getPositionDataFor(servoNumber);
}
bool PositionFrame::setServoData(int servoNumber, int data)
{
    if (servoNumber  > 12 || servoNumber < 1)
    {
        qDebug() << "Servo value passed out of range on: " << __LINE__
                 << " in bool PositionFrame::setServoData(int servoNumber, int data)";
        return false;
    }
    if (data < 0 || data > 97)
    {
        qDebug()<< "Servo data passed out of range on: " << __LINE__
                << " in bool PositionFrame::setServoData(int servoNumber, int data)";
        return false;
    }
    this->servoEdits[servoNumber-1]->valueChanged(data);
    this->m_position->addServoPosition((quint8)servoNumber, (quint8)data);
    return true;
}

PositionFrame* PositionFrame::copy(QWidget *parent)
{
    PositionFrame* output = new PositionFrame(parent);
    for (int i(1); i < 12; ++i)
    {
        output->setServoData(i,this->getServoData(i));
    }
    output->setName(this->getName());
    return output;
}

/*Private slots*/
void PositionFrame::newName(QString name)
{
    m_position->setName(name);
}


void PositionFrame::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton && active)
    {
        return;
    }
    active  = !active;
    if (active)
    {
        this->selected();
    }
    else
    {
       this->unselected();
    }
    this->focusChanged(13); //Nothing gets the focus anymore

}

void PositionFrame::focusChanged(int newFocusIndex)
{
    if (newFocusIndex != 0)
    {
        name->lostFocus();
    }
    if (newFocusIndex < 13)
    {
        this->selected();
        this->active = true;
    }
    emit this->newFocus(newFocusIndex);
}
void PositionFrame::dataChanged(int newValue, int index)
{
    if (m_position == 0)
    {
        m_position = new Position();
    }
    m_position->addServoPosition(index,newValue);
    this->unselected();
    this->active = false;
}
void PositionFrame::selected()
{
    for (int i(0); i < 12; ++i)
    {
        servoEdits[i]->setFrameStyle(QFrame::Raised | QFrame::Box);
        servoEdits[i]->setLineWidth(1);
        servoEdits[i]->setMidLineWidth(0);
    }
    name->setFrameStyle(QFrame::Raised | QFrame::Box);
    name->setLineWidth(1);
    name->setMidLineWidth(0);
}

void PositionFrame::unselected()
{
    for (int i(0); i < 12; ++i)
    {
        servoEdits[i]->setFrameShape(QFrame::Panel);
        servoEdits[i]->setLineWidth(1);
    }
    name->setFrameShape(QFrame::Panel);
    name->setLineWidth(1);
}
void PositionFrame::initalizePosition()
{
    m_position = new Position();
    for (int i(0); i < 12; ++i)
    {
        m_position->addServoPosition(i+1,servoEdits[i]->getValue());
    }
    m_position->setName(name->getName());
}
