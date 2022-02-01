#ifndef FUNCTIONSHELPDIALOG_H
#define FUNCTIONSHELPDIALOG_H

#include <QObject>
#include <QMap>
#include "module.h"
#include "jdialog.h"
#include "jcombobox.h"
#include "jlabel.h"
#include "jeditorpane.h"

class FunctionsHelpDialog : public QObject
{
  Q_OBJECT
 public:
  explicit FunctionsHelpDialog(QObject *parent = nullptr);
  /*public*/  void showDialog();

 signals:

 private:
  /*private*/ static /*final*/ int panelWidth;// = 500;
  /*private*/ static /*final*/ int panelHeight;// = 500;

  /*private*/ static /*final*/ QMap<QString, Module*> _modules;// = QMap<QString, Module*>();
  /*private*/ JDialog* _selectItemTypeDialog = nullptr;
  /*private*/ /*final*/ JComboBox/*<Module>*/* _moduleComboBox = new JComboBox();
  /*private*/ /*final*/ JComboBox/*<SortableFunction>*/* _functionComboBox = new JComboBox();
  /*private*/ /*final*/ JLabel* _moduleLabel = new JLabel(tr("Module") + ":");  // NOI18N
  /*private*/ /*final*/ JLabel* _functionLabel = new JLabel(tr("Function") + ":");   // NOI18N
  /*private*/ /*final*/ JEditorPane* _documentationEditorPane = new JEditorPane();

};

#endif // FUNCTIONSHELPDIALOG_H
