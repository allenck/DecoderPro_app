#include "directorysearcher.h"
#include "fileutil.h"
#include <QLabel>
#include <QMessageBox>
#include "catalogtreemanager.h"
#include "jframe.h"
#include <QDir>
#include <QVBoxLayout>
#include "previewdialog.h"
#include "jtextfield.h"
#include <QFileInfo>

/*static*/ DirectorySearcher* DirectorySearcher::_instance = NULL;
/*static*/ QFileDialog* DirectorySearcher::_directoryChooser = NULL;


DirectorySearcher::DirectorySearcher(QObject *parent) :
    QObject(parent)
{
 _waitText = new JTextField();
 _quitLooking = false;
 _previewDialog = NULL;
 setProperty("InstanceManagerAutoDefault", "yes");

}
/**
 * A file system directory searcher to locate Image files to include in an Image Catalog.
 *  This is a singleton class.
 * <P>
 *
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Pete Cressman  Copyright 2010
 *
 */
///*public*/ class DirectorySearcher {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.catalog.CatalogBundle");


//    private DirectorySearcher() {
//    }

/*public*/ /*static*/ DirectorySearcher* DirectorySearcher::instance() {
    if (_instance == NULL) {
        _instance = new DirectorySearcher();
    }
    return _instance;
}

/*
* Open file anywhere in the file system and let the user decide whether
* to add it to the Catalog
*/
/*private*/ /*static*/ QDir* DirectorySearcher::getDirectory(QString /*msg*/, bool recurseDirs) {
//    if (_directoryChooser == NULL) {
        //_directoryChooser = new JFileChooser(System.getProperty("user.dir")+java.io.File.separator+"resources");
//        _directoryChooser = new QFileDialog(0,tr("Search File System for icons"),FileUtil::getUserResourcePath(),tr("Graphics Files (*.png *.Jpg *.gif *.bmp)"));
        //jmri.util.FileChooserFilter filt = new jmri.util.FileChooserFilter("Graphics Files");
//            for (int i=0; i<CatalogTreeManager.IMAGE_FILTER.length; i++) {
//                filt.addExtension(CatalogTreeManager.IMAGE_FILTER[i]);
//            }
//            _directoryChooser.setFileFilter(filt);
//    }
    //_directoryChooser.setDialogTitle(tr(msg));
    //_directoryChooser.rescanCurrentDirectory();

    //_directoryChooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
//    _directoryChooser->setOption(QFileDialog::ReadOnly);
    QWidget* panel = new QWidget();
    panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
    QLabel* label = new QLabel(tr("Select any"));
    panel->layout()->addWidget(label);
    label = new QLabel(tr("image file"));
    panel->layout()->addWidget(label);
    label = new QLabel(tr("to preview"));
    panel->layout()->addWidget(label);
    label = new QLabel(tr("the Directory"));
    panel->layout()->addWidget(label);
//    _directoryChooser->setAccessory(panel);
//        int retVal = _directoryChooser.showOpenDialog(NULL);
//        if (retVal != JFileChooser.APPROVE_OPTION) return NULL;  // give up if no file selected
//    if(_directoryChooser->exec() == QDialog::Rejected)
//      return NULL;
//    QStringList l = _directoryChooser->selectedFiles();
//    QDir* dir = NULL;
//    if(l.size() == 0) return NULL;
//    QFileInfo* info = new QFileInfo(l.at(0));
    //File dir = _directoryChooser.getSelectedFile();

    QString dirName = QFileDialog::getExistingDirectory(0,tr("Search File System for icons"),FileUtil::getUserResourcePath());
    if(dirName == "") return NULL;
    QDir* dir = new QDir(dirName);
#if 1
    if (dir!=NULL) {
//        if (!info->isDir()) {
//            dir = new QDir(info->path());
//        }
        if (hasImageFiles(dir)) {
            return dir; // OK directory has image files
        }
        if (!recurseDirs) {
            return NULL;
        }
    }
#endif
    return dir;
}

/*private*/ /*static*/ bool DirectorySearcher::hasImageFiles(QDir* dir)
{
 //File[] files = dir.listFiles();
    QStringList filters;
    filters << "*.jpg" << "*.gif" << "*.png" << "*.bmp";
    QFileInfoList files = dir->entryInfoList(filters);
    for (int i=0; i<files.length(); i++) {
//        String ext = jmri.util.FileChooserFilter.getFileExtension(files[i]);
//        for (int k=0; k<CatalogTreeManager.IMAGE_FILTER.length; k++) {
//            if (ext != NULL && ext.equalsIgnoreCase(CatalogTreeManager.IMAGE_FILTER[k])) {
//                return true; // OK directory has image files
        if(files.at(i).isFile())
            return true;
//            }
//        }
    }
    return false;
}

/*private*/ void DirectorySearcher::showWaitFrame() {
    _waitDialog = new JFrame(tr("Please Wait"));
    QWidget* panel = new QWidget();
    panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
    panel->layout()->addWidget(new QLabel(tr("This may take some time...")));

    _waitText->setText(tr("Please wait while the window is being constructed"));
    _waitText->setDisabled(true);
    _waitText->setFont( QFont("Dialog", QFont::Bold, 12));
//    _waitText.setBackground(panel.getBackground());
//    _waitText.setOpaque(true);
    panel->layout()->addWidget(_waitText);

    if(_waitDialog->centralWidget()== NULL)
    {
        QWidget* centralWidget = new QWidget();
        centralWidget->setLayout(new QVBoxLayout);
        _waitDialog->setCentralWidget(centralWidget);
    }
    _waitDialog->centralWidget()->layout()->addWidget(panel);
    _waitDialog->setLocation(400,40);
    _waitDialog->pack();
    _waitDialog->setVisible(false);
}

/*private*/ void DirectorySearcher::closeWaitFrame() {
    if (_waitDialog != NULL) {
        _waitDialog->dispose();
        _waitDialog = NULL;
    }
}

/**
*  Open one directory.
* @param addDir - <pre>if true, allows directory to be added as a tree to the Catalog.
*                      if false, allows preview panel to drag icons.
*/
/*public*/ void DirectorySearcher::openDirectory(bool addDir)
{
 showWaitFrame();
 QDir* dir = getDirectory("openDirMenu", false);
 if (dir != NULL)
 {
  if (addDir)
  {
   doPreviewDialog(dir, new AActionListener(dir,this), new MActionListener(dir, true,this), NULL, new CActionListener(this), 0);
  }
  else
  {
   doPreviewDialog(dir, NULL, new MActionListener(dir, true,this),
                            NULL, new CActionListener(this), 0);
  }
 }
 else
 {
  //JOptionPane.showMessageDialog(NULL, tr("NoImagesInDir"), tr("searchFSMenu"),  JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(NULL, tr("Search File System for Icons"), tr("Directory does not have any image files."));
 }
 closeWaitFrame();
}

/*public*/ QDir* DirectorySearcher::searchFS() {
    showWaitFrame();
    _addDir = NULL;
    QDir* dir = getDirectory(tr("Search File System for Icons"), true);
    if (dir != NULL) {
        getImageDirectory(new QDir(dir->path()), CatalogTreeManager::IMAGE_FILTER);
        if (!_quitLooking) {
//                JOptionPane.showMessageDialog(NULL, tr("DirNotFound"), tr("searchFSMenu"),
//                                                     JOptionPane.INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Search File System for Icons"),tr("No sub-directories contain image files.") );
        }
    }
    closeWaitFrame();
    return _addDir;
}

//    class AActionListener implements ActionListener {
//        File dir;
    /*public*/ AActionListener::AActionListener(QDir* d, DirectorySearcher* s) {
        dir = d;
        this->s = s;
    }
    /*public*/ void AActionListener::actionPerformed(JActionEvent* /*a*/) {
        s->_addDir = dir;
        s->cancelLooking();
    }
//};
//    class MActionListener implements ActionListener {
//        File dir;
//        boolean oneDir;
    /*public*/ MActionListener::MActionListener(QDir* d, bool o, DirectorySearcher* /*s*/) {
        dir = d;
        oneDir = o;
    }
    /*public*/ void MActionListener::actionPerformed(JActionEvent* /*a*/) {
    s->displayMore(new QDir(dir->path()), oneDir);
    }
//};
//    class LActionListener implements ActionListener {
LActionListener::LActionListener(DirectorySearcher* s)
{
this->s = s;
}
    /*public*/ void LActionListener::actionPerformed(JActionEvent* /*a*/) {
        s->keepLooking();
    }
//    };
//    class CActionListener implements ActionListener {
CActionListener::CActionListener(DirectorySearcher* s)
{
this->s = s;
}
    /*public*/ void CActionListener::actionPerformed(JActionEvent* /*a*/) {
        s->cancelLooking();
    }
//    };

/*private*/ void DirectorySearcher::doPreviewDialog(QDir* dir, ActionListener* addAction, ActionListener* moreAction,
                             ActionListener* lookAction, ActionListener* cancelAction,
                             int startNum) {
    _quitLooking = false;
    // if both addAction & lookAction not NULL dialog will be modeless - i.e dragable
    _previewDialog = new PreviewDialog(NULL, "previewDir", dir, CatalogTreeManager::IMAGE_FILTER);
    _previewDialog->init(addAction, moreAction, lookAction, cancelAction,
                        startNum, _waitDialog);
    if (lookAction == NULL) {
        closeWaitFrame();
    }
}

/**
* Directory dir has image files
*/
/*private*/ void DirectorySearcher::getImageDirectory(QDir* dir, QStringList filter) {
    QStringList filters;
    foreach (QString s, filter) {
        filters << QString("*.%1").arg(s);
    }
    QFileInfoList files = dir->entryInfoList(filters, QDir::Files);
    if (files.isEmpty()) {
        return;
    }
    if (hasImageFiles(dir)) {
        doPreviewDialog(dir, new AActionListener(dir,this), new MActionListener(dir, false,this),
                            new LActionListener(this), new CActionListener(this), 0);
        if (_quitLooking) {
            return;
        }
    }
    for (int k=0; k<files.length(); k++) {
        if (files.at(k).isDir()) {
            getImageDirectory(new QDir(files.at(k).path()), filter);
            if (_quitLooking) {
                return;
            }
        }
    }
}


void DirectorySearcher::displayMore(QDir* dir, bool oneDir) {
    if (_previewDialog != NULL) {
        _quitLooking = false;
        int numFilesShown = _previewDialog->getNumFilesShown();
        _previewDialog->dispose();
        if (oneDir) {
            doPreviewDialog(dir, NULL, new MActionListener(dir, oneDir, this),
                            NULL, new CActionListener(this), numFilesShown);
        } else {
            doPreviewDialog(dir, NULL, new MActionListener(dir,oneDir,this),
                            new LActionListener(this), new CActionListener(this), numFilesShown);
        }
    }
}

void DirectorySearcher::keepLooking() {
    if (_previewDialog != NULL) {
        _quitLooking = false;
        _previewDialog->dispose();
        _previewDialog = NULL;
    }
}

/*public*/ void DirectorySearcher::cancelLooking() {
    if (_previewDialog != NULL) {
        _quitLooking = true;
        _previewDialog->dispose();
        _previewDialog = NULL;
    }
}

/*public*/ void DirectorySearcher::close() {
    closeWaitFrame();
    cancelLooking();
}

