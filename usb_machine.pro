TEMPLATE = app
CONFIG            += qt warn_on opengl thread zlib
QT                += widgets core opengl

MOC_DIR           = tmp
OBJECTS_DIR       = tmp

HEADERS = mainwindow.h \
    mainwidget.h \
    customedittext.h \
    optionswidget.h \
    mainoptions.h \
    machineoptions.h \
    codehighlighter.h \
    compilator.h \
    DEF.h \
    Parser.h \
    parsertypes.h \
    ast.h \
    modeling.h \
    usbconnection.h \
    highlightrule.h \
    instrumentwidget.h \
    searchwidget.h \
    usbtool.h \
    jenia.h \
    track.h

SOURCES = main.cpp \
    mainwindow.cpp \
    mainwidget.cpp \
    customedittext.cpp \
    optionswidget.cpp \
    mainoptions.cpp \
    machineoptions.cpp \
    codehighlighter.cpp \
    compilator.cpp \
    func.cpp \
    lex.yy.cpp \
    Parser.cpp \
    ast.cpp \
    usbconnection.cpp \
    highlightrule.cpp \
    instrumentwidget.cpp \
    modeling.cpp \
    searchwidget.cpp \
    usbtool.cpp \
    jenia.cpp \
    track.cpp

INSTALLS += target

QMAKE_CXXFLAGS_RELEASE += -O3

LIBS += -L"C:/Program Files (x86)/GnuWin32/lib" -lfl \
#    static/lib/qwtplot3d.dll \
    -lusb-1.0

#INCLUDEPATH += static/include

LIBS +=  -lqwtplot3d \
    -lalglib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/static/lib/ \
    -lqwtplot3d -lalglib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/static/lib/ \
    -lqwtplot3d -lalglib

INCLUDEPATH += $$PWD/static/include
DEPENDPATH += $$PWD/static/include
