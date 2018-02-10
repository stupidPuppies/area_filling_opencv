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
    cannytesterwindow.cpp

HEADERS += \
        mainwindow.h \
    imgoperate.h \
    cannytesterwindow.h

FORMS += \
        mainwindow.ui \
    cannytesterwindow.ui



win32-g++ {
    LIBS += -llibopencv_calib3d331 \
    -llibopencv_core331 \
    -llibopencv_dnn331 \
    -llibopencv_features2d331 \
    -llibopencv_flann331 \
    -llibopencv_highgui331 \
    -llibopencv_imgcodecs331 \
    -llibopencv_imgproc331 \
    -llibopencv_ml331 \
    -llibopencv_objdetect331 \
    -llibopencv_photo331 \
    -llibopencv_shape331 \
    -llibopencv_stitching331 \
    -llibopencv_superres331 \
    -llibopencv_video331 \
    -llibopencv_videoio331 \
    -llibopencv_videostab331
}
win32-msvc*{
INCLUDEPATH += C:/opencv/3.4.0/build/include
LIBS += C:/opencv/3.4.0/build/x64/vc15/lib/opencv_world340d.lib
}
