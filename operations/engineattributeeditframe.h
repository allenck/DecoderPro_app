#ifndef ENGINEATTRIBUTEEDITFRAME_H
#define ENGINEATTRIBUTEEDITFRAME_H
#include "rollingstockattributeeditframe.h"
#include "appslib_global.h"

class JComboBox;
class PropertyChangeSupport;
class JTextField;
class QLabel;
class QPushButton;
namespace Operations
{
 class Control;
 class EngineManager;
 class APPSLIBSHARED_EXPORT EngineAttributeEditFrame : public RollingStockAttributeEditFrame
 {
  Q_OBJECT
 public:
  explicit EngineAttributeEditFrame(QWidget *parent = 0);
  /*public*/ void initComponents(QString comboboxName) ;
  /*public*/ void initComponents(QString comboboxName, QString name);
  /*public*/ void dispose() override;
  PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
  /*public*/ QString getClassName();
  // valid attributes for this frame
  /*public*/ static /*final*/ QString ROAD;// = tr("Road");
  /*public*/ static /*final*/ QString MODEL;// = tr("Model");
  /*public*/ static /*final*/ QString TYPE;// = tr("Type");
  /*public*/ static /*final*/ QString COLOR;// = tr("Color");
  /*public*/ static /*final*/ QString LENGTH;// = tr("Length");
  /*public*/ static /*final*/ QString OWNER;// = tr("Owner");
  /*public*/ static /*final*/ QString CONSIST;// = tr("Consist");

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:

  EngineManager* engineManager;// = EngineManager .instance();
  Logger* log;

  protected:
  /*protected*/ void deleteAttributeName(QString deleteItem);
  /*protected*/ void addAttributeName(QString addItem)override;
  /*protected*/ void replaceItem(QString oldItem, QString newItem) override;
  /*protected*/ void loadCombobox() override;


 friend class EngineEditFrame;
 };
}
#endif // ENGINEATTRIBUTEEDITFRAME_H
