#ifndef JFILECHOOSER_H
#define JFILECHOOSER_H

#include <QObject>
#include <QStringList>
#include "javaqt_global.h"
#include <QTimer>

class File;
class PropertyChangeSupport;
class QFileDialog;
class JAVAQTSHARED_EXPORT JFileChooser : public QObject
{
 Q_OBJECT
public:
  explicit JFileChooser(QObject *parent = 0);
  /*public*/ static /*final*/ int OPEN_DIALOG; // = 0;
  /*public*/ static /*final*/ int SAVE_DIALOG;// = 1;
  /*public*/ static /*final*/ int CUSTOM_DIALOG;// = 2;
  /*public*/ static /*final*/ QString APPROVE_SELECTION;// = "ApproveSelection";
  /*public*/ static /*final*/ int CANCEL_OPTION;// = 1;
  /*public*/ static /*final*/ int APPROVE_OPTION;// = 0;
  /*public*/ static /*final*/ int ERROR_OPTION;// = -1;
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
 /*public*/ JFileChooser(QString currentDirectoryPath, QObject *parent = 0);
 /*public*/ JFileChooser(File* currentDirectory, QObject* parent = 0);
 /*public*/void setFileFilter(QString fileFilter);
 /*public*/ void setDialogType(int);
 /*public*/ void setApproveButtonText(QString text);
 /*public*/ int showOpenDialog(QWidget* parent) /*throws HeadlessException*/;
 /*public*/ int showSaveDialog(QWidget* parent) /*throws HeadlessException*/;
 /*public*/ void setFileSelectionMode(int);
 /*public*/ void setSelectedFile(File* file);
 /*public*/ QString getAcceptAllFileFilter();
 /*public*/ QString getFileFilter();
 /*public*/ void setCurrentDirectory(File* dir);
 /*public*/ File* getCurrentDirectory();
 /*public*/ void settimeout(int i);
 /*public*/ int getTimeout();

signals:

public slots:
 void on_filterSelected(QString);

private:
 int dialogType;
 QFileDialog* dialog;
 PropertyChangeSupport* pcs;
 int returnValue;
 File* selectedFile;
 QStringList files;
 QString currentDirectoryPath;
 QString fileFilter;
 QString approveButtonText;
 int selectionMode;
 QString selectedFilter;
 File* currentDirectory;
 QString title;
 int _timeout = -1;
 QTimer* timer = nullptr;

 void common();

protected:
 /*protected*/ QFileDialog* createDialog(QWidget* parent);// /*throws HeadlessException */

};

#endif // JFILECHOOSER_H
