#include "pushbuttondelegate.h"
#include <QPushButton>
#include <QApplication>
#include <QEvent>
#include <QMouseEvent>
#include "jtogglebutton.h"
#include <QPainter>

PushButtonDelegate::PushButtonDelegate(QObject *parent) : QItemDelegate(parent)
{
}

QWidget* PushButtonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex & index ) const
{

 QPushButton* editor;
#if QT_VERSION < 0x050000
 if(index.data().canConvert<QString>())
#else
 if(index.data().canConvert(QMetaType::type("QString")))
#endif
  editor = new QPushButton(index.data().toString(),parent);
 else
 {
  QIcon icon = index.data().value<QIcon>();
  editor = new QPushButton(icon, "", parent);
 }
 return editor;
}

void PushButtonDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
 QPushButton *button = static_cast<QPushButton*>(editor);
 int value = index.model()->data(index, Qt::EditRole).toUInt();
 button->setText(index.data().toString());
}

void PushButtonDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
 QPushButton *button = static_cast<QPushButton*>(editor);
 model->setData(index, QVariant(), Qt::EditRole);
}

void PushButtonDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
 editor->setGeometry(option.rect);
}

void PushButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
 QPushButton* widget = new QPushButton();
 setEditorData(widget, index);
 widget->resize(option.rect.size());
 QPixmap pixmap(option.rect.size());
 widget->render(&pixmap);
 painter->drawPixmap(option.rect,pixmap);
}

ToggleButtonDelegate::ToggleButtonDelegate(QObject *parent) : QItemDelegate(parent)
{
}

QWidget* ToggleButtonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex & index ) const
{

 QPushButton* editor;
#if QT_VERSION < 0x050000
 if(index.data().canConvert<QString>())
#else
 if(index.data().canConvert(QMetaType::type("QString")))
#endif
  editor = new QPushButton(index.data().toString(),parent);
 else
 {
  QIcon icon = index.data().value<QIcon>();
  editor = new QPushButton(icon, "", parent);
 }
 return editor;
}

void ToggleButtonDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
 JToggleButton *button = static_cast<JToggleButton*>(editor);
 int value = index.model()->data(index, Qt::EditRole).toUInt();
}

void ToggleButtonDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
 JToggleButton *button = static_cast<JToggleButton*>(editor);
 model->setData(index, QVariant(), Qt::EditRole);
}

void ToggleButtonDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
 editor->setGeometry(option.rect);
}
void ToggleButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
 //bool state = index.data().toString() == this->on;
 JToggleButton* widget = new JToggleButton(index.data().toString());
 //widget->setLabels(on, off);
 //widget->setChecked(state);
 setEditorData(widget, index);
 widget->resize(option.rect.size());
 QPixmap pixmap(option.rect.size());
 widget->render(&pixmap);
 painter->drawPixmap(option.rect,pixmap);
}

MyDelegate::MyDelegate(QObject *parent)
     : QItemDelegate(parent)
 {
 }
void MyDelegate::setText(QString text) {buttonText = text;}

 void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
     QStyleOptionButton button;
     QRect r = option.rect;//getting the rect of the cell
     int x,y,w,h;
//     x = r.left() + r.width() - 30;//the X coordinate
     x = r.left() +1;
     y = r.top();//the Y coordinate
//     w = 30;//button width
     w = r.width();
//     h = 30;//button height
     h = r.height();
     button.rect = QRect(x,y,w,h);
     //button.text = "=^.^=";
//     if(buttonText != "")
//      button.text = buttonText;
//     else
      button.text = index.model()->data(index).toString();
     button.state = QStyle::State_Enabled;

     QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter);
 }

 bool MyDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
 {
  if( event->type() == QEvent::MouseButtonRelease )
  {
   QMouseEvent * e = (QMouseEvent *)event;
   int clickX = e->x();
   int clickY = e->y();

   QRect r = option.rect;//getting the rect of the cell
   int x,y,w,h;
   //x = r.left() + r.width() - 30;//the X coordinate
   x = r.left() +1;
   y = r.top();//the Y coordinate
   //w = 30;//button width
   w = r.width();
   h = 30;//button height

   if( clickX > x && clickX < x + w )
   {
    if( clickY > y && clickY < y + h )
    {
//                 QDialog * d = new QDialog();
//                 d->setGeometry(0,0,100,100);
//                 d->show();
     model->setData(index, QVariant(), Qt::EditRole);

    }
   }
   return true;
  }
  return false;
 }
