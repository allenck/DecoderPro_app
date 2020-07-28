#ifndef ENTERGRIDSIZESDIALOG_H
#define ENTERGRIDSIZESDIALOG_H

#include <QObject>
#include "jmrijframe.h"
#include"jtextfield.h"
#include <QPushButton>
#include "layouteditor.h"

class LayoutEditor;
class EnterGridSizesDialog : public QObject
{
  Q_OBJECT
 public:
  /*public*/ EnterGridSizesDialog(/*@Nonnull*/ LayoutEditor* thePanel);
  /*public*/ void enterGridSizes();


 signals:

 public slots:

 private:
  /*====================================*\
  |* Dialog box to enter new grid sizes *|
  \*====================================*/
  //operational variables for enter grid sizes pane
  /*private*/ JmriJFrame* enterGridSizesFrame = nullptr;
  /*private*/ bool enterGridSizesOpen = false;
  /*private*/ bool gridSizesChange = false;
  /*private*/ /*final*/ JTextField* primaryGridSizeField = new JTextField(6);
  /*private*/ /*final*/ JTextField* secondaryGridSizeField = new JTextField(6);
  /*private*/ QPushButton* gridSizesDone;
  /*private*/ QPushButton* gridSizesCancel;
  // operational instance variables shared between dialogs
  /*private*/ LayoutEditor* layoutEditor = nullptr;
  /*private*/ void showEntryErrorDialog(QWidget* parentComponent, NumberFormatException e);

 private slots:
  /*private*/ void gridSizesDonePressed(/*@Nonnull ActionEvent event*/);
  /*private*/ void gridSizesCancelPressed(/*ActionEvent event*/);


  friend class EGSD_WindowListener;
};
class EGSD_WindowListener : public WindowListener
{
  Q_OBJECT
  EnterGridSizesDialog* dlg;
 public:
  EGSD_WindowListener(EnterGridSizesDialog* dlg) {this->dlg = dlg;}

  void windowClosing(QCloseEvent*)
  {
   dlg->gridSizesCancelPressed();
  }
};
#endif // ENTERGRIDSIZESDIALOG_H
