QT          += core gui
QT          += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= console


RC_FILE += myapp.rc

SOURCES += \
    begin.cpp \
    main.cpp \
    opentab.cpp \
    school.cpp

HEADERS += \
    begin.h \
    opentab.h \
    school.h

FORMS += \
    begin.ui \
    opentab.ui \
    school.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ico.qrc
