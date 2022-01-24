#include "profilepreferencespanel.h"
#include "profilemanager.h"
#include <QPushButton>
#include <QMenu>
#include <QTableView>
#include <QCheckBox>
#include <QBoxLayout>
#include <QListView>
#include "profile.h"
#include "profiletablemodel.h"
#include "flowlayout.h"
//#include "searchpathslistmodel.h"
#include <QFileDialog>
#include "fileutil.h"
#include "profilefileview.h"
#include <QMouseEvent>
#include <QHeaderView>
#include <QMessageBox>
#include "logger.h"
#include "vptr.h"
#include "jfilechooser.h"
#include "roster.h"

#include "filenamefilter.h"

//ProfilePreferencesPanel::ProfilePreferencesPanel(QWidget *parent) :
//    PreferencesPanel(parent)
//{
//}
/**
 *
 * @author rhwood
 */
///*public*/ final class ProfilePreferencesPanel extends JPanel implements PreferencesPanel, ListSelectionListener {

/**
 *
 */
//    /*private*/ static final long serialVersionUID = -1375670900469426701L;
//    /*private*/ static final Logger log = LoggerFactory.getLogger(ProfilePreferencesPanel.class);

/**
 * Creates new form ProfilePreferencesPanel
 */
/*public*/ ProfilePreferencesPanel::ProfilePreferencesPanel(QWidget *parent)
    :  QWidget(parent)
{
 log= new Logger("ProfilePreferencesPanel");
 initComponents();
 this->chkStartWithActiveProfile->setChecked(ProfileManager::getDefault()->isAutoStartActiveProfile());
 this->valueChanged(QItemSelection(), QItemSelection());
 int index = ProfileManager::getDefault()->getAllProfiles().indexOf(ProfileManager::getDefault()->getActiveProfile());
 if (index != -1)
 {
  //this->profilesTbl->setRowSelectionInterval(index, index);
  QItemSelectionModel* m = new QItemSelectionModel(profilesTbl->model());
     m->select(profilesTbl->model()->index(index,0),QItemSelectionModel::Rows);
 }
}

/**
 * This method is called from within the constructor to initialize the form.
 * WARNING: Do NOT modify this code. The content of this method is always
 * regenerated by the Form Editor.
 */
//@SuppressWarnings("unchecked")
// <editor-fold defaultstate="collapsed" desc="Generated Code">
/*private*/ void ProfilePreferencesPanel::initComponents()
{
 profilesPopupMenu = new QMenu();
 renameMI = new QAction("",this);
 //jSeparator1 = new QMenuSeparator();
 copyMI = new QAction("", this);
 deleteMI = new QAction("",this);
 jTabbedPane1 = new QTabWidget();
 enabledPanel = new QWidget();
 chkStartWithActiveProfile = new QCheckBox();
    //jScrollPane1 = new JScrollPane();
 //    profilesTbl = new QTableView() {
 //        /**
 //         *
 //         */
 //        /*private*/ static final long serialVersionUID = -1464593093073508972L;

 //        //Implement table cell tool tips.
 //        /*public*/ QString getToolTipText(MouseEvent e) {
 //            try {
 //                return getValueAt(rowAtPoint(e.getPoint()), -1).toString();
 //            } catch (RuntimeException e1) {
 //                //catch null pointer exception if mouse is over an empty line
 //            }
 //            return null;
 //        }};
 profilesTbl = new QTableView();
 btnOpenExistingProfile = new QPushButton();
 btnDeleteProfile = new QPushButton();
 btnCreateNewProfile = new QPushButton();
 btnActivateProfile = new QPushButton();
 btnExportProfile = new QPushButton();
 btnCopyProfile = new QPushButton();
 searchPathsPanel = new QWidget();
 //jScrollPane2 = new JScrollPane();
 searchPaths = new QListView();
 btnRemoveSearchPath = new QPushButton();
 btnAddSearchPath = new QPushButton();

#if 0
 profilesPopupMenu.addPopupMenuListener(new PopupMenuListener() {
            /*public*/ void popupMenuWillBecomeVisible(PopupMenuEvent evt) {
                profilesPopupMenuPopupMenuWillBecomeVisible(evt);
            }
            /*public*/ void popupMenuWillBecomeInvisible(PopupMenuEvent evt) {
            }
            /*public*/ void popupMenuCanceled(PopupMenuEvent evt) {
            }
        });
#endif
 //ResourceBundle bundle = ResourceBundle.getBundle("jmri/profile/Bundle"); // NOI18N
 renameMI->setText(tr("Rename...")); // NOI18N
//        renameMI.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                renameMIActionPerformed(evt);
//            }
//        });
 connect(renameMI, SIGNAL(triggered()), this, SLOT(renameMIActionPerformed()));
 profilesPopupMenu->addAction(renameMI);
 profilesPopupMenu->addSeparator();

 copyMI->setText(tr("ProfilePreferencesPanel.copyMI.text")); // NOI18N
 profilesPopupMenu->addAction(copyMI);

 deleteMI->setText(tr("Copy...")); // NOI18N
 profilesPopupMenu->addAction(deleteMI);

 chkStartWithActiveProfile->setText(tr("Automatically start application with last used profile")); // NOI18N
 chkStartWithActiveProfile->setToolTip(tr("The last used profile will be automatically activated after 10 seconds.")); // NOI18N
//        chkStartWithActiveProfile.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                chkStartWithActiveProfileActionPerformed(evt);
//            }
//        });
 connect(chkStartWithActiveProfile, SIGNAL(clicked()), this, SLOT(chkStartWithActiveProfileActionPerformed()));

 profilesTbl->setModel(new ProfileTableModel());
 profilesTbl->resizeColumnsToContents();
 profilesTbl->horizontalHeader()->setStretchLastSection(true);

 //profilesTbl->getSelectionModel().addListSelectionListener(this);
 profilesTbl->setContextMenuPolicy(Qt::CustomContextMenu);
 profilesTbl->setSelectionBehavior(QAbstractItemView::SelectRows);
 //connect(profilesTbl, SIGNAL(clicked(QModelIndex)), this, SLOT(valueChanged(QModelIndex)));
 connect(profilesTbl->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(valueChanged(QItemSelection, QItemSelection)));
 //profilesTbl->setSortingEnabled(true);
 //jScrollPane1.setViewportView(profilesTbl);

 btnOpenExistingProfile->setText(tr("Add Existing...")); // NOI18N
 btnOpenExistingProfile->setToolTip(tr("Add an existing profile that can be used when starting a JMRI application.")); // NOI18N
//        btnOpenExistingProfile.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                btnOpenExistingProfileActionPerformed(evt);
//            }
//        });
 connect(btnOpenExistingProfile, SIGNAL(clicked()), this, SLOT(btnOpenExistingProfileActionPerformed()));
 btnDeleteProfile->setText(tr("Delete")); // NOI18N
 btnDeleteProfile->setToolTip(tr("Remove this profile from disk. This will cause all profile contents to be lost.")); // NOI18N
//        btnDeleteProfile.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                btnDeleteProfileActionPerformed(evt);
//            }
//        });
 connect(btnDeleteProfile, SIGNAL(clicked()), this, SLOT(btnDeleteProfileActionPerformed()));
 btnCreateNewProfile->setText(tr("New...")); // NOI18N
 btnCreateNewProfile->setToolTip(tr("Create a new profile.")); // NOI18N
//        btnCreateNewProfile.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                btnCreateNewProfileActionPerformed(evt);
//            }
//        });
 connect(btnCreateNewProfile, SIGNAL(clicked()), this, SLOT(btnCreateNewProfileActionPerformed()));

 btnActivateProfile->setText(tr("Activate")); // NOI18N
 btnActivateProfile->setToolTip(tr("Make the selected profile be the profile automatically started when this JMRI application is next launched.")); // NOI18N
//        btnActivateProfile.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                btnActivateProfileActionPerformed(evt);
//            }
//        });
 connect(btnActivateProfile, SIGNAL(clicked()), this, SLOT(btnActivateProfileActionPerformed()));
 btnExportProfile->setText(tr("Export...")); // NOI18N
 btnExportProfile->setToolTip(tr("Export profile as a ZIP archive for sharing.")); // NOI18N
//        btnExportProfile.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                btnExportProfileActionPerformed(evt);
//            }
//        });
 connect(btnExportProfile, SIGNAL(clicked()), this, SLOT(btnExportProfileActionPerformed()));

 btnCopyProfile->setText(tr("Copy...")); // NOI18N
//        btnCopyProfile.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                btnCopyProfileActionPerformed(evt);
//            }
//        });
 connect(btnCopyProfile, SIGNAL(clicked()), this, SLOT(btnCopyProfileActionPerformed()));

//        GroupLayout enabledPanelLayout = new GroupLayout(enabledPanel);
//        enabledPanel.setLayout(enabledPanelLayout);
//        enabledPanelLayout.setHorizontalGroup(
//            enabledPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
//            .addGroup(enabledPanelLayout.createSequentialGroup()
//                .addContainerGap()
//                .addGroup(enabledPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
//                    .addComponent(jScrollPane1)
//                    .addGroup(enabledPanelLayout.createSequentialGroup()
//                        .addGroup(enabledPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
//                            .addComponent(chkStartWithActiveProfile)
//                            .addGroup(enabledPanelLayout.createSequentialGroup()
//                                .addComponent(btnActivateProfile)
//                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
//                                .addComponent(btnOpenExistingProfile)
//                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
//                                .addComponent(btnCreateNewProfile)
//                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
//                                .addComponent(btnCopyProfile)
//                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
//                                .addComponent(btnExportProfile)
//                                .addGap(18, 18, 18)
//                                .addComponent(btnDeleteProfile)))
//                        .addGap(0, 0, Short.MAX_VALUE)))
//                .addContainerGap())
//        );
 QVBoxLayout* enabledPanelLayout = new QVBoxLayout;
 enabledPanel->setLayout(enabledPanelLayout);
 enabledPanelLayout->addWidget(profilesTbl);
 enabledPanelLayout->addWidget(chkStartWithActiveProfile);
 FlowLayout* buttonLayout = new FlowLayout;
 buttonLayout->addWidget(btnActivateProfile);
 buttonLayout->addWidget(btnOpenExistingProfile);
 buttonLayout->addWidget(btnCreateNewProfile);
 buttonLayout->addWidget(btnCopyProfile);
 buttonLayout->addWidget(btnExportProfile);
 buttonLayout->addWidget(btnDeleteProfile);
 enabledPanelLayout->addLayout(buttonLayout);

//        enabledPanelLayout.setVerticalGroup(
//            enabledPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
//            .addGroup(enabledPanelLayout.createSequentialGroup()
//                .addContainerGap()
//                .addComponent(jScrollPane1, GroupLayout.DEFAULT_SIZE, 206, Short.MAX_VALUE)
//                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
//                .addGroup(enabledPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
//                    .addComponent(btnOpenExistingProfile)
//                    .addComponent(btnCreateNewProfile)
//                    .addComponent(btnActivateProfile)
//                    .addComponent(btnExportProfile)
//                    .addComponent(btnDeleteProfile)
//                    .addComponent(btnCopyProfile))
//                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
//                .addComponent(chkStartWithActiveProfile)
//                .addContainerGap())
//        );

 jTabbedPane1->addTab(enabledPanel, tr("Config Profiles")); // NOI18N

// searchPaths->setModel(new SearchPathsListModel());
//        searchPaths.addListSelectionListener(new ListSelectionListener() {
//            /*public*/ void valueChanged(ListSelectionEvent evt) {
//                searchPathsValueChanged(evt);
//            }
//        });
// connect(searchPaths, SIGNAL(clicked(QModelIndex)), this, SLOT(searchPathsValueChanged()));
        //jScrollPane2.setViewportView(searchPaths);


 btnRemoveSearchPath->setText(tr("Remove")); // NOI18N
 btnRemoveSearchPath->setToolTip(tr("Prevent JMRI from searching in this directory for profiles.")); // NOI18N
//        btnRemoveSearchPath.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                btnRemoveSearchPathActionPerformed(evt);
//            }
//        });
 connect(btnRemoveSearchPath, SIGNAL(clicked()), this, SLOT(btnRemoveSearchPathActionPerformed()));

 btnAddSearchPath->setText(tr("Add...")); // NOI18N
 btnAddSearchPath->setToolTip(tr("Add a directory in which JMRI should search for profiles.")); // NOI18N
//        btnAddSearchPath.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent evt) {
//                btnAddSearchPathActionPerformed(evt);
//            }
//        });
 connect(btnAddSearchPath, SIGNAL(clicked()), this, SLOT(btnAddSearchPathActionPerformed()));

//        GroupLayout searchPathsPanelLayout = new GroupLayout(searchPathsPanel);
//        searchPathsPanel.setLayout(searchPathsPanelLayout);
//        searchPathsPanelLayout.setHorizontalGroup(
//            searchPathsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
//            .addGroup(searchPathsPanelLayout.createSequentialGroup()
//                .addContainerGap()
//                .addGroup(searchPathsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
//                    .addGroup(searchPathsPanelLayout.createSequentialGroup()
//                        .addComponent(btnAddSearchPath)
//                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
//                        .addComponent(btnRemoveSearchPath)
//                        .addGap(0, 0, Short.MAX_VALUE))
//                    .addComponent(jScrollPane2, GroupLayout.DEFAULT_SIZE, 666, Short.MAX_VALUE))
//                .addContainerGap())
//        );
//        searchPathsPanelLayout.setVerticalGroup(
//            searchPathsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
//            .addGroup(searchPathsPanelLayout.createSequentialGroup()
//                .addContainerGap()
//                .addComponent(jScrollPane2, GroupLayout.DEFAULT_SIZE, 235, Short.MAX_VALUE)
//                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
//                .addGroup(searchPathsPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
//                    .addComponent(btnAddSearchPath)
//                    .addComponent(btnRemoveSearchPath))
//                .addContainerGap())
//        );
 QVBoxLayout* searchPathsPanelLayout = new QVBoxLayout;
 searchPathsPanel->setLayout(searchPathsPanelLayout);
 searchPathsPanelLayout->addWidget(searchPaths);
 FlowLayout* buttonLayout2 = new FlowLayout;
 buttonLayout2->addWidget(btnAddSearchPath);
 buttonLayout2->addWidget(btnRemoveSearchPath);
 searchPathsPanelLayout->addLayout(buttonLayout2);

 jTabbedPane1->addTab(searchPathsPanel, tr("Search Paths")); // NOI18N

//        GroupLayout layout = new GroupLayout(this);
//        this->setLayout(layout);
//        layout.setHorizontalGroup(
//            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
//            .addComponent(jTabbedPane1, GroupLayout.Alignment.TRAILING)
//        );
//        layout.setVerticalGroup(
//            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
//            .addComponent(jTabbedPane1)
//        );
 QVBoxLayout* thisLayout = new QVBoxLayout;
 setLayout(thisLayout);
 thisLayout->addWidget(jTabbedPane1);

//        jTabbedPane1.getAccessibleContext().setAccessibleName(tr("ProfilePreferencesPanel.enabledPanel.TabConstraints.tabTitle")); // NOI18N
}// </editor-fold>

//QString ProfilesTable::getToolTipText(QMouseEvent *e)
//{
// //try {
// //return getValueAt(rowAtPoint(e.getPoint()), -1).toString();
// return indexAt(e->pos()).data().toString();

////} catch (RuntimeException e1) {
////    //catch null pointer exception if mouse is over an empty line
////}
////return null;
//}

/*private*/ void ProfilePreferencesPanel::renameMIActionPerformed(JActionEvent* /*evt*/) {
    // TODO add your handling code here:
}
#if 0
/*private*/ void profilesPopupMenuPopupMenuWillBecomeVisible(PopupMenuEvent evt) {
    QModelIndexList mil = profilesTbl->selectedIndexes();
    if (profilesTbl.mil.count() == 1) {
        this->renameMI.setEnabled(true);
    }
}
#endif

/*private*/ void ProfilePreferencesPanel::btnAddSearchPathActionPerformed(JActionEvent* /*evt*/)
{
//    JFileChooser chooser = new JFileChooser(FileUtil.getPreferencesPath());
//    chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
//    chooser.setFileFilter(new ProfileFileFilter());
//    chooser.setFileView(new ProfileFileView());
 setCursor(Qt::WaitCursor);
 QString dir = QFileDialog::getExistingDirectory(this,tr("Select ProfileSearchPath"));
 setCursor(Qt::ArrowCursor);
 // TODO: Use NetBeans OpenDialog if its availble
 //if (chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION)
 if(dir != "")
 {
//        try {
  ProfileManager::getDefault()->addSearchPath(/*chooser.getSelectedFile()*/new File(dir));
// TODO:  searchPaths->setSelectedValue(chooser.getSelectedFile(), true);
//        } catch (IOException* ex) {
//            log.warn("Unable to write profiles while adding search path {}", chooser.getSelectedFile().getPath(), ex);
//            JOptionPane.showMessageDialog(this,
//                    tr("ProfilePreferencesPanel.btnAddSearchPath.errorMessage",
//                            chooser.getSelectedFile().getPath(),
//                            ex->getLocalizedMessage()),
//                    tr("ProfilePreferencesPanel.btnAddSearchPath.errorTitle"),
//                    JOptionPane.ERROR_MESSAGE);
//        }
 }
}

/*private*/ void ProfilePreferencesPanel::btnRemoveSearchPathActionPerformed(JActionEvent* /*evt*/)
{
#if 1
 foreach (QVariant value, this->searchPaths->selectionModel()->selectedRows())
 { // getSelectedValues is deprecated in Java 1.7
  File* path = new File(value.toString());
//        try {
            ProfileManager::getDefault()->removeSearchPath(path);
//        } catch (IOException* ex) {
//            log.warn("Unable to write profiles while removing search path {}", path.getPath(), ex);
//            JOptionPane.showMessageDialog(this,
//                    tr("ProfilePreferencesPanel.btnRemoveSearchPath.errorMessage", path.getPath(), ex->getLocalizedMessage()),
//                    tr("ProfilePreferencesPanel.btnRemoveSearchPath.errorTitle"),
//                    JOptionPane.ERROR_MESSAGE);
//        }
    }
#endif
}

/*private*/ void ProfilePreferencesPanel::searchPathsValueChanged(ListSelectionEvent* evt)
{
 //if (searchPaths.getSelectedValue() == null || searchPaths.getSelectedValue()==(new File(FileUtil.getPreferencesPath())))
 QString selectedValue = searchPaths->currentIndex().data().toString();
 if(selectedValue == "" || selectedValue == FileUtil::getPreferencesPath())
 {
  this->btnRemoveSearchPath->setEnabled(false);
 }
 else
 {
  this->btnRemoveSearchPath->setEnabled(true);
 }
}

/*private*/ void ProfilePreferencesPanel::btnExportProfileActionPerformed(JActionEvent* /*evt*/)
{
 Profile* p = ProfileManager::getDefault()->getProfiles(profilesTbl->currentIndex().row());
#if 1
 JFileChooser* chooser = new JFileChooser();
 chooser->setFileFilter("Zip Archives *.zip" ); //new FileNameExtensionFilter("ZIP Archives", "zip"));
 //chooser->setFileView(new ProfileFileView());
 chooser->setFileSelectionMode(JFileChooser::FILES_ONLY);
 chooser->setSelectedFile(new File(p->getName() + ".zip"));

 if (chooser->showSaveDialog(this) == JFileChooser::APPROVE_OPTION)
 {
  try
  {
#if 0 // chooser does this check so not needed here.
   if (chooser->getSelectedFile()->exists())
   {
//                int result = JOptionPane.showConfirmDialog(this,
//                        tr("ProfilePreferencesPanel.btnExportProfile.overwriteMessage",
//                                chooser->getSelectedFile()->getName(),
//                                chooser->getSelectedFile()->getParentFile()->getName()),
//                        tr("ProfilePreferencesPanel.btnExportProfile.overwriteTitle"),
//                        JOptionPane.YES_NO_OPTION,
//                        JOptionPane.WARNING_MESSAGE);
//                if (result == JOptionPane.YES_OPTION) {
    int result = QMessageBox::question(this, tr("Replace file?"), tr("\"%1\" already exists in the directory %2. Do you want to replace it?\nReplacing it will overwrite its current contents.").arg(chooser->getSelectedFile()->getName()).arg(                                                                chooser->getSelectedFile()->getParentFile()->getName()), QMessageBox::Yes | QMessageBox::No);
    if(result == QMessageBox::Yes)
    {
     chooser->getSelectedFile()->_delete();
    }
    else
    {
     this->btnExportProfileActionPerformed(evt);
     return;
    }
   }
#endif
   bool exportExternalUserFiles = false;
   bool exportExternalRoster = false;
   if (!(new File(FileUtil::getUserFilesPath()))->getCanonicalPath().startsWith(p->getPath()->getCanonicalPath()))
   {
//                int result = JOptionPane.showConfirmDialog(this,
//                        tr("ProfilePreferencesPanel.btnExportProfile.externalUserFilesMessage"),
//                       externalUserFilesTitle tr("ProfilePreferencesPanel.btnExportProfile."),
//                        JOptionPane.YES_NO_OPTION,
//                        JOptionPane.QUESTION_MESSAGE);
//                if (result == JOptionPane.YES_OPTION) {
    int result = QMessageBox::question(this, tr("Export user files"), tr("Your JMRI user files are not in the profile directory.\nDo you want to include them in the exported profile?"), QMessageBox::Yes | QMessageBox::No);
    if(result == QMessageBox::Yes)
    {
           exportExternalUserFiles = true;
    }
   }
   if (!(new File(Roster::getDefault()->getRosterLocation()))->getCanonicalPath().startsWith(p->getPath()->getCanonicalPath())
           && !Roster::getDefault()->getRosterLocation().startsWith(FileUtil::getUserFilesPath()))
   {
//                int result = JOptionPane.showConfirmDialog(this,
//                        tr("ProfilePreferencesPanel.btnExportProfile.externalRosterMessage"),
//                        tr("ProfilePreferencesPanel.btnExportProfile.externalRosterTitle"),
//                        JOptionPane.YES_NO_OPTION,
//                        JOptionPane.QUESTION_MESSAGE);
//                if (result == JOptionPane.YES_OPTION) {
       int result = QMessageBox::question(this, tr("Export roster"), tr("Your roster is not in the profile directory.\nDo you want to include it in the exported profile?"), QMessageBox::Yes | QMessageBox::No);
       if(result == QMessageBox::Yes)
       {
        exportExternalRoster = true;
       }
      }
      if (ProfileManager::getDefault()->getActiveProfile() == p)
      {
          // TODO: save roster, panels, operations if needed and safe to do so
      }
      ProfileManager::getDefault()->_export(p, chooser->getSelectedFile(), exportExternalUserFiles, exportExternalRoster);
      log->info(tr("Profile \"%1\" exported to \"%2\"").arg(p->getName()).arg(chooser->getSelectedFile()->getName()));
//            JOptionPane.showMessageDialog(this,
//                    tr("ProfilePreferencesPanel.btnExportProfile.successMessage",
//                            p->getName(), chooser->getSelectedFile()->getName()),
//                    tr("ProfilePreferencesPanel.btnExportProfile.successTitle"),
//                    JOptionPane.INFORMATION_MESSAGE);
      QMessageBox::information(this, tr("Profile exported"), tr("Profile \"%1\" exported to %2.").arg(p->getName()).arg( chooser->getSelectedFile()->getName()));
  }
  catch (JDOMException* ex)
  {
      log->warn(tr("Unable to export profile \"%1\" to %2").arg(p->getName()).arg(chooser->getSelectedFile()->getPath()/*, ex*/));
//      JOptionPane.showMessageDialog(this,
//              tr("ProfilePreferencesPanel.btnExportProfile.errorMessage",
//                      p->getName(),
//                      chooser->getSelectedFile()->getPath(),
//                      ex->getLocalizedMessage()),
//              tr("ProfilePreferencesPanel.btnExportProfile.errorTitle"),
//              JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Error exporting profile"), tr("Unable to export profile %1 to %2.\n%3\nSee logs for more details.").arg(p->getName()).arg(chooser->getSelectedFile()->getPath()).arg( ex->getLocalizedMessage()));
  }
 }
#endif
}

/*private*/ void ProfilePreferencesPanel::btnActivateProfileActionPerformed(JActionEvent* /*evt*/) {
//    try {
        Profile* p = ProfileManager::getDefault()->getProfiles(profilesTbl->currentIndex().row());
        ProfileManager::getDefault()->setNextActiveProfile(p);
        ProfileManager::getDefault()->saveActiveProfile(p, ProfileManager::getDefault()->isAutoStartActiveProfile());
//    } catch (IOException* ex) {
//        log.error("Unable to save profile preferences", ex);
//        JOptionPane.showMessageDialog(this, "Usable to save profile preferences.\n" + ex->getLocalizedMessage(), "Error", JOptionPane.ERROR_MESSAGE);
//    }
}

/*private*/ void ProfilePreferencesPanel::btnCreateNewProfileActionPerformed(JActionEvent* /*evt*/)
{
#if 0
    AddProfileDialog apd = new AddProfileDialog((Frame) SwingUtilities.getWindowAncestor(this), true, true);
    apd.setLocationRelativeTo(this);
    apd.setVisible(true);
#endif
    AddProfileDialog* apd = new AddProfileDialog(this, true,true);
    apd->setLocationRelativeTo(this);
    apd->setVisible(true);
}

/*private*/ void ProfilePreferencesPanel::btnDeleteProfileActionPerformed(JActionEvent* /*evt*/)
{
 QModelIndexList mil = profilesTbl->selectionModel()->selectedIndexes();


 QVector<Profile*> profiles =  QVector<Profile*>(mil.count());
 for (int i; i < mil.count(); i++)
 {
  Profile* profile = VPtr<Profile>::asPtr(mil.at(i).data(Qt::UserRole));
        profiles.append(profile);
 }
 foreach (Profile* deletedProfile, profiles) {
//        int result = JOptionPane.showOptionDialog(this,
//                tr("ProfilePreferencesPanel.btnDeleteProfile.dlgMessage", deletedProfile.getName()), // NOI18N
//                tr("ProfilePreferencesPanel.btnDeleteProfile.dlgTitle", deletedProfile.getName()), // NOI18N
//                JOptionPane.OK_CANCEL_OPTION,
//                JOptionPane.QUESTION_MESSAGE,
//                null, // use default icon
//                new String[]{
//                    tr("ProfilePreferencesPanel.btnDeleteProfile.text"), // NOI18N
//                    tr("AddProfileDialog.btnCancel.text") // NOI18N
//                },
//                JOptionPane.CANCEL_OPTION
//        );
//        if (result == JOptionPane.OK_OPTION) {
     int result = QMessageBox::question(this, tr("Delete"),tr("Are you sure want to delete profile %1?\nThis will cause all profile contents to be lost." ).arg(deletedProfile->getName()),
       QMessageBox::Ok | QMessageBox::Cancel);
     if(result == QMessageBox::Cancel)
     {
       if (!FileUtil::_delete(deletedProfile->getPath()))
       {
        log->warn(tr("Unable to delete profile directory %1").arg( deletedProfile->getPath()->getPath()));
//                JOptionPane.showMessageDialog(this,
//                        tr("ProfilePreferencesPanel.btnDeleteProfile.errorMessage", deletedProfile.getPath()),
//                        tr("ProfilePreferencesPanel.btnDeleteProfile.errorMessage"),
//                        JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(this, tr("Error"), tr("Unable to delete profile %1}.").arg(deletedProfile->getPath()->getPath()));
       }
       ProfileManager::getDefault()->removeProfile(deletedProfile);
       log->info(tr("Removed profile \"%1\" from %2").arg( deletedProfile->getName()).arg(deletedProfile->getPath()->getPath()));
            //profilesTbl.repaint();
      }
    }
}

/*private*/ void ProfilePreferencesPanel::btnOpenExistingProfileActionPerformed(JActionEvent* /*evt*/)
{
// JFileChooser chooser = new JFileChooser(FileUtil.getPreferencesPath());
// chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
// chooser.setFileFilter(new ProfileFileFilter());
// chooser.setFileView(new ProfileFileView());
 setCursor(Qt::WaitCursor);
 QString path = QFileDialog::getOpenFileName(this, tr("Select Profile"), FileUtil::getProfilePath(), "Profiles (*.*) ");
 setCursor(Qt::ArrowCursor);
 // TODO: Use NetBeans OpenDialog if its availble
 //if (chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
 if(path  != "")
 {
  //try {
  Profile* p = new Profile(/*chooser.getSelectedFile()*/new File(path));
  ProfileManager::getDefault()->addProfile(p);
  int index = ProfileManager::getDefault()->getAllProfiles().indexOf(p);
//  profilesTbl->setRowSelectionInterval(index, index);
//  } catch (IOException* ex) {
//    log.warn("{} is not a profile directory", chooser.getSelectedFile());
//    JOptionPane.showMessageDialog(this,
//            tr("ProfilePreferencesPanel.btnOpenExistingProfile.errorMessage", chooser.getSelectedFile().getPath()),
//            tr("ProfilePreferencesPanel.btnOpenExistingProfile.errorMessage"),
//            JOptionPane.ERROR_MESSAGE);
//  }
 }
}

/*private*/ void ProfilePreferencesPanel::chkStartWithActiveProfileActionPerformed(JActionEvent* evt) {
    ProfileManager::getDefault()->setAutoStartActiveProfile(this->chkStartWithActiveProfile->isChecked());
//    try {
        ProfileManager::getDefault()->saveActiveProfile();
//    } catch (IOException* ex) {
//        log.error("Unable to save active profile.", ex);
//    }
}

/*private*/ void ProfilePreferencesPanel::btnCopyProfileActionPerformed(JActionEvent* evt)
{
#if 1
    QModelIndexList mil = profilesTbl->selectionModel()->selectedIndexes();
    if(mil.size() == 0)
     return; // must select a profile.
    Profile* profile = VPtr<Profile>::asPtr(mil.at(0).data(Qt::UserRole));
#endif
    AddProfileDialog* apd = new AddProfileDialog(this, true, true);
    apd->setSourceProfile(profile);
    apd->setLocationRelativeTo(this);
    apd->setVisible(true);

}


//@Override
/*public*/ QString ProfilePreferencesPanel::getPreferencesItem() {
    return "Profiles"; // NOI18N
}

//@Override
/*public*/ QString ProfilePreferencesPanel::getPreferencesItemText() {
    return tr("Config Profiles");
}

//@Override
/*public*/ QString ProfilePreferencesPanel::getTabbedPreferencesTitle() {
    return "";
}

//@Override
/*public*/ QString ProfilePreferencesPanel::getLabelKey() {
    return "";
}

//@Override
/*public*/ QWidget* ProfilePreferencesPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool ProfilePreferencesPanel::isPersistant() {
    return false;
}

//@Override
/*public*/ QString ProfilePreferencesPanel::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void ProfilePreferencesPanel::savePreferences() {
    // Nothing to do since ProfileManager preferences are saved immediately
}

//@Override
/*public*/ int ProfilePreferencesPanel::getSortOrder() {
    return 1000;
}

/*public*/ void ProfilePreferencesPanel::dispose() {
//    ProfileManager::getDefault()->removePropertyChangeListener((ProfileTableModel*) profilesTbl->model());
}

//@Override
/*public*/ void ProfilePreferencesPanel::valueChanged(QItemSelection, QItemSelection)
{
 QItemSelectionModel* selectionModel = profilesTbl->selectionModel();
 QModelIndexList mil = selectionModel->selectedRows();
 if(mil.size()== 0)
 {
  this->btnCopyProfile->setEnabled(false);
  this->btnExportProfile->setEnabled(false);
 }

 if (mil.count() == 1 && mil.at(0).row() < ProfileManager::getDefault()->getAllProfiles().size())
 {
  Profile* p = ProfileManager::getDefault()->getAllProfiles().at(mil.at(0).row());
  this->btnDeleteProfile->setEnabled(p!=(ProfileManager::getDefault()->getActiveProfile()));
  if (ProfileManager::getDefault()->getNextActiveProfile() != NULL)
  {
   this->btnActivateProfile->setEnabled(p!=(ProfileManager::getDefault()->getNextActiveProfile()));
  }
  else
  {
   this->btnActivateProfile->setEnabled(p!=(ProfileManager::getDefault()->getActiveProfile()));
  }
  this->btnCopyProfile->setEnabled(true);
  this->btnExportProfile->setEnabled(true);
  }
  else if (mil.count() > 1)
  {
   this->btnDeleteProfile->setEnabled(true);
   //foreach (int row : this->profilesTbl->getSelectedRows())
   for(int i = 0; i << mil.count(); i++)
   {
   int row = mil.at(i).row();
   Profile* p = ProfileManager::getDefault()->getAllProfiles().at(row);
   if (p==(ProfileManager::getDefault()->getActiveProfile()))
   {
    this->btnDeleteProfile->setEnabled(false);
    break;
   }
  }
  this->btnCopyProfile->setEnabled(false);
  this->btnExportProfile->setEnabled(false);
  this->btnActivateProfile->setEnabled(false);
 }
 else
 {
  this->btnDeleteProfile->setEnabled(false);
  this->btnCopyProfile->setEnabled(false);
  this->btnExportProfile->setEnabled(false);
  this->btnActivateProfile->setEnabled(false);
 }
}

//@Override
/*public*/ bool ProfilePreferencesPanel::isDirty() {
    return false; // ProfileManager preferences are saved immediately, so this is always false
}

//@Override
/*public*/ bool ProfilePreferencesPanel::isRestartRequired() {
    // true if the next profile to use has changed, false otherwise.
    // Since next profile defaults to null when application starts, restart
    // is required only if next profile is not null and is not the same
    // profile as the current profile
    return ProfileManager::getDefault()->getNextActiveProfile() != NULL
            && ProfileManager::getDefault()->getActiveProfile()!=(ProfileManager::getDefault()->getNextActiveProfile()
            );
}
/* Comment out until I get around to utilizing this, so Jenkins does not throw warnin
 private static class ZipFileFilter extends FileFilter {

 public ZipFileFilter() {
 }

 //@Override
 public bool accept(File f) {
 if (!f.isDirectory()) {
 int i = f.getName().lastIndexOf('.');
 if (i > 0 && i < f.getName().length() - 1) {
 return f.getName().substring(i + 1).toLowerCase()==IgnoreCase("zip"); // NOI18N
 }
 return false;
 }
 return true;
 }

 //@Override
 public QString getDescription() {
 return "Zip archives (.zip)";
 }
 }
 */
/*public*/ QString ProfilePreferencesPanel::className() {return "jmri.profile.ProfilePreferencesPanel";}
