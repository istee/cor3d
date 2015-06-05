#pragma once

#include "IMainWindowTab.h"

#include "ui_PostureEditorTab.h"

class PostureEditorTab: public IMainWindowTab, public Ui::PostureEditorTab
{
    Q_OBJECT
public:
    PostureEditorTab(QWidget* parent = 0);
    void initialize();

private slots:
    void handle_model_skeleton_added(const string& name);
    void handle_model_skeleton_deleted(const string& name);
    void handle_model_skeleton_selection_changed(const string& oldSelectionName, const string& newSelectionName);
    void handle_model_skeleton_renamed(const string& oldName, const string& newName);
};
