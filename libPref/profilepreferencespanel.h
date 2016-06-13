#ifndef PROFILEPREFERENCESPANEL_H
#define PROFILEPREFERENCESPANEL_H
#include "preferencespanel.h"
#include <QTableView>
#include "libpref_global.h"
class ProfilesTable;
class File;
class ListSelectionEvent;
class ActionEvent;
class QAction;
class QListView;
class QTabWidget;
class QCheckBox;
class QPushButton;
class LIBPREFSHARED_EXPORT ProfilePreferencesPanel : public PreferencesPanel
{
    Q_OBJECT
public:
    explicit ProfilePreferencesPanel(QWidget *parent = 0);
    ~ProfilePreferencesPanel() {}
    ProfilePreferencesPanel(const ProfilePreferencesPanel&) : PreferencesPanel() {}
    /*public*/ bool accept(File f);
    //@Override
    /*public*/ QString getPreferencesItem();
    /*public*/ QString getPreferencesItemText();
    /*public*/ QString getTabbedPreferencesTitle() ;
    /*public*/ QString getLabelKey();
    /*public*/ QWidget* getPreferencesComponent();
    /*public*/ bool isPersistant();
    /*public*/ QString getPreferencesTooltip();
    /*public*/ void savePreferences();
    /*public*/ void dispose();
    /*public*/ bool isDirty() ;
    /*public*/ bool isRestartRequired() ;
     /*public*/ bool accept(File* f);
     /*public*/ QString getDescription() ;
signals:

public slots:
    /*public*/ void valueChanged(ListSelectionEvent* e = 0);
private:
    /*private*/ void initComponents();
    // Variables declaration - do not modify
    /*private*/ QPushButton* btnActivateProfile;
    /*private*/ QPushButton* btnAddSearchPath;
    /*private*/ QPushButton* btnCopyProfile;
    /*private*/ QPushButton* btnCreateNewProfile;
    /*private*/ QPushButton* btnDeleteProfile;
    /*private*/ QPushButton* btnExportProfile;
    /*private*/ QPushButton* btnOpenExistingProfile;
    /*private*/ QPushButton* btnRemoveSearchPath;
    /*private*/ QCheckBox* chkStartWithActiveProfile;
    /*private*/ QAction* copyMI;
    /*private*/ QAction* deleteMI;
    /*private*/ QWidget* enabledPanel;
//    /*private*/ JScrollPane jScrollPane1;
//    /*private*/ JScrollPane jScrollPane2;
//    /*private*/ JPopupMenu.Separator jSeparator1;
    /*private*/ QTabWidget* jTabbedPane1;
    /*private*/ QMenu* profilesPopupMenu;
    /*private*/ ProfilesTable* profilesTbl;
    /*private*/ QAction* renameMI;
    /*private*/ QListView* searchPaths;
    /*private*/ QWidget* searchPathsPanel;
    // End of variables declaration

private slots:
    /*private*/ void renameMIActionPerformed(ActionEvent* evt = 0);
    /*private*/ void chkStartWithActiveProfileActionPerformed(ActionEvent* evt = 0);
    /*private*/ void btnOpenExistingProfileActionPerformed(ActionEvent* evt = 0);
    /*private*/ void btnDeleteProfileActionPerformed(ActionEvent* evt = 0);
    /*private*/ void btnCreateNewProfileActionPerformed(ActionEvent* evt = 0);
    /*private*/ void btnActivateProfileActionPerformed(ActionEvent* evt = 0);
    /*private*/ void btnExportProfileActionPerformed(ActionEvent* evt = 0);
    /*private*/ void btnCopyProfileActionPerformed(ActionEvent* evt = 0);
    /*private*/ void searchPathsValueChanged(ListSelectionEvent* evt =0);
    /*private*/ void btnRemoveSearchPathActionPerformed(ActionEvent* evt = 0);
    /*private*/ void btnAddSearchPathActionPerformed(ActionEvent* evt = 0);
};
class ProfilesTable : public QTableView
{
 Q_OBJECT
 public:
    ProfilesTable(QWidget* parent = 0) : QTableView(parent) {}
    /*public*/ QString getToolTipText(QMouseEvent* e);
};

#endif // PROFILEPREFERENCESPANEL_H
