#ifndef SEQUENCESCROLLAREA_H
#define SEQUENCESCROLLAREA_H

#include <QScrollArea>
#include <QMenu>
#include <QPoint>
#include <QContextMenuEvent>
#include <QDebug>
namespace Ui {
class SequenceScrollArea;
}

class SequenceScrollArea : public QScrollArea
{
    Q_OBJECT
    
public:
    explicit SequenceScrollArea(QWidget *parent = 0);
    ~SequenceScrollArea();
protected:
    void contextMenuEvent(QContextMenuEvent *);

private slots:
    void insertBefore();
    void insertAfter();
    
private:
    Ui::SequenceScrollArea *ui;
};

#endif // SEQUENCESCROLLAREA_H
