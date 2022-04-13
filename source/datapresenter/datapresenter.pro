QT       += core gui network
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barchartcard.cpp \
    cardarea.cpp \
    checkboxgroup.cpp \
    concretestatfi.cpp \
    controller.cpp \
    leftsidebar.cpp \
    linechartcard.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    rightsidebar.cpp \
    timerangedialog.cpp \
    timerangewidget.cpp \
    valuetabledialog.cpp

HEADERS += \
    barchartcard.hh \
    cardarea.hh \
    chartcard.hh \
    checkboxgroup.hh \
    concretestatfi.hh \
    controller.hh \
    idatafetcher.hh \
    leftsidebar.hh \
    linechartcard.hh \
    mainwindow.hh \
    model.hh \
    rightsidebar.hh \
    timerangedialog.hh \
    timerangewidget.hh \
    valuetabledialog.hh

FORMS += \
    mainwindow.ui \
    timerangedialog.ui \
    valuetabledialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
