#ifndef MANAGERCOMBOBOX_H
#define MANAGERCOMBOBOX_H
#include "jcombobox.h"
#include "abstractmanager.h"

class ManagerComboBox : public JComboBox
{
  Q_OBJECT
 public:
  ManagerComboBox(QObject* parent = nullptr);
  /*public*/ ManagerComboBox(/*@Nonnull*/ QList<AbstractManager *> list, QObject* parent = nullptr);
  /*public*/ ManagerComboBox(/*@Nonnull*/ QList<AbstractManager *> list, Manager/*<B>*/* selection, QObject* parent);
  /*public*/ void setManagers(/*@Nonnull*/ QList<AbstractManager *> list);
  /*public*/ void setManagers(/*@Nonnull*/ QList<AbstractManager *> list, Manager/*<B>*/* selection);
  /*public*/ void setManagers(/*@Nonnull*/ QList<Manager *> list, Manager/*<B>*/* selection);
  /*public*/ void setManagers(/*@Nonnull*/ Manager/*<B>*/* manager);
  /*public*/ Manager/*<B>*/* getSelectedItem();
  /*public*/ void setName(QString);
  /*public*/ QVariant getItemAt(int i) {return vl.at(i);}
private:
  QVariantList vl = QVariantList();

};

#endif // MANAGERCOMBOBOX_H
