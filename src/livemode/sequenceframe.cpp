#include "sequenceframe.h"
#include "ui_sequenceframe.h"

SequenceFrame::SequenceFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SequenceFrame),
    isCopyOnClipboard(false)
{
    ui->setupUi(this);
    frames = new QList<PositionFrame*>();
    clipboard = new QList<PositionFrame*>();
}

SequenceFrame::~SequenceFrame()
{
    delete ui;
    while (!frames->isEmpty())
    {
        PositionFrame* f = frames->takeFirst();
        delete f;
    }
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
/*Protected Methods*/
void SequenceFrame::contextMenuEvent(QContextMenuEvent *ev)
{
    QMenu* menu = new QMenu(this);
    menu->addAction("Insert Before",this,SLOT(insertBefore()));
    menu->addAction("Insert After",this,SLOT(insertAfter()));
    menu->addAction("Delete",this,SLOT(deleteFrame()));
    menu->addAction("Cut",this,SLOT(cutFrame()));
    menu->addAction("Copy",this,SLOT(copyFrame()));
    if (!clipboard->isEmpty())
    {
        menu->addAction("Paste Before");
        menu->addAction("Paste After");
    }
    lastRightClick.rx() = ev->pos().x();
    lastRightClick.ry() = ev->pos().y();
    menu->exec(ev->globalPos());
}
/*Private Slots*/
void SequenceFrame::insertBefore()
{
    PositionFrame* f = this->getFrameUnderPosition(lastRightClick);
    if (f != 0)
    {
        int index = this->frames->indexOf(f);
        this->frames->insert(index, new PositionFrame(this));
        this->drawPositionFrames();
    }
    else
    {
        qDebug() << "Insert before failed as there was no position to insert before. In: "
                 << __LINE__ << " void sequenceFrame:insertBefore()";
    }
}
void SequenceFrame::insertAfter()
{
    PositionFrame* f = this->getFrameUnderPosition(lastRightClick);
    if (f != 0)
    {
        int index = this->frames->indexOf(f);
        this->frames->insert(index + 1, new PositionFrame(this));
        this->drawPositionFrames();
    }
    else
    {
        this->frames->insert(0, new PositionFrame(this));
        this->drawPositionFrames();
    }
}
void SequenceFrame::deleteFrame()
{
    PositionFrame* f = this->getFrameUnderPosition(lastRightClick);
    if (f != 0)
    {
        int index = this->frames->indexOf(f);
        f = this->frames->takeAt(index);
        delete f;
        this->drawPositionFrames();

    }
    else
    {
        qDebug() << "Could not delete frame as one was not clicked in: " << __LINE__
                 << " void SequenceFrame::deleteFrame()";
    }
}
void SequenceFrame::cutFrame()
{
    PositionFrame* f = this->getFrameUnderPosition(lastRightClick);
    if (f != 0)
    {
        int index = this->frames->indexOf(f);
        f = this->frames->takeAt(index);
        this->clearClipboard();
        this->clipboard->append(f);
        delete f;
        this->isCopyOnClipboard = false;
        this->drawPositionFrames();
    }
    else
    {
        qDebug() << "Could not cut frame as there was not one clicked on in: " << __LINE__
                 << " void SequenceFrame::cutFrame()";
    }
}
void SequenceFrame::copyFrame()
{
    PositionFrame* f = this->getFrameUnderPosition(lastRightClick);
    if (f != 0)
    {
        this->clearClipboard();
        this->clipboard->append(f);
        delete f;
        this->isCopyOnClipboard = true;
        this->drawPositionFrames();
    }
    else
    {
        qDebug() << "Could not cut frame as there was not one clicked on in: " << __LINE__
                 << " void SequenceFrame::copyFrame()";
    }
}
void SequenceFrame::pasteFrameBefore()
{
    PositionFrame* f - this->getFrameUnderPosition(lastRightClick);
    if (f != 0)
    {

    }
    else
    {
        qDebug() << "Could not paste before frame as there was not one clicked on in: " << __LINE__
                 << " void SequenceFrame::pasteBeforeFrame()";
    }
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
        QRect r(frames->at(i)->pos().x(),frames->at(i)->pos().y(),
                frames->at(i)->width(),frames->at(i)->height());
        //We have to use pos, thus can't compare to the bounding rect, the bounding rect is not in the same
        //cordinate system as the click is returned in.
        if (r.contains(framePos))
        {
            return (*frames)[i];
        }
    }
    qDebug() << "Click event was outside of the current frames. On: " << __LINE__ <<
                ", SequenceFrame::getFrameUnderPosition(QPoint& framePosition)";
    return 0;
}
void SequenceFrame::clearClipboard()
{
    if (isCopyOnClipboard)
    {//Don't free the shared memory that is the frames list's problem now.
        clipboard->clear();
        return;
    }
    else //This is our mess to free.
    {
        while(!this->clipboard->isEmpty())
        {
            PositionFrame *f  = clipboard->takeFirst();
            delete f;
        }
    }
}
