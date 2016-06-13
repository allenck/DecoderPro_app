#include "rosterentryselectorpanel.h"

//RosterEntrySelectorPanel::RosterEntrySelectorPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 *
 * @author rhwood
 */
///*public*/ class RosterEntrySelectorPanel extends JPanel implements RosterEntrySelector, RosterGroupSelector {


/*public*/ RosterEntrySelectorPanel::RosterEntrySelectorPanel(QWidget *parent)
    : QFrame(parent)
{
 //RosterEntrySelectorPanel(NULL, "", parent);
 init(NULL, "");
}

/*public*/ RosterEntrySelectorPanel::RosterEntrySelectorPanel(RosterEntry* re, QString rg, QWidget *parent)
    : QFrame(parent)
{
 //super();
 //this.setLayout(new FlowLayout());
    init(re, rg);
}

void RosterEntrySelectorPanel::init(RosterEntry* re, QString /*rg*/)
{
 setObjectName(QString::fromUtf8("rosterEntrySelectorPanel"));
 resize(196,50);
 setFrameShape(QFrame::StyledPanel);
 setFrameShadow(QFrame::Raised);
 horizontalLayout = new QHBoxLayout(this);
 horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
 //entryCombo = new RosterEntryComboBox(rg );
 entryCombo = new RosterEntryComboBox();
 entryCombo->setObjectName(QString::fromUtf8("rosterEntryComboBox"));
 entryCombo->setVisible(true);
 entryCombo->setEnabled(true);
 if (re != NULL)
 {
  entryCombo->setCurrentIndex(this->entryCombo->findText(re->titleString()));
 }

 //groupCombo = new RosterGroupComboBox(rg);
 groupCombo = new RosterGroupComboBox();
 groupCombo->setObjectName(QString::fromUtf8("rosterGroupComboBox"));
 groupCombo->setVisible(true);
 groupCombo->setEnabled(true);
 horizontalLayout->addWidget(groupCombo);
 horizontalLayout->addWidget(entryCombo);
 QMetaObject::connectSlotsByName(this);
 setVisible(true);
//    this.groupCombo.addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent ae) {
//            entryCombo.update(getSelectedRosterGroup());
//        }

//    });
 connect(groupCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_rosterGroup_changed(QString)));

//    this.entryCombo.addPropertyChangeListener(new PropertyChangeListener() {

//        @Override
//        /*public*/ void propertyChange(PropertyChangeEvent pce) {
//            if (pce.getPropertyName().equals(RosterEntrySelector.SELECTED_ROSTER_ENTRIES)) {
//                fireSelectedRosterEntriesPropertyChange(pce.getOldValue(), pce.getNewValue());
//            }
//        }
 connect(entryCombo, SIGNAL(propertyChange(QString,QList<RosterEntry*>*,QList<RosterEntry*>*)), this, SLOT(on_rosterEntryPropertyChange(QString,QList<RosterEntry*>*,QList<RosterEntry*>*)));
//    });
}
void RosterEntrySelectorPanel::on_rosterGroup_changed(QString /*text*/)
{
 entryCombo->update(getSelectedRosterGroup());
}

//protected void fireSelectedRosterEntriesPropertyChange(Object oldValue, Object newValue) {
//    this.firePropertyChange(RosterEntrySelector.SELECTED_ROSTER_ENTRIES, oldValue, newValue);
//}
void RosterEntrySelectorPanel::on_rosterEntryPropertyChange(QString propertyName ,QList<RosterEntry*>* oldValue,QList<RosterEntry*>* newValue)
{
 if(propertyName == "selectedRosterEntries")
  emit propertyChange(new PropertyChangeEvent(this, propertyName, VPtr<QList<RosterEntry*> >::asQVariant(oldValue), VPtr<QList<RosterEntry*> >::asQVariant(newValue)));
}

//@Override
/*public*/ QList<RosterEntry*>* RosterEntrySelectorPanel::getSelectedRosterEntries()
{
 return entryCombo->getSelectedRosterEntries();
}

/*public*/ void RosterEntrySelectorPanel::setSelectedRosterEntry(RosterEntry* re)
{
 entryCombo->setCurrentIndex(entryCombo->findText((re != NULL) ? re->getId() : ""));
}

/*public*/ void RosterEntrySelectorPanel::setSelectedRosterEntryAndGroup(RosterEntry* re, QString rg)
{
 setSelectedRosterEntry(re);
 setSelectedRosterGroup(rg);
}

//@Override
/*public*/ QString RosterEntrySelectorPanel::getSelectedRosterGroup() {
    return groupCombo->getSelectedRosterGroup();
}

/*public*/ void RosterEntrySelectorPanel::setSelectedRosterGroup(QString rg) {
    groupCombo->update(rg);
}

/*public*/ RosterEntryComboBox* RosterEntrySelectorPanel::getRosterEntryComboBox() {
    return entryCombo;
}

/*public*/ RosterGroupComboBox* RosterEntrySelectorPanel::getRosterGroupComboBox() {
    return groupCombo;
}

//@Override
/*public*/ void RosterEntrySelectorPanel::setEnabled(bool enabled) {
    entryCombo->setEnabled(enabled);
    groupCombo->setEnabled(enabled);
}

//@Override
/*public*/ bool RosterEntrySelectorPanel::isEnabled() {
    return entryCombo->isEnabled();
}

/*public*/ QString RosterEntrySelectorPanel::getNonSelectedItem() {
    return entryCombo->getNonSelectedItem();
}

/*public*/ void RosterEntrySelectorPanel::setNonSelectedItem(QString itemText) {
    entryCombo->setNonSelectedItem(itemText);
}

