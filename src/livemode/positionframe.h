#ifndef POSITIONFRAME_H
#define POSITIONFRAME_H

#include <QMouseEvent>
#include <QFrame>
#include "nameeditarea.h"
#include "editarea.h"
#include "servoboard/position.h"

namespace Ui {
class PositionFrame;
}

class PositionFrame : public QFrame
{
    Q_OBJECT
    
public:
    explicit PositionFrame(QWidget *parent = 0);
    ~PositionFrame();

    QString getName();

protected:
    void mouseReleaseEvent(QMouseEvent * ev);

private slots:
    void focusChanged(int newFocusIndex);
    void dataChanged(int newValue, int index);
    void newName(QString name);
signals:
    void newFocus(int i);
    
private:
    void initalizePosition();
    void selected();
    void unselected();
    Ui::PositionFrame *ui;
    EditArea* servoEdits[12];
    NameEditArea* name;
    Position* m_position;
    bool active;
};

#endif // POSITIONFRAME_H
