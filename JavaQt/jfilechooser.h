#ifndef JFILECHOOSER_H
#define JFILECHOOSER_H

#include <QObject>
#include <QStringList>
#include "javaqt_global.h"
#include <QTimer>
#include <QFileDialog>
#include <QKeyEvent>

class JFCFileDialog;
class FileSystemView;
class Logger;
class File;
class SwingPropertyChangeSupport;
class QFileDialog;
class JAVAQTSHARED_EXPORT JFileChooser : public QObject
{
 Q_OBJECT
public:
  explicit JFileChooser(QObject *parent = 0);
  /*public*/ static /*final*/ int OPEN_DIALOG; // = 0;
  /*public*/ static /*final*/ int SAVE_DIALOG;// = 1;
  /*public*/ static /*final*/ int CUSTOM_DIALOG;// = 2;
  /*public*/ static /*final*/ int CANCEL_OPTION;// = 1;
  /*public*/ static /*final*/ int APPROVE_OPTION;// = 0;
  /*public*/ static /*final*/ int ERROR_OPTION;// = -1;
  /*public*/ static /*final*/ QString CANCEL_SELECTION;// = "CancelSelection";
  /*public*/ static /*final*/ QString APPROVE_SELECTION;// = "ApproveSelection";
  /*public*/ static /*final*/ QString APPROVE_BUTTON_TEXT_CHANGED_PROPERTY;// = "ApproveButtonTextChangedProperty";
  /*public*/ static /*final*/ QString APPROVE_BUTTON_TOOL_TIP_TEXT_CHANGED_PROPERTY;// = "ApproveButtonToolTipTextChangedProperty";
  /*public*/ static /*final*/ QString APPROVE_BUTTON_MNEMONIC_CHANGED_PROPERTY;// = "ApproveButtonMnemonicChangedProperty";
  /*public*/ static /*final*/ QString CONTROL_BUTTONS_ARE_SHOWN_CHANGED_PROPERTY;// = "ControlButtonsAreShownChangedProperty";
  /*public*/ static /*final*/ QString DIRECTORY_CHANGED_PROPERTY;// = "directoryChanged";
  /*public*/ static /*final*/ QString SELECTED_FILE_CHANGED_PROPERTY;// = "SelectedFileChangedProperty";
  /*public*/ static /*final*/ QString SELECTED_FILES_CHANGED_PROPERTY;// = "SelectedFilesChangedProperty";
  /*public*/ static /*final*/ QString MULTI_SELECTION_ENABLED_CHANGED_PROPERTY;// = "MultiSelectionEnabledChangedProperty";
  /*public*/ static /*final*/ QString FILE_SYSTEM_VIEW_CHANGED_PROPERTY;// = "FileSystemViewChanged";
  /*public*/ static /*final*/ QString FILE_VIEW_CHANGED_PROPERTY;// = "fileViewChanged";
  /*public*/ static /*final*/ QString FILE_HIDING_CHANGED_PROPERTY;// = "FileHidingChanged";
  /*public*/ static /*final*/ QString FILE_FILTER_CHANGED_PROPERTY;// = "fileFilterChanged";
  /*public*/ static /*final*/ QString FILE_SELECTION_MODE_CHANGED_PROPERTY;// = "fileSelectionChanged";
  /*public*/ static /*final*/ QString ACCESSORY_CHANGED_PROPERTY;// = "AccessoryChangedProperty";
  /*public*/ static /*final*/ QString ACCEPT_ALL_FILE_FILTER_USED_CHANGED_PROPERTY;// = "acceptAllFileFilterUsedChanged";
  /*public*/ static /*final*/ QString DIALOG_TITLE_CHANGED_PROPERTY;// = "DialogTitleChangedProperty";
  /*public*/ static /*final*/ QString DIALOG_TYPE_CHANGED_PROPERTY;// = "DialogTypeChangedProperty";
  /*public*/ static /*final*/ QString CHOOSABLE_FILE_FILTER_CHANGED_PROPERTY;// = "ChoosableFileFilterChangedProperty";
  enum MODES
  {
   FILES_ONLY = 0,
   DIRECTORIES_ONLY = 1,
   FILES_AND_DIRECTORIES = 2
  };

 JFileChooser(int dialogType, QObject *parent);

 /*public*/ int showDialog(QWidget* parent, QString approveButtonText);
 /*public*/ File* getSelectedFile();
 /*public*/void setDialogTitle(QString title);
 /*public*/ QString getDialogTitle();
 /*public*/ JFileChooser(QString currentDirectoryPath, QObject *parent = 0);
 /*public*/ JFileChooser(File* currentDirectory, QObject* parent = 0);
 /*public*/void setFileFilter(QString fileFilter);
 /*public*/ void setDialogType(int);
 /*public*/ void setApproveButtonText(QString text);
 /*public*/ QString getApproveButtonText();
 /*public*/ void setApproveButtonToolTipText(QString string);
 /*public*/ QString getApproveButtonToolTipText();
 /*public*/ int showOpenDialog(QWidget* parent) /*throws HeadlessException*/;
 /*public*/ int showSaveDialog(QWidget* parent) /*throws HeadlessException*/;
 /*public*/ void setFileSelectionMode(int);
 /*public*/ int getFileSelectionMode();
 /*public*/ void setFileNameToolTipText(QString txt);
 /*public*/ void setSelectedFile(File* file);
 /*public*/ QString getAcceptAllFileFilter();
 /*public*/ QString getFileFilter();
 /*public*/ void setCurrentDirectory(File* dir);
 /*public*/ File* getCurrentDirectory();
 /*public*/ void settimeout(int i);
 /*public*/ int getTimeout();
 /*public*/ void setMultiSelectionEnabled(bool bln);
 /*public*/ bool isMultiSelectionEnabled();
 /*public*/ void ensureFileIsVisible(File* file);
 /*public*/ FileSystemView* getFileSystemView();

signals:

public slots:
 void on_filterSelected(QString);

private:
 int dialogType;
 JFCFileDialog* dialog = nullptr;
 SwingPropertyChangeSupport* pcs = nullptr;
 int returnValue;
 File* selectedFile = nullptr;
 QStringList files;
 QString currentDirectoryPath;
 QString fileFilter;
 QString approveButtonText;
 /*private*/ QString approveButtonToolTipText;
 /*private*/ QString fileNameToolTipText;
 int selectionMode;
 QString selectedFilter;
 File* currentDirectory = nullptr;
 QString title;
 int _timeout = -1;
 QTimer* timer = nullptr;
 bool multiSelectionEnabled =false;
 void common();
 static Logger* log;
 QList<File*>* selectedFiles = new QList<File*>();

protected:
 /*protected*/ JFCFileDialog *createDialog(QWidget* parent);// /*throws HeadlessException */

};

class JFCFileDialog : public QFileDialog
{
   Q_OBJECT
public:
    explicit JFCFileDialog(QWidget *parent = nullptr,
                         const QString &caption = QString(),
                         const QString &directory = QString(),
                         const QString &filter = QString())
        : QFileDialog(parent, caption, directory, filter) {}
signals:
    void keyPress(QKeyEvent*);
private:
    void keyPressEvent(QKeyEvent* e)
    {
     if(e)
     {
      QFileDialog::keyPressEvent(e);
      emit keyPress(e);
     }
    }
    void mouseReleaseEvent(QMouseEvent*)
    {
     emit keyPressEvent(nullptr);
    }
};

#endif // JFILECHOOSER_H
