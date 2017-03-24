QT += core widgets

SOURCES += \
    main.cpp \
    scene.cpp \
    mainwindow.cpp \
    lineitem.cpp \
    commands.cpp \
    colorlatexwidget.cpp \
    abstractitem.cpp \
    userpenstyle.cpp \
    polylineitem.cpp \
    abstractline.cpp \
    abstractshape.cpp \
    rectangleltem.cpp \
    latextext.cpp \
    ellipseitem.cpp \
    polygonitem.cpp \
    textitem.cpp

HEADERS += \
    scene.h \
    mainwindow.h \
    lineitem.h \
    abstractitem.h \
    commands.h \
    colorlatexwidget.h \
    paramslines.h \
    userpenstyle.h \
    polylineitem.h \
    abstractline.h \
    abstractshape.h \
    rectangleltem.h \
    latextext.h \
    ellipseitem.h \
    polygonitem.h \
    textitem.h

RESOURCES += \
    userdrawing.qrc

#DEFINES += QT_NO_DEBUG_OUTPUT

include(color_widgets.pri)

FORMS += \
    colorlatexwidget.ui \
    userpenstyle.ui \
    latextextnew.ui
