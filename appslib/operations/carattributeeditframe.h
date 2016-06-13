#ifndef CARATTRIBUTEEDITFRAME_H
#define CARATTRIBUTEEDITFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"

class ActionEvent;
class JTextField;
class QPushButton;
class QLabel;
class PropertyChangeSupport;
namespace Operations
{
 class CarManager;
 class APPSLIBSHARED_EXPORT CarAttributeEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  CarAttributeEditFrame(QWidget* parent = 0);
  PropertyChangeSupport* pcs;//;//= new java.beans.PropertyChangeSupport(this);
  // property change
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  /*public*/ void initComponents(QString comboboxName);
  /*public*/ void initComponents(QString comboboxName, QString select);
public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void deleteUnusedAttribures();
  /*public*/ void dispose();
  /*public*/ void toggleShowQuanity();
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  CarManager* carManager;//= CarManager.instance();

  // labels
  QLabel* textAttribute;//= new JLabel();
  QLabel* textSep;//= new JLabel();
  QLabel* quanity;//= new JLabel("0");

  // major buttons
  QPushButton* addButton;//= new JButton();
  QPushButton* deleteButton;//= new JButton();
  QPushButton* replaceButton;//= new JButton();

  // combo box
  QComboBox* comboBox;

  // text box
  JTextField* addTextBox;//= new JTextField(Control.max_len_string_attibute);
  QString _comboboxName; // used to determine which combo box is being edited
  /*private*/ void firePcs(QString p, QVariant old, QVariant n);
  Logger* log;
  static bool showDialogBox;// = true;
  /*private*/ void deleteItemFromCombobox(QString deleteItem);
  bool showQuanity;// = false;
  /*private*/ void loadCombobox();
  /*private*/ void addItemToCombobox(QString addItem);
  /*private*/ void replaceItem(QString oldItem, QString newItem);
  /*private*/ void updateCarQuanity();
  bool deleteUnused;// = false;
  bool cancel;// = false;

 protected:
  /*protected*/ void comboBoxActionPerformed(QWidget* ae);
 friend class OperationsFrame;
 };
}
#endif // CARATTRIBUTEEDITFRAME_H
