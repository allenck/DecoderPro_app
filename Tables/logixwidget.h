#ifndef LOGIXWIDGET_H
#define LOGIXWIDGET_H

#include <QWidget>
#include "logger.h"
#include <qabstractitemdelegate.h>

namespace Ui {
class LogixWidget;
}


class QSignalMapper;
class Logix;
class PropertyChangeEvent;
class LogixTableAction;
class DefaultLogixManager;
class DefaultLogix;
class LogixWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogixWidget(QWidget *parent = 0);
    ~LogixWidget();
    LogixTableAction* logixTableAction();

private:
    Ui::LogixWidget *ui;
    QVector<DefaultLogix*> rows;
    DefaultLogixManager* mgr;
    Logger* log;
    LogixTableAction* act;
//    void updateRow(int row, DefaultLogix* r);
    bool bLoading;

private slots:
    void on_btnAdd_clicked();
//    void propertyChange(PropertyChangeEvent*);
//    void on_newLogixCreated(Logix* x);
//    void on_tableWidget_cellChanged(int,int);
};
class ItemDelegate : public QAbstractItemDelegate
{
  Q_OBJECT
 public:
  ItemDelegate(QStringList items, QObject *parent);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
  QStringList Items;
  //int row;
signals:
private slots:
};

#endif // LOGIXWIDGET_H
