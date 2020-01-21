#ifndef ENGINEATTRIBUTEEDITFRAME_H
#define ENGINEATTRIBUTEEDITFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"

class PropertyChangeSupport;
class JTextField;
class QLabel;
class QPushButton;
namespace Operations
{
 class Control;
 class EngineManager;
 class APPSLIBSHARED_EXPORT EngineAttributeEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  explicit EngineAttributeEditFrame(QWidget *parent = 0);
  /*public*/ void initComponents(QString comboboxName) ;
  /*public*/ void initComponents(QString comboboxName, QString select);
  /*public*/ void dispose();
  PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
  /*public*/ QString getClassName();

 signals:

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:

  EngineManager* engineManager;// = EngineManager .instance();

  // labels
  QLabel* textAttribute;// = new QLabel();
  QLabel* textSep;// = new QLabel();

  // major buttons
  QPushButton* addButton;// = new QPushButton();
  QPushButton* deleteButton;// = new QPushButton();
  QPushButton* replaceButton;// = new QPushButton();

  // combo box
  QComboBox* comboBox;

  // text box
  JTextField* addTextBox;// = new JTextField(Control.max_len_string_attibute);

  // property change
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  QString _comboboxName; // track which combo box is being edited
  bool menuActive;// = false;
  /*private*/ void deleteItemFromCombobox(QString deleteItem);
  /*private*/ void addItemToCombobox(QString addItem);
  Logger* log;
  /*private*/ void loadCombobox();
  /*private*/ void replaceItem(QString oldItem, QString newItem);
  /*private*/ void firePcs(QString p, QVariant old, QVariant n);


 friend class EngineEditFrame;
 };
}
#endif // ENGINEATTRIBUTEEDITFRAME_H
