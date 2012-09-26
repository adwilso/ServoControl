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

void SequenceFrame::contextMenuEvent(QContextMenuEvent *ev)
{
    QMenu* menu = new QMenu(this);
    menu->addAction("Insert Before",this,SLOT(insertBefore()));
    menu->addAction("Insert After",this,SLOT(insertAfter()));
    menu->addAction("Delete");
    menu->addAction("Cut");
    menu->addAction("Copy");
    menu->addAction("Paste Before");
    menu->addAction("Paste After");
    lastRightClick.rx() = ev->pos().x();
    lastRightClick.ry() = ev->pos().y();
    menu->exec(ev->globalPos());
}
void SequenceFrame::insertBefore()
{
    qDebug() << "insert before";
    PositionFrame* f = this->getFrameUnderPosition(lastRightClick);
    if (f != 0){
    qDebug() << "Frame name: " << f->getName();
    }
    else
    {
        qDebug() << "There was no frame returned";
    }
}
void SequenceFrame::insertAfter()
{
    qDebug() << "insert after";
}

/*Private Methods*/
bool SequenceFrame::drawPositionFrames()
{
    if (frames->isEmpty())
    {
        return false;
    }
    this->resize((*frames)[0]->size().width(),(*frames)[0]->size().height() * frames->size());
    for (int i(0); i < frames->size(); ++i) /// TODO:Yes this is quadratic, no I don't care, fix it later.
    {
        (*frames)[i]->move(0,i * (*frames)[i]->size().height());
        (*frames)[i]->setVisible(true);
    }
    return true;
}
PositionFrame* SequenceFrame::getFrameUnderPosition(QPoint framePos)
{
    if (framePos.y() > this->size().height() || framePos.x() > this->size().width())
    {
        qDebug() << "Click event outside of widget on: " << __LINE__ <<
                    " SequenceFrame::getFrameUnderPosition(QPoint& framePos)";
        return 0;
    }
    qDebug() << "Point x: " << framePos.x() << " y: " << framePos.y();
    for (int i(0); i < frames->size(); ++i ) /// TODO: Quadratic, needs to be fixed.
    {

       /* qDebug() << i << ": x: " <<frames->at(i)->frameRect().x() << " y: " << frames->at(i)->frameRect().y() <<
        "width: " << frames->at(i)->frameRect().width() << " height: " << frames->at(i)->frameRect().height();
        */QRect r(frames->at(i)->pos().x(),frames->at(i)->pos().y(),
                frames->at(i)->width(),frames->at(i)->height());
        if (r.contains(framePos))
        {
            return (*frames)[i];
        }
    }
    qDebug() << "Click event was outside of the current frames. On: " << __LINE__ <<
                ", SequenceFrame::getFrameUnderPosition(QPoint& framePosition)";
    return 0;
}
