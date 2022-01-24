#ifndef AUTOMATTABLEDATAMODEL_H
#define AUTOMATTABLEDATAMODEL_H
#include "abstracttablemodel.h"
#include "liblayouteditor_global.h"

class PropertyChangeEvent;
class JTable;
class QPushButton;
class Logger;
class AutomatSummary;
class LIBLAYOUTEDITORSHARED_EXPORT AutomatTableDataModel : public AbstractTableModel
{
 Q_OBJECT
public:
 explicit AutomatTableDataModel(QObject *parent = 0);
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ QString getColumnClass(int col);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ int getPreferredWidth(int col);
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ void configureTable(JTable* table);
 /*public*/ void dispose();

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
 enum COLUMNS
 {
  NAMECOL = 0,		// display name
  TURNSCOL = 1,		// number of times through the loop
  KILLCOL = 2 		//
 };
 static /*final*/ int NUMCOLUMN;// = 3;

 AutomatSummary* summary;// = AutomatSummary.instance();
 Logger* log;
 void setColumnToHoldButton(JTable* table, int column, QPushButton* sample) ;
};
#endif // AUTOMATTABLEDATAMODEL_H
