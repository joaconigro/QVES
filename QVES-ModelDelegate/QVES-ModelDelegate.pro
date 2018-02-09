#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T10:06:53
#
#-------------------------------------------------

QT       -= gui

TARGET = QVES-ModelDelegate
TEMPLATE = lib
CONFIG += lib c++11
DEFINES += QVESMODELDELEGATE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        QVESModelDelegate.cpp \
    TableModel.cpp \
    XYDataTable.cpp

HEADERS += \
        QVESModelDelegate.h \
        qves-modeldelegate_global.h \ 
    TableModel.h \
    XYDataTable.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../VES-Core/release/ -lVES-Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../VES-Core/debug/ -lVES-Core
else:unix: LIBS += -L$$OUT_PWD/../VES-Core/ -lVES-Core
#else:mac: DYLD_LIBRARY_PATH += -L$$OUT_PWD/../VES-Core/ -lVES-Core

INCLUDEPATH += $$PWD/../VES-Core
DEPENDPATH += $$PWD/../VES-Core

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
