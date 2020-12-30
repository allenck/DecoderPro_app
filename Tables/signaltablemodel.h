#ifndef SIGNALTABLEMODEL_H
#define SIGNALTABLEMODEL_H
#include "abstracttablemodel.h"
#include <QStringList>
#include "libtables_global.h"
#include "comparatort.h"
#include "tableframes.h"
#include "namedbean.h"

class QPushButton;
class JTable;
class SignalRow;
class Logger;
class OBlock;
class Portal;
class NamedBean;
class DecimalFormat;
//class TableFrames;
class PortalManager;
class PropertyChangeEvent;

class LIBTABLESSHARED_EXPORT SignalTableModel : public AbstractTableModel
{
 Q_OBJECT
public:
  /*static*/ class SignalRow
  {

   NamedBean* _signal;
   OBlock* _fromBlock;
   Portal* _portal;
   OBlock* _toBlock;
   float _length;  // adjustment to speed change point
   bool _isMetric;
  public:
   SignalRow(NamedBean* signal, OBlock* fromBlock, Portal* portal, OBlock* toBlock, float length, bool isMetric);
   void setSignal(NamedBean* signal);
   NamedBean* getSignal();
   void setFromBlock(OBlock* fromBlock);
   OBlock* getFromBlock();
   void setPortal(Portal* portal);
   Portal* getPortal();
   void setToBlock(OBlock* toBlock);
   OBlock* getToBlock();
   void setLength(float length);
   float getLength();
   void setMetric(bool isMetric);
   bool isMetric();

   friend class SignalEditFrame;
   friend class NameSorter;

  };

  /*static*/ class SignalArray : public QList<SignalRow*> {

   public:
    SignalArray() {}
    SignalArray(QList<SignalRow*> temp)
    {
     foreach (SignalRow* sr, temp) {
      append(sr);
     }
    }
    /*public*/ int numberOfSignals() {
        return size();
    }
  };
 //explicit SignalTableModel(QObject *parent = 0);
 enum COLUMNS
 {
   NAME_COLUMN = 0,
   FROM_BLOCK_COLUMN = 1,
   PORTAL_COLUMN = 2,
   TO_BLOCK_COLUMN = 3,
   LENGTHCOL = 4,
   UNITSCOL = 5,
   DELETE_COL = 6,
   EDIT_COL = 7, // only used on _tabbed UI
   NUMCOLS = 7
 };
 /*public*/ SignalTableModel(TableFrames* parent);
 /*public*/ void init();
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 static /*public*/ int getPreferredWidth(int col);
 /*public*/ QString getColumnClass(int col);
 /*public*/ bool editMode();
 /*public*/ void setEditMode(bool editing);

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
 PortalManager* _portalMgr;
 /*private*/ float _tempLen;// = 0.0f;      // mm for length col of tempRow

 ///*private*/ QList<SignalRow*>* _signalList;// = new ArrayList<SignalRow>();

 /*private*/ QStringList tempRow;// = new String[NUMCOLS];
 bool inEditMode = false;
 DecimalFormat* twoDigit;// = new java.text.DecimalFormat("0.00");

 TableFrames* _parent;
 /*private*/ SignalArray _signalList;
 /*private*/ /*final*/ bool _tabbed; // updated from prefs (restart required)void initTempRow();
 /*private*/ void makeList();
 Logger* log;
 static /*private*/ void addToList(QList<SignalRow*> tempList, SignalRow* sr);
 /*private*/ QString checkSignalRow(SignalRow* sr);
 /*private*/ Portal* getPortalwithBlocks(OBlock* fromBlock, OBlock* toBlock);
 /*private*/ QString checkDuplicateSignal(NamedBean* signal);
 /*private*/ QString checkDuplicateSignal(SignalRow* row);
 /*private*/ QString checkDuplicateProtection(SignalRow* row);
 /*private*/ void deleteSignal(SignalRow* signalRow);
 /*private*/ void editSignal(NamedBean* signal, SignalRow* sr);
 static /*private*/ QString setSignal(SignalRow* signalRow, bool deletePortal);
 static /*private*/ bool checkPortalBlock(Portal* portal, OBlock* block);
 QList<int> buttonMap;
 void setPersistentButtons();
 JTable* table;
 void fireTableRowsUpdated(int, int);
 void fireTableDataChanged();
 void initTempRow();
 int _lastIdx; // for debug

protected:
 /*protected*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/ = NULL);
 friend class TableFrames;
 friend class SignalEditFrame;
 friend class NameSorter;
};
class NameSorter : public ComparatorT<SignalRow*>
{
 public:
  //NameSorter() {}
  //@Override
  /*public*/ static int compare(SignalTableModel::SignalRow* o1, SignalTableModel::SignalRow* o2) {
      return o2->getSignal()->compareTo(o1->getSignal());
  }
};

#endif // SIGNALTABLEMODEL_H
