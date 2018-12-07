#include "rosterconfigpane.h"
#include "QFileDialog"
#include "jtextfield.h"
#include <QLabel>
#include "fileutil.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include "roster.h"
#include <QPushButton>
#include "rosterentry.h"
#include <QMessageBox>

//RosterConfigPane::RosterConfigPane(QWidget *parent) :
//    PreferencesPanel(parent)
//{
//}
#if 1
/**
 * Provide GUI to configure Roster defaults.
 *
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003, 2007
 * @version	$Revision: 28431 $
 */
// /*public*/ class RosterConfigPane extends QWidget* implements PreferencesPanel {

//    private static final long serialVersionUID = -8185051724790761792L;
//    private final ResourceBundle apb = ResourceBundle.getBundle("apps.AppsConfigBundle");

/*public*/ RosterConfigPane::RosterConfigPane(QWidget *parent)
    : PreferencesPanel(parent)
{
 setObjectName("RosterConfigPane");
 owner = new JTextField(20);

 setCursor(Qt::WaitCursor);
 fc = new QFileDialog(this, tr("Select Roster file"),FileUtil::getUserFilesPath(), tr("Roster file (roster.xml)"));
 setCursor(Qt::ArrowCursor);
    // filter to only show the roster.xml file
    //    FileFilter filt = new FileFilter() {
    //        //@Override
    //        /*public*/ boolean accept(File f) {
    //            if (f.getName()==("roster.xml")) {
    //                return true;
    //            } else {
    //                return f.isDirectory();
    //            }
    //        }

    //        //@Override
    //        /*public*/ String getDescription() {
    //            return "roster.xml only";
    //        }
    //    };

//    fc.setDialogTitle(tr("DialogTitleMove"));
//    fc.setFileFilter(filt);

    QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout);//(this, BoxLayout.Y_AXIS));
    FlowLayout* pLayout = new FlowLayout();
    //QWidget* p = new QWidget();
    //p->setLayout(pLayout = new FlowLayout());
    pLayout->addWidget(new QLabel(tr("Move Location")));

    pLayout->addWidget(filename = new QLabel(Roster::getDefault()->getRosterLocation()));
    // don't show default location, so it's not deemed a user selection
    // and saved
    if (FileUtil::getUserFilesPath()==(Roster::getDefault()->getRosterLocation()))
    {
        filename->setText("");
    }
    QPushButton* b = new QPushButton(tr("Set..."));

//    b.addActionListener(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -1593137799319787064L;

//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            // prompt with instructions
//            if (JOptionPane.OK_OPTION != JOptionPane.showConfirmDialog(RosterConfigPane.this.getTopLevelAncestor(),
//                    tr("DialogMsgMoveWarning"),
//                    tr("DialogMsgMoveQuestion"),
//                    JOptionPane.OK_CANCEL_OPTION
//            )) {
//                return;
//            }

//            // get the file
//            fc.rescanCurrentDirectory();
//            fc.showOpenDialog(null);
//            if (fc.getSelectedFile() == null) {
//                return; // cancelled
//            }
//            if (!fc.getSelectedFile().getName()==("roster.xml")) {
//                return; // wrong file
//            }
//            filename.setText(fc.getSelectedFile().getParent() + File.separator);
//            validate();
//            if (getTopLevelAncestor() != null) {
//                ((JFrame) getTopLevelAncestor()).pack();
//            }
//        }
//    });
    connect(b, SIGNAL(clicked()), this, SLOT(On_set_clicked()));
    pLayout->addWidget(b);
    b = new QPushButton(tr("Reset"));
    //    b.addActionListener(new AbstractAction() {
    //        /**
    //         *
    //         */
    //        private static final long serialVersionUID = 898239723894109746L;

    //        //@Override
    //        /*public*/ void actionPerformed(ActionEvent e) {
    //            filename.setText("");
    //            validate();
    //            if (getTopLevelAncestor() != null) {
    //                ((JFrame) getTopLevelAncestor()).pack();
    //            }
    //        }
    //    });
    connect(b, SIGNAL(clicked()), this, SLOT(On_b_clicked()));
    pLayout->addWidget(b);
    thisLayout->addLayout(pLayout);

    //QWidget* p2 = new QWidget();
    //p2.setLayout(new FlowLayout());
    FlowLayout* p2Layout = new FlowLayout;
    p2Layout->addWidget(new QLabel(tr("Default Owner")));
    owner->setText(RosterEntry::getDefaultOwner());
    p2Layout->addWidget(owner);
    thisLayout->addLayout(p2Layout);
}
void RosterConfigPane::On_set_clicked()
{
 // prompt with instructions
//    if (JOptionPane.OK_OPTION != JOptionPane.showConfirmDialog(RosterConfigPane.this.getTopLevelAncestor(),
//            tr("DialogMsgMoveWarning"),
//            tr("DialogMsgMoveQuestion"),
//            JOptionPane.OK_CANCEL_OPTION
//    ))
    if(QMessageBox::warning(getTopLevelAncestor(), tr("Question"), tr("Do you want to move this file?"),
                            QMessageBox::Yes | QMessageBox::No)!= QMessageBox::Yes)
    {
        return;
    }

    // get the file
    //fc->rescanCurrentDirectory();
    //fc.showOpenDialog(null);
    if (fc->selectedFiles().at(0) == "") {
        return; // cancelled
    }
    if (QFileInfo(fc->selectedFiles().at(0)).fileName()!=("roster.xml")) {
        return; // wrong file
    }
    filename->setText(QFileInfo(fc->selectedFiles().at(0)).path() + QDir::separator());
    //validate();
    if (getTopLevelAncestor() != NULL) {
        ((JFrame*) getTopLevelAncestor())->pack();
    }

}

void RosterConfigPane::On_b_clicked()
{
 filename->setText("");
 //validate();
if (getTopLevelAncestor() != NULL) {
    ((JFrame*) getTopLevelAncestor())->pack();
}

}

/*public*/ QString RosterConfigPane::getDefaultOwner() {
    return owner->text();
}

/*public*/ void RosterConfigPane::setDefaultOwner(QString defaultOwner) {
    owner->setText(defaultOwner);
}

/*public*/ QString RosterConfigPane::getSelectedItem() {
    return filename->text();
}

//@Override
/*public*/ QString RosterConfigPane::getPreferencesItem() {
    return "ROSTER"; // NOI18N
}

//@Override
/*public*/ QString RosterConfigPane::getPreferencesItemText() {
    return this->tr("Roster"); // NOI18N
}

//@Override
/*public*/ QString RosterConfigPane::getTabbedPreferencesTitle() {
    return this->tr("Roster"); // NOI18N
}

//@Override
/*public*/ QString RosterConfigPane::getLabelKey() {
    return this->tr("Roster"); // NOI18N
}

//@Override
/*public*/ QWidget*  RosterConfigPane::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool RosterConfigPane::isPersistant() {
    return true;
}

//@Override
/*public*/ QString RosterConfigPane::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void RosterConfigPane::savePreferences() {
    // do nothing - the persistant manager will take care of this
}

//@Override
/*public*/ bool RosterConfigPane::isDirty() {
    return (this->isFileLocationChanged()
            || RosterEntry::getDefaultOwner()!=(this->getDefaultOwner()));
}

//@Override
/*public*/ bool RosterConfigPane::isRestartRequired() {
    return this->isFileLocationChanged();
}

/*private*/ bool RosterConfigPane::isFileLocationChanged() {
    return (this->getSelectedItem() == NULL || this->getSelectedItem()==(""))
            ? Roster::getDefault()->getRosterLocation()!=(FileUtil::getUserFilesPath())
            : Roster::getDefault()->getRosterLocation()!=(this->getSelectedItem());
}
#endif
