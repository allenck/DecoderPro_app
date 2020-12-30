#ifndef CARATTRIBUTEEDITFRAME_H
#define CARATTRIBUTEEDITFRAME_H
#include "rollingstockattributeeditframe.h"
#include "appslib_global.h"
#include "jcombobox.h"

class JActionEvent;
class JTextField;
class QPushButton;
class QLabel;
class PropertyChangeSupport;
namespace Operations
{
 class CarManager;
 class APPSLIBSHARED_EXPORT CarAttributeEditFrame : public RollingStockAttributeEditFrame
 {
  Q_OBJECT
 public:
  CarAttributeEditFrame(QWidget* parent = 0);
  PropertyChangeSupport* pcs;//;//= new java.beans.PropertyChangeSupport(this);
  // property change
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  /*public*/ void initComponents(QString comboboxName);
  /*public*/ void initComponents(QString comboboxName, QString select);
  /*public*/ QString getClassName();
  // valid attributes for this frame
  /*public*/ static /*final*/ QString ROAD;//  Bundle.getMessage("Road");
  /*public*/ static /*final*/ QString TYPE;//  Bundle.getMessage("Type");
  /*public*/ static /*final*/ QString COLOR;//  Bundle.getMessage("Color");
  /*public*/ static /*final*/ QString LENGTH;//  Bundle.getMessage("Length");
  /*public*/ static /*final*/ QString OWNER;//  Bundle.getMessage("Owner");
  /*public*/ static /*final*/ QString KERNEL;//  Bundle.getMessage("Kernel");
  /*public*/ void toggleShowQuanity();
  /*public*/ void deleteUnusedAttributes();
  /*public*/ void dispose();

public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  CarManager* carManager;//= CarManager.instance();
  static Logger* log;

  bool deleteUnused = false;
  bool cancel = false;
  /*private*/ void updateCarQuanity();

 protected:
  /*protected*/ void comboBoxActionPerformed(QWidget* ae) override;
  /*protected*/ void deleteAttributeName(QString deleteItem) override;
  /*protected*/ void addAttributeName(QString addItem) override;
  /*protected*/ void replaceItem(QString oldItem, QString newItem) override;
  /*protected*/ void loadCombobox() override;

 friend class OperationsFrame;
 };
}
#endif // CARATTRIBUTEEDITFRAME_H
