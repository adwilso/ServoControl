/*
 *This is used to represent a single set of positions that can be sent to
 *the servo board along with the information about the PWM parameters used
 *during the motion and the delay before the next motion can occur.
 *
 *The values to be sent to each servo are stored in a dictionary with the
 *servo number as the key and the servo value as the value. Also in the
 *dictionary are the special function values, which are keyed using the
 *SpecialFunction enum.
 *
 *The toString and fromString function are inverses of each other assuming
 *legacy mode is false. In the case of legacy mode being true they are not
 *guaranteed to be inverses.
 *
 *The getSerialData returns a byte stream that will be sent to the board.
 *The choice to separate the PWM values from the rest of the data was done
 *to allow for backwards compatibility with older boards that cannot handle
 *the PWM commands.
 *
 *
 *Storage Notes: Store PWMRepeat as 0-->7, use lookup for actual value.
 *This is done as the board accepts a number from 0-7 as the repeat value,
 *and then uses an internal lookup table to convert that value to the actual
 *one. All user facing strings and values must contain the number of repeats
 *the board will actually use. The mapping can be found in m_PWMRepeatMap
 *where the key is the value sent to the board, and the value is the user-
 *visible value.
 *
 *Usage Note: If a parsing from string fails, the state of the position
 *cannot be ensured to be valid. Once parsing fails, you must either parse
 *a valid string or get a new object. The only exception is parsing an empty
 *string, which will return true, but set that there is no data. Check this
 *afterwards to be sure.
 *
 *This does not inherit from QObject as the copy constuctor is needed in
 *a number of places and there is no use for signals or slots in the current
 *implementation.
 */
#ifndef POSITION_H
#define POSITION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QMap>
#include <QDebug>

class Position
{
public:
    //Used as keys for the QMap to get the values for each special function.
    enum SpecialFunction {PWMRepeat = 13, PWMSweep = 14, SeqDelay = 15};

    //The autogenerated copy constuctor is just fine
    Position();

    //These are used to get the strings displayed on on the screen and to
    //parse changes to files. They are full of noisy debug statments
    QString toString(bool legacyMode = false);//Human readable string
    bool fromString(QString input);

    //The byte array is NULL terminated, can't just get a pointer to it

    //This is only contains only up to 12 servo addresses and value pairs,
    //and freeze/unfreeze commands.
    QByteArray toServoSerialData();

    //This returns the two byte PWM command
    QByteArray getPWMSerialData(bool* okay = 0);
    //Make sure you check this before asking for the serial command,
    //otherwise you may get junk back.
    bool hasPWMData();

    //Used to set the board number for chaining multiple boards together,
    //This is completely untested in real applications.
    int getBoardNumber();
    bool setBoardNumber(int boardNumber);
    //Set if there needs to be a freeze/unfreeze command included in the PWMSerialdata
    void setFreeze(bool newFreeze);
    int getDelay();//returns zero if there is none;

    bool isEmpty();//This checks servo values, delays, sweeps, and repeats.

    //Used for displaying data to the user about the positions
    bool hasPositonDataFor(int servoNumber);
    int getPositionDataFor(int servoNumber);

    //Add new single servo values to the positon.
    bool addServoPosition(quint8 servoNum, quint8 servoPosition, bool& overwrite);//False on invalid data
    bool addServoPosition(quint8 servoNum, quint8 servoPosition);
    //Add new special functions to the positon
    bool addAdvancedPosition(SpecialFunction function, quint8 value);//No lookup for PWM repeat, use value as given
    bool addAdvancedPositionIndex(SpecialFunction function, quint8 index); //Will lookup for PWM repeat

private:
    //Sets up the m_PWMRepeat map
    void init();
    //Used in string formations, intelligently chooses to add needed commas
    void addTerminatingComma(QString& string);
    //Builds the freeze and PWMSweep/Repeat section of the user visible string
    //Cannot be used for legacy strings.
    QString createStartOfString();
    //Parse the PWMRepeats/sweeps from the start of an input string and removes them
    bool parseStartOfString(QStringList& input);
    //Parses through all the servo positions in a string and stores them.
    bool parseServoPositions(QStringList& input);
    //Utility methods for making the commands
    void bitSet(quint8& byte, int position);
    void bitClear(quint8& byte, int position);

    //Holds the mapping between PWMRepeat value stored and the
    //user visible value
    QMap<quint8,int> m_PWMRepeatMap;
    //Stores address value pairs, along with the special function values.
    QMap<quint8,quint8> m_data;
    //Current board number.
    int m_boardNumber;
    //Flags to save time coding.
    bool m_hasData;
    bool m_isFreeze;
    bool m_hasDelay;
    bool m_hasPWM;

};

#endif // POSITION_H
