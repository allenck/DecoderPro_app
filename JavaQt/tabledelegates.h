#ifndef TABLEDELEGATES_H
#define TABLEDELEGATES_H
#include "tablecelleditor.h"
#include "tablecellrenderer.h"
#include <QItemDelegate>
#include "jtogglebutton.h"
#include "jbutton.h"
#include "jcombobox.h"

class ButtonRenderer : public QItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
    Q_INTERFACES(TableCellEditor TableCellRenderer )
public:
    ButtonRenderer(QObject* parent = nullptr) : QItemDelegate(parent) {}
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

    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
   }
};

class ToggleButtonRenderer : public QItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
    Q_INTERFACES(TableCellEditor TableCellRenderer )
public:
    ToggleButtonRenderer(QString sq, QString s2, QObject* parent = nullptr) : QItemDelegate(parent) {}
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

class ValueRenderer : public QItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
    Q_INTERFACES(TableCellEditor TableCellRenderer )
public:
    ValueRenderer(QObject* parent = nullptr) : QItemDelegate(parent) {}
    QObject* self() {return (QObject*)this;}
};

class ButtonEditor : public QItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
  Q_INTERFACES(TableCellEditor TableCellRenderer )
public:
    ButtonEditor(QObject* parent = nullptr) : QItemDelegate(parent) {}
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
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QPushButton *button = static_cast<QPushButton*>(editor);
        model->setData(index, QVariant(), Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
     editor->setGeometry(option.rect);
    }
};

class ToggleButtonEditor : public QItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
    Q_INTERFACES(TableCellEditor TableCellRenderer )
    QString on;
    QString off;

public:
    ToggleButtonEditor(QObject* parent = nullptr) : QItemDelegate(parent) {}
    QObject* self() {return (QObject*)this;}
    ToggleButtonEditor(QString on, QString off, QObject* parent = nullptr) : QItemDelegate(parent)
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

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        editor->setGeometry(option.rect);

    }
};

class JComboBoxEditor : public QItemDelegate, public TableCellEditor, public TableCellRenderer
{
    Q_OBJECT
    Q_INTERFACES(TableCellEditor TableCellRenderer )
    QStringList values = QStringList();
public:
    JComboBoxEditor(QObject* parent = nullptr) : QItemDelegate(parent) {}
    QObject* self() {return (QObject*)this;}
    JComboBoxEditor(QStringList values, QObject* parent = nullptr) : QItemDelegate(parent)
    {
        this->values = values;
    }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QComboBox* editor = new QComboBox(parent);
        editor->addItems(values);
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const{
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        int value = index.model()->data(index, Qt::EditRole).toUInt();
        comboBox->setCurrentIndex(value);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        model->setData(index, comboBox->currentText(), Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        editor->setGeometry(option.rect);
    }
    void setValues(QStringList values) {this->values = values;}
};
#endif // TABLEDELEGATES_H
