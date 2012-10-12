#ifndef SERVOBOARDCONTROLLER_H
#define SERVOBOARDCONTROLLER_H

#include <QObject>
#include <QFileDialog>
#include <QTimer>

#include <abstractserial.h>
#include "servoboard_main.h"
#include "sequence.h"
#include "position.h"


class ServoboardController : public QObject
{
    Q_OBJECT
    enum PlaybackState {play, pause, stop};
public:
    explicit ServoboardController(AbstractSerial* port, servoboard_main* form, QObject *parent = 0);
    ~ServoboardController();
    AbstractSerial* returnSerialPort();

signals:
    void newPositionSent(Position* p);
public slots:
    void loadFile();
    void saveFile();
    void saveFileAs();
    void newPositionForSequence(Position* p);
    void playPosition(Position *p);
    void playCurrentSequence();
    void timerTimeout();
    void setGlobalDelay(int delay);
    void setGlobalReplay(int replay);
    void globalVariableSetRequested();
    void suppressChangeNotifications(bool isChecked);
    void pauseSequence();
    void stopSequence();
    void setStartPosition(Position* p);
    void burnStartPosition();
    void hotModeToggle(Position* p);
    void hotModeUpdate();


private:
    explicit ServoboardController(QObject *parent = 0); //A kitten dies when you call this and segfault so don't
    void init();

    bool checkForChangesToTextSequence();
    void resetAfterPlayback();

    void setGlobalPWMValues(int globalPWMSweep, int globalPWMRepeat);

    AbstractSerial* port;
    servoboard_main* view;
    Sequence* displayedData;

    QTimer* timer;
    int globalDelay;
    int globalReplay;
    int currentReplays;
    int globalPWMSweep;
    int globalPWMReplay;
    bool suppressChangeNotification;
    PlaybackState playState;
    static QString fileName;
    bool isHotMode;




};


#endif // SERVOBOARDCONTROLLER_H
