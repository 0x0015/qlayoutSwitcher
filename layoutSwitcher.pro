QT += widgets
#requires(qtConfig(filedialog))

HEADERS             = layoutSwitcher.h \
                      options.hpp \
                      SimpleCppTextFileHandler/file.hpp \
                      SimpleCppTextFileHandler/fileManipulation.hpp
SOURCES             = main.cpp \
                      layoutSwitcher.cpp \
                      options.cpp \
                      SimpleCppTextFileHandler/file.cpp \
                      SimpleCppTextFileHandler/fileManipulation.cpp
CONFIG+=c++17
#LIBS+=
RESOURCES = images.qrc
include(vendor/vendor.pri)
TARGET = qlayoutSwitcher
# install
