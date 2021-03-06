#-------------------------------------------------
#
# Project created by QtCreator 2017-06-03T12:54:06
#
#-------------------------------------------------

QT       += core gui charts opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QVES
TEMPLATE = app

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
        main.cpp \
        MainWindow.cpp \
    DataPanel.cpp \
    MainChart.cpp \
    VESPropertiesPanel.cpp \
    TableDelegate.cpp \
    QVESChartSerie.cpp \
    QVESSettings.cpp \
    Commands/ChangeCurrentVESCommand.cpp \
    Commands/ZohdyInversionCommand.cpp \
    PanelsDelegateMediator.cpp \
    Commands/EditVESNameCommand.cpp \
    Commands/EditVESDataCommand.cpp \
    Commands/CommandsManager.cpp \
    Commands/VFSAInversionCommand.cpp \
    Dialogs/QVESSettingsDialog.cpp \
    Dialogs/NewCustomModelDialog.cpp \
    Dialogs/VFSAInversionDialog.cpp

HEADERS += \
        MainWindow.h \
    DataPanel.h \
    MainChart.h \
    VESPropertiesPanel.h \
    TableDelegate.h \
    QVESChartSerie.h \
    QVESSettings.h \
    Commands/ChangeCurrentVESCommand.h \
    Commands/ZohdyInversionCommand.h \
    PanelsDelegateMediator.h \
    Commands/EditVESNameCommand.h \
    Commands/EditVESDataCommand.h \
    Commands/CommandsManager.h \
    Commands/VFSAInversionCommand.h \
    Dialogs/QVESSettingsDialog.h \
    Dialogs/NewCustomModelDialog.h \
    Dialogs/VFSAInversionDialog.h

FORMS += \
        MainWindow.ui \
    DataPanel.ui \
    VESPropertiesPanel.ui \
    Dialogs/QVESSettingsDialog.ui \
    Dialogs/NewCustomModelDialog.ui \
    Dialogs/VFSAInversionDialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../VES-Core/release/ -lVES-Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../VES-Core/debug/ -lVES-Core
else:unix: LIBS += -L$$OUT_PWD/../VES-Core/ -lVES-Core
#else:mac: DYLD_LIBRARY_PATH += -L$$OUT_PWD/../VES-Core/ -lVES-Core

INCLUDEPATH += $$PWD/../VES-Core
DEPENDPATH += $$PWD/../VES-Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QVES-ModelDelegate/release/ -lQVES-ModelDelegate
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QVES-ModelDelegate/debug/ -lQVES-ModelDelegate
else:unix: LIBS += -L$$OUT_PWD/../QVES-ModelDelegate/ -lQVES-ModelDelegate
#else:mac: DYLD_LIBRARY_PATH += -L$$OUT_PWD/../QVES-ModelDelegate/ -lQVES-ModelDelegate

INCLUDEPATH += $$PWD/../QVES-ModelDelegate
DEPENDPATH += $$PWD/../QVES-ModelDelegate

RESOURCES += \
    resources.qrc

windows {
       ICON = icon.png
}
linux {
       ICON = icon.png
}
macx {
       ICON = icon.icns
}
