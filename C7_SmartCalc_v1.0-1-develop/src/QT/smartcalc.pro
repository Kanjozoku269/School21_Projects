QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = Calculator

SOURCES += ../QT/credit.cpp \
           ../QT/graph.cpp \
           ../QT/mainwindow.cpp \
           ../QT/main.cpp \
           ../QT/qcustomplot.cpp \
           ../backend/backend.c

HEADERS += ../QT/credit.h \
           ../QT/graph.h \
           ../QT/mainwindow.h \
           ../QT/qcustomplot.h \
           ../backend/backend.h

FORMS += ../QT/credit.ui \
         ../QT/graph.ui \
         ../QT/mainwindow.ui

         

# Default rules for deployment.
target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ICON = ../QT/1.icns

