#ifndef IDTAGTABLEDATAMODEL_H
#define IDTAGTABLEDATAMODEL_H

#include <beantabledatamodel.h>
#include "idtagmanager.h"
#include "idtag.h"

class IdTagTableDataModel : public BeanTableDataModel
{
  Q_OBJECT
 public:
  enum COLUMNS
  {
   WHERECOL = NUMCOLUMN,
   WHENCOL = WHERECOL + 1,
   CLEARCOL = WHENCOL + 1
  };
  explicit IdTagTableDataModel(Manager/*<IdTag>*/* mgr, QObject *parent = nullptr);
  /*public*/ QString getValue(QString name) override;
  /*public*/ /*Manager<IdTag>*/AbstractManager* getManager()override;
  /*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString name) const override;
  /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString name) override;
  /*public*/ void clickOn(NamedBean* t)override;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  /*public*/ int columnCount(const QModelIndex &parent) const override;
  /*public*/ QString getColumnName(int col) const override;
  /*public*/ QString getColumnClass(int col)const override;
  /*public*/ bool isCellEditable(int row, int col) const override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ int getPreferredWidth(int col) override;
  /*public*/ void configValueColumn(JTable* table) override;
  /*public*/ QPushButton* configureButton() override;

 private:
  static Logger* log;
  /*private*/ IdTagManager* tagManager;

 protected:
  /*protected*/ /*final*/ void setManager(/*Manager<IdTag>*/AbstractManager* mgr) override;
  /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;
  /*protected*/ QString getMasterClassName() override;

};

#endif // IDTAGTABLEDATAMODEL_H
