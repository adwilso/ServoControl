#ifndef SEQUENCEFRAME_H
#define SEQUENCEFRAME_H

#include <QFrame>
#include <QList>
#include <QDebug>

#include "positionframe.h"

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
    
private:
    bool drawPositionFrames();
    Ui::SequenceFrame *ui;
    QList <PositionFrame*>* frames;
};

#endif // SEQUENCEFRAME_H
