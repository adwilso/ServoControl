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
    this->setAcceptDrops(true);
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
        menu->addAction("Paste Before",this,SLOT(pasteFrameBefore()));
        menu->addAction("Paste After",this,SLOT(pasteFrameAfter()));
    }
    lastRightClick.rx() = ev->pos().x();
    lastRightClick.ry() = ev->pos().y();
    menu->exec(ev->globalPos());
}
void SequenceFrame::mousePressEvent(QMouseEvent *event)
{
    if (!event->buttons() & Qt::LeftButton)
    {
        return;
    }
    PositionFrame* frame = this->getFrameUnderPosition(event->pos());
    if (frame == 0)
    {
        dragStart = QPoint();
        return;
    }
    dragStart = QPoint(event->pos());
}
void SequenceFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons() & Qt::LeftButton || dragStart.isNull())
    {
        return;
    }
    if ((event->pos() - dragStart).manhattanLength() < QApplication::startDragDistance()
            || lastRightClick == dragStart)
    {
        return;
    }

    lastRightClick = dragStart;
    this->cutFrame();

    QMimeData* data = new QMimeData();
    QByteArray bytes("garbage");
    data->setData("application/x-position",bytes);
    QDrag *drag  = new QDrag(this);
    drag->setMimeData(data);
    if (drag->exec(Qt::MoveAction) != Qt::MoveAction)
    {
        this->clearClipboard();
    }
}
void SequenceFrame::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-position"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
void SequenceFrame::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-position"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
void SequenceFrame::dropEvent(QDropEvent *event)
{
    if (!event->mimeData()->hasFormat("application/x-position"))
    {
        qDebug() << "Drop event ignored" << event->mimeData()->formats();
        event->ignore();
        return;
    }
    lastRightClick = event->pos();
    PositionFrame* droppedOnFrame = this->getFrameUnderPosition(event->pos());
    QPoint pointInFrame = droppedOnFrame->pos() = event->pos();
    if (pointInFrame.y() > (droppedOnFrame->height() / 2))
    {
        qDebug() << "Paste after";
        this->pasteFrameAfter();
    }
    else
    {
        qDebug() << "Paste before";
        this->pasteFrameBefore();
    }
    event->accept();
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
        this->frames->insert(0, new PositionFrame(this));
        this->drawPositionFrames();
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
        this->frames->insert(frames->length(), new PositionFrame(this));
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
        f->setVisible(false);
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
    PositionFrame* f = this->getFrameUnderPosition(lastRightClick);
    if (f != 0)
    {
        int index = this->frames->indexOf(f);
        this->frames->insert(index, clipboard->first()->copy(this));
        this->drawPositionFrames();
    }
    else
    {
        this->frames->insert(0, clipboard->first()->copy(this));
        this->drawPositionFrames();
    }
}
void SequenceFrame::pasteFrameAfter()
{
    PositionFrame* f = this->getFrameUnderPosition(lastRightClick);
    if (f != 0)
    {
        int index = this->frames->indexOf(f);
        this->frames->insert(index + 1, clipboard->first()->copy(this));
        this->drawPositionFrames();
    }
    else
    {
        this->frames->insert(frames->length(), clipboard->first()->copy(this));
        this->drawPositionFrames();
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
