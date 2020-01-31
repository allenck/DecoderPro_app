#ifndef ENTERREPORTERDIALOG_H
#define ENTERREPORTERDIALOG_H

#include <QObject>
#include "exceptions.h"
#include "windowlistener.h"

class Logger;
class Compoonent;
class JmriJFrame;
class JButton;
class JTextField;
class LayoutEditor;
class EnterReporterDialog : public QObject
{
 Q_OBJECT
public:
 explicit EnterReporterDialog(/*@Nonnull*/ LayoutEditor* thePanel, QObject *parent = nullptr);
 /*public*/ void enterReporter(int defaultX, int defaultY);

signals:

public slots:
private:
 static Logger* log;
 // operational instance variables shared between tools
 /*private*/ LayoutEditor* layoutEditor = nullptr;
 /*private*/ /*transient*/ JmriJFrame* enterReporterFrame = nullptr;
 /*private*/ bool reporterOpen = false;
 /*private*/ /*transient*/ JTextField* xPositionField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* yPositionField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* reporterNameField;// = new JTextField(6);
 /*=======================================*\
 |* Dialog box to enter new reporter info *|
 \*=======================================*/
 //operational variables for enter reporter pane
 /*private*/ /*transient*/ JButton* reporterDone;
 /*private*/ /*transient*/ JButton* reporterCancel;
 /*private*/ void showEntryErrorDialog(QWidget* parentComponent, NumberFormatException e);

private slots:
 /*private*/ void reporterDonePressed(/*@Nonnull*/ /*ActionEvent event*/);
 /*private*/ void reporterCancelPressed();

 friend class ERDWindowListener;
};

class ERDWindowListener : public WindowListener
{
 Q_OBJECT
 EnterReporterDialog* dlg;
public:
 ERDWindowListener(EnterReporterDialog* dlg) {this->dlg = dlg;}
 /*public*/ void windowClosing(QCloseEvent* event) {
     dlg->reporterCancelPressed();
 }

};
#endif // ENTERREPORTERDIALOG_H
