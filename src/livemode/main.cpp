#include <QtGui/QApplication>
#include "sequencebox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sequenceBox w;
    w.show();
    
    return a.exec();
}
