#include "programmerconfigpane.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QLabel>
#include <QComboBox>
#include "progdefault.h"
#include <QCheckBox>
#include "paneprogframe.h"

//ProgrammerConfigPane::ProgrammerConfigPane(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Provide GUI to configure symbolic programmer defaults.
 *
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
 * @version	$Revision: 28433 $
 */
// /*public*/ class ProgrammerConfigPane extends JPanel implements PreferencesPanel {

//private static final long serialVersionUID = 3341676760826030384L;
//private final ResourceBundle apb = ResourceBundle.getBundle("apps.AppsConfigBundle");

/*public*/ ProgrammerConfigPane::ProgrammerConfigPane(QWidget* parent)
    : QWidget(parent)
{
 common();
}
/*public*/ ProgrammerConfigPane::ProgrammerConfigPane(const ProgrammerConfigPane &)
{
 common();
}

void /*private*/ ProgrammerConfigPane::common()
{
 setObjectName("ProgrammerConfigPane");
 QBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.PAGE AXIS));
 QWidget* p = new QWidget();
 FlowLayout* pLayout;
 p->setLayout(pLayout = new FlowLayout());
 pLayout->addWidget(new QLabel("Format:"));
 pLayout->addWidget(programmerBox = new QComboBox()); //<String>(jmri.jmrit.symbolicprog.ProgDefault.findListOfProgFiles()));
 programmerBox->addItems(ProgDefault::findListOfProgFiles());
 programmerBox->setCurrentIndex(programmerBox->findText(ProgDefault::getDefaultProgFile()));
 thisLayout->addWidget(p);

 // also create the advanced panel
 advancedPanel = new QWidget();
 QVBoxLayout* advancedPanelLayout;
 advancedPanel->setLayout(advancedPanelLayout = new QVBoxLayout); //(advancedPanel, BoxLayout.Y_AXIS));
 advancedPanelLayout->addWidget(showEmptyTabs = new QCheckBox("Show empty tabs"));
 showEmptyTabs->setChecked(PaneProgFrame::isShowingEmptyPanes());
 advancedPanelLayout->addWidget(ShowCvNums = new QCheckBox("Show CV numbers in tool tips"));
 ShowCvNums->setChecked(PaneProgFrame::getShowCvNumbers());
 thisLayout->addWidget(advancedPanel);
 //thisLayout->addWidget(javax.swing.Box.createVerticalGlue());
}

/**
 * This constructor does nothing different than the default constructor.
 *
 * @deprecated since 3.9.5
 */
///*public*/ ProgrammerConfigPane(boolean include) {
//    this();
//}

/*public*/ QString ProgrammerConfigPane::getSelectedItem() {
    return  programmerBox->currentText();
}

/*public*/ QWidget* ProgrammerConfigPane::getAdvancedPanel() {
    return advancedPanel;
}

/*public*/ bool ProgrammerConfigPane::getShowEmptyTabs() {
    return showEmptyTabs->isChecked();
}

/*public*/ bool ProgrammerConfigPane::getShowCvNums() {
    return ShowCvNums->isChecked();
}

//@Override
/*public*/ QString ProgrammerConfigPane::getPreferencesItem() {
    return "ROSTER"; // NOI18N
}

//@Override
/*public*/ QString ProgrammerConfigPane::getPreferencesItemText() {
    return tr("Roster"); // NOI18N
}

//@Override
/*public*/ QString ProgrammerConfigPane::getTabbedPreferencesTitle() {
    return tr("Programmer"); // NOI18N
}

//@Override
/*public*/ QString ProgrammerConfigPane::getLabelKey() {
    return tr("\"Advanced\" contains everything.\n\"Basic\" is the minimal starting point."); // NOI18N
}

//@Override
/*public*/ QWidget* ProgrammerConfigPane::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool ProgrammerConfigPane::isPersistant() {
    return true;
}

//@Override
/*public*/ QString ProgrammerConfigPane::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void ProgrammerConfigPane::savePreferences() {
    // do nothing - the persistant manager will take care of this
}

//@Override
/*public*/ bool ProgrammerConfigPane::isDirty() {
    return (this->getShowEmptyTabs() != PaneProgFrame::isShowingEmptyPanes()
            || this->getShowCvNums() != PaneProgFrame::getShowCvNumbers()
            || this->getSelectedItem()!=(ProgDefault::getDefaultProgFile()));
}

//@Override
/*public*/ bool ProgrammerConfigPane::isRestartRequired() {
    return this->isDirty();
}

//@Override
/*public*/ bool ProgrammerConfigPane::isPreferencesValid() {
    return true; // no validity checking performed
}

/*public*/ QString ProgrammerConfigPane::className() {return "jmri.jmrit.symbolicprog.ProgrammerConfigPane";}
