#-------------------------------------------------
#
# Project created by QtCreator 2011-01-10T12:51:05
#
#-------------------------------------------------

QT       += core gui

TARGET = serial_app
TEMPLATE = app

unix:include(src/qserialdevice/unix/ttylocker.pri)
include(src/qserialdevice/qserialdeviceenumerator/qserialdeviceenumerator.pri)
include(src/qserialdevice/qserialdevice/qserialdevice.pri)

SOURCES += src/main.cpp\
    src/mainwidget.cpp \
    src/infowidget.cpp \
    src/tracewidget.cpp \
    src/mainwindow.cpp \
    src/logviewer.cpp \
    src/logviewerdialog.cpp
HEADERS += src/mainwidget.h \
    src/infowidget.h \
    src/tracewidget.h \
    src/mainwindow.h \
    src/logviewer.h \
    src/logviewerdialog.h
FORMS += src/mainwidget.ui \
    src/infowidget.ui \
    src/tracewidget.ui \
    src/mainwindow.ui

win32 {
    LIBS += -lsetupapi -luuid -ladvapi32
}
unix:!macx {
    LIBS += -ludev
}

OTHER_FILES +=

RESOURCES += \
    src/SerialPortIcons.qrc












