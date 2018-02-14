#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T18:23:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = area_filling_opencv
TEMPLATE = app

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
    imgoperate.cpp \
    cannytesterwindow.cpp \
    dragablelabel.cpp

HEADERS += \
        mainwindow.h \
    imgoperate.h \
    cannytesterwindow.h \
    dragablelabel.h

FORMS += \
        mainwindow.ui \
    cannytesterwindow.ui



win32-g++ {
    LIBS += -llibopencv_calib3d \
    -llibopencv_core \
    -llibopencv_dnn \
    -llibopencv_features2d \
    -llibopencv_flann \
    -llibopencv_highgui \
    -llibopencv_imgcodecs \
    -llibopencv_imgproc \
    -llibopencv_ml \
    -llibopencv_objdetect \
    -llibopencv_photo \
    -llibopencv_shape \
    -llibopencv_stitching \
    -llibopencv_superres \
    -llibopencv_video \
    -llibopencv_videoio \
    -llibopencv_videostab
}
win32-msvc*{
INCLUDEPATH += C:/opencv/3.4.0/build/include
LIBS += C:/opencv/3.4.0/build/x64/vc15/lib/opencv_world340d.lib
}
