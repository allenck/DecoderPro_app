#ifndef TABLEDELEGATES_H
#define TABLEDELEGATES_H
#include "tablecelleditor.h"
#include "tablecellrenderer.h"
#include <QStyledItemDelegate>
#include "jtogglebutton.h"
#include "jbutton.h"
#include "jcombobox.h"
#include <QPainter>
#include "togglebutton.h"
#include <QApplication>
#include "vptr.h"

class ButtonRenderer : public QStyledItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
    Q_INTERFACES(TableCellEditor TableCellRenderer )
public:
    ButtonRenderer(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    QObject* self() {return (QObject*)this;}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        JButton* editor;
       #if QT_VERSION < 0x050000
        if(index.data().canConvert<QString>())
       #else
        if(index.data().canConvert(QMetaType::type("QString")))
       #endif
         editor = new JButton(index.data().toString(),parent);
        else
        {
         QIcon icon = index.data().value<QIcon>();
         editor = new JButton( "", icon, parent);
        }
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        JButton *button = static_cast<JButton*>(editor);
        int value = index.model()->data(index, Qt::EditRole).toUInt();

    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        JButton *button = static_cast<JButton*>(editor);
        model->setData(index, QVariant(), Qt::EditRole);
        QApplication::beep();
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
   }
};

class ToggleButtonRenderer : public QStyledItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
    Q_INTERFACES(TableCellEditor TableCellRenderer )
public:
    ToggleButtonRenderer(QString sq, QString s2, QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    QObject* self() {return (QObject*)this;}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        JToggleButton* editor;
       #if QT_VERSION < 0x050000
        if(index.data().canConvert<QString>())
       #else
        if(index.data().canConvert(QMetaType::type("QString")))
       #endif
         editor = new JToggleButton(index.data().toString(),parent);
        else
        {
         QIcon icon = index.data().value<QIcon>();
         editor = new JToggleButton(icon, "", parent);
        }
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        JToggleButton *button = static_cast<JToggleButton*>(editor);
        int value = index.model()->data(index, Qt::EditRole).toUInt();
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        JToggleButton *button = static_cast<JToggleButton*>(editor);
        model->setData(index, QVariant(), Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

class ValueRenderer : public QStyledItemDelegate, public TableCellEditor, public TableCellRenderer
{
  Q_OBJECT
  Q_INTERFACES(TableCellEditor TableCellRenderer )
 public:
     ValueRenderer(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
     QObject* self() {return (QObject*)this;}
     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
     {
         QWidget* editor = VPtr<QWidget>::asPtr(index.model()->data(index, Qt::DisplayRole));
         return editor;
     }
     void setEditorData(QWidget *editor, const QModelIndex &index) const{
//         JComboBox *comboBox = static_cast<JComboBox*>(editor);
//         QString value = index.model()->data(index, Qt::DisplayRole).toString();
//         comboBox->setCurrentText(value);
     }
     void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
     {
//         JComboBox *comboBox = static_cast<JComboBox*>(editor);
//         model->setData(index, comboBox->currentText(), Qt::EditRole);
     }

     void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
         editor->setGeometry(option.rect);
     }

     void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
     {
      //bool state = index.data().toString() == this->on;
      QWidget* widget = new QWidget();
//      widget->setCurrentText(index.model()->data(index, Qt::DisplayRole).toString());
      widget->resize(option.rect.size());
      QPixmap pixmap(option.rect.size());
      widget->render(&pixmap);
      painter->drawPixmap(option.rect,pixmap);
     }
};

class ButtonEditor : public QStyledItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
  Q_INTERFACES(TableCellEditor TableCellRenderer )
public:
    ButtonEditor(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    QObject* self() {return (QObject*)this;}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
     QPushButton *button = static_cast<QPushButton*>(editor);
     int value = index.model()->data(index, Qt::EditRole).toUInt();
     button->setText(index.data().toString());
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QPushButton *button = static_cast<QPushButton*>(editor);
        model->setData(index, QVariant(), Qt::EditRole);
        QApplication::beep();
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
     editor->setGeometry(option.rect);
    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
     QPushButton* widget = new QPushButton(index.data().toString());
     setEditorData(widget, index);
     widget->resize(option.rect.size());
     QPixmap pixmap(option.rect.size());
     widget->render(&pixmap);
     painter->drawPixmap(option.rect,pixmap);
    }
};

class ToggleButtonEditor : public QStyledItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
    Q_INTERFACES(TableCellEditor TableCellRenderer )
    QString on;
    QString off;

public:
    ToggleButtonEditor(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    QObject* self() {return (QObject*)this;}
    ToggleButtonEditor(QString on, QString off, QObject* parent = nullptr) : QStyledItemDelegate(parent)
    {
        this->on = on;
        this->off = off;
    }
    void setValues(QString on, QString off)
    {
        this->on = on;
        this->off = off;
    }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        ToggleButton* editor;
        bool state;
       #if QT_VERSION < 0x050000
        if(index.data().canConvert<QString>())
       #else
        if(index.data().canConvert(QMetaType::type("QString")))
       #endif
        {
         state = index.data().toString() == this->on;
         editor = new ToggleButton(10,8,parent);
         editor->setLabels(on, off);
         editor->setChecked(state);
        }
        else
        {
         QIcon icon = index.data().value<QIcon>();
         editor = new ToggleButton(10,8, parent);
        }
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        ToggleButton *button = static_cast<ToggleButton*>(editor);
        int value = index.model()->data(index, Qt::EditRole).toUInt();
        if(button->isChecked())
         button->setText(this->on);
        else
         button->setText(this->off);

    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        ToggleButton *button = static_cast<ToggleButton*>(editor);
//        if(button->isChecked())
//         model->setData(index, this->on, Qt::EditRole);
//        else
//         model->setData(index, this->off, Qt::EditRole);
        model->setData(index, button->isChecked(), Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        editor->setGeometry(option.rect);
    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
     bool state = index.data().toString() == this->on;
     ToggleButton* widget = new ToggleButton(10,8);
     widget->setLabels(on, off);
     widget->setChecked(state);
     setEditorData(widget, index);
     widget->resize(option.rect.size());
     QPixmap pixmap(option.rect.size());
     widget->render(&pixmap);
     painter->drawPixmap(option.rect,pixmap);
    }
};

class JComboBoxEditor : public QStyledItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
    Q_INTERFACES(TableCellEditor TableCellRenderer )
    QStringList values = QStringList();
public:
    JComboBoxEditor(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    QObject* self() {return (QObject*)this;}
    JComboBoxEditor(QStringList values, QObject* parent = nullptr) : QStyledItemDelegate(parent)
    {
        this->values = values;
    }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        JComboBox* editor = new JComboBox(parent);
        editor->addItems(values);
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const{
        JComboBox *comboBox = static_cast<JComboBox*>(editor);
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        comboBox->setCurrentText(value);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        JComboBox *comboBox = static_cast<JComboBox*>(editor);
        model->setData(index, comboBox->currentText(), Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        editor->setGeometry(option.rect);
    }
    void setValues(QStringList values) {this->values = values;}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
     //bool state = index.data().toString() == this->on;
     JComboBox* widget = new JComboBox(values);
     widget->setCurrentText(index.model()->data(index, Qt::DisplayRole).toString());
     widget->resize(option.rect.size());
     QPixmap pixmap(option.rect.size());
     widget->render(&pixmap);
     painter->drawPixmap(option.rect,pixmap);
    }
};
#endif // TABLEDELEGATES_H
