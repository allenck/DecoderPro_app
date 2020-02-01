#ifndef CONSISTDATAMODEL_H
#define CONSISTDATAMODEL_H
#include "abstracttablemodel.h"

class AbstractConsistManager;
class DccLocoAddress;
class Logger;
class Consist;
class ConsistManager;
class ConsistDataModel : public AbstractTableModel
{
 Q_OBJECT
public:
 ConsistDataModel(QObject *parent = nullptr);
 void initTable(JTable* consistTable);
 /*public*/ void setConsist(Consist* consist);
 /*public*/ void setConsist(DccLocoAddress* address);
 /*public*/ Consist* getConsist();
 /*public*/ int getRowCount() const;
 /*public*/ int getColumnCount() const;
 /*public*/ QString getColumnName(int col) const override;
 /*public*/ QString getColumnClass(int col) const;
 /*public*/ bool isCellEditable(int row, int col);
 /*public*/ QVariant getValueAt(int row, int col) const;
 /*public*/ void setValueAt(QVariant value, int row, int col);

private:
 static Logger* log;
 enum COLS
 {
  ADDRCOLUMN = 0,    // Locomotive address
  ROSTERCOLUMN = 1,  // Roster Entry, this exists
  DIRECTIONCOLUMN = 2,  // Relative Direction
  DELCOLUMN = 3,     // Remove Button
  NUMCOLUMN = 4
 };
 //Q_ENUM(COLS)
 // a place holder for a consist and Consist Manager objects.
 /*private*/ Consist* _consist = nullptr;
 /*private*/ AbstractConsistManager* consistMan = nullptr;

};

#endif // CONSISTDATAMODEL_H
