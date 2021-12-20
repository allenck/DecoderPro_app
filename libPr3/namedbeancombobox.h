#ifndef NAMEDBEANCOMBOBOX_H
#define NAMEDBEANCOMBOBOX_H
#include "jcombobox.h"
#include "manager.h"
//#include "namedbeancomparator.h"
#include "systemnamecomparator.h"
#include "algorithm"
#include "alphanumcomparator.h"

class NamedBeanComboBox : public JComboBox
{
 Q_OBJECT
public:
 NamedBeanComboBox(QWidget *parent = nullptr);
 /*public*/ NamedBeanComboBox(Manager/*<B>*/* manager, QWidget *parent=nullptr);
 /*public*/ NamedBeanComboBox(Manager/*<B>*/* manager, NamedBean* selection, QWidget* parent=nullptr);
 /*public*/ NamedBeanComboBox(Manager/*<B>*/* manager, NamedBean* selection, NamedBean::DisplayOptions displayOrder, QWidget* parent=nullptr);
 /*public*/ Manager/*<B>*/* getManager();
 /*public*/ NamedBean::DisplayOptions getDisplayOrder() ;
 /*public*/ /*final*/ void setDisplayOrder(NamedBean::DisplayOptions displayOrder);
 /*public*/ bool isValidatingInput();
 /*public*/ void setValidatingInput(bool validatingInput);
 /*public*/ bool isAllowNull();
 /*public*/ void setAllowNull(bool allowNull);
 /*public*/ NamedBean* getSelectedItem();
 /*public*/ bool isProviding();
 /*public*/ void setProviding(bool providing);
 /*public*/ void setEditable(bool editable);
 /*public*/ QString getSelectedItemDisplayName();
 /*public*/ QString getSelectedItemSystemName();
 /*public*/ QString getSelectedItemUserName();
 /*public*/ void setSelectedItem(NamedBean* item);
 /*public*/ void setSelectedItemByName(QString name) ;
 /*public*/ void dispose();
 /*public*/ void setManager(Manager* manager);
 /*public*/ NamedBean* getNamedBean();
 /*public*/ QSet<NamedBean*> getExcludedItems();
 /*public*/ void setExcludedItems(QSet<NamedBean*> excludedItems);
 /*public*/ QString getBeanInUseMessage(QString beanType, QString displayName);
 /*public*/ QString getInvalidNameFormatMessage(QString beanType, QString text, QString exception);
 /*public*/ QString getNoMatchingBeanMessage(QString beanType, QString text);
 /*public*/ QString getWillCreateBeanMessage(QString beanType, QString text);

private:
 static Logger* log;
 /*private*/ void sort();
 Manager* manager;
 NamedBean::DisplayOptions displayOptions;
 bool validatingInput = false;
 bool allowNull=false;
 bool providing = false;
 QString userInput;
 QSet<NamedBean*> excludedItems;
 PropertyChangeListener* managerListener = nullptr;

 private slots:
 void PropertyChange(PropertyChangeEvent* evt)
 {
  if(evt->getPropertyName() == "bean")
  {

  }
 }
};

class NBSystemNameComparator //: public SystemNameComparator
{
 public:
  static bool compare( const NamedBean *o1, const NamedBean *o2)
  {
   return SystemNameComparator::compare(o1->getSystemName(), o2->getSystemName());
  }
};


#endif // NAMEDBEANCOMBOBOX_H
