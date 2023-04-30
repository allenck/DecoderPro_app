#include "jfilechooser.h"
#include "file.h"
#include "swingpropertychangesupport.h"
#include "loggerfactory.h"
#include "vptr.h"
#include "filesystemview.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLineEdit>

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
 pcs = new SwingPropertyChangeSupport(this, nullptr);
 dialog = nullptr;
 dialogType = OPEN_DIALOG;
 approveButtonText = "";
 currentDirectoryPath = "";
 selectionMode = FILES_AND_DIRECTORIES;
 selectedFile = nullptr;
 files = QStringList();
 currentDirectory =  new File(QDir::currentPath());
 selectedFile = currentDirectory;
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
 common();
 //this(currentDirectory, (FileSystemView) null);
 this->currentDirectory = currentDirectory;
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
/*public*/ /*static*/ /*final*/ QString JFileChooser::CANCEL_SELECTION = "CancelSelection";
///*public*/ /*static*/ /*final*/ QString JFileChooser::APPROVE_SELECTION = "ApproveSelection";
/*public*/ /*static*/ /*final*/ QString JFileChooser::APPROVE_BUTTON_TEXT_CHANGED_PROPERTY = "ApproveButtonTextChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::APPROVE_BUTTON_TOOL_TIP_TEXT_CHANGED_PROPERTY = "ApproveButtonToolTipTextChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::APPROVE_BUTTON_MNEMONIC_CHANGED_PROPERTY = "ApproveButtonMnemonicChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::CONTROL_BUTTONS_ARE_SHOWN_CHANGED_PROPERTY = "ControlButtonsAreShownChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::DIRECTORY_CHANGED_PROPERTY = "directoryChanged";
/*public*/ /*static*/ /*final*/ QString JFileChooser::SELECTED_FILE_CHANGED_PROPERTY = "SelectedFileChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::SELECTED_FILES_CHANGED_PROPERTY = "SelectedFilesChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::MULTI_SELECTION_ENABLED_CHANGED_PROPERTY = "MultiSelectionEnabledChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::FILE_SYSTEM_VIEW_CHANGED_PROPERTY = "FileSystemViewChanged";
/*public*/ /*static*/ /*final*/ QString JFileChooser::FILE_VIEW_CHANGED_PROPERTY = "fileViewChanged";
/*public*/ /*static*/ /*final*/ QString JFileChooser::FILE_HIDING_CHANGED_PROPERTY = "FileHidingChanged";
/*public*/ /*static*/ /*final*/ QString JFileChooser::FILE_FILTER_CHANGED_PROPERTY = "fileFilterChanged";
/*public*/ /*static*/ /*final*/ QString JFileChooser::FILE_SELECTION_MODE_CHANGED_PROPERTY = "fileSelectionChanged";
/*public*/ /*static*/ /*final*/ QString JFileChooser::ACCESSORY_CHANGED_PROPERTY = "AccessoryChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::ACCEPT_ALL_FILE_FILTER_USED_CHANGED_PROPERTY = "acceptAllFileFilterUsedChanged";
/*public*/ /*static*/ /*final*/ QString JFileChooser::DIALOG_TITLE_CHANGED_PROPERTY = "DialogTitleChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::DIALOG_TYPE_CHANGED_PROPERTY = "DialogTypeChangedProperty";
/*public*/ /*static*/ /*final*/ QString JFileChooser::CHOOSABLE_FILE_FILTER_CHANGED_PROPERTY = "ChoosableFileFilterChangedProperty";


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
 pcs->firePropertyChange(DIALOG_TYPE_CHANGED_PROPERTY, oldValue, dialogType);
}

/*public*/ int JFileChooser::showDialog(QWidget* parent, QString approveButtonText)
        /*throws HeadlessException*/
{
 if (dialog != nullptr)
 {
  // Prevent to show second instance of dialog if the previous one still exists
  return JFileChooser::ERROR_OPTION;
 }

 dialog = createDialog(parent);

 if(!approveButtonText.isEmpty())
 {
  setDialogType(CUSTOM_DIALOG);
  setApproveButtonText(approveButtonText);
 }

 if(!approveButtonToolTipText.isEmpty()){
  QString label = dialog->labelText(QFileDialog::Accept);
  QList<QPushButton*> buttons = dialog->findChildren<QPushButton*>();
  foreach(QPushButton* button, buttons)
  {
   if(button->text() == label)
   {
    button->setToolTip(approveButtonToolTipText);
    break;
   }
  }
 }
 if(!fileNameToolTipText.isEmpty())
 {
  setFileNameToolTipText(this->fileNameToolTipText);
 }

 if(dialogType == SAVE_DIALOG)
 {
  //QFileDialog::getSaveFileName((QWidget*)this->parent(), tr("Enter save folder name"), selectedFile->getPath(), "xml (*.xml)");
  dialog->selectFile(selectedFile->fileName());
 }

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
  connect(timer, &QTimer::timeout, [=]
  {
      dialog->close();
      timer->deleteLater();
  } );
  timer->start(_timeout);
 }

 log->debug(tr("executing QFileDialog at %1").arg(dialog->directory().path()));
 int rslt = dialog->exec();
 switch (rslt)
 {
  case QDialog::Accepted:
  {
   returnValue = APPROVE_OPTION;
   files = dialog->selectedFiles();
   selectedFiles->clear();
   foreach(QString fn, files)
   {
    selectedFiles->append(new File(fn));
   }
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

/*protected*/ JFCFileDialog* JFileChooser::createDialog(QWidget* parent) /*throws HeadlessException */
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
 dialog = new JFCFileDialog(parent, QString(), currentDirectoryPath);
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
  dialog->setFileMode(multiSelectionEnabled?QFileDialog::ExistingFiles: QFileDialog::ExistingFile);
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
   dialog->setFileMode(multiSelectionEnabled?QFileDialog::ExistingFiles: QFileDialog::ExistingFile );
  else
   dialog->setFileMode(QFileDialog::AnyFile );
  break;
 }

 dialog->setViewMode(QFileDialog::Detail);
 dialog->setDirectory(currentDirectoryPath);
 dialog->setNameFilter(fileFilter);
// if(dialogType == SAVE_DIALOG && selectedFile != nullptr)
//  dialog->selectFile(selectedFile->getAbsolutePath());
 if(selectedFilter != "" )
   dialog->selectNameFilter(selectedFilter);
 connect(dialog, SIGNAL(filterSelected(QString)), this, SLOT(on_filterSelected(QString)));
 if(approveButtonText != "")
  dialog->setLabelText(QFileDialog::Accept, this->approveButtonText);
 if(!this->title.isEmpty())
     dialog->setWindowTitle(this->title);
 else
 {
     if(!approveButtonText.isEmpty())
         dialog->setWindowTitle(this->approveButtonText);
  if(!approveButtonToolTipText.isEmpty())
  {
   QString label = dialog->labelText(QFileDialog::Accept);
   QList<QPushButton*> buttons = dialog->findChildren<QPushButton*>();
   foreach(QPushButton* button, buttons)
   {
    if(button->text() == approveButtonToolTipText)
     button->setToolTip(approveButtonToolTipText);
    break;
   }
  }
 }
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

/*public*/ QString JFileChooser::getDialogTitle() {
 if(dialog != nullptr)
 {
  this->title = dialog->windowTitle();
 }
 return this->title;
}

/*public*/void JFileChooser::setFileFilter(QString fileFilter)
{
 this->fileFilter = fileFilter;
 if(dialog)
    dialog->setNameFilters(this->fileFilter.split(";"));
}

/*public*/void JFileChooser::setApproveButtonText(QString text)
{
 if(dialog != nullptr)
  dialog->setLabelText(QFileDialog::Accept, text);
 this->approveButtonText = text;
}

/*public*/ QString JFileChooser::getApproveButtonText()
{
 return approveButtonText;
}

/*public*/ void JFileChooser::setApproveButtonToolTipText(QString string) {
 if(dialog != nullptr)
 {
  QString label = dialog->labelText(QFileDialog::Accept);
  QList<QPushButton*> buttons = dialog->findChildren<QPushButton*>();
  foreach(QPushButton* button, buttons)
  {
   if(button->text() == string)
    button->setToolTip(string);
   break;
  }
 }
 approveButtonToolTipText = string;
}

/*public*/ QString JFileChooser::getApproveButtonToolTipText() {
  return approveButtonToolTipText;
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

/*public*/ int JFileChooser::getFileSelectionMode() {
 return selectionMode;
}

/*public*/ void JFileChooser::setFileNameToolTipText(QString txt)
{
 QList<QLineEdit*> widgets = dialog->findChildren<QLineEdit*>();
 foreach(QLineEdit* widget, widgets)
 {
   widget->setToolTip(txt);
  break;
 }
 this->fileNameToolTipText = txt;
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
#if 1
 if(selectedFile != nullptr)
 {
  if (file->isAbsolute() && !getFileSystemView()->isParent(getCurrentDirectory(), selectedFile)) {
         setCurrentDirectory(selectedFile->getParentFile());
     }
     if (!isMultiSelectionEnabled() || selectedFiles == nullptr || selectedFiles->length() == 1) {
         ensureFileIsVisible(selectedFile);
     }
     //dialog->getSaveFileName(nullptr, tr("Enter save folder name"), selectedFile->getPath(), "xml (*.xml)");
 }
 pcs->firePropertyChange(SELECTED_FILE_CHANGED_PROPERTY, oldValue?oldValue->getPath():QString(), selectedFile->getPath());
#endif
}

/*public*/ void JFileChooser::setMultiSelectionEnabled(bool bln) {
 multiSelectionEnabled = bln;
}

/*public*/ bool JFileChooser::isMultiSelectionEnabled() {
 return multiSelectionEnabled;
}

/*public*/ FileSystemView* JFileChooser::getFileSystemView(){
 return new FileSystemView();
}

/*public*/ void JFileChooser::ensureFileIsVisible(File *file)
{

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
    selectedFile = dir;

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

    pcs->firePropertyChange(DIRECTORY_CHANGED_PROPERTY, oldValue, currentDirectory);
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
 connect(dialog, &JFCFileDialog::keyPress, [=] {
     timer->start(i*1000);
 });
}
/*public*/ int JFileChooser::getTimeout(){
 return _timeout / 1000;
}

Logger* JFileChooser::log = LoggerFactory::getLogger("JFileChooser");
