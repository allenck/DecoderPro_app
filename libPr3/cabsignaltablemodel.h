#ifndef CABSIGNALTABLEMODEL_H
#define CABSIGNALTABLEMODEL_H
#include "abstracttablemodel.h"

class PropertyChangeEvent;
class CabSignalManager;
class Logger;
class CabSignalTableModel : public AbstractTableModel
{
public:
 // column order needs to match list in columnToolTips

 enum COLS
 {
  LOCO_ID_COLUMN = 0,
  SEND_CABSIG_COLUMN = 1,
  CURRENT_BLOCK = 2,
  BLOCK_DIR = 3,
  REVERSE_BLOCK_DIR_BUTTON_COLUMN = 4,
  NEXT_BLOCK = 5,
  NEXT_SIGNAL = 6,
  NEXT_ASPECT = 7,
  NEXT_ASPECT_ICON = 8,

  MAX_COLUMN = 9
 };

 CabSignalTableModel(int row, int column, QObject *parent);
 /*public*/ int getRowCount();
 /*public*/ int getColumnCount();
 /*public*/ QString getColumnName(int col);
 /*public*/ static int getPreferredWidth(int col);
 /*public*/ QString getColumnClass(int col);
 /*public*/ bool isCellEditable(int row, int col);
 /*public*/ void configureTable(JTable* cmdStatTable);
 /*public*/ QVariant getValueAt(int row, int col);
 /*public*/ void setValueAt(QVariant value, int row, int col);
 /*public*/ void dispose();

public slots:
 void propertyChange(PropertyChangeEvent*);

private:
 static Logger* log;
/*private*/ CabSignalManager* cabSignalManager;
 /*private*/ void chngblockdir(int row);

protected:
 static /*protected*/ /*final*/ QVector<int> startupColumns;// = {0,1,2,3,4,5,6,7,8};
 static /*protected*/ /*final*/QStringList columnToolTips;// = {
//     null, // loco id
//     Bundle.getMessage("CabsigCheckboxTip"),
//     Bundle.getMessage("BlockUserName"),
//     Bundle.getMessage("BlockDirectionTip"),
//     null, // block lookup button
//     Bundle.getMessage("NextBlockTip"),
//     Bundle.getMessage("NextSignalTip"),
//     Bundle.getMessage("NextAspectTip"),
//     Bundle.getMessage("NextAspectTip"), // aspect icon
// }; // Length = number of items in array should (at least) match number of columns

/*protected*/ void setPanelPauseButton(bool isPaused);

};

#endif // CABSIGNALTABLEMODEL_H