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
    bool setName(QString name);

    quint8 getServoData(int servoNumber);
    bool setServoData(int servoNumber, int data);

    PositionFrame* copy(QWidget *parent = 0);

    void unselected();

protected:
    void mouseReleaseEvent(QMouseEvent * ev);

private slots:
    void focusChanged(int newFocusIndex);
    void dataChanged(int newValue, int index);
    void newName(QString name);
signals:
    void newFocus(int i);
    void selected(PositionFrame* selectedFrame);
    
private:
    void initalizePosition();
    void selected();
    Ui::PositionFrame *ui;
    EditArea* servoEdits[12];
    NameEditArea* name;
    Position* m_position;
    bool active;
};

#endif // POSITIONFRAME_H
