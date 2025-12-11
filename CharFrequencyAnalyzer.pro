QT += core gui widgets concurrent


CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    fullstatsdialog.cpp


HEADERS += \
    mainwindow.h \
    fullstatsdialog.h

FORMS += \
    mainwindow.ui \
    FullStatsDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

!isEmpty(target.path): INSTALLS += target
