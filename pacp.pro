TEMPLATE = app
INCLUDEPATH += .

QT           += network
QT           += network widgets
QT           += widgets
QT += gui

# Input
HEADERS += ledmeter.h sprites.h toplevel.h view.h animateditem.h \
    geome.h \
    gmu.h \
    ghost.h \
    pacsettings.h \
    messages.h \
    consco.h \
    pacinit.h \
    texthuds.h \
    lios.h \
    qbarrayio.h \
    ghostmode2.h
SOURCES += ledmeter.cpp main.cpp toplevel.cpp view.cpp animateditem.cpp \
    geome.cpp \
    ghost.cpp \
    consco.cpp \
    messages.cpp \
    texthuds.cpp \
    lios.cpp \
    qbarrayio.cpp
QT           += network
#RESOURCES += pacp.qrc
#contains(QT_CONFIG,  opengl): QT += opengl

qtHaveModule(opengl): QT += opengl

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/graphicsview/portedasteroids
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS pacman.pro  
#sources.path = $$[QT_INSTALL_EXAMPLES]/graphicsview/portedasteroids

INSTALLS += target sources

