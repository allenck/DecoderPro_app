#ifndef OPERATIONS_ROLLINGSTOCKGROUPMANAGER_H
#define OPERATIONS_ROLLINGSTOCKGROUPMANAGER_H

#include "swingpropertychangesupport.h"
#include "rollingstockgroup.h"
#include "jcombobox.h"

namespace Operations {

 class RollingStockGroupManager : public SwingPropertyChangeSupport
 {
  public:
   explicit RollingStockGroupManager(QObject *parent = nullptr);
   /*public*/  static /*final*/ QString NONE;// = "";
   /*public*/  static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "GroupListLengthChanged"; // NOI18N
   /*public*/  JComboBox/*<String>*/* getComboBox();
   /*public*/  void updateComboBox(JComboBox/*<String>*/* box);
   /*public*/  QList<QString> getNameList();
   /*public*/  int getMaxNameLength();


  protected:
   /*protected*/ QMap<QString, RollingStockGroup*> _groupHashTable = QMap<QString, RollingStockGroup*>();

 };

} // namespace Operations

#endif // OPERATIONS_ROLLINGSTOCKGROUPMANAGER_H
