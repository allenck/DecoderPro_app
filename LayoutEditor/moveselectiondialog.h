#ifndef MOVESELECTIONDIALOG_H
#define MOVESELECTIONDIALOG_H

#include <QObject>
#include "layouteditor.h"

class MoveSelectionDialog : public QObject
{
  Q_OBJECT
 public:
  /*public*/ MoveSelectionDialog(/*@Nonnull*/ LayoutEditor* thePanel);
  /*public*/ void moveSelection();


 signals:

 public slots:

 private:
  /*=========================================*\
  |* Dialog box to enter move selection info *|
  \*=========================================*/
  //operational variables for move selection pane
  /*private*/ JmriJFrame* moveSelectionFrame = nullptr;
  /*private*/ bool moveSelectionOpen = false;
  /*private*/ /*final*/ JTextField* xMoveField = new JTextField(6);
  /*private*/ /*final*/ JTextField* yMoveField = new JTextField(6);
  /*private*/ QPushButton* moveSelectionDone;
  /*private*/ QPushButton* moveSelectionCancel;

  LayoutEditor* layoutEditor;
  /*private*/ void showEntryErrorDialog(QWidget* parentComponent, NumberFormatException *e);

 private slots:
  /*private*/ void moveSelectionDonePressed(/*@Nonnull ActionEvent event*/);
  /*private*/ void moveSelectionCancelPressed();


  friend class MSD_windowListener;
};

class MSD_windowListener : public WindowListener
{
  Q_OBJECT
  MoveSelectionDialog* dlg;
 public:
  MSD_windowListener(MoveSelectionDialog* dlg) {this->dlg = dlg;}
  void windowClosing(QCloseEvent*)
  {
   dlg->moveSelectionCancelPressed();
  }
};
#endif // MOVESELECTIONDIALOG_H
