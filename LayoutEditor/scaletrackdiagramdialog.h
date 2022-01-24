#ifndef SCALETRACKDIAGRAMDIALOG_H
#define SCALETRACKDIAGRAMDIALOG_H

#include <QObject>
#include "jmrijframe.h"
#include "jtextfield.h"
#include <QPushButton>

class LayoutEditor;
class ScaleTrackDiagramDialog : public QObject
{
 Q_OBJECT
public:
 /*public*/ ScaleTrackDiagramDialog(/*@Nonnull*/ LayoutEditor* thePanel);
 /*public*/ void scaleTrackDiagram();


signals:

public slots:

private:
 // operational instance variables shared between tools
 /*private*/ LayoutEditor* layoutEditor = nullptr;
 //operational variables for scale/translate track diagram pane
 /*private*/ /*final*/ JmriJFrame* scaleTrackDiagramFrame = nullptr;
 /*private*/ bool scaleTrackDiagramOpen = false;
 /*private*/ /*final*/ JTextField* xFactorField = new JTextField(6);
 /*private*/ /*final*/ JTextField* yFactorField = new JTextField(6);
 /*private*/ /*final*/ JTextField* xTranslateField = new JTextField(6);
 /*private*/ /*final*/ JTextField* yTranslateField = new JTextField(6);
 /*private*/ /*final*/ QPushButton* scaleTrackDiagramDone;
 /*private*/ /*final*/ QPushButton* scaleTrackDiagramCancel;
 /*private*/ void scaleTrackDiagramDonePressed(/*@Nonnull ActionEvent event*/);
 static Logger* log;
 /*private*/ void showEntryErrorDialog(QWidget* parentComponent, NumberFormatException *e);
 /*private*/ void scaleTrackDiagramCancelPressed(/*ActionEvent event*/);
 friend class MyWindowListener;
};

#endif // SCALETRACKDIAGRAMDIALOG_H
