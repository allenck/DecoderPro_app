#ifndef MANAGERCOMBOBOX_H
#define MANAGERCOMBOBOX_H
#include "jcombobox.h"
#include "manager.h"

class ManagerComboBox : public JComboBox
{
  Q_OBJECT
 public:
  ManagerComboBox(QObject* parent = nullptr);
  /*public*/ ManagerComboBox(/*@Nonnull*/ QList<Manager/*<B>*/*> list, QObject* parent = nullptr);
  /*public*/ ManagerComboBox(/*@Nonnull*/ QList<Manager/*<B>*/*> list, Manager/*<B>*/* selection, QObject* parent);
  /*public*/ void setManagers(/*@Nonnull*/ QList<Manager/*<B>*/*> list);
  /*public*/ void setManagers(/*@Nonnull*/ QList<Manager/*<B>*/*> list, Manager/*<B>*/* selection);
  /*public*/ void setManagers(/*@Nonnull*/ Manager/*<B>*/* manager);
  /*public*/ Manager/*<B>*/* getSelectedItem();
  /*public*/ void setName(QString);
  /*public*/ QVariant getItemAt(int i) {return vl.at(i);}
private:
  QVariantList vl = QVariantList();

};

#endif // MANAGERCOMBOBOX_H
