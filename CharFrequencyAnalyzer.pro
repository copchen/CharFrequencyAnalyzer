QT += core gui widgets concurrent
QT += xml




CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    docxanalyzer.cpp \


HEADERS += \
    mainwindow.h \
    docxanalyzer.h \
    analysisdata.h \


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

!isEmpty(target.path): INSTALLS += target
