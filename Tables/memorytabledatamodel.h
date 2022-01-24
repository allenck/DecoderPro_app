#ifndef MEMORYTABLEDATAMODEL_H
#define MEMORYTABLEDATAMODEL_H

#include <beantabledatamodel.h>
#include "memory.h"

class MemoryTableDataModel : public BeanTableDataModel
{
  Q_OBJECT
 public:
  explicit MemoryTableDataModel(Manager/*<Memory>*/* mgr, QObject *parent = nullptr);
  /*public*/ QString getValue(QString name)override;
  /*public*/ /*Manager<Memory>*/AbstractManager* getManager() override;
  /*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString name) const override ;
  /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString name) override;
  /*public*/ void clickOn(NamedBean* t) override;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  /*public*/ QString getColumnName(int col)const override;
  /*public*/ QString getColumnClass(int col) const override;
  /*public*/ void configValueColumn(JTable* table) override;
  /*public*/ QPushButton* configureButton() override;

 private:
  static Logger* log;

 protected:
  /*protected*/ QString getMasterClassName() override;
  /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;

};

#endif // MEMORYTABLEDATAMODEL_H
