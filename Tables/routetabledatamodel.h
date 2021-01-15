#ifndef ROUTETABLEDATAMODEL_H
#define ROUTETABLEDATAMODEL_H
#include "beantabledatamodel.h"
#include "runnable.h"
#include "routeeditframe.h"

class RouteManager;
class Route;
class RouteTableDataModel : public BeanTableDataModel
{
  Q_OBJECT
 public:
  RouteTableDataModel(QObject* parent = nullptr);
  /*public*/ int columnCount(const QModelIndex &parent) const override;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ QString getColumnClass(int col) const override;
  /*public*/ int getPreferredWidth(int col) override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  /*public*/ void configureTable(JTable* table) override;
  /*public*/ Manager* getManager() override;
  /*public*/ NamedBean* getBySystemName(QString name) const override;
  /*public*/ NamedBean* getByUserName(QString name) override;
  /*public*/ void clickOn(NamedBean* t) override;
  /*public*/ QString getValue(QString s) const override;

 private:
  enum COLS
  {
  ENABLECOL = NUMCOLUMN,
  LOCKCOL = ENABLECOL + 1,
  SETCOL = ENABLECOL + 2
  };
  static Logger* log;
//  QVariant getValueAt(int row, int col) const;

 protected:
  /*protected*/ QString getMasterClassName() override;
  /*protected*/ void doDelete(NamedBean* bean) override;
  /*protected*/ QString getBeanType() override;

  protected slots:
  /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;
};

class WindowMaker : public Runnable
{
  Q_OBJECT
  int row;
  RouteTableDataModel* model;
 public:
  WindowMaker(int row, RouteTableDataModel* model) {
   this->row = row;
  this->model = model;
  }
  /*public*/ void run() {
    JmriJFrame* editFrame = new RouteEditFrame(model->data(model->index(row, RouteTableDataModel::SYSNAMECOL),Qt::DisplayRole).toString());
    editFrame->setVisible(true);
  }

};
#endif // ROUTETABLEDATAMODEL_H
