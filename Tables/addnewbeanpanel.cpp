#include "addnewbeanpanel.h"
#include <QBoxLayout>
#include "gridbagconstraints.h"
#include <QGridLayout>
#include "jlabel.h"
#include <QPushButton>
#include "jcheckbox.h"
#include "jtextfield.h"
#include "actionlistener.h"
#include "flowlayout.h"
#include <QPushButton>

//AddNewBeanPanel::AddNewBeanPanel(QWidget *parent) :
//  JmriPanel(parent)
//{
//}
/**
 * JPanel to create a new JMRI devices HiJacked to serve other beantable tables.
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @author Pete Cressman Copyright (C) 2010
 * @version $Revision: 28746 $
 */
///*public*/ class AddNewBeanPanel extends jmri.util.swing.JmriPanel {

 /**
  *
  */
 //private static final long serialVersionUID = -7238135491102630527L;

 /*public*/ AddNewBeanPanel::AddNewBeanPanel(JTextField* sys, JTextField* userName, JSpinner* endRange, JCheckBox* addRange, JCheckBox* autoSystem,
         QString addButtonLabel, ActionListener* listener, ActionListener* cancelListener, JLabel* statusBar, QWidget *parent) :
  JmriPanel(parent)
{
 sysNameLabel = new QLabel(tr("System Name"));
 userNameLabel = new QLabel(tr("User Name"));
 finishLabel = new QLabel(tr("Number To Add"));

     sysName = sys;
     //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(this);
     _endRange = endRange;
     _range = addRange;
     _autoSys = autoSystem;

     QWidget* p;
     p = new QWidget();
     //p.setLayout(new FlowLayout());
     QGridLayout* g;
     p->setLayout(g = new QGridLayout());
     GridBagConstraints c =  GridBagConstraints();
     c.gridwidth = 1;
     c.gridheight = 1;
     c.gridx = 0;
     c.gridy = 0;
     c.anchor = GridBagConstraints::EAST;
     c.gridx = 0;
     c.gridy = 1;
     g->addWidget(sysNameLabel, c.gridy,c.gridx, c.rowSpan(), c.colSpan());
     c.gridy = 2;
     g->addWidget(userNameLabel, c.gridy,c.gridx, c.rowSpan(), c.colSpan());
     c.gridx = 2;
     c.gridy = 1;
     c.anchor = GridBagConstraints::WEST;
     c.weightx = 1.0;
     c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
     c.gridy = 0;
     g->addWidget(autoSystem, c.gridy,c.gridx, c.rowSpan(), c.colSpan());
     c.gridx = 3;
     g->addWidget(addRange, c.gridy,c.gridx, c.rowSpan(), c.colSpan());
     c.gridx = 2;
     c.gridy = 1;
     g->addWidget(sys, c.gridy,c.gridx, c.rowSpan(), c.colSpan());
     c.gridx = 3;
     g->addWidget(finishLabel, c.gridy,c.gridx, c.rowSpan(), c.colSpan());
     c.gridx = 4;
     g->addWidget(endRange, c.gridy,c.gridx, c.rowSpan(), c.colSpan());
     c.gridx = 2;
     c.gridy = 2;
     g->addWidget(userName, c.gridy,c.gridx, c.rowSpan(), c.colSpan());
     thisLayout->addWidget(p);

     finishLabel->setEnabled(false);
     _endRange->setEnabled(false);

     // add status bar above buttons
     JPanel* panelStatus = new JPanel();
     panelStatus->setLayout(new FlowLayout());
     //statusBar.setFont(statusBar.getFont().deriveFont(0.9f * sysNameLabel.getFont().getSize())); // a bit smaller
     QFont f = sysNameLabel->font();
     float ps = f.pointSizeF();
     QFont f2 = statusBar->font();
     f2.setPointSizeF(.9 * ps);
     statusBar->setFont(f2);
     statusBar->setForeground(Qt::gray);
     panelStatus->layout()->addWidget(statusBar);
     thisLayout-> addWidget(panelStatus);// cancel + add buttons at bottom of window

     QWidget* panelBottom = new QWidget();
     panelBottom->setLayout(new FlowLayout(/*FlowLayout::TRAILING*/));
     QPushButton* cancel;
     panelBottom->layout()->addWidget(cancel = new QPushButton(tr("Cancel")));
     //cancel.addActionListener(cancelListener);
     connect(cancel, SIGNAL(clicked()), cancelListener, SLOT(actionPerformed()));

     panelBottom->layout()->addWidget(ok = new QPushButton(addButtonLabel));
     //ok.addActionListener(okListener);
     connect(ok, SIGNAL(clicked(bool)), listener, SLOT(actionPerformed()));

     layout()->addWidget(panelBottom);


//     addRange.addItemListener(
//             new ItemListener() {
//                 /*public*/ void itemStateChanged(ItemEvent e) {
//                     rangeState();
//                 }
//             });
     connect(addRange, SIGNAL(clicked()), this, SLOT(rangeState()));

//     sysName.addKeyListener(new KeyAdapter() {
//         /*public*/ void keyReleased(KeyEvent a) {
//             if (sysName.getText().length() > 0) {
//                 ok.setEnabled(true);
//                 ok.setToolTipText(null);
//             } else {
//                 ok.setEnabled(false);
//             }
//         }
//     });

//     autoSystem.addItemListener(
//             new ItemListener() {
//                 /*public*/ void itemStateChanged(ItemEvent e) {
//                     autoSystemName();
//                 }
//             });
     connect(autoSystem, SIGNAL(clicked()), this, SLOT(autoSystemName()));
}
 /*private*/ void AddNewBeanPanel::autoSystemName() {
     if (_autoSys->isChecked()) {
         ok->setEnabled(true);
         sysName->setEnabled(false);
         sysNameLabel->setEnabled(false);
     } else {
         if (sysName->text().length() > 0) {
             ok->setEnabled(true);
         } else {
             ok->setEnabled(false);
         }
         sysNameLabel->setEnabled(true);
         sysName->setEnabled(true);
         sysNameLabel->setEnabled(true);
     }
 }

 /*private*/ void AddNewBeanPanel::rangeState() {
     if (_range->isChecked()) {
         finishLabel->setEnabled(true);
         _endRange->setEnabled(true);
     } else {
         finishLabel->setEnabled(false);
         _endRange->setEnabled(false);
     }
 }

