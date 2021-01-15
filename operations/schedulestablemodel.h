#ifndef SCHEDULESTABLEMODEL_H
#define SCHEDULESTABLEMODEL_H

#include "abstracttablemodel.h"
#include "tabledelegates.h"

class Logger;
class JComboBox;
class PropertyChangeEvent;
namespace Operations
{
 class LocationTrackPair;
 class Schedule;
 class ScheduleEditFrame;
 class SchedulesTableFrame;
 class ScheduleManager;
 class SchedulesTableModel : public AbstractTableModel
 {
  Q_OBJECT
 public:
  SchedulesTableModel(QObject* parent = 0);
  /*public*/ /*final*/ int SORTBYNAME;// = 1;
  /*public*/ /*final*/ int SORTBYID;// = 2;
  /*public*/ void setSort(int sort);
  /*public*/ int rowCount(const QModelIndex &parent) const;
  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ QString getColumnClass(int col);
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ void dispose();
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
  /*public*/ int getRowCount() {return rowCount(QModelIndex());}
  /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent *e);
 private:
  enum COLUMNS
  {
   // Defines the columns
    ID_COLUMN = 0,
    NAME_COLUMN = ID_COLUMN + 1,
    SCHEDULE_STATUS_COLUMN = NAME_COLUMN + 1,
    SPUR_NUMBER_COLUMN = SCHEDULE_STATUS_COLUMN + 1,
    SPUR_COLUMN = SPUR_NUMBER_COLUMN + 1,
    STATUS_COLUMN = SPUR_COLUMN + 1,
    MODE_COLUMN = STATUS_COLUMN + 1,
    EDIT_COLUMN = MODE_COLUMN + 1,
    DELETE_COLUMN = EDIT_COLUMN + 1,

    HIGHEST_COLUMN = DELETE_COLUMN + 1
  };
  ScheduleManager* scheduleManager; // There is only one manager
  /*private*/ int _sort;// = SORTBYNAME;
  /*synchronized*/ void updateList();
  QList<Schedule*> sysList;// = null;
  JTable* table;
  void initTable(SchedulesTableFrame* frame, JTable* table);
  /*private*/ void setPreferredWidths(SchedulesTableFrame* frame, JTable* table);
  ScheduleEditFrame* sef;// = null;
  /*private*/ void removePropertyChangeSchedules();
  /*private*/ void addPropertyChangeTracks() ;
  /*private*/ void removePropertyChangeTracks();
  ///*private*/ JComboBox* getComboBox(int row, Schedule* schedule) const;
  Logger* log;
  /*private*/ QString getScheduleStatus(int row) const;
  /*private*/ QString getSpurStatus(int row) const;
  /*private*/ QString getSpurMode(int row) const;
  /*private*/ LocationTrackPair* getLocationTrackPair(int row) const;
  /*private*/ void editSchedule(int row);
  /*private*/ void deleteSchedule(int row);
  /*private*/ void selectJComboBox(JComboBox* box, int row);

 protected:
  /*protected*/ QHash<Schedule*, QString> comboSelect;// = new Hashtable<Schedule, String>();
 friend class SchedulesTableFrame;
 friend class STMSComboBoxDelegate;
 };

 typedef JComboBox* (*GETCOMBO1)(Schedule*, SchedulesTableModel* );

 class STMSComboBoxDelegate : public JComboBoxEditor
 {
 Q_OBJECT
 public:
   STMSComboBoxDelegate(SchedulesTableModel* model,  GETCOMBO1, QObject *parent = 0);
   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//   void setEditorData(QWidget *editor, const QModelIndex &index) const;
//   void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//   void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

 private:
   SchedulesTableModel* model;
   QStringList items;
   JComboBox* (*box)(Schedule*, SchedulesTableModel*);

 };
}
#endif // SCHEDULESTABLEMODEL_H
