#include "usermessagepreferencespane.h"
#include "jmriuserpreferencesmanager.h"
#include "instancemanager.h"
#include <QBoxLayout>
#include "jmriuserpreferencesmanager.h"
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QList>
#include <QScrollArea>
#include "jlabel.h"
#include <QFormLayout>
#include <appconfigbase.h>
#include "logixtableaction.h"
#include "lroutetableaction.h"
#include "routetableaction.h"
#include "sensortableaction.h"
#include "signalheadtableaction.h"
#include "turnouttableaction.h"

#if 1
/**
 * Pane to show User Message Preferences
 *
 * @author	Kevin Dickerson Copyright (C) 2009
 * @version	$Revision: 28158 $
 */
// /*public*/ class UserMessagePreferencesPane extends JmriPanel implements PreferencesPanel {

    /**
     *
     */
//    /*private*/ static final long serialVersionUID = 6892195773335485275L;
//    protected static final ResourceBundle rb = ResourceBundle.getBundle("apps.AppsConfigBundle");

/*public*/UserMessagePreferencesPane::UserMessagePreferencesPane(QWidget *parent) :
    PreferencesPanel(parent)
{
 if(objectName().isEmpty())
  setObjectName("UserMessagePreferencesPane");
 resize(400,300);
 tab = new QTabWidget();

 _comboBoxes =  QMap<QComboBox*, ListItems*>();
 _checkBoxes =  QMap<QCheckBox*, ListItems*>();
 updating = false;


  //super();
  p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
//    p->addPropertyChangeListener((PropertyChangeEvent e) -> {
//        if (e.getPropertyName()==("PreferencesUpdated")) {
//            refreshOptions();
//        }
//    });

  UserPreferencesManager* dp =(UserPreferencesManager*)p;
  connect(dp, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  QVBoxLayout* thisLayout;
  setLayout(thisLayout = new QVBoxLayout);//(this, BoxLayout.Y_AXIS));

  setMinimumMessagePref();
  thisLayout->addWidget(tab);
}
void UserMessagePreferencesPane::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("PreferencesUpdated"))
 {
    refreshOptions();
 }
}
/*private*/ void UserMessagePreferencesPane::setMinimumMessagePref()
{
 //This ensures that as a minimum that the following items are at least initialised and appear in the preference panel
 p->setClassDescription("jmri.jmrit.beantable.AudioTableAction");
 p->setClassDescription("jmri.jmrit.beantable.BlockTableAction");

 p->setClassDescription("jmri.jmrit.beantable.LightTableAction");
 p->setClassDescription("jmri.jmrit.beantable.LogixTableAction");
 p->setClassDescription(LRouteTableAction::getName());
 p->setClassDescription("jmri.jmrit.beantable.MemoryTableAction");

 p->setClassDescription("jmri.jmrit.beantable.ReporterTableAction");
 p->setClassDescription(RouteTableAction::getName());

 p->setClassDescription(SensorTableAction::getName());
 p->setClassDescription("jmri.jmrit.beantable.SignalGroupTableAction");
 p->setClassDescription(SignalHeadTableAction::getName());
 p->setClassDescription("jmri.jmrit.beantable.SignalMastTableAction");

 p->setClassDescription("jmri.jmrit.beantable.TransitTableAction");
 p->setClassDescription(TurnoutTableAction::getName());

 p->setClassDescription(AppConfigBase::getName());

 newMessageTab();
}

/*private*/ void UserMessagePreferencesPane::newMessageTab()
{
 layout()->removeWidget(tab);
 tab = new QTabWidget();

 //might need to redo this so that it doesn't recreate everything all the time.
 _comboBoxes =  QMap<QComboBox*, ListItems*>();
 _checkBoxes =  QMap<QCheckBox*, ListItems*>();

 QStringList preferenceClassList = p->getPreferencesClasses();
 foreach (QString strClass, preferenceClassList)
 {
  QWidget* classholder = new QWidget();
  QVBoxLayout* classholderLayout;
  classholder->setLayout(classholderLayout = new QVBoxLayout());

  QMap<int, QString> options;
  bool add = false;
  bool addtoindependant = false;
  if (p->getPreferencesSize(strClass) > 1)
  {
   addtoindependant = true;
  }
  QWidget* classPanel = new QWidget();
  QVBoxLayout* classPanelLayout;
  classPanel->setLayout(classPanelLayout = new QVBoxLayout); //(classPanel, BoxLayout.Y_AXIS));
  //classPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
  for (int j = 0; j < p->getMultipleChoiceSize(strClass); j++)
  {
   QString itemName = p->getChoiceName(strClass, j);
   options = p->getChoiceOptions(strClass, itemName);
   if (!options.isEmpty())
   {
    QComboBox* optionBox = new QComboBox();
    ListItems* li = new ListItems(strClass, itemName);
    _comboBoxes.insert(optionBox, li);
    li->isIncluded(addtoindependant);
    optionBox->clear();
    foreach (QString value, options.values())
    {
     optionBox->addItem(value);
    }
    int current = p->getMultipleChoiceOption(strClass, itemName);

    if (options.contains(current))
    {
     optionBox->setCurrentIndex(optionBox->findText(options.value(current)));
    }
    if (addtoindependant)
    {
     QWidget* optionPanel = new QWidget();
     QHBoxLayout* optionPanelLayout = new QHBoxLayout;
     optionPanel->setLayout(optionPanelLayout);
     QLabel* _comboLabel = new QLabel(p->getChoiceDescription(strClass, itemName));
     _comboLabel->setAlignment(Qt::AlignLeft);
//                    _comboLabel.setAlignmentX(0.5f);
     optionPanelLayout->addWidget(_comboLabel);
     optionPanelLayout->addWidget(optionBox);
     add = true;
     classPanelLayout->addWidget(optionPanel);
    }
   }
  }
  QStringList singleList = p->getPreferenceList(strClass);
  if (!singleList.isEmpty())
  {
   for (int i = 0; i < singleList.size(); i++)
   {
    QString itemName = p->getPreferenceItemName(strClass, i);
    QString description = p->getPreferenceItemDescription(strClass, itemName);
    if ((description != NULL) && (description!=("")))
    {
     QCheckBox* check = new QCheckBox(description);
     check->setChecked(p->getPreferenceState(strClass, itemName));
     ListItems* li = new ListItems(strClass, itemName);
     _checkBoxes.insert(check, li);
     li->isIncluded(addtoindependant);

     if (addtoindependant)
     {
      classPanelLayout->addWidget(check);
      add = true;
     }
    }
   }
  }
  if (add)
  {
   classholderLayout->addWidget(classPanel, /*BorderLayout.NORTH*/0, Qt::AlignTop);
   if (p->getPreferencesSize(strClass) > 1)
   {
    QScrollArea* scrollPane = new QScrollArea(/*classholder*/);
    scrollPane->setWidget(classholder);
    scrollPane->setMinimumSize(QSize(300, 300));
//                scrollPane.setBorder(BorderFactory.createEmptyBorder());
    tab->addTab(scrollPane, p->getClassDescription(strClass));
   }
  }
 }
 QMap<QString, QList<ListItems*>* > countOfItems = QMap<QString, QList<ListItems*>* >();
 QMap<QString, QList<QCheckBox*>* > countOfItemsCheck = QMap<QString, QList<QCheckBox*>* >();
 QMap<QString, QList<QComboBox*>* > countOfItemsCombo = QMap<QString, QList<QComboBox*>* >();
 foreach (QComboBox* key, this->_comboBoxes.keys())
 {
  if (!_comboBoxes.value(key)->isIncluded())
  {
   QString strItem = _comboBoxes.value(key)->getItem();
   if (!countOfItems.contains(strItem))
   {
    countOfItems.insert(strItem, new QList<ListItems*>());
    countOfItemsCombo.insert(strItem, new QList<QComboBox*>());
   }

   QList<ListItems*>* a = countOfItems.value(strItem);
   a->append(_comboBoxes.value(key));

   QList<QComboBox*>* acb = countOfItemsCombo.value(strItem);
   acb->append(key);
  }
 }

 foreach (QCheckBox* key, this->_checkBoxes.keys())
 {
  if (!_checkBoxes.value(key)->isIncluded())
  {
   QString strItem = _checkBoxes.value(key)->getItem();

   if (!countOfItems.contains(strItem))
   {
    countOfItems.insert(strItem, new QList<ListItems*>());
    countOfItemsCheck.insert(strItem,  new QList<QCheckBox*>());
   }
   QList<ListItems*>* a = countOfItems.value(strItem);
   a->append(_checkBoxes.value(key));

   QList<QCheckBox*>* acb = countOfItemsCheck.value(strItem);
   acb->append(key);
  }
 }
 QWidget* miscPanel = new QWidget();
 QVBoxLayout* miscPanelLayout;
 miscPanel->setLayout(miscPanelLayout = new QVBoxLayout); //(miscPanel, BoxLayout.Y_AXIS));

 QWidget* mischolder = new QWidget();
 QHBoxLayout* mischolderLayout;
 mischolder->setLayout(mischolderLayout = new /*BorderLayout()*/QHBoxLayout);
//    mischolder.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
 foreach (QString item, countOfItems.keys())
 {
  QList<ListItems*>* a = countOfItems.value(item);
  QList<QCheckBox*>* chb = countOfItemsCheck.value(item);
  QList<QComboBox*>* cob = countOfItemsCombo.value(item);
  if (a->size() > 1)
  {
   QWidget* tableDeleteTabPanel = new QWidget();
   QVBoxLayout* tableDeleteTabPanelLayout;
   tableDeleteTabPanel->setLayout(tableDeleteTabPanelLayout= new QVBoxLayout); //(tableDeleteTabPanel, BoxLayout.Y_AXIS));
   QLabel* tableDeleteInfoLabel = new JLabel(p->getChoiceDescription(a->at(0)->getClassName(), a->at(0)->getItem()), JLabel::CENTER);
   //tableDeleteInfoLabel.setAlignmentX(0.5f);
   tableDeleteTabPanelLayout->addWidget(tableDeleteInfoLabel);
   QWidget* inside = new QWidget();
   QHBoxLayout* insideLayout = new QHBoxLayout;
   inside->setLayout(insideLayout);
   if (!cob->isEmpty())
   {
    QWidget* insideCombo = new QWidget();
    int gridsize = (int) (qCeil((cob->size() / 2.0)));
    QFormLayout* insideComboLayout = new QFormLayout;
    //insideCombo->setLayout(new GridLayout2(gridsize, 2 * 2, 10, 2));
    insideCombo->setLayout(insideComboLayout);
    foreach (QComboBox* combo, *cob)
    {
     QLabel* _comboLabel = new JLabel(p->getClassDescription(_comboBoxes.value(combo)->getClassName()), JLabel::RIGHT);
     _comboBoxes.value(combo)->isIncluded(true);
//                    insideComboLayout->addWidget(_comboLabel);
//                    insideComboLayout->addWidget(combo);
     insideComboLayout->addRow(_comboLabel, combo);
    }
    insideLayout->addWidget(insideCombo);
   }
   if (chb != NULL && !chb->isEmpty())
   {
    QWidget* insideCheck = new QWidget();
    QFormLayout* insideCheckLayout = new QFormLayout;
    insideCheck->setLayout(insideCheckLayout);
    //insideCheck->setLayout(new GridLayout2(chb.size(), 1));
    insideCheck->setLayout(new QFormLayout);
    foreach (QCheckBox* check, *chb)
    {
     QLabel* _checkLabel = new JLabel(p->getClassDescription(_checkBoxes.value(check)->getClassName()), JLabel::RIGHT);
     _checkBoxes.value(check)->isIncluded(true);
//                    insideCheckLayout->addWidget(_checkLabel);
//                    insideCheckLayout->addW(check);
     insideCheckLayout->addRow(_checkLabel, check);
    }
    insideLayout->addWidget(insideCheck);
   }
   tableDeleteTabPanelLayout->addWidget(inside);
   QScrollArea* scrollPane = new QScrollArea(/*tableDeleteTabPanel*/);
   scrollPane->setWidget(tableDeleteTabPanel);
   scrollPane->setMinimumSize( QSize(300, 300));
   tab->addTab(scrollPane, item);
  }
  else
  {
   QWidget* itemPanel = new QWidget();
   QVBoxLayout* itemPanelLayout = new QVBoxLayout;
   itemPanel->setLayout(itemPanelLayout);
   QVBoxLayout* subItemLayout;
   QWidget* subItem = new QWidget();
   subItem->setLayout(subItemLayout=new QVBoxLayout); //(subItem, BoxLayout.Y_AXIS));
   if(a->size() > 0)
    subItemLayout->addWidget(new JLabel(p->getClassDescription(a->value(0)->getClassName()), JLabel::CENTER));
   else
    subItemLayout->addWidget(new JLabel("???"));

   if (countOfItemsCheck.contains(item))
   {
    if(a->size() > 0)
     subItemLayout->addWidget(countOfItemsCheck.value(item)->at(0));
    itemPanelLayout->addWidget(subItem);
    miscPanelLayout->addWidget(itemPanel);
   }
  }
 }

 layout()->addWidget(tab);
 mischolderLayout->addWidget(miscPanel, /*BorderLayout.NORTH*/0, Qt::AlignTop);
 QScrollArea* miscScrollPane = new QScrollArea(/*mischolder*/);
 miscScrollPane->setMinimumSize( QSize(300, 300));
 miscScrollPane->setWidget(mischolder);
 tab->addTab(miscScrollPane, "Misc items");
 //revalidate();
}

//@Override
/*public*/ QString UserMessagePreferencesPane::getPreferencesItem() {
    return "MESSAGES"; // NOI18N
}

//@Override
/*public*/ QString UserMessagePreferencesPane::getPreferencesItemText() {
    return tr("Messages"); // NOI18N
}

//@Override
/*public*/ QString UserMessagePreferencesPane::getTabbedPreferencesTitle() {
    return NULL;
}

//@Override
/*public*/ QString UserMessagePreferencesPane::getLabelKey() {
    return NULL;
}

//@Override
/*public*/ QWidget* UserMessagePreferencesPane::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool UserMessagePreferencesPane::isPersistant() {
    return false;
}

//@Override
/*public*/ QString UserMessagePreferencesPane::getPreferencesTooltip() {
    return NULL;
}

//@Override
/*public*/ void UserMessagePreferencesPane::savePreferences() {
    this->updateManager();
}

//@Override
/*public*/ bool UserMessagePreferencesPane::isDirty()
{
    foreach (QComboBox* key, this->_comboBoxes.keys())
    {
        QString strClass = _comboBoxes.value(key)->getClassName();
        QString strItem = _comboBoxes.value(key)->getItem();
        if (p->getChoiceOptions(strClass, strItem).value(p->getMultipleChoiceOption(strClass, strItem))!=(key->currentText())) {
            return true;
        }
    }
    foreach (QCheckBox* key, this->_checkBoxes.keys()) {
        QString strClass = _checkBoxes.value(key)->getClassName();
        QString strItem = _checkBoxes.value(key)->getItem();
        if (p->getPreferenceState(strClass, strItem) != key->isChecked()) {
            return true;
        }
    }
    return false;
}

//@Override
/*public*/ bool UserMessagePreferencesPane::isRestartRequired() {
    return false;
}

    UserMessagePreferencesPane::ListItems::ListItems(QString strClass, QString item) {
        this->strClass = strClass;
        this->item = item;
        included = false;
    }

    QString UserMessagePreferencesPane::ListItems::getClassName() {
        return strClass;
    }

    QString UserMessagePreferencesPane::ListItems::getItem() {
        return item;
    }

    bool UserMessagePreferencesPane::ListItems::isIncluded() {
        return included;
    }

    void UserMessagePreferencesPane::ListItems::isIncluded(bool boo) {
        included = boo;
    }
//};


/*public*/ void UserMessagePreferencesPane::updateManager()
{
 updating = true;
 p->setLoading();

 foreach (QComboBox* key, this->_comboBoxes.keys())
 {
  QString strClass = _comboBoxes.value(key)->getClassName();
  QString strItem = _comboBoxes.value(key)->getItem();
  QString strSelection =  key->currentText();
  p->setMultipleChoiceOption(strClass, strItem, strSelection);
 }

 foreach (QCheckBox* key, this->_checkBoxes.keys())
 {
  QString strClass = _checkBoxes.value(key)->getClassName();
  QString strItem = _checkBoxes.value(key)->getItem();
  p->setPreferenceState(strClass, strItem, key->isChecked());
 }

 updating = false;
 p->finishLoading();
 refreshOptions();
}

/*private*/ void UserMessagePreferencesPane::refreshOptions()
{
 if (updating)
 {
  return;
 }
 newMessageTab();
}
//}
#endif
