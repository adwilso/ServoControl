#include "sequencebox.h"
#include "ui_sequencebox.h"

sequenceBox::sequenceBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sequenceBox)
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

    scroll = new SequenceScrollArea(this);
    scroll->setWidgetResizable(false);
    scroll->setWidget(sequence);
    scroll->move(50,50);

}

sequenceBox::~sequenceBox()
{
    delete ui;
}

void sequenceBox::on_pushButton_clicked()
{
    PositionFrame* f = new PositionFrame(this);
    f->setVisible(true);
    sequence->addPositionFrame(f);

}
