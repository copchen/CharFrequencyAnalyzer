QT += core gui widgets concurrent
QT += xml

CONFIG += c++17

SOURCES += \
    fullstatsdialog.cpp \
    main.cpp \
    mainwindow.cpp \


HEADERS += \
    fullstatsdialog.h \
    mainwindow.h \
    analysisdata.h \


FORMS += \
    FullStatsDialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

!isEmpty(target.path): INSTALLS += target
