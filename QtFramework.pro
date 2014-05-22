SOURCES += \
    main.cpp \
    GUI/MainWindow.cpp \
    GUI/GLWidget.cpp \
    GUI/SideWidget.cpp \
    Core/RealSquareMatrices.cpp \
    Core/GenericCurves3.cpp \
    Core/Lights.cpp \
    Core/Materials.cpp \
    Core/TriangulatedMeshes3.cpp \
    Core/LinearCombination3.cpp

HEADERS += \
    GUI/MainWindow.h \
    GUI/GLWidget.h \
    GUI/SideWidget.h \
    Core/DCoordinates3.h \
    Core/Matrices.h \
    Core/RealSquareMatrices.h \
    Core/GenericCurves3.h \
    Core/HCoordinates3.h \
    Core/TriangularFaces.h \
    Core/Lights.h \
    Core/Exceptions.h \
    Core/Colors4.h \
    Core/Materials.h \
    Core/TriangulatedMeshes3.h \
    Core/TCoordinates4.h \
    Core/LinearCombination3.h \
    Model/Joints.h \
    Model/Skeleton.h

FORMS += \
    GUI/MainWindow.ui \
    GUI/SideWidget.ui \

QT += opengl

INCLUDEPATH += ./Dependencies/Include

LIBS += ./Dependencies/LIB/GL/glew32.lib ./Dependencies/LIB/GL/glew32.dll

CONFIG += console
