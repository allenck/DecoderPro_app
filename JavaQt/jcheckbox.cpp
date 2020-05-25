#include "jcheckbox.h"
#include "changeevent.h"

JCheckBox::JCheckBox(QWidget *parent) : QCheckBox(parent)
{
 connect(this, &JCheckBox::clicked, [=]{
  emit stateChanged(new ChangeEvent(this));
 });

}

JCheckBox::JCheckBox(QString text, QWidget *parent) : QCheckBox(text, parent)
{
 connect(this, &JCheckBox::clicked, [=]{
  emit stateChanged(new ChangeEvent(this));
 });
}

/*public*/ void JCheckBox::addChangeListener(ChangeListener* l)
{
 //listeners.append(l);
 connect(this, SIGNAL(stateChanged(ChangeEvent*)), l, SLOT(stateChanged(ChangeEvent*)));

}
/*public*/ void JCheckBox::removeChangeListener(ChangeListener* l)
{
 //listeners.removeOne(l);
 disconnect(this, SIGNAL(stateChanged(ChangeEvent*)), l, SLOT(stateChanged(ChangeEvent*)));
}

/*public*/ void JCheckBox::addFocusListener(FocusListener* l)
{
 //listeners.append(l);
 connect(this, SIGNAL(focusGained(FocusEvent*)), l, SLOT(focusGained(FocusEvent*)));

}

/*public*/ void JCheckBox::removeFocusListener(FocusListener *l)
{
 //listeners.removeOne(l);
 disconnect(this, SIGNAL(focusLost(FocusEvent*)), l, SLOT(focusLost(FocusEvent*)));
}

/*private*/ void JCheckBox::focusInEvent(QFocusEvent* e)
{
 emit focusGained(new FocusEvent());
}

/*private*/ void JCheckBox::focusOutEvent(QFocusEvent* e)
{
 emit focusLost(new FocusEvent());
}
