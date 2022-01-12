#include "rollingstockgroupmanager.h"

namespace Operations {

 /**
  *
  *
  * @author Daniel Boudreau Copyright (C) 2021
  */
 // /*public*/  abstract class RollingStockGroupManager extends SwingPropertyChangeSupport {

 /*public*/  /*static*/ /*final*/ QString RollingStockGroupManager::NONE = "";


 /*public*/  /*static*/ /*final*/ QString RollingStockGroupManager::LISTLENGTH_CHANGED_PROPERTY = "GroupListLengthChanged"; // NOI18N

 /*public*/  RollingStockGroupManager::RollingStockGroupManager(QObject *parent )
  : SwingPropertyChangeSupport(this, parent) {
 }

 /**
  * Get a comboBox loaded with current group names
  *
  * @return comboBox with group names.
  */
 /*public*/  JComboBox/*<String>*/* RollingStockGroupManager::getComboBox() {
     JComboBox/*<String>*/* box = new JComboBox();
     box->addItem(NONE);
     for (QString name : getNameList()) {
         box->addItem(name);
     }
     return box;
 }

 /**
  * Update an existing comboBox with the current kernel names
  *
  * @param box comboBox requesting update
  */
 /*public*/  void RollingStockGroupManager::updateComboBox(JComboBox/*<String>*/* box) {
     box->clear();
     box->addItem(NONE);
     for (QString name : getNameList()) {
         box->addItem(name);
     }
 }

 /**
  * Get a list of group names
  *
  * @return ordered list of group names
  */
 /*public*/  QList<QString> RollingStockGroupManager::getNameList() {
     QList<QString> out = QList<QString>();
     //Enumeration<String> en = _groupHashTable.keys();
     QStringListIterator en (_groupHashTable.keys());
     while (en.hasNext()) {
         out.append(en.next());
     }
//     Collections.sort(out);
     return out;
 }

 /*public*/  int RollingStockGroupManager::getMaxNameLength() {
     int maxLength = 0;
     for (QString name : getNameList()) {
         if (name.length() > maxLength) {
             maxLength = name.length();
         }
     }
     return maxLength;
 }

} // namespace Operations
