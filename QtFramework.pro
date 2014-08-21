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
    Core/LinearCombination3.cpp \
    Model/Skeleton.cpp \
    Core/Transformations.cpp \
    GUI/SceneGLWidget.cpp \
    GUI/PostureGLWidget.cpp \
    GUI/SkeletonGLWidget.cpp \
    GUI/SceneView.cpp \
    GUI/Render.cpp \
    GUI/EditJoint.cpp \
    GUI/SkeletonList.cpp \
    GUI/AddNewSkeleton.cpp \
    GUI/EditSkeleton.cpp \
    GUI/SkeletonSideWidget.cpp \
    Model/Cor3d.cpp

HEADERS += \
    GUI/MainWindow.h \
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
    Model/Skeleton.h \
    Core/Constants.h \
    Core/Transformations.h \
    GUI/SkeletonGLWidget.h \
    GUI/PostureGLWidget.h \
    GUI/SceneGLWidget.h \
    GUI/SceneView.h \
    GUI/Render.h \
    GUI/glwidget.h \
    GUI/EditJoint.h \
    GUI/SkeletonList.h \
    GUI/AddNewSkeleton.h \
    GUI/EditSkeleton.h \
    Model/ISkeleton.h \
    Model/BaseEntity.h \
    GUI/SkeletonSideWidget.h \
    Model/Posture.h \
    Model/Joint.h \
    Model/Cor3d.h

FORMS += \
    GUI/MainWindow.ui \
    GUI/SideWidget.ui \
    GUI/Render.ui\
    GUI/Render.ui \
    GUI/EditJoint.ui \
    GUI/SkeletonList.ui \
    GUI/AddNewSkeleton.ui \
    GUI/EditSkeleton.ui \
    GUI/EditSkeleton.ui \
    GUI/SkeletonSideWidget.ui

QT += opengl

INCLUDEPATH += ./Dependencies/Include

LIBS += ./Dependencies/LIB/GL/glew32.lib ./Dependencies/LIB/GL/glew32.dll

CONFIG += console
