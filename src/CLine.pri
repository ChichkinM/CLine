INCLUDEPATH *= $$PWD

!CPAINTER_IS_DEF {
    CONFIG += CPAINTER_IS_DEF

    HEADERS += $$PWD/cpainter.h
    SOURCES += $$PWD/cpainter.cpp
}

HEADERS *= \
    $$PWD/cline.h

SOURCES *= \
    $$PWD/cline.cpp
