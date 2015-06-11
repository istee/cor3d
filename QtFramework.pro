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
    GUI/SideWidgets/SkeletonSideWidget.cpp \
    GUI/EditWidgets/SkeletonEditWidget.cpp \
    GUI/SideWidgets/JointSideWidget.cpp \
    GUI/BasicWidgets/BaseEntityComboBox.cpp \
    GUI/SkeletonEditorTab.cpp \
    GUI/BasicWidgets/FileChooser.cpp \
    GUI/BasicWidgets/BaseEntityNameEdit.cpp \
    GUI/SideWidgets/RenderingOptionsWidget.cpp \
    Model/RenderingOptions.cpp \
    GUI/PostureEditorTab.cpp \
    GUI/SceneEditorTab.cpp \
    Model/BaseEntity.cpp \
    GUI/PopupWindows/Export.cpp \
    GUI/PopupWindows/Import.cpp \
    GUI/Toolbars/TransformationsToolbar.cpp \
    GUI/IMainWIndowTab.cpp \
    GUI/Toolbars/FileToolbar.cpp \
    GUI/BasicWidgets/BaseEntityListItem.cpp \
    GUI/WidgetExtensions/TreeWidgetExtension.cpp \
    GUI/SideWidgets/PostureSideWidget.cpp \
    GUI/SideWidgets/PostureJointSideWidget.cpp \
    GUI/EditWidgets/BaseEditWidget.cpp \
    GUI/WidgetExtensions/ListWidgetExtension.cpp \
    Model/Posture.cpp \
    GUI/EditWidgets/PostureEditWidget.cpp \
    GUI/WidgetExtensions/GroupBoxExtension.cpp \
    GUI/EditWidgets/JointEditWidget.cpp


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
    GUI/SideWidgets/SkeletonSideWidget.h \
    GUI/EditWidgets/SkeletonEditWidget.h \
    GUI/SideWidgets/JointSideWidget.h \
    GUI/IMainWindowTab.h \
    GUI/SkeletonEditorTab.h \
    GUI/BasicWidgets/FileChooser.h \
    GUI/BasicWidgets/BaseEntityNameEdit.h \
    GUI/SideWidgets/RenderingOptionsWidget.h \
    GUI/SideWidgets/BaseSideWidget.h \
    Model/MaterialContainer.h \
    GUI/PostureEditorTab.h \
    GUI/SceneEditorTab.h \
    Model/BaseEntityCollection.h \
    GUI/MainWindowTabWidgetIncludes.h \
    Model/Chain.h \
    GUI/PopupWindows/Export.h \
    GUI/PopupWindows/Import.h \
    GUI/Toolbars/TransformationsToolbar.h \
    GUI/WidgetExtensions/SpinboxExtension.h \
    GUI/Toolbars/FileToolbar.h \
    GUI/BasicWidgets/BaseEntityListItem.h \
    GUI/WidgetExtensions/TreeWidgetExtension.h \
    GUI/SideWidgets/PostureSideWidget.h \
    GUI/SideWidgets/PostureJointSideWidget.h \
    GUI/EditWidgets/BaseEditWidget.h \
    GUI/WidgetExtensions/ListWidgetExtension.h \
    GUI/WidgetExtensions/ToolButtonExtension.h \
    GUI/EditWidgets/PostureEditWidget.h \
    GUI/WidgetExtensions/GroupBoxExtension.h \
    GUI/EditWidgets/JointEditWidget.h

FORMS += \
    GUI/BasicWidgets/DCoordinate3GroupBox.ui \
    GUI/BasicWidgets/BaseEntityComboBox.ui \
    GUI/SideWidgets/SkeletonSideWidget.ui \
    GUI/EditWidgets/SkeletonEditWidget.ui \
    GUI/SideWidgets/JointSideWidget.ui \
    GUI/MainWindow.ui \
    GUI/SkeletonEditorTab.ui \
    GUI/BasicWidgets/BaseEntityNameEdit.ui \
    GUI/BasicWidgets/FileChooser.ui \
    GUI/SideWidgets/RenderingOptionsWidget.ui \
    GUI/PostureEditorTab.ui \
    GUI/SceneEditorTab.ui \
    GUI/PopupWindows/Export.ui \
    GUI/PopupWindows/Import.ui \
    GUI/Toolbars/TransformationsToolbar.ui \
    GUI/Toolbars/FileToolbar.ui \
    GUI/BasicWidgets/BaseEntityListItem.ui \
    GUI/SideWidgets/PostureSideWidget.ui \
    GUI/SideWidgets/PostureJointSideWidget.ui \
    GUI/EditWidgets/PostureEditWidget.ui \
    GUI/EditWidgets/JointEditWidget.ui


QT += opengl

INCLUDEPATH += ./Dependencies/Include

LIBS += ./Dependencies/LIB/GL/glew32.lib ./Dependencies/LIB/GL/glew32.dll

CONFIG += console

RESOURCES += Resources.qrc
