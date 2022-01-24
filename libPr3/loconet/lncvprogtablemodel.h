#ifndef LNCVPROGTABLEMODEL_H
#define LNCVPROGTABLEMODEL_H
#include "abstracttablemodel.h"
#include "programmingtool.h"
#include "lncvdevicesmanager.h"

class LncvProgPane;
class LncvProgTableModel : public AbstractTableModel, public ProgrammingTool
{
  Q_OBJECT
  Q_INTERFACES(ProgrammingTool)
 public:
  enum COLS
  {
   COUNT_COLUMN = 0,
   ARTICLE_COLUMN = 1,
   MODADDR_COLUMN = 2,
   CV_COLUMN = 3,
   VALUE_COLUMN = 4,
   DEVICENAMECOLUMN = 5,
   ROSTERENTRYCOLUMN = 6,
   OPENPRGMRBUTTONCOLUMN = 7,
   NUMCOLUMNS = 8
  };
  LncvProgTableModel(LncvProgPane* pane, /*@Nonnull*/ LocoNetSystemConnectionMemo* memo, QObject* parent = nullptr);
  /*public*/ void initTable(JTable* lncvModulesTable);
  /*public*/ QString getColumnName(int c) const override;
  /*public*/ QString getColumnClass(int c) const override;
  /*public*/ bool isCellEditable(int r, int c) const override;
  /*public*/ int getColumnCount() const override;
  /*public*/ int getRowCount() const override;
  /*public*/ QVariant getValueAt(int r, int c) const override;
  /*public*/ void setValueAt(QVariant value, int r, int c) override;
  /*public*/ void openPaneOpsProgFrame(RosterEntry* re, QString name,
                                       QString programmerFile, Programmer* p);
  /*public*/ void dispose();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* evt);

 private:
  /*private*/ /*final*/ QWidget* pane;
  /*private*/ /*final*/ /*transient*/ LocoNetSystemConnectionMemo* memo;
  static Logger* log;
  /*private*/ void openProgrammer(int r);
  /*private*/ void createRosterEntry(LncvDevice* dev);

 protected:
  /*protected*/ Roster* _roster;
  /*protected*/ LncvDevicesManager* lncvdm;

};

#endif // LNCVPROGTABLEMODEL_H
