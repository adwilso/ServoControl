
#ifndef SEQUENCECONTAINER_H
#define SEQUENCECONTAINER_H

#include <QFrame>
#include "editarea.h"
#include "nameeditarea.h"
#include "positionframe.h"
#include "sequenceframe.h"
#include "sequencecontainer.h"
#include "QScrollArea"
#include "QMenu"

namespace Ui {
class SequenceContainer;
}

class SequenceContainer : public QFrame
{
    Q_OBJECT
    
public:
    explicit SequenceContainer(QWidget *parent = 0);
    ~SequenceContainer();


    
private:
    Ui::SequenceContainer *ui;

    EditArea* edit;
    EditArea* edit2;
    NameEditArea* edit3;
    PositionFrame* frame;
    PositionFrame* frame2;
    PositionFrame* frame3;
    SequenceFrame* sequence;

    QScrollArea* sequenceScroll;
};

#endif // SEQUENCECONTAINER_H
