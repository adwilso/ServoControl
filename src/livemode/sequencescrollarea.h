#ifndef SEQUENCESCROLLAREA_H
#define SEQUENCESCROLLAREA_H

#include <QScrollArea>
#include <QMenu>
#include <QPoint>
#include <QContextMenuEvent>
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
    
private:
    Ui::SequenceScrollArea *ui;
};

#endif // SEQUENCESCROLLAREA_H
