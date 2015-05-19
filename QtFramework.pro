SOURCES += \
    main.cpp \
    GUI/MainWindow.cpp \
    GUI/GLWidget.cpp \
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
    Model/Cor3d.cpp \
    Model/Joint.cpp \
    GUI/BasicWidgets/DCoordinate3GroupBox.cpp \
    GUI/SideWidgetComponents/SkeletonList.cpp \
    GUI/SideWidgetComponents/EditSkeleton.cpp \
    GUI/SideWidgetComponents/EditJoint.cpp \
    GUI/SideWidgetComponents/AddNewSkeleton.cpp \
    GUI/SideWidgetComponents/AddNewJoint.cpp \
    GUI/BasicWidgets/BaseEntityComboBox.cpp \
    GUI/SkeletonEditorTab.cpp \
    GUI/BasicWidgets/FileDisplayAndChooser.cpp \
    GUI/BasicWidgets/NameLineEdit.cpp \
    GUI/SideWidgetComponents/TransformationsWidget.cpp \
    GUI/SideWidgetComponents/RenderingOptionsWidget.cpp \
    Model/RenderingOptions.cpp \
    GUI/PostureEditorTab.cpp \
    GUI/SceneEditorTab.cpp \
    Model/BaseEntity.cpp \
    GUI/SideWidgetComponents/ManagePoses.cpp \
    GUI/SideWidgetComponents/ConfigurePose.cpp \
    GUI/SideWidgetComponents/ManageScene.cpp \
    GUI/SideWidgetComponents/ManageSceneTimePoints.cpp \
    GUI/PopupWindows/Export.cpp \
    GUI/PopupWindows/Import.cpp \
    GUI/Toolbars/TransformationsToolbar.cpp \
    GUI/IMainWIndowTab.cpp


HEADERS += \
    GUI/MainWindow.h \
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
    GUI/glwidget.h \
    Model/BaseEntity.h \
    Model/Posture.h \
    Model/Joint.h \
    Model/Cor3d.h \
    Cor3dApplication.h \
    StdExtension.h \
    GUI/RenderingOptions.h \
    GUI/BasicWidgets/DCoordinate3GroupBox.h \
    GUI/BasicWidgets/BaseEntityComboBox.h \
    GUI/SideWidgetComponents/SkeletonList.h \
    GUI/SideWidgetComponents/EditSkeleton.h \
    GUI/SideWidgetComponents/EditJoint.h \
    GUI/SideWidgetComponents/AddNewSkeleton.h \
    GUI/SideWidgetComponents/AddNewJoint.h \
    GUI/IMainWindowTab.h \
    GUI/SkeletonEditorTab.h \
    GUI/BasicWidgets/FileDisplayAndChooser.h \
    GUI/BasicWidgets/NameLineEdit.h \
    GUI/SideWidgetComponents/TransformationsWidget.h \
    GUI/SideWidgetComponents/RenderingOptionsWidget.h \
    GUI/SideWidgetComponents/SideWidgetGroupBox.h \
    GUI/SideWidgetComponents/BaseSideWidget.h \
    Model/MaterialContainer.h \
    GUI/PostureEditorTab.h \
    GUI/SceneEditorTab.h \
    Model/BaseEntityCollection.h \
    GUI/SideWidgetComponents/ConfigurePose.h \
    GUI/SideWidgetComponents/ManagePoses.h \
    GUI/SideWidgetComponents/ManageScene.h \
    GUI/SideWidgetComponents/ManageSceneTimePoints.h \
    GUI/MainWindowTabWidgetIncludes.h \
    Model/Chain.h \
    GUI/PopupWindows/Export.h \
    GUI/PopupWindows/Import.h \
    GUI/Toolbars/TransformationsToolbar.h

FORMS += \
    GUI/BasicWidgets/DCoordinate3GroupBox.ui \
    GUI/BasicWidgets/BaseEntityComboBox.ui \
    GUI/SideWidgetComponents/SkeletonList.ui \
    GUI/SideWidgetComponents/EditSkeleton.ui \
    GUI/SideWidgetComponents/EditJoint.ui \
    GUI/SideWidgetComponents/AddNewSkeleton.ui \
    GUI/SideWidgetComponents/AddNewJoint.ui \
    GUI/MainWindow.ui \
    GUI/SkeletonEditorTab.ui \
    GUI/BasicWidgets/NameLineEdit.ui \
    GUI/BasicWidgets/FileDisplayAndChooser.ui \
    GUI/SideWidgetComponents/TransformationsWidget.ui \
    GUI/SideWidgetComponents/RenderingOptionsWidget.ui \
    GUI/PostureEditorTab.ui \
    GUI/SceneEditorTab.ui \
    GUI/SideWidgetComponents/ConfigurePose.ui \
    GUI/SideWidgetComponents/ManagePoses.ui \
    GUI/SideWidgetComponents/ManageScene.ui \
    GUI/SideWidgetComponents/SetScenePose.ui \
    GUI/SideWidgetComponents/ManageSceneTimePoints.ui \
    GUI/SideWidgetComponents/DeleteTimePoint.ui \
    GUI/SideWidgetComponents/ManageAnimationTransitions.ui \
    GUI/PopupWindows/Export.ui \
    GUI/PopupWindows/Import.ui \
    GUI/Toolbars/TransformationsToolbar.ui


QT += opengl

INCLUDEPATH += ./Dependencies/Include \
    C:/boost_1_58_0/boost

LIBS += ./Dependencies/LIB/GL/glew32.lib ./Dependencies/LIB/GL/glew32.dll

CONFIG += console

RESOURCES +=
