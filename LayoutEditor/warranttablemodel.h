#ifndef WARRANTTABLEMODEL_H
#define WARRANTTABLEMODEL_H
#include "beantabledatamodel.h"
#include "liblayouteditor_global.h"

class Warrant;
class WarrantTableFrame;
class WarrantManager;
class LIBLAYOUTEDITORSHARED_EXPORT WarrantTableModel : public BeanTableDataModel
{
 Q_OBJECT
public:
 //explicit WarrantTableModel(QObject *parent = 0);
 /*public*/ WarrantTableModel(WarrantTableFrame* frame, QObject *parent = 0);
 /*public*/ void addHeaderListener(JTable* table);
 /*public*/ Manager* getManager();
 /*public*/ NamedBean* getBySystemName(QString name) const;
 /*public*/ QString getValue(QString name) ;
 /*public*/ NamedBean* getByUserName(QString name);
 /*public*/ void clickOn(NamedBean* t);
 /*public*/ /*synchronized*/ void init();
 /*public*/ void addNXWarrant(Warrant* w);
 /*public*/ void removeNXWarrant(Warrant* w);
 /*public*/ Warrant* getWarrantAt(int index) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ QString getColumnClass(int col);
 /*public*/ int getPreferredWidth(int col);

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 void on_buttonClicked(QModelIndex* index, QString name);

private:
 enum COLUMNS
 {
  WARRANT_COLUMN = 0,
  ROUTE_COLUMN = 1,
  TRAIN_NAME_COLUMN = 2,
  ADDRESS_COLUMN = 3,
  ALLOCATE_COLUMN = 4,
  DEALLOC_COLUMN = 5,
  SET_COLUMN = 6,
  AUTO_RUN_COLUMN = 7,
  MANUAL_RUN_COLUMN = 8,
  CONTROL_COLUMN = 9,
  EDIT_COLUMN = 10,
  DELETE_COLUMN = 11,
  NUMCOLS = 12
 };
  WarrantManager* _manager;
  WarrantTableFrame* _frame;
  /*private*/ QList<Warrant*> _warList;
  /*private*/ QList<Warrant*> _warNX; // temporary warrants appended to table
  static QColor myGreen;// = new QColor(0, 100, 0);
  static QColor myGold;// = new QColor(200, 100, 0);
  /*private*/ int getRow(Warrant* w);
  /*private*/ void openWarrantFrame(Warrant* warrant);
  Logger* log;

protected:
  /*protected*/ QString getBeanType();
  /*protected*/ QString getMasterClassName();
  /*protected*/ void haltAllTrains();
  /*protected*/ Warrant* getWarrant(QString name);
 friend class WarrantTableFrame;
 friend class CheckForTermination;
 friend class Engineer;
};

#endif // WARRANTTABLEMODEL_H
