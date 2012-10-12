#ifndef SEQUENCEFRAME_H
#define SEQUENCEFRAME_H

#include <QFrame>
#include <QList>
#include <QDebug>
#include <QMenu>

#include "positionframe.h"
#include <QRect>


namespace Ui {
class SequenceFrame;
}

class SequenceFrame : public QFrame
{
    Q_OBJECT
    
public:
    explicit SequenceFrame(QWidget *parent = 0);
    ~SequenceFrame();

    bool addPositionFrame(PositionFrame* newFrame, int index = -1);
    QSize sizeHint() const;
    
protected:
    void contextMenuEvent(QContextMenuEvent *);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void mouseMoveEvent(QMouseEvent *);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void insertBefore();
    void insertAfter();
    void deleteFrame();
    void cutFrame();
    void copyFrame();
    void pasteFrameBefore();
    void pasteFrameAfter();

    void newPositionSelected(PositionFrame* selected);
private:
    bool drawPositionFrames();
    PositionFrame* getFrameUnderPosition(QPoint framePos);
    void clearClipboard();

    Ui::SequenceFrame *ui;
    QList <PositionFrame*>* frames;
    QPoint lastRightClick;
    QPoint dragStart;
    QList <PositionFrame*>* clipboard;
    bool isCopyOnClipboard;
};

#endif // SEQUENCEFRAME_H
