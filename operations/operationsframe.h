#ifndef OPERATIONSFRAME_H
#define OPERATIONSFRAME_H
#include "jmrijframe.h"
#include "appslib_global.h"

class HtmlTextEdit;
class QScrollArea;
class JTextArea;
class JTable;
class ChangeEvent;
class QSignalMapper;
class JButton;
class QRadioButton;
class JComboBox;
class QCheckBox;
class QSpinBox;
namespace Operations
{
 class OperationsPanel;
 class APPSLIBSHARED_EXPORT OperationsFrame : public JmriJFrame
 {
  Q_OBJECT
 public:
  /*public*/ static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
  /*public*/ static /*final*/ QString NONE;// = ""; // NOI18N
  /*public*/ OperationsFrame(QString s, QWidget* parent = 0);
  /*public*/ OperationsFrame(QWidget* parent = 0);
  /*public*/ OperationsFrame(OperationsPanel* p, QWidget* parent = 0);
  /*public*/ OperationsFrame(QString s, OperationsPanel* p, QWidget* parent = 0);
  /*public*/ void initComponents() override;
  /*public*/ void initMinimumSize();
  /*public*/ void initMinimumSize(QSize dimension);
  /*public*/ bool loadTableDetails(JTable* table);
  /*public*/ void dispose()override;

 private:
  void common();
  Logger* log;

protected:
  /*protected*/ /*synchronized*/ void createShutDownTask();
  /*protected*/ void addButtonAction(JButton* b);
  /*protected*/ void addRadioButtonAction(QRadioButton* b);
  /*protected*/ void addCheckBoxAction(QCheckBox* b);
  /*protected*/ void addSpinnerChangeListerner(QSpinBox* s);
  /*protected*/ void addComboBoxAction(JComboBox* b) ;
  /*protected*/ void selectNextItemComboBox(JComboBox* b);
  /*protected*/ void clearTableSort(JTable* table);

  /*protected*/ void addItem(JPanel* p, QWidget* c, int x, int y) ;
  /*protected*/ void addItemLeft(JPanel* p, QWidget* c, int x, int y);
  /*protected*/ void addItemTop(JPanel* p, QWidget* c, int x, int y) ;
  /*protected*/ void addItemWidth(JPanel *p, QWidget *c, int width, int x, int y);
  /*protected*/ int getNumberOfCheckboxesPerLine();
  /*protected*/ void saveTableDetails(JTable* table);
  /*protected*/ void addItem(QWidget *c, int x, int y);
//  /*protected*/ void addItemLeft(QWidget* c, int x, int y);
//  /*protected*/ void addItemWidth(QWidget* c, int width, int x, int y);
  /*protected*/ void storeValues();

  protected slots:
  /*protected*/ virtual void comboBoxActionPerformed(QWidget* ae);
  /*protected*/ virtual void buttonActionPerformed(QWidget* b);
  /*protected*/ virtual void radioButtonActionPerformed(QWidget* b);
  /*protected*/ virtual void checkBoxActionPerformed(QWidget* b) ;
  /*protected*/ virtual void spinnerChangeEvent(QWidget* ae) ;
  /*protected*/ void adjustTextAreaColumnWidth(QWidget* scrollPane, JTextArea* textArea);
  /*protected*/ void adjustTextAreaColumnWidth(QWidget* scrollPane, HtmlTextEdit* textArea);

 };
}
#endif // OPERATIONSFRAME_H
