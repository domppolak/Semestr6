QT       += core gui opengl openglwidgets serialport
LIBS += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/car_item.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/obstacleCar.cpp \
    src/plotwindow.cpp \
    src/qcustomplot.cpp \
    src/receiverthread.cpp \
    src/road_item.cpp \
    src/scene.cpp \
    src/serialportreader.cpp \
    src/settingwindow.cpp

HEADERS += \
    inc/car_item.hh \
    inc/mainwindow.hh \
    inc/memsdata.hh \
    inc/obstacleCar.hh \
    inc/plotwindow.hh \
    inc/qcustomplot.h \
    inc/receiverthread.hh \
    inc/road_item.hh \
    inc/scene.hh \
    inc/serialportreader.hh \
    inc/settingwindow.hh \
    int/openglwidget.hh

FORMS += \
    forms/mainwindow.ui \
    forms/plotwindow.ui \
    forms/settingwindow.ui \

TRANSLATIONS += \
   translation/WDS_SRSP_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/led/led_blue.png \
    img/led/led_green.png \
    img/led/led_lightGray.png \
    img/led/led_red.png \
    img/led/led_yellow-00.png \
    img/led/led_yellow-01.png \
    img/led/led_yellow-02.png \
    img/led/led_yellow-03.png \
    img/led/led_yellow-04.png \
    img/led/led_yellow-05.png \
    img/led/led_yellow-06.png \
    img/led/led_yellow-07.png \
    img/led/led_yellow-08.png \
    img/led/led_yellow-09.png \
    img/led/led_yellow-10.png \
    img/led/led_yellow-11.png \
    img/led/led_yellow.png

INCLUDEPATH += inc\
    src\
    forms\
    translation



FORMS += \
    forms/mainwindow.ui \
    forms/settingwindow.ui \
    forms/plotwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

INCLUDEPATH += inc\
    src\
    forms\
    translation

RESOURCES += \
    resources.qrc

