QT       += core gui \
            charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animal.cpp \
    coord.cpp \
    grille.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    population.cpp

HEADERS += \
    animal.h \
    coord.h \
    grille.h \
    mainmenu.h \
    mainwindow.h \
    population.h

FORMS += \
    mainmenu.ui \
    mainwindow.ui

RC_ICONS += icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
