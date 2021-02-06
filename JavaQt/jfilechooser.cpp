#include "jfilechooser.h"
#include <QFileDialog>
#include "file.h"
#include "propertychangesupport.h"

JFileChooser::JFileChooser(QObject *parent) : QObject(parent)
{
 common();
}

JFileChooser::JFileChooser(int dialogType, QObject *parent) :
  QObject(parent)
{
 common();
 this->dialogType = dialogType;
}
void JFileChooser::common()
{
 pcs = new PropertyChangeSupport(this);
 dialog = nullptr;
 dialogType = OPEN_DIALOG;
 approveButtonText = "";
 currentDirectoryPath = "";
 selectionMode = FILES_AND_DIRECTORIES;
 selectedFile = nullptr;
 files = QStringList();
 currentDirectory =  new File(QDir::currentPath());
}

/*public*/ JFileChooser::JFileChooser(QString currentDirectoryPath, QObject *parent) : QObject(parent)
{
 common();
 //this(currentDirectoryPath, (FileSystemView) NULL);
 this->currentDirectoryPath = currentDirectoryPath;
}

/**
 * Constructs a <code>JFileChooser</code> using the given <code>File</code>
 * as the path. Passing in a <code>null</code> file
 * causes the file chooser to point to the user's default directory.
 * This default depends on the operating system. It is
 * typically the "My Documents" folder on Windows, and the user's
 * home directory on Unix.
 *
 * @param currentDirectory  a <code>File</code> object specifying
 *                          the path to a file or directory
 */
/*public*/ JFileChooser::JFileChooser(File* currentDirectory, QObject* parent) : QObject(parent)
{
 //this(currentDirectory, (FileSystemView) null);
 this->currentDirectoryPath = currentDirectory->getPath();
}

/**
 * Type value indicating that the <code>JFileChooser</code> supports an
 * "Open" file operation.
 */
/*public*/ /*static*/ /*final*/ int JFileChooser::OPEN_DIALOG = 0;

/**
 * Type value indicating that the <code>JFileChooser</code> supports a
 * "Save" file operation.
 */
/*public*/ /*static*/ /*final*/ int JFileChooser::SAVE_DIALOG = 1;
/**
 * Type value indicating that the <code>JFileChooser</code> supports a
 * developer-specified file operation.
 */
/*public*/ /*static*/ /*final*/ int JFileChooser::CUSTOM_DIALOG = 2;

/**
 * Instruction to approve the current selection
 * (same as pressing yes or ok).
 */
/*public*/ /*static*/ /*final*/ QString JFileChooser::APPROVE_SELECTION = "ApproveSelection";
/**
  * Return value if cancel is chosen.
  */
 /*public*/ /*static*/ /*final*/ int JFileChooser::CANCEL_OPTION = 1;

 /**
  * Return value if approve (yes, ok) is chosen.
  */
 /*public*/ /*static*/ /*final*/ int JFileChooser::APPROVE_OPTION = 0;

 /**
  * Return value if an error occurred.
  */
 /*public*/ /*static*/ /*final*/ int JFileChooser::ERROR_OPTION = -1;
/** Instruction to display only files. */

/*public*/ void JFileChooser::setDialogType(int dialogType)
{
 if(this->dialogType == dialogType)
 {
  return;
 }
 if(!(dialogType == OPEN_DIALOG || dialogType == SAVE_DIALOG || dialogType == CUSTOM_DIALOG))
 {
  Logger::error("Incorrect Dialog Type: " + QString::number(dialogType));
 }
 int oldValue = this->dialogType;
 this->dialogType = dialogType;
 if(dialogType == OPEN_DIALOG || dialogType == SAVE_DIALOG)
 {
  setApproveButtonText("");
 }
// firePropertyChange(DIALOG_TYPE_CHANGED_PROPERTY, oldValue, dialogType);

}
/*public*/ int JFileChooser::showDialog(QWidget* parent, QString approveButtonText)
        /*throws HeadlessException*/
{
 if (dialog != nullptr)
 {
  // Prevent to show second instance of dialog if the previous one still exists
  return JFileChooser::ERROR_OPTION;
 }

 if(approveButtonText != "")
 {
  setApproveButtonText(approveButtonText);
  setDialogType(CUSTOM_DIALOG);
 }
 dialog = createDialog(parent);
// dialog.addWindowListener(new WindowAdapter() {
//     public void windowClosing(WindowEvent e) {
//         returnValue = CANCEL_OPTION;
//     }
// });
 returnValue = ERROR_OPTION;
 //rescanCurrentDirectory();
  if(_timeout > 0)
  {
   // One shot timer to close the dialog programmatically
   timer = new QTimer(this);
   timer->setSingleShot(true);
   connect(timer, &QTimer::timeout, [=]()
   {
       dialog->close();
       timer->deleteLater();
   } );
   timer->start(_timeout);
  }

 int rslt = dialog->exec();
 switch (rslt)
 {
  case QDialog::Accepted:
  {
   returnValue = APPROVE_OPTION;
   files = dialog->selectedFiles();
   if(files.count() == 1)
   {
    selectedFile = new File(files.at(0));
    break;
   }
   selectedFile = nullptr;
   returnValue = CANCEL_OPTION;
   break;
  }
  default:
  case QDialog::Rejected:
  {
   returnValue = CANCEL_OPTION;
  }
 }

// firePropertyChange("JFileChooserDialogIsClosingProperty", dialog, NULL);

 // Remove all components from dialog. The MetalFileChooserUI.installUI() method (and other LAFs)
 // registers AWT listener for dialogs and produces memory leaks. It happens when
 // installUI invoked after the showDialog method.
// dialog.getContentPane().removeAll();
 delete dialog;
 dialog = nullptr;
 if(timer)
 {
  timer->stop();
  timer = nullptr;
 }
 return returnValue;
}

/*protected*/ QFileDialog* JFileChooser::createDialog(QWidget* parent) /*throws HeadlessException */
{
 //FileChooserUI ui = getUI();
 //QString title = ui.getDialogTitle(this);
 //putClientProperty(AccessibleContext.ACCESSIBLE_DESCRIPTION_PROPERTY,
//                          title);

//        JDialog dialog;
//        Window window = JOptionPane.getWindowForComponent(parent);
//        if (window instanceof Frame) {
//            dialog = new JDialog((Frame)window, title, true);
//        } else {
//            dialog = new JDialog((Dialog)window, title, true);
//        }
//        dialog.setComponentOrientation(this.getComponentOrientation());

//        Container contentPane = dialog.getContentPane();
//        contentPane.setLayout(new BorderLayout());
//        contentPane.add(this, BorderLayout.CENTER);

//        if (JDialog.isDefaultLookAndFeelDecorated()) {
//            boolean supportsWindowDecorations =
//            UIManager.getLookAndFeel().getSupportsWindowDecorations();
//            if (supportsWindowDecorations) {
//                dialog.getRootPane().setWindowDecorationStyle(JRootPane.FILE_CHOOSER_DIALOG);
//            }
//        }
//        dialog.pack();
//        dialog.setLocationRelativeTo(parent);
 dialog = new QFileDialog(parent);
 dialog->setOption(QFileDialog::DontUseNativeDialog);
 if(dialogType == OPEN_DIALOG)
 {
  //dialog->setFileMode(QFileDialog::ExistingFile);
  dialog->setAcceptMode(QFileDialog::AcceptOpen);
 }
 else
 {
  //dialog->setFileMode(QFileDialog::AnyFile);
  dialog->setAcceptMode(QFileDialog::AcceptSave);
 }
 switch (selectionMode)
 {
 case FILES_ONLY:
  if(dialogType == OPEN_DIALOG)
  dialog->setFileMode(QFileDialog::ExistingFile);
  else
  dialog->setFileMode(QFileDialog::AnyFile);
  break;
 case DIRECTORIES_ONLY:
  dialog->setFileMode(QFileDialog::Directory);
  dialog->setOption(QFileDialog::ShowDirsOnly, true);
  break;
 default:
 case FILES_AND_DIRECTORIES:
  if(dialogType == OPEN_DIALOG)
   dialog->setFileMode(QFileDialog::ExistingFile );
  else
   dialog->setFileMode(QFileDialog::AnyFile );
  break;
 }

 dialog->setViewMode(QFileDialog::Detail);
 dialog->setDirectory(currentDirectoryPath);
 dialog->setNameFilter(fileFilter);
 if(dialogType == SAVE_DIALOG && selectedFile != nullptr)
  dialog->selectFile(selectedFile->getAbsolutePath());
 if(selectedFilter != "" )
   dialog->selectNameFilter(selectedFilter);
 connect(dialog, SIGNAL(filterSelected(QString)), this, SLOT(on_filterSelected(QString)));
 if(approveButtonText != "")
  dialog->setLabelText(QFileDialog::Accept, this->approveButtonText);
 if(!this->title.isEmpty())
     dialog->setWindowTitle(this->title);
 else
     if(!approveButtonText.isEmpty())
         dialog->setWindowTitle(this->approveButtonText);

 dialog->showNormal();
 dialog->activateWindow();
 dialog->raise();

 return dialog;
}
/**
* Returns the selected file. This can be set either by the
* programmer via <code>setSelectedFile</code> or by a user action, such as
* either typing the filename into the UI or selecting the
* file from a list in the UI.
*
* @see #setSelectedFile
* @return the selected file
*/
/*public*/ File* JFileChooser::getSelectedFile()
{
 //files = dialog->selectedFiles();
 if(files.count() == 1)
 {
  selectedFile = new File(files.at(0));
  currentDirectoryPath = selectedFile->getParent();
  return selectedFile;
 }
 selectedFile = new File("");
 return selectedFile;
}
/*public*/ void JFileChooser::setDialogTitle(QString title)
{
 if(dialog != nullptr)
 {
  dialog->setLabelText(QFileDialog::FileName, title);
  dialog->setWindowTitle(title);
 }
 this->title = title;
}

/*public*/void JFileChooser::setFileFilter(QString fileFilter)
{
 this->fileFilter = fileFilter;
 if(dialog)
    dialog->setNameFilters(this->fileFilter.split(";"));
}

/*public*/void JFileChooser::setApproveButtonText(QString text)
{
 this->approveButtonText = text;
 if(dialog != nullptr)
  dialog->setLabelText(QFileDialog::Accept, this->approveButtonText);
}
/*public*/ int JFileChooser::showOpenDialog(QWidget* parent) /*throws HeadlessException*/
{
 setDialogType(OPEN_DIALOG);

 return showDialog(parent, "");

}
/*public*/ int JFileChooser::showSaveDialog(QWidget* parent) /*throws HeadlessException*/
{
 setDialogType(SAVE_DIALOG);
 return showDialog(parent, "");
}
/*public*/ void JFileChooser::setFileSelectionMode(int mode)
{
 selectionMode = mode;
}
/**
 * Sets the selected file. If the file's parent directory is
 * not the current directory, changes the current directory
 * to be the file's parent directory.
 *
 * @beaninfo
 *   preferred: true
 *       bound: true
 *
 * @see #getSelectedFile
 *
 * @param file the selected file
 */
/*public*/ void JFileChooser::setSelectedFile(File* file)
{
 File* oldValue = selectedFile;
 selectedFile = file;
#if 0
 if(selectedFile != NULL)
 {
  if (file->isAbsolute() && !getFileSystemView().isParent(getCurrentDirectory(), selectedFile)) {
         setCurrentDirectory(selectedFile.getParentFile());
     }
     if (!isMultiSelectionEnabled() || selectedFiles == null || selectedFiles.length == 1) {
         ensureFileIsVisible(selectedFile);
     }
 }
    firePropertyChange(SELECTED_FILE_CHANGED_PROPERTY, oldValue, selectedFile);
#endif
}
/*public*/ void JFileChooser::on_filterSelected(QString filter)
{
 selectedFilter = filter;
}

QString JFileChooser::getAcceptAllFileFilter()
{
 return "All files (*.*)";
}

QString JFileChooser::getFileFilter() { return selectedFilter;}

/**
 * Returns the current directory.
 *
 * @return the current directory
 * @see #setCurrentDirectory
 */
/*public*/ File* JFileChooser::getCurrentDirectory() {
    return currentDirectory;
}

/**
 * Sets the current directory. Passing in <code>null</code> sets the
 * file chooser to point to the user's default directory.
 * This default depends on the operating system. It is
 * typically the "My Documents" folder on Windows, and the user's
 * home directory on Unix.
 *
 * If the file passed in as <code>currentDirectory</code> is not a
 * directory, the parent of the file will be used as the currentDirectory.
 * If the parent is not traversable, then it will walk up the parent tree
 * until it finds a traversable directory, or hits the root of the
 * file system.
 *
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: The directory that the JFileChooser is showing files of.
 *
 * @param dir the current directory to point to
 * @see #getCurrentDirectory
 */
/*public*/ void JFileChooser::setCurrentDirectory(File* dir) {
    File* oldValue = currentDirectory;

    if (dir != nullptr && !dir->exists()) {
        dir = currentDirectory;
    }
    if (dir == nullptr) {
     dir = /*getFileSystemView().getDefaultDirectory();*/ new File(QDir::currentPath());
    }
    if (currentDirectory != nullptr) {
        /* Verify the toString of object */
        if (this->currentDirectory==(dir)) {
            return;
        }
    }
// TODO:
//    File* prev = nullptr;
//    while (!isTraversable(dir) && prev != dir) {
//        prev = dir;
//        dir = getFileSystemView().getParentDirectory(dir);
//    }
//    currentDirectory = dir;

//    firePropertyChange(DIRECTORY_CHANGED_PROPERTY, oldValue, currentDirectory);
}

/*public*/ void JFileChooser::settimeout(int i)
{
 _timeout = i * 1000;
 if(_timeout)
 {
  if(timer)
  {
   timer->stop();
   timer = nullptr;
  }
 }
 else
 {
  if(timer)
   timer->stop();
 }
}
/*public*/ int JFileChooser::getTimeout(){
 return _timeout / 1000;
}
