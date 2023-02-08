#-------------------------------------------------
#
# Project created by QtCreator 2018-06-29T15:58:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ml-app
TEMPLATE = app

CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    detectionwindow.cpp \
    facedetector.cpp \
    objectdetector.cpp \
    help.cpp \
    language.cpp

HEADERS += \
        mainwindow.h \
    detectionwindow.h \
    detectortype.h \
    facedetector.h \
    detector.h \
    objectdetector.h \
    help.h \
    language.h

FORMS += \
        mainwindow.ui \
    detectionwindow.ui \
    help.ui

RESOURCES += \
    resources.qrc

unix {
QT_CONFIG -= no-pkg-config
CONFIG  += link_pkgconfig
PKGCONFIG += opencv
}

win32 {
INCLUDEPATH += includes

LIBS += D:\Develop\Qt\machine-learning-app\machine-learning-app\src\ml-app\lib\libopencv_core341.dll
LIBS += D:\Develop\Qt\machine-learning-app\machine-learning-app\src\ml-app\lib\libopencv_highgui341.dll
LIBS += D:\Develop\Qt\machine-learning-app\machine-learning-app\src\ml-app\lib\libopencv_imgproc341.dll
LIBS += D:\Develop\Qt\machine-learning-app\machine-learning-app\src\ml-app\lib\libopencv_videoio341.dll
LIBS += D:\Develop\Qt\machine-learning-app\machine-learning-app\src\ml-app\lib\libopencv_dnn341.dll
LIBS += D:\Develop\Qt\machine-learning-app\machine-learning-app\src\ml-app\lib\libopencv_imgcodecs341.dll
LIBS += D:\Develop\Qt\machine-learning-app\machine-learning-app\src\ml-app\lib\libopencv_objdetect341.dll
}
