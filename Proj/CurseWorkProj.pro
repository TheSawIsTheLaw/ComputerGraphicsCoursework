QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS +=  -fopenmp
QMAKE_CXXFLAGS += -O3
QMAKE_LFLAGS += -O3

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additivemathelements.cpp \
    illuminantplacechooser.cpp \
    main.cpp \
    mainwindow.cpp \
    objecthangman.cpp \
    objects.cpp \
    placechooser.cpp \
    RotationChooser.cpp \
    sizechanger.cpp \
    sizechooser.cpp \
    specialgraphicsview.cpp \
    usagefacade.cpp

HEADERS += \
    additivemathelements.hpp \
    config.hpp \
    illuminantplacechooser.hpp \
    mainwindow.h \
    objecthangman.hpp \
    objects.hpp \
    placechooser.h \
    RotationChooser.hpp \
    sizechanger.hpp \
    sizechooser.hpp \
    specialgraphicsview.hpp \
    usagefacade.hpp

FORMS += \
    illuminantplacechooser.ui \
    mainwindow.ui \
    objecthangman.ui \
    placechooser.ui \
    RotationChooser.ui \
    sizechanger.ui \
    sizechooser.ui

RC_ICONS += imgs\icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
