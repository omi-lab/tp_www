TARGET = tp_www
TEMPLATE = lib

DEFINES += TDP_WWW_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_www/Globals.h

SOURCES += src/Request.cpp
HEADERS += inc/tp_www/Request.h

SOURCES += src/Route.cpp
HEADERS += inc/tp_www/Route.h

SOURCES += src/routes/DebugRoute.cpp
HEADERS += inc/tp_www/routes/DebugRoute.h
