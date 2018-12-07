#include "rostergrouptableaction.h"
#include "jmripanel.h"
#include "windowinterface.h"
#include "rostergrouptablemodel.h"
#include "rostergrouptableframe.h"
#include "jmrijframe.h"
#include <QComboBox>
#include "roster.h"
#include "rostergroupcombobox.h"
#include <QHBoxLayout>
#include <QLabel>

//RosterGroupTableAction::RosterGroupTableAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a Roster Group Table.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2003
 * @author	Kevin Dickerson Copyright (C) 2009
 * @version	$Revision: 28746 $
 */
// /*public*/ class RosterGroupTableAction extends jmri.util.swing.JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -6077873425282362402L;

/*public*/ RosterGroupTableAction::RosterGroupTableAction(QString s, WindowInterface* wi)
 : JmriAbstractAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ RosterGroupTableAction::RosterGroupTableAction(QString s, QIcon i, WindowInterface* wi)
 : JmriAbstractAction(s, i,wi)
{
 //super(s, i, wi);
 common();
}

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame. Perhaps this should be changed?
 *
 * @param s
 */
/*public*/ RosterGroupTableAction::RosterGroupTableAction(QString s, QObject* parent) : JmriAbstractAction(s, parent)
{
 //super(s);
 common();
}

/*public*/ RosterGroupTableAction::RosterGroupTableAction(QObject* parent)
 : JmriAbstractAction("Roster Group Table", parent)
{
 //this(Bundle.getMessage("RosterGroupTable"));
 common();
}

void RosterGroupTableAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void RosterGroupTableAction::createModel()
{
 m = new RosterGroupTableModel();
}

/*public*/ void RosterGroupTableAction::actionPerformed(ActionEvent* )
{
    // create the JTable model, with changes for specific NamedBean
    createModel();

    // create the frame
    f = new MyRosterGroupTableFrame(m, helpTarget(), this);
//    {
//        /**
//         *
//         */
//        private static final long serialVersionUID = 3167164123972770969L;

//        /**
//         * Include an "add" button
//         */
//        void extras() {
//            final JComboBox<String> selectCombo = new RosterGroupComboBox();
//            selectCombo.insertItemAt("", 0);
//            selectCombo.setSelectedIndex(-1);
//            JPanel p25 = new JPanel();
//            p25.add(new JLabel(Bundle.getMessage("SelectRosterGroup")));
//            p25.add(selectCombo);
//            addToTopBox(p25);
//            selectCombo.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    comboSelected(e, selectCombo.getSelectedItem().toString());
//                }
//            });
//            selectCombo.setVisible(true);

//        }
//    };
    setTitle();
    addToFrame(f);
    f->pack();
    f->setVisible(true);
}

MyRosterGroupTableFrame::MyRosterGroupTableFrame(RosterGroupTableModel *m, QString helpTarget, RosterGroupTableAction *self)
 : RosterGroupTableFrame(m, helpTarget)
{
 this->self = self;
}

void MyRosterGroupTableFrame::extras()
{
    /*final*/ QComboBox* selectCombo = new RosterGroupComboBox();
    selectCombo->addItem("", 0);
    selectCombo->setCurrentIndex(-1);
    QWidget* p25 = new QWidget();
    QHBoxLayout* p25Layout = new QHBoxLayout;
    p25->setLayout(p25Layout);
    p25Layout->addWidget(new QLabel(tr("Select Roster Group")));
    p25Layout->addWidget(selectCombo);
    addToTopBox(p25);
//    selectCombo.addActionListener(new ActionListener() {
//        public void actionPerformed(ActionEvent e) {
//            comboSelected(e, selectCombo.getSelectedItem().toString());
//        }
    connect(selectCombo, SIGNAL(currentIndexChanged(QString)), self, SLOT(comboSelected(QString)));
}

/*public*/ void RosterGroupTableAction::addToFrame(RosterGroupTableFrame* f) {
}

void RosterGroupTableAction::setTitle() {
    f->setTitle(tr("Roster Group Table"));
}

QString RosterGroupTableAction::helpTarget() {
    return "package.jmri.jmrit.roster.swing"; // NOI18N
}

void RosterGroupTableAction::comboSelected(/*ActionEvent* e,*/ QString group) {
    Roster* roster = Roster::getDefault();
    m->setGroup(Roster::ROSTER_GROUP_PREFIX + group);
    m->fireTableDataChanged();

}

/*public*/ JmriPanel* RosterGroupTableAction::makePanel() {
    throw  IllegalArgumentException("Should not be invoked");
}
