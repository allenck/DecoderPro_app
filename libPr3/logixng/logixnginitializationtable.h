#ifndef LOGIXNGINITIALIZATIONTABLE_H
#define LOGIXNGINITIALIZATIONTABLE_H

#include <jmrijframe.h>
#include "defaultlogixnginitializationmanager.h"
#include "instancemanager.h"
#include "abstracttablemodel.h"

class InitializationTableModel;
class LogixNGInitializationTable : public JmriJFrame
{
  Q_OBJECT
 public:
  LogixNGInitializationTable(QWidget* parent = nullptr) : JmriJFrame(parent) {setObjectName("LogixNGInitializationTable");}
  /*public*/  void initComponents()override;
  /*public*/  void initMinimumSize(QSize dimension);

 private:
  /*private*/ static /*final*/ int panelWidth700;// = 700;
  /*private*/ static /*final*/ int panelHeight500;// = 500;
  /*private*/ /*final*/ LogixNG_InitializationManager* _initManager = (DefaultLogixNGInitializationManager*)
          InstanceManager::getDefault("LogixNG_InitializationManager");

  /*private*/ InitializationTableModel* _initTableModel = nullptr;

  friend class InitializationTableModel;
};

/*private*/ /*final*/ class InitializationTableModel : public AbstractTableModel {
Q_OBJECT
  /*private*/ /*final*/ QList<LogixNG*> _logixNGs;
  LogixNGInitializationTable* frame;
 public:
  enum COLUMNS
  {
    SYSTEM_NAME_COLUMN = 0,
    USER_NAME_COLUMN = SYSTEM_NAME_COLUMN + 1,
    BUTTON_DELETE_COLUMN = USER_NAME_COLUMN + 1,
    BUTTON_MOVE_UP_COLUMN = BUTTON_DELETE_COLUMN + 1,
    BUTTON_MOVE_DOWN_COLUMN = BUTTON_MOVE_UP_COLUMN + 1,
    NUM_COLUMNS = BUTTON_MOVE_DOWN_COLUMN + 1
  };


    /*public*/  InitializationTableModel(LogixNGInitializationTable* frame, QObject* parent = nullptr);
    /*public*/  /*Class<?>*/QString getColumnClass(int c) const override ;
    /*public*/  int columnCount(const QModelIndex&) const override;
    /*public*/  int rowCount(const QModelIndex&) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    /*private*/ void deleteLogixNG(int row);
    /*private*/ void moveUp(int row) ;
    /*private*/ void moveDown(int row) ;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

};
#endif // LOGIXNGINITIALIZATIONTABLE_H
