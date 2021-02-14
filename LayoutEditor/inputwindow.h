#ifndef INPUTWIDOW_H
#define INPUTWIDOW_H

#include <QWidget>
#include "PythonQt_QtAll.h"
#include "PythonQt.h"
#include <QEventLoop>

class QComboBox;
class UserPreferencesManager;
class PythonQtObjectPtr;
class File;
class Logger;
class JFileChooser;
class JTextArea;
class QPushButton;
class QCheckBox;
class QLabel;
class InputWindow : public QWidget
{
 Q_OBJECT
public:
 explicit InputWindow(QWidget *parent = 0);
 static /*public*/ File* getFile(JFileChooser* fileChooser);

signals:

public slots:
 void on_cursorPositionChanged();

private:
 JTextArea* area;
 QPushButton* button;
 QPushButton* loadButton;
 QPushButton* storeButton;
 QPushButton* stopButton;
 QLabel* status;
 QCheckBox* alwaysOnTopCheckBox;// = new JCheckBox();
 QComboBox* languages;// = new JComboBox<>();
 JFileChooser* userFileChooser;
 /*private*/ void updateStatus(int linenumber, int columnnumber);
 Logger* log;
 PythonQtObjectPtr interp;
 UserPreferencesManager* pref;
 QString alwaysOnTop;
 QThread* thread;
 QEventLoop loop;

private slots:
 void buttonPressed();
 void storeButtonPressed();
 void loadButtonPressed();
 void on_alwaysOnTop_toggled(bool);
 void stopButtonPressed();
 void on_pythonStdErr(QString);

protected:
 /*protected*/ bool loadFile(JFileChooser* fileChooser);
 /*protected*/ bool storeFile(JFileChooser* fileChooser);
 friend class Worker;
};

class Worker : public QObject
{
 Q_OBJECT
 InputWindow* parent;
 QString script;
 PythonQtObjectPtr interp;
public:
 Worker(QString script, InputWindow* parent);
 ~Worker() {}

 signals:
   void finished();

 public slots:
  void process();
  void stopRequested();
};

#endif // INPUTWIDOW_H
