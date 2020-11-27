QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        dirmodel.cpp \
        listfiles.cpp \
        main.cpp \
        models/dirmodel.cpp \
        models/listfiles.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    translations/cpp-code-analyzer_pl_PL.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += \
    $$PWD/models

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dirmodel.h \
    listfiles.h \
    models/dirmodel.h \
    models/listfiles.h
