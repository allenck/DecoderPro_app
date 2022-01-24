#ifndef LOCOIOTABLEMODEL_H
#define LOCOIOTABLEMODEL_H

#include "abstracttablemodel.h"
#include <QVector>
#include <QItemDelegate>
#include "propertychangelistener.h"

class QSignalMapper;
class JTable;
class QPushButton;
class PropertyChangeEvent;
class JTextField;
class LocoIOData;
class Logger;
class LocoIOTableModel : public AbstractTableModel, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
    //explicit LocoIOTableModel(QObject *parent = 0);
 /**
 * Define the contents of the individual columns
 */
 enum columnsAboutToBeInserted
 {
  PINCOLUMN = 0,  // pin number
  MODECOLUMN = 1,  // what makes this happen?
  ADDRCOLUMN = 2,  // what address is involved?
  SV0COLUMN = 3,  //  SV config code
  SV1COLUMN = 4,  //  SV Value1
  SV2COLUMN = 5,  //  SV Value2
  CAPTURECOLUMN = 6,  // "capture" button
  READCOLUMN = 7,  // "read" button
  WRITECOLUMN = 8  // "write" button
 };
 static int   HIGHESTCOLUMN;// = WRITECOLUMN + 1
 /*public*/ LocoIOTableModel(LocoIOData* ldata, QObject *parent = 0);
 // basic methods for AbstractTableModel implementation
 /*public*/ int rowCount(const QModelIndex &parent) const override;
 /*public*/ int columnCount(const QModelIndex &parent) const override;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
 /*public*/ QVariant data(const QModelIndex &index, int role) const override;
 /*public*/ int getPreferredWidth(int col);
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ void dispose();
 /*public*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/);
 QObject* self() override {return (QObject*)this;}

signals:
 void buttonClicked(QModelIndex*);

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt) override;

private:
 /*private*/ static Logger* log;// = LoggerFactory::getLogger("LocoIOTableModel");
 /*private*/ LocoIOData* liodata;
 /*private*/ bool inHex;
 /**
 * Define the number of rows in the table, which is also the number of
 * "channels" in a single LocoIO unit
 */
 /*private*/ int _numRows;// = 16;
 /*private*/ QVector<QString> msg;// = new String[_numRows];

 /**
 * Reference to the JTextField which should receive status info
 */
 /*private*/ JTextField* status;// = NULL;

 /**
 * Reference to JLabel for firmware version
 */
 ///*private*/ JLabel     firmware = NULL;
 ///*private*/ JLabel     locobuffer = NULL;
  QMap<int, QSignalMapper*>* buttonMap;

protected:
protected slots:
    void OnButtonClicked(QObject* o);

};
class LMPBDelegate : public QItemDelegate
{
Q_OBJECT
    QSignalMapper* mapper;
public:
  LMPBDelegate(QSignalMapper* mapper, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//  void setEditorData(QWidget *editor, const QModelIndex &index) const;
//  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // LOCOIOTABLEMODEL_H
