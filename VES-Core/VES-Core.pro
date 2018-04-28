#-------------------------------------------------
#
# Project created by QtCreator 2017-06-03T12:52:56
#
#-------------------------------------------------

QT       += core network svg concurrent

QT       -= gui

TARGET = VES-Core
TEMPLATE = lib
CONFIG += lib c++11
DEFINES += VESCORE_LIBRARY

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
        VESCore.cpp \
    BasicData.cpp \
    SpliceData.cpp \
    ModelData.cpp \
    LocationData.cpp \
    InversionModel.cpp \
    VES.cpp \
    XmlSerializer.cpp \
    Project.cpp \
    OldProject.cpp \
    ZohdyModel.cpp \
    VFSAInversionModel.cpp \
    VFSA/VFSASolutionJob.cpp \
    VFSA/VFSAJobResult.cpp \
    VFSA/VFSACalculator.cpp \
    VFSA/VFSAParameters.cpp \
    VFSA/VFSAParameterLimit.cpp

HEADERS += \
        VESCore.h \
        ves-core_global.h \ 
    BasicData.h \
    SpliceData.h \
    ModelData.h \
    LocationData.h \
    InversionModel.h \
    VES.h \
    Serializable.h \
    Serializer.h \
    XmlSerializer.h \
    Project.h \
    OldProject.h \
    ZohdyModel.h \
    VFSAInversionModel.h \
    VFSA/VFSASolutionJob.h \
    VFSA/VFSAJobResult.h \
    VFSA/VFSACalculator.h \
    VFSA/VFSAParameters.h \
    VFSA/VFSAParameterLimit.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
