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
    menu->addAction("Insert Before",this,SLOT(insertBefore()));
    menu->addAction("Insert After",this,SLOT(insertAfter()));
    menu->addAction("Delete");
    menu->addAction("Cut");
    menu->addAction("Copy");
    menu->addAction("Paste Before");
    menu->addAction("Paste After");
    menu->exec(ev->globalPos());
}
void SequenceScrollArea::insertBefore()
{
    qDebug() << "insert before";
}
void SequenceScrollArea::insertAfter()
{
    qDebug() << "insert after";
}
