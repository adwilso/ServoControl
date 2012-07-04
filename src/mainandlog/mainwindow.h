#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <abstractserial.h>


#include "serialtools/connectioncontroller.h"
#include "servoboard/servoboardcontroller.h"
#include "livemode/sequencebox.h"

QT_BEGIN_NAMESPACE
class LogViewer;
class QGridLayout;
class QTabWidget;
class SerialWidget;
class NetworkWidget;
class servoboard_main;
QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // public methods
    explicit MainWindow(QWidget *parent = 0, QPointer<LogViewer> = NULL);
    ~MainWindow();

public slots:
    void logWindowHidden();

private slots:
    void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_actionView_Log_triggered();
    void on_actionAbout_Qt_triggered();

private slots:
    void tabChanged(int index);

private:
    // private methods
    void SetupStatusBar();
    void SetupLayout();
    void initConnection();
    void cleanUpConnection();
    void initServoBoard();
    void cleanupServoBoard();
    void initNetworking();
    void cleanUpNetworking();


private:
    // private variables
    Ui::MainWindow *ui;
    QGridLayout *layout;
    QTabWidget *tabs;
    SerialWidget *serialconnecter;
    NetworkWidget *networktab;
    servoboard_main *servotab;
    QPointer<LogViewer> logWindow;



    ConnectionController* connectControl;
    ServoboardController* servoControl;
    AbstractSerial* port;

    sequenceBox *liveMode;

    bool destroying;



};

#endif // MAINWINDOW_H
