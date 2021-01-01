#ifndef PUSHBUTTONDELEGATE_H
#define PUSHBUTTONDELEGATE_H

#include <QItemDelegate>
#include <javaqt_global.h>

class JToggleButton;
class QPushButton;
class JAVAQTSHARED_EXPORT PushButtonDelegate : public QItemDelegate
{
Q_OBJECT

public:
  PushButtonDelegate( QObject *parent = 0);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class JAVAQTSHARED_EXPORT ToggleButtonDelegate : public QItemDelegate
{
Q_OBJECT

public:
  ToggleButtonDelegate( QObject *parent = 0);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class JAVAQTSHARED_EXPORT MyDelegate : public QItemDelegate
{
    Q_OBJECT
QString buttonText;
public:
    MyDelegate(QObject *parent = 0);
    void setText(QString text);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};
#endif // PUSHBUTTONDELEGATE_H
