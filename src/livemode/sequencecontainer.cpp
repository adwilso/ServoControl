#include "sequencecontainer.h"
#include "ui_sequencecontainer.h"

SequenceContainer::SequenceContainer(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SequenceContainer)
{
    ui->setupUi(this);

    frame = new PositionFrame(this);
    frame->setVisible(true);
    frame->move(10,160);
    frame2 = new PositionFrame(this);
    frame2->setVisible(true);
    frame2->move(10,181);
    frame3 = new PositionFrame(this);
    frame3->setVisible(true);
    frame3->move(10,202);

    sequence = new SequenceFrame(this);
    sequence->setVisible(true);
    sequence->move(50,50);
    sequence->addPositionFrame(frame);
    sequence->addPositionFrame(frame2);
    sequence->addPositionFrame(frame3);

    PositionFrame* f = new PositionFrame(this);
    f->setVisible(true);
    sequence->addPositionFrame(f);





    sequenceScroll = new QScrollArea(this);
    sequenceScroll->move(0,21);
    sequenceScroll->resize(407,150);
    sequenceScroll->setWidgetResizable(false);
    sequenceScroll->setWidget(sequence);
    sequenceScroll->setVisible(true);
    sequence->setParent(sequenceScroll);


}

SequenceContainer::~SequenceContainer()
{
    delete ui;
}

