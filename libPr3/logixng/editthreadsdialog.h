#ifndef EDITTHREADSDIALOG_H
#define EDITTHREADSDIALOG_H

#include <QObject>
#include "abstracttablemodel.h"

class ConditionalNG;
class JDialog;
class LogixNG_Thread;
class JLabel;
class ThreadTableModel;
class EditThreadsDialog : public QObject
{
  Q_OBJECT
 public:
  explicit EditThreadsDialog(ConditionalNG* conditionalNG, QObject *parent = nullptr);
  /*public*/  void showDialog();

 private:
  /*private*/ /*final*/ ConditionalNG* _conditionalNG;
  /*private*/ JDialog* _editThreadsDialog;
  /*private*/ LogixNG_Thread* _newStartupThread;
  /*private*/ JLabel* _startupThreadNameLabel;
  ThreadTableModel* _threadTableModel = nullptr;
  /*private*/ void abortPressed();
  /*private*/ void okPressed();

  friend class ThreadTableModel;
};
/*private*/ /*final*/ class ThreadTableModel : public AbstractTableModel {
Q_OBJECT
  /*private*/ /*final*/ QList<LogixNG_Thread*> _threads;
  EditThreadsDialog* dlg;
 public:
  enum COLUMNS {
    THREAD_ID_COLUMN = 0,
    THREAD_NAME_COLUMN = THREAD_ID_COLUMN + 1,
    BUTTON_SELECT_THREAD_COLUMN = THREAD_NAME_COLUMN + 1,
    BUTTON_DELETE_COLUMN = BUTTON_SELECT_THREAD_COLUMN + 1,
    NUM_COLUMNS = BUTTON_DELETE_COLUMN + 1
  };
    /*public*/  ThreadTableModel(EditThreadsDialog* dlg);
    /*public*/  QString getColumnClass(int c) const override;
    /*public*/  int columnCount(const QModelIndex&) const override;
    /*public*/  int rowCount(const QModelIndex&) const override;
    /*public*/  Qt::ItemFlags flags(const QModelIndex&) const override;
    /*public*/  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/  int getPreferredWidth(int col);
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

 private:
    /*private*/ void deleteThread(int row);
    /*private*/ void changeThreadName(QVariant value, int row);

    friend class EditThreadsDialog;
};
#endif // EDITTHREADSDIALOG_H
