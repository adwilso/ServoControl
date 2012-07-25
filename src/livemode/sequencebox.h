#ifndef SEQUENCEBOX_H
#define SEQUENCEBOX_H

#include <QMainWindow>
#include "editarea.h"
#include "nameeditarea.h"
#include "positionframe.h"
#include "sequenceframe.h"
#include "sequencecontainer.h"
namespace Ui {
class sequenceBox;
}

class sequenceBox : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit sequenceBox(QWidget *parent = 0);
    ~sequenceBox();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::sequenceBox *ui;
    EditArea* edit;
    EditArea* edit2;
    NameEditArea* edit3;
    PositionFrame* frame;
    PositionFrame* frame2;
    PositionFrame* frame3;
    SequenceFrame* sequence;
    SequenceContainer* scroll;

};

#endif // SEQUENCEBOX_H
