QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/ImageManager
INCLUDEPATH += $$PWD/Filters
INCLUDEPATH += $$PWD/Converter
INCLUDEPATH += $$PWD/ImageHistoryManager
INCLUDEPATH += $$PWD/ImageIO
INCLUDEPATH += $$PWD/ImageHistoryIO
INCLUDEPATH += $$PWD/UI

SOURCES += \
    Converter/converter.cpp \
    Filters/filters.cpp \
    Filters/filtersfactory.cpp \
    ImageHistoryManager/imagehistory.cpp \
    ImageHistoryIO/imagehistoryio.cpp \
    ImageHistoryManager/imagehistorymanager.cpp \
    ImageIO/imageio.cpp \
    ImageManager/imagemanager.cpp \
    UI/main.cpp \
    UI/mainwindow.cpp

HEADERS += \
    Converter/converter.h \
    Filters/filters.h \
    Filters/filtersfactory.h \
    ImageHistoryManager/imagehistory.h \
    ImageHistoryIO/imagehistoryio.h \
    ImageHistoryManager/imagehistorymanager.h \
    ImageIO/imageio.h \
    ImageManager/imagemanager.h \
    UI/mainwindow.h

FORMS += \
    UI/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DEPENDPATH += $$PWD/../../OpenCV/opencv/build/include
INCLUDEPATH += $$PWD/../../OpenCV/opencv/build/include

win32:CONFIG(release, debug|release) {
    LIBS += -L$$PWD/../../OpenCV/opencv/build/x64/vc16/lib -lopencv_world4120
}

win32:CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../OpenCV/opencv/build/x64/vc16/lib -lopencv_world4120d
}


