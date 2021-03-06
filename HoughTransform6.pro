#-------------------------------------------------
#
# Project created by QtCreator 2016-03-20T18:27:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HoughTransform6
TEMPLATE = app

RC_FILE = mainwindow.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    mattoqimage.cpp \
    capture.cpp \
    processframe.cpp \
    canny.cpp \
    canny.cpp \
    mytransform.cpp \
    opencvtransform.cpp

HEADERS  += mainwindow.h \
    mattoqimage.h \
    capture.h \
    processframe.h \
    canny.h \
    mytransform.h \
    opencvtransform.h \
    transform.h

FORMS    += mainwindow.ui \
    capture.ui \
    canny.ui

####################################################

INCLUDEPATH += C:\opencv\build\include
LIBS += -LC:\opencv\mybuild\lib\Debug\
 -lopencv_imgcodecs310d \
 -lopencv_imgproc310d \
 -lopencv_ml310d \
 -lopencv_objdetect310d \
 -lopencv_photo310d \
 -lopencv_shape310d \
 -lopencv_stitching310d \
 -lopencv_superres310d \
 -lopencv_ts310d \
 -lopencv_video310d \
 -lopencv_videoio310d \
 -lopencv_videostab310d \
 -lopencv_calib3d310d \
 -lopencv_core310d \
 -lopencv_features2d310d \
 -lopencv_flann310d \
 -lopencv_highgui310d

LIBS += -Lc:\opencv\mybuild\3rdparty\lib\Debug\
 -lIlmImfd \
 -llibjasperd \
 -llibjpegd \
 -llibpngd \
 -llibtiffd \
 -llibwebpd \
 -lzlibd

###################################################
