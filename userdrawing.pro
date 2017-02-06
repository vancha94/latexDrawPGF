QT += widgets

SOURCES += \
    main.cpp \
    scene.cpp \
    mainwindow.cpp \
    lineitem.cpp \
    latextext.cpp \
    commands.cpp

HEADERS += \
    scene.h \
    mainwindow.h \
    lineitem.h \
    latextext.h \
    abstractitem.h \
    commands.h

RESOURCES += \
    userdrawing.qrc

DEFINES += QT_NO_DEBUG_OUTPUT
