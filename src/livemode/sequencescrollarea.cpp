#include "sequencescrollarea.h"
#include "ui_sequencescrollarea.h"

SequenceScrollArea::SequenceScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::SequenceScrollArea)
{
    ui->setupUi(this);
}

SequenceScrollArea::~SequenceScrollArea()
{
    delete ui;
}
void SequenceScrollArea::contextMenuEvent(QContextMenuEvent *ev)
{
    QMenu* menu = new QMenu(this);
    menu->addAction("Insert Before");
    menu->addAction("Insert After");
    menu->addAction("Delete");
    menu->addAction("Cut");
    menu->addAction("Copy");
    menu->addAction("Paste Before");
    menu->addAction("Paste After");
    menu->exec(ev->globalPos());
}
