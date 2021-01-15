#ifndef ROUTEEDITTABLEMODEL_H
#define ROUTEEDITTABLEMODEL_H

#include "abstracttablemodel.h"
#include <QStyledItemDelegate>

class HtmlTextEdit;
class JDialog;
class Logger;
class PropertyChangeEvent;
namespace Operations
{
 class RouteLocation;
 class Route;
 class RouteEditFrame;
 class RouteEditTableModel : public AbstractTableModel
 {
  Q_OBJECT
 public:
  RouteEditTableModel(QObject* parent = 0);
  // Defines the columns
  enum COLUMNS
  {
   ID_COLUMN = 0,
   NAME_COLUMN = ID_COLUMN + 1,
   TRAIN_DIRECTION_COLUMN = NAME_COLUMN + 1,
   MAXMOVES_COLUMN = TRAIN_DIRECTION_COLUMN + 1,
   RANDOM_CONTROL_COLUMN = MAXMOVES_COLUMN + 1,
   PICKUP_COLUMN = RANDOM_CONTROL_COLUMN + 1,
   DROP_COLUMN = PICKUP_COLUMN + 1,
   WAIT_COLUMN = DROP_COLUMN + 1,
   MAXLENGTH_COLUMN = WAIT_COLUMN + 1,
   GRADE = MAXLENGTH_COLUMN + 1,
   TRAINICONX = GRADE + 1,
   TRAINICONY = TRAINICONX + 1,
   COMMENT_COLUMN = TRAINICONY + 1,
   UP_COLUMN = COMMENT_COLUMN + 1,
   DOWN_COLUMN = UP_COLUMN + 1,
   DELETE_COLUMN = DOWN_COLUMN + 1,

   HIGHEST_COLUMN = DELETE_COLUMN + 1
  };
  /*public*/ void setWait(bool showWait);
  /*public*/ void dispose();
  /*public*/ int rowCount(const QModelIndex &parent) const;
  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ QString getColumnClass(int col);
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ int getLastTrainDirection();
  /*public*/ int getLastMaxTrainMoves();
  /*public*/ int getLastMaxTrainLength();
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
  /*public*/ int getRowCount() {return rowCount(QModelIndex());}
  /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  void on_okayButton_clicked();
  void on_cancelButton_clicked();

 private:
  /*private*/ bool _showWait;// = true;
  /*private*/ JTable* _table;
  /*private*/ Route* _route;
  /*private*/ RouteEditFrame* _frame;
  /*synchronized*/ void updateList();
  QList<RouteLocation*>* routeList;// = new ArrayList<RouteLocation>();
  /*private*/ void removePropertyChangeRouteLocations();
  Logger* log;
  void initTable(RouteEditFrame* frame, JTable* table, Route* route);
  void initTable(JTable* table);
  /*private*/ void setPreferredWidths(JTable* table);
  /*private*/ int _trainDirection;// = Setup.getDirectionInt(Setup.getTrainDirectionList().get(0));
  /*private*/ int _maxTrainLength;// = Setup.getMaxTrainLength();
  /*private*/ int _maxTrainMoves;// = Setup.getCarMoves();
  /*private*/ void moveUpRouteLocation(int row);
  /*private*/ void moveDownRouteLocation(int row);
  /*private*/ void deleteRouteLocation(int row);
  /*private*/ void setTrainDirection(QVariant value, int row);
  /*private*/ void setMaxTrainMoves(QVariant value, int row);
  /*private*/ void setRandomControlValue(QVariant value, int row);
  /*private*/ void setDrop(QVariant value, int row);
  /*private*/ void setPickup(QVariant value, int row);
  /*private*/ void setWait(QVariant value, int row);
  /*private*/ void setDepartureTime(QVariant value, int row);
  /*private*/ void setMaxTrainLength(QVariant value, int row) ;
  /*private*/ void setGrade(QVariant value, int row);
  /*private*/ void setTrainIconX(QVariant value, int row) ;
  /*private*/ void setTrainIconY(QVariant value, int row);
  /*private*/ void setComment(int row);
   RouteLocation* rl;
   JDialog* dialog;
   HtmlTextEdit* commentTextArea;

 friend class RouteEditFrame;
 };

#if 0
 class RETComboBoxDelegate : public QStyledItemDelegate
 {
 Q_OBJECT
 public:
   RETComboBoxDelegate(RouteEditTableModel* model, QStringList items, QObject *parent = 0);

   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   void setEditorData(QWidget *editor, const QModelIndex &index) const;
   void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
   void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

 private:
   RouteEditTableModel* model;
   QStringList items;

 };
#endif
}
#endif // ROUTEEDITTABLEMODEL_H
