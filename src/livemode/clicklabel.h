#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(QWidget *parent = 0);
    
signals:
    void clicked();

protected:
    void mouseReleaseEvent( QMouseEvent * event ) ;

    
};

#endif // CLICKLABEL_H
