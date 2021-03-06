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

 bool isOpaque() override;
 /*public*/ QColor getForeground() override;
 QColor getBackground() override;
 void setBackground(QColor) override;
 void setOpaque(bool) override;
 QFont getFont() override;
 void setFont(QFont) override;
 QObject* jself() override {return (QObject*)this;}
 /*public*/ void setBorder(Border* border) override {this->_border = border;}
 /*public*/ Border* getBorder() override {return _border;}
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
 /*public*/ void clear();
 /*public*/ QVariant currentData();
 /*public*/ void addItem(QString text, const QVariant &data = QVariant());
// /*public*/ void  addItem(QString text) {QComboBox::addItem(text);}
signals:
 void itemStateChanged(ItemEvent* e);
 /*public*/ void focusGained(FocusEvent* fe);
 /*public*/ void focusLost(FocusEvent* fe);

 public slots:
 void currentIndexChanged(int);

private:
 bool _opaque = false;
 Border* _border = nullptr;
 /*private*/ void focusInEvent(QFocusEvent* e)override;
 /*private*/ void focusOutEvent(QFocusEvent* e)override;
 QStringListModel* cbModel;
 QMap<QString, QVariant> map = QMap<QString, QVariant>();

private slots:
 //void on_selected();
};
Q_DECLARE_METATYPE(JComboBox)
#endif // JCOMBOBOX_H
