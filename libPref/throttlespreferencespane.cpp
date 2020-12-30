#include "throttlespreferencespane.h"
#include "instancemanager.h"
#include "throttlespreferences.h"
#include "gridbagconstraints.h"
#include <QPushButton>
#include <QCheckBox>
#include <QGridLayout>
#include "throttleframemanager.h"
#include "jframe.h"
#include "rosterentry.h"
#include "throttlespreferences.h"
#include "gridbagconstraints.h"
#include <QGridLayout>

//ThrottlesPreferencesPane::ThrottlesPreferencesPane(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 *
 * @author lionel
 */
// /*public*/ class ThrottlesPreferencesPane extends javax.swing.JPanel implements PropertyChangeListener {
//	/*private*/ static final long serialVersionUID = -5473594799045080011L;

#if 1
/** Creates new form ThrottlesPreferencesPane */
/*public*/ ThrottlesPreferencesPane::ThrottlesPreferencesPane(QWidget *parent) : QWidget(parent)
{
 common();
}
/*public*/ ThrottlesPreferencesPane::ThrottlesPreferencesPane(const ThrottlesPreferencesPane & ): QWidget()
{
 //common();
}

void ThrottlesPreferencesPane::common()
{
 m_container = NULL;
 if(InstanceManager::getDefault("ThrottlesPreferences")==NULL)
 {
  InstanceManager::store(new ThrottlesPreferences(), "ThrottlesPreferences");
 }
 ThrottlesPreferences* tp = (ThrottlesPreferences*)InstanceManager::getDefault("ThrottlesPreferences");
 initComponents();
 setComponents(tp);
 checkConsistancy(true);
 //tp->addPropertyChangeListener(this);
 connect(ThrottleFrameManager::instance()->getThrottlesPreferences(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*private*/ void ThrottlesPreferencesPane::initComponents()
{
 GridBagConstraints* gridBagConstraints13 = new GridBagConstraints();
 gridBagConstraints13->gridx = 0;
 gridBagConstraints13->insets = new Insets(2, 23, 2, 2);
 gridBagConstraints13->ipady = 16;
 gridBagConstraints13->anchor = GridBagConstraints::WEST;
 gridBagConstraints13->gridy = 99;

 GridBagConstraints* gridBagConstraints14 = new GridBagConstraints();
 gridBagConstraints14->gridx = 0;
 gridBagConstraints14->insets = new Insets(2, 23, 2, 2);
 gridBagConstraints14->anchor = GridBagConstraints::WEST;
 gridBagConstraints14->gridy = 10;

 GridBagConstraints* gridBagConstraints12 = new  GridBagConstraints();
 gridBagConstraints12->gridx = 0;
 gridBagConstraints12->insets = new Insets(2, 23, 2, 2);
 gridBagConstraints12->anchor = GridBagConstraints::WEST;
 gridBagConstraints12->gridy = 9;

 GridBagConstraints* gridBagConstraints15 = new  GridBagConstraints();
 gridBagConstraints15->gridx = 0;
 gridBagConstraints15->insets = new Insets(2, 23, 2, 2);
 gridBagConstraints15->anchor = GridBagConstraints::WEST;
 gridBagConstraints15->gridy = 8;

 GridBagConstraints* gridBagConstraints11 = new GridBagConstraints();
 gridBagConstraints11->gridx = 0;
 gridBagConstraints11->insets = new Insets(2, 23, 2, 2);
 gridBagConstraints11->anchor = GridBagConstraints::WEST;
 gridBagConstraints11->gridy = 7;

 GridBagConstraints* gridBagConstraints6 = new GridBagConstraints();
 gridBagConstraints6->insets = new Insets(2, 23, 2, 2);
 gridBagConstraints6->gridy = 5;
 gridBagConstraints6->anchor = GridBagConstraints::WEST;
 gridBagConstraints6->gridx = 0;

 GridBagConstraints* gridBagConstraints10 = new  GridBagConstraints();
 gridBagConstraints10->insets = new Insets(2, 43, 2, 2);
 gridBagConstraints10->gridy = 6;
 gridBagConstraints10->anchor = GridBagConstraints::WEST;
 gridBagConstraints10->gridx = 0;
 GridBagConstraints* gridBagConstraints5 = new GridBagConstraints();
 gridBagConstraints5->insets = new Insets(2, 23, 2, 2);
 gridBagConstraints5->gridy = 4;
 gridBagConstraints5->anchor = GridBagConstraints::WEST;
 gridBagConstraints5->gridx = 0;
 GridBagConstraints* gridBagConstraints4 = new GridBagConstraints();
 gridBagConstraints4->insets = new Insets(2, 43, 2, 2);
 gridBagConstraints4->gridy = 3;
 gridBagConstraints4->anchor = GridBagConstraints::WEST;
 gridBagConstraints4->gridx = 0;
 GridBagConstraints* gridBagConstraints3 = new GridBagConstraints();
 gridBagConstraints3->insets = new Insets(2, 23, 2, 2);
 gridBagConstraints3->gridy = 2;
 gridBagConstraints3->anchor = GridBagConstraints::WEST;
 gridBagConstraints3->gridx = 0;
 GridBagConstraints* gridBagConstraints2 = new  GridBagConstraints();
 gridBagConstraints2->insets = new Insets(2, 23, 2, 2);
 gridBagConstraints2->gridy = 1;
 gridBagConstraints2->anchor = GridBagConstraints::WEST;
 gridBagConstraints2->gridx = 0;
 GridBagConstraints* gridBagConstraints1 = new GridBagConstraints();
 gridBagConstraints1->insets = new Insets(8, 5, 2, 2);
 gridBagConstraints1->gridy = 0;
 gridBagConstraints1->anchor = GridBagConstraints::WEST;
 gridBagConstraints1->gridx = 0;

 // last line: buttons
 GridBagConstraints* gridBagConstraints9 = new  GridBagConstraints();
 gridBagConstraints9->insets = new Insets(5, 3, 5, 5);
 gridBagConstraints9->gridy = 100;
 gridBagConstraints9->gridx = 1;
 GridBagConstraints* gridBagConstraints8 = new  GridBagConstraints();
 gridBagConstraints8->insets = new Insets(5, 3, 5, 2);
 gridBagConstraints8->gridy = 100;
 gridBagConstraints8->anchor = GridBagConstraints::WEST;
 gridBagConstraints8->gridx = 0;
 GridBagConstraints* gridBagConstraints7 = new GridBagConstraints();
 gridBagConstraints7->insets = new Insets(5, 3, 5, 2);
 gridBagConstraints7->gridy = 100;
 gridBagConstraints7->gridx = 8;

 jbCancel = new QPushButton();
 jbSave = new QPushButton();
 jbApply = new QPushButton();

 cbUseExThrottle = new QCheckBox();
 cbUseToolBar = new QCheckBox();
 cbUseFunctionIcon = new QCheckBox();
 cbUseRosterImage = new QCheckBox();
 cbResizeWinImg = new QCheckBox();
 cbEnableRosterSearch = new QCheckBox();
 cbEnableAutoLoad  = new QCheckBox();
 cbHideUndefinedButtons = new QCheckBox();
 cbIgnoreThrottlePosition = new QCheckBox();
 cbSaveThrottleOnLayoutSave = new QCheckBox();

 labelApplyWarning = new QLabel();

 cbUseExThrottle->setText(tr("Use extended throttle"));
 cbResizeWinImg->setText(tr("Do not scale image"));
 cbUseToolBar->setText(tr("Enable throttle toolbar"));
 cbUseFunctionIcon->setText(tr("Enable button icons when available"));
 cbUseRosterImage->setText(tr("Use roster image as background"));
 cbEnableRosterSearch->setText(tr("Search roster info when address entered"));
 cbEnableAutoLoad->setText(tr("Automatic load of throttle window preferences when linked to roster"));
 cbHideUndefinedButtons->setText(tr("Hide undefined roster function buttons"));
 cbIgnoreThrottlePosition->setText(tr("Ignore throttle frame position"));
 labelApplyWarning->setText(tr("For new preferences to be fully applied, all throttles windows must be closed and reopened."));
 cbSaveThrottleOnLayoutSave->setText(tr("Save throttles when saving throttle windows layout"));

//    java.awt.event.ActionListener al = new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            checkConsistancy();
//        }
//    };
    //cbUseExThrottle.addActionListener(al);
 connect(cbUseExThrottle, SIGNAL(toggled(bool)), this, SLOT(checkConsistancy(bool)));
    //cbUseToolBar.addActionListener(al);
 connect(cbUseToolBar, SIGNAL(toggled(bool)), this, SLOT(checkConsistancy(bool)));
    //cbUseRosterImage.addActionListener(al);
 connect(cbUseRosterImage, SIGNAL(toggled(bool)), this, SLOT(checkConsistancy(bool)));
    //cbEnableAutoLoad.addActionListener(al);
 connect(cbEnableAutoLoad, SIGNAL(toggled(bool)), this, SLOT(checkConsistancy(bool)));

 jbSave->setText(tr("Save"));
//    jbSave.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            jbSaveActionPerformed(evt);
//        }
//    });
 connect(jbSave, SIGNAL(clicked()), this, SLOT(jbSaveActionPerformed()));
 jbSave->setVisible(false);

 jbCancel->setText(tr("Reset"));
//    jbCancel.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            jbCancelActionPerformed(evt);
//        }
//    });
 connect(jbCancel, SIGNAL(clicked()), this, SLOT(jbCancelActionPerformed()));

 jbApply->setText(tr("Apply"));
//    jbApply.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            jbApplyActionPerformed(evt);
//        }
//    });
 connect(jbApply, SIGNAL(clicked()), this, SLOT(jbApplyActionPerformed()));

 QGridLayout* g;
 setLayout(g = new QGridLayout());
 g->setObjectName("QGridLayout");

 g->addWidget(cbUseExThrottle, gridBagConstraints1->gridy, gridBagConstraints1->gridx,gridBagConstraints1->rowSpan(),gridBagConstraints1->colSpan());
 g->addWidget(cbSaveThrottleOnLayoutSave, gridBagConstraints2->gridy, gridBagConstraints2->gridx,gridBagConstraints2->rowSpan(),gridBagConstraints2->colSpan());
 g->addWidget(cbUseRosterImage, gridBagConstraints3->gridy, gridBagConstraints3->gridx,gridBagConstraints3->rowSpan(),gridBagConstraints3->colSpan());
 g->addWidget(cbResizeWinImg, gridBagConstraints4->gridy, gridBagConstraints4->gridx,gridBagConstraints4->rowSpan(),gridBagConstraints4->colSpan());
 g->addWidget(cbEnableRosterSearch, gridBagConstraints5->gridy, gridBagConstraints5->gridx,gridBagConstraints5->rowSpan(),gridBagConstraints5->colSpan());
 g->addWidget(cbEnableAutoLoad, gridBagConstraints6->gridy, gridBagConstraints6->gridx,gridBagConstraints6->rowSpan(),gridBagConstraints6->colSpan());
 g->addWidget(jbSave, gridBagConstraints7->gridy, gridBagConstraints7->gridx,gridBagConstraints7->rowSpan(),gridBagConstraints7->colSpan());
 g->addWidget(jbCancel, gridBagConstraints8->gridy, gridBagConstraints8->gridx,gridBagConstraints8->rowSpan(),gridBagConstraints8->colSpan());
 g->addWidget(jbApply, gridBagConstraints9->gridy, gridBagConstraints9->gridx,gridBagConstraints9->rowSpan(),gridBagConstraints9->colSpan());
 g->addWidget(cbHideUndefinedButtons, gridBagConstraints11->gridy, gridBagConstraints11->gridx,gridBagConstraints11->rowSpan(),gridBagConstraints11->colSpan());
 g->addWidget(cbIgnoreThrottlePosition, gridBagConstraints10->gridy, gridBagConstraints10->gridx,gridBagConstraints10->rowSpan(),gridBagConstraints10->colSpan());
 g->addWidget(cbUseToolBar, gridBagConstraints12->gridy, gridBagConstraints12->gridx,gridBagConstraints12->rowSpan(),gridBagConstraints12->colSpan());
 g->addWidget(cbUseFunctionIcon, gridBagConstraints14->gridy, gridBagConstraints14->gridx,gridBagConstraints14->rowSpan(),gridBagConstraints14->colSpan());
 g->addWidget(labelApplyWarning, gridBagConstraints13->gridy, gridBagConstraints13->gridx,gridBagConstraints13->rowSpan(),gridBagConstraints13->colSpan());
}

/*private*/ void ThrottlesPreferencesPane::setComponents(ThrottlesPreferences* tp)
{
 if (tp==NULL) return;
 cbSaveThrottleOnLayoutSave->setChecked( tp->isSavingThrottleOnLayoutSave() );
 cbResizeWinImg->setChecked( tp->isResizingWindow() );
 cbUseToolBar->setChecked( tp->isUsingToolBar() );
 cbUseFunctionIcon->setChecked( tp->isUsingFunctionIcon() );
 cbUseRosterImage->setChecked( tp->isUsingRosterImage() );
 cbUseExThrottle->setChecked( tp->isUsingExThrottle() );
 cbEnableRosterSearch->setChecked( tp->isEnablingRosterSearch() );
 cbEnableAutoLoad->setChecked( tp->isAutoLoading() );
 cbHideUndefinedButtons->setChecked( tp->isHidingUndefinedFuncButt() );
 cbIgnoreThrottlePosition->setChecked( tp->isIgnoringThrottlePosition() );
}

/*private*/ ThrottlesPreferences* ThrottlesPreferencesPane::getThrottlesPreferences()
{
    ThrottlesPreferences* tp = new ThrottlesPreferences();
    tp->setUseExThrottle (cbUseExThrottle->isChecked() );
    tp->setUsingToolBar(cbUseToolBar->isChecked() );
    tp->setUsingFunctionIcon(cbUseFunctionIcon->isChecked() );
    tp->setResizeWindow(cbResizeWinImg->isChecked());
    tp->setUseRosterImage(cbUseRosterImage->isChecked());
    tp->setSaveThrottleOnLayoutSave( cbSaveThrottleOnLayoutSave->isChecked() );
    tp->setEnableRosterSearch( cbEnableRosterSearch->isChecked() );
    tp->setAutoLoad( cbEnableAutoLoad->isChecked() );
    tp->setHideUndefinedFuncButt( cbHideUndefinedButtons->isChecked() );
    tp->setIgnoreThrottlePosition( cbIgnoreThrottlePosition->isChecked() );
    return tp;
}

/*private*/ void ThrottlesPreferencesPane::checkConsistancy(bool)
{
 cbSaveThrottleOnLayoutSave->setEnabled( cbUseExThrottle->isChecked() );
 cbUseToolBar->setEnabled( cbUseExThrottle->isChecked() );
 cbUseFunctionIcon->setEnabled( cbUseExThrottle->isChecked() );
 cbEnableRosterSearch->setEnabled( cbUseExThrottle->isChecked() );
 cbEnableAutoLoad->setEnabled( cbUseExThrottle->isChecked() );
 cbUseRosterImage->setEnabled( cbUseExThrottle->isChecked() );
 cbResizeWinImg->setEnabled( cbUseExThrottle->isChecked()  &&  cbUseRosterImage->isChecked() );
 cbHideUndefinedButtons->setEnabled( cbUseExThrottle->isChecked() );
 cbIgnoreThrottlePosition->setEnabled( cbUseExThrottle->isChecked() && cbEnableAutoLoad->isChecked() );
 if ( cbUseExThrottle->isChecked() )
 {
  if ( cbUseToolBar->isChecked() )
  {
   cbIgnoreThrottlePosition->setChecked( true );
   cbIgnoreThrottlePosition->setEnabled( false );
  }
 }
}

/*private*/ void ThrottlesPreferencesPane::jbApplyActionPerformed(JActionEvent* evt)
{
 ThrottleFrameManager::instance()->getThrottlesPreferences()->set(getThrottlesPreferences());
}

/*public*/ void ThrottlesPreferencesPane::jbSaveActionPerformed(JActionEvent* evt)
{
 ThrottleFrameManager::instance()->getThrottlesPreferences()->set(getThrottlesPreferences());
 ThrottleFrameManager::instance()->getThrottlesPreferences()->save();
 if (m_container != NULL)
 {
  //ThrottleFrameManager::instance()->getThrottlesPreferences()->removePropertyChangeListener(this);
  disconnect(ThrottleFrameManager::instance()->getThrottlesPreferences(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  m_container->setVisible(false); // should do with events...
  m_container->dispose();
 }
}

/*private*/ void ThrottlesPreferencesPane::jbCancelActionPerformed(JActionEvent* evt)
{
 setComponents(ThrottleFrameManager::instance()->getThrottlesPreferences());
 checkConsistancy(true);
 if (m_container != NULL)
 {
  //ThrottleFrameManager::instance()->getThrottlesPreferences()->removePropertyChangeListener(this);
  disconnect(ThrottleFrameManager::instance()->getThrottlesPreferences(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  m_container->setVisible(false); // should do with events...
  m_container->dispose();
 }
}

/*public*/ void ThrottlesPreferencesPane::setContainer(JFrame* f)
{
 m_container = f;
 jbSave->setVisible(true);
 jbCancel->setText(tr("Cancel"));
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(ThrottlesPreferencesPane.class.getName());

/*public*/ void ThrottlesPreferencesPane::propertyChange(PropertyChangeEvent* evt)
{
 if ((evt == NULL) || (evt->getPropertyName() == "")) return;
 if (evt->getPropertyName()== ("ThrottlePreferences") == 0) {
 if ((evt->getNewValue() == QVariant()) || (! (qobject_cast<ThrottlesPreferences*>(VPtr<ThrottlesPreferences>::asPtr(evt->getNewValue() )))))
  return;
 setComponents((ThrottlesPreferences*)VPtr<ThrottlesPreferences*>::asPtr(evt->getNewValue()));
  checkConsistancy(true);
 }
}
/*public*/ QString ThrottlesPreferencesPane::getPreferencesItem() {
    return "THROTTLE";
}

//@Override
/*public*/ QString ThrottlesPreferencesPane::getPreferencesItemText() {
    // need to move resource into ThrottleBundle.properties
    //ResourceBundle rb = ResourceBundle.getBundle("apps.AppsConfigBundle");
    return tr("Throttle");
}

//@Override
/*public*/ QString ThrottlesPreferencesPane::getTabbedPreferencesTitle() {
    return "";
}

//@Override
/*public*/ QString ThrottlesPreferencesPane::getLabelKey() {
    return "";
}

//@Override
/*public*/ QWidget* ThrottlesPreferencesPane::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool ThrottlesPreferencesPane::isPersistant() {
    return false;
}

//@Override
/*public*/ QString ThrottlesPreferencesPane::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void ThrottlesPreferencesPane::savePreferences() {
    this->jbSaveActionPerformed();
}

//@Override
/*public*/ bool ThrottlesPreferencesPane::isDirty() {
    return ((ThrottlesPreferences*)InstanceManager::getDefault("ThrottlesPreferences"))->isDirty();
}

//@Override
/*public*/ bool ThrottlesPreferencesPane::isRestartRequired() {
    return false;
}

/*public*/ QString ThrottlesPreferencesPane::className() {return "jmri.jmrit.throttle.ThrottlesPreferencesPane";}
//}
#endif
