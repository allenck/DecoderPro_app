#ifndef JCOMBOBOX_H
#define JCOMBOBOX_H
#include <qcombobox.h>
#include "jcomponent.h"
#include "changelistener.h"
#include "focuslistener.h"
#include "itemlistener.h"
#include <QStringListModel>
#include "comboboxmodel.h"

class EventObject;
class JComboBox : public QComboBox, public JComponent
{
 Q_OBJECT
 Q_INTERFACES(JComponent)
public:
 JComboBox(QWidget* parent = nullptr);
 JComboBox(QStringList list, QWidget* parent = nullptr);
 JComboBox(ComboBoxModel* model, QWidget* parent = nullptr);
 ~JComboBox() {}
 JComboBox(const JComboBox&) : QComboBox() {}

 bool isOpaque();
 /*public*/ QColor getForeground();
 QColor getBackground();
 void setBackground(QColor);
 void setOpaque(bool);
 QFont getFont();
 void setFont(QFont);
 QObject* jself() {return (QObject*)this;}
 /*public*/ void setBorder(Border* border) override {this->_border = border;}
 /*public*/ Border* getBorder() {return _border;}
 /*public*/ void addChangeListener(ChangeListener* l);
 /*public*/ void removeChangeListener(ChangeListener* l);
 /*public*/ void addFocusListener(FocusListener *l);
 /*public*/ void removeFocusListener(FocusListener* l);
 /*public*/ void addItemListener(ItemListener* listener);
 /*public*/ void setEnabled(bool b) override {QComboBox::setEnabled(b);}
 /*public*/ QString getSelectedItem() {return currentText();}
 /*public*/ int getSelectedIndex() {return currentIndex();}
 /*public*/ void setSelectedIndex(int i){setCurrentIndex(i);}
 /*public*/ virtual void setSelectedItem(QString t) {setCurrentText(t);}
 /*public*/ int getItemCount() {return count();}
 /*public*/ QStringList itemList();
 /*public*/ QVariant getItemAt(int i);

signals:
 void itemStateChanged(ItemEvent* e);
 /*public*/ void focusGained(FocusEvent* fe);
 /*public*/ void focusLost(FocusEvent* fe);

 public slots:
 void currentIndexChanged(int);

private:
 bool _opaque = false;
 Border* _border = nullptr;
 /*private*/ void focusInEvent(QFocusEvent* e);
 /*private*/ void focusOutEvent(QFocusEvent* e);
 QStringListModel* cbModel;
private slots:
 //void on_selected();
};
Q_DECLARE_METATYPE(JComboBox)
#endif // JCOMBOBOX_H
