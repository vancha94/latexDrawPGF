QT += core widgets

SOURCES += \
    main.cpp \
    scene.cpp \
    mainwindow.cpp \
    lineitem.cpp \
    latextext.cpp \
    commands.cpp \
    colorlatexwidget.cpp \
    abstractitem.cpp \
    userpenstyle.cpp

HEADERS += \
    scene.h \
    mainwindow.h \
    lineitem.h \
    latextext.h \
    abstractitem.h \
    commands.h \
    colorlatexwidget.h \
    paramslines.h \
    userpenstyle.h

RESOURCES += \
    userdrawing.qrc

#DEFINES += QT_NO_DEBUG_OUTPUT

include(color_widgets.pri)

FORMS += \
    colorlatexwidget.ui \
    userpenstyle.ui
