#ifndef OPERATIONSPANEL_H
#define OPERATIONSPANEL_H

#include "preferencespanel.h"
#include "appslib_global.h"

class JTextArea;
class HtmlTextEdit;
class QSCrollArea;
class JTable;
class QComboBox;
class ChangeEvent;
class QSpinBox;
class QCheckBox;
class QRadioButton;
class Logger;
class QSignalMapper;
class JActionEvent;
class QPushButton;
namespace Operations
{
 class APPSLIBSHARED_EXPORT OperationsPanel : /*public PreferencesPanel,*/ public QWidget
 {
  Q_OBJECT
  //Q_INTERFACES(PreferencesPanel)

 public:
  explicit OperationsPanel(QWidget *parent = 0);
  /*public*/ static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
  /*public*/ static /*final*/ QString NONE;// = ""; // NOI18N
  /*public*/ void initMinimumSize() ;
  /*public*/ void initMinimumSize(QSize dimension) ;
  /*public*/ void dispose();
  /*public*/ bool loadTableDetails(JTable* table);

 signals:

 public slots:
 private:
  QSignalMapper* buttonMapper;
  QSignalMapper* radioButtonMapper;
  QSignalMapper* checkBoxMapper;
  QSignalMapper* comboBoxMapper;
  Logger* log;
  /*private*/ static /*final*/ int MIN_CHECKBOXES;// = 5;
  /*private*/ static /*final*/ int MAX_CHECKBOXES;// = 11;

 protected:
  /*protected*/ /*synchronized*/ void createShutDownTask();
  /*protected*/ void addButtonAction(QPushButton* b);
  /*protected*/ void addRadioButtonAction(QRadioButton* b);
  /*protected*/ void addCheckBoxAction(QCheckBox* b);
  /*protected*/ void addComboBoxAction(QComboBox* b);
  /*protected*/ void selectNextItemComboBox(QComboBox* b);
  /*protected*/ void clearTableSort(JTable* table);
  /*protected*/ void addItem(QWidget* c, int x, int y);
  /*protected*/ void addItemLeft(QWidget* c, int x, int y);
  /*protected*/ void addItemWidth(QWidget* c, int width, int x, int y);
  /*protected*/ void addItem(QWidget* p, QWidget* c, int x, int y);
  /*protected*/ void addItemLeft(QWidget* p, QWidget* c, int x, int y);
  /*protected*/ void addItemTop(QWidget* p, QWidget* c, int x, int y);
  /*protected*/ void addItemWidth(QWidget* p, QWidget* c, int width, int x, int y);
  /*protected*/ int getNumberOfCheckboxesPerLine() ;
  /*protected*/ int getNumberOfCheckboxesPerLine(QSize size);
  QString gbStyleSheet;
  /*protected*/ void storeValues();

 protected slots:
  /*protected*/ virtual void buttonActionPerformed(QWidget*);
  /*protected*/ virtual void radioButtonActionPerformed(QWidget*);
  /*protected*/ virtual void checkBoxActionPerformed(QWidget *);
  /*protected*/ void addSpinnerChangeListerner(QSpinBox* s);
  /*protected*/ virtual void spinnerChangeEvent(ChangeEvent* ae = 0);
  /*protected*/ virtual void comboBoxActionPerformed(QWidget* ae);
  /*protected*/ void adjustTextAreaColumnWidth(QWidget* scrollPane, JTextArea* textArea);
  /*protected*/ void adjustTextAreaColumnWidth(QWidget* scrollPane, HtmlTextEdit* textArea);
  /*protected*/ void adjustTextAreaColumnWidth(QWidget* scrollPane, JTextArea* textArea, QSize size);
  /*protected*/ void adjustTextAreaColumnWidth(QWidget* scrollPane, HtmlTextEdit* textArea, QSize size);
  /*protected*/ QString getWindowFrameRef();

 friend class OperationsFrame;
 };
}

#endif // OPERATIONSPANEL_H
