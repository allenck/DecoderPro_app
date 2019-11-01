#ifndef CARLOADEDITFRAME_H
#define CARLOADEDITFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"

class PropertyChangeEvent;
class JTextField;
class QLabel;
namespace Operations
{
 class CarLoads;
 class APPSLIBSHARED_EXPORT CarLoadEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  CarLoadEditFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString NONE;// = "";
  /*public*/ void initComponents(QString type, QString select);
  /*public*/ void toggleShowQuanity();
  /*public*/ void dispose();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  CarLoads* carLoads;//= CarLoads.instance();

  // labels
  QLabel* textSep;//= new JLabel();
  QLabel* quanity;//= new JLabel("0");

  // major buttons
  QPushButton* addButton;//= new JButton(Bundle.getMessage("Add"));
  QPushButton* deleteButton;//= new JButton(Bundle.getMessage("Delete"));
  QPushButton* replaceButton;//= new JButton(Bundle.getMessage("Replace"));
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  // combo boxes
  QComboBox* loadComboBox;
  QComboBox* priorityComboBox;
  QComboBox* loadTypeComboBox;//= carLoads.getLoadTypesComboBox();

  // text boxes
  JTextField* addTextBox;//= new JTextField(10);
  JTextField* pickupCommentTextField;//= new JTextField(35);
  JTextField* dropCommentTextField;//= new JTextField(35);
  QString _type;
  bool menuActive;// = false;
  Logger* log;
  bool showQuanity;// = false;
  /*private*/ void loadComboboxes();
  /*private*/ void updateLoadType();
   /*private*/ void updatePriority();
  /*private*/ void updateCarQuanity();
  /*private*/ void updateCarCommentFields();
  /*private*/ void replaceAllLoads(QString oldLoad, QString newLoad) ;
  /*private*/ void deleteLoadFromCombobox(QString type, QString name);
  /*private*/ void replaceLoad(QString type, QString oldLoad, QString newLoad);
  /*private*/ void addLoadToCombobox(QString type, QString name);

 protected slots:
 /*protected*/ void comboBoxActionPerformed(QWidget* ae);
 };

}
#endif // CARLOADEDITFRAME_H
