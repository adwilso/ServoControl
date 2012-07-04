#include "sequenceframe.h"
#include "ui_sequenceframe.h"

SequenceFrame::SequenceFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SequenceFrame)
{
    ui->setupUi(this);
    frames = new QList<PositionFrame*>();
}

SequenceFrame::~SequenceFrame()
{
    delete ui;
}
/*Public Methods*/
bool SequenceFrame::addPositionFrame(PositionFrame *newFrame, int index)
{
    newFrame->setParent(this);
    if (index > frames->size() + 1)
    {
        qDebug() << "Position could not be added to SequenceFrame, index out of range.";
        return false;
    }
    if (index != -1)
    {
        frames->insert(index,newFrame);
    }
    else
    {
        frames->append(newFrame);
    }
    return this->drawPositionFrames();

}
/*Private Methods*/
bool SequenceFrame::drawPositionFrames()
{
    if (frames->isEmpty())
    {
        return false;
    }
    this->resize((*frames)[0]->size().width(),(*frames)[0]->size().height() * frames->size());
    for (int i(0); i < frames->size(); ++i)
    {
        (*frames)[i]->move(0,i * (*frames)[i]->size().height());
        (*frames)[i]->setVisible(true);
    }
    return true;
}
