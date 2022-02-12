#ifndef REPORTERTABLEDATAMODEL_H
#define REPORTERTABLEDATAMODEL_H

#include <beantabledatamodel.h>
#include "reportermanager.h"
#include "reporter.h"
#include "abstractreporter.h"
#include "libtables_global.h"

class LIBTABLESSHARED_EXPORT ReporterTableDataModel : public BeanTableDataModel
{
  Q_OBJECT
 public:
  explicit ReporterTableDataModel();
  ~ReporterTableDataModel() override {}
  ReporterTableDataModel(const ReporterTableDataModel&) : BeanTableDataModel() {}
  /*public*/ ReporterTableDataModel(Manager *mgr, QObject* parent = nullptr);
  /*public*/ QString getValue(QString name) override;
  /*public*/ /*final*/ void setManager(/*Manager<Reporter>*/Manager* rm) override;
  /*public*/ Manager *getManager() override;
  /*public*/ NamedBean *getBySystemName(/*@Nonnull*/ QString name) const override;
  /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString name)override;
  /*public*/ void clickOn(NamedBean* t) override;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  /*public*/ int columnCount(const QModelIndex& index) const override;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  /*public*/ QString getColumnClass(int col) const override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ int getPreferredWidth(int col) override;
  /*public*/ void configValueColumn(JTable* table) override;
  /*public*/ QPushButton* configureButton() override;

 private:
  static Logger* log;
  /*public*/ static /*final*/ const int LASTREPORTCOL; //= NUMCOLUMN;
  /*private*/ ReporterManager* reporterManager;

 protected:
  /*protected*/ QString getMasterClassName()override;
  /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;

};
Q_DECLARE_METATYPE(ReporterTableDataModel)

#endif // REPORTERTABLEDATAMODEL_H
