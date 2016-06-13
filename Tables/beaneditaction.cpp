#include "beaneditaction.h"
#include "namedbean.h"
#include "jtextfield.h"
#include "jtextarea.h"
#include <QScrollArea>
#include <QBoxLayout>
#include "jmrijframe.h"
#include "logger.h"
#include "gridbagconstraints.h"
#include "namedbeanhandlemanager.h"
#include "instancemanager.h"
#include <QStringList>
#include <QMessageBox>
#include <QTableView>
#include <QListWidget>
#include "flowlayout.h"
#include <QPushButton>
#include "beanitempanel.h"
#include "beanitempanel.h"
#include "beanedititem.h"
#include <QLabel>
//#include "jtextpane.h"

BeanEditAction::BeanEditAction(QObject *parent) :
  QAction("Bean Edit", parent)
{
 common();
}
/**
 * Provides the basic information and structure for for a editing the details of
 * a bean object
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version	$Revision: 17977 $
 */
// abstract class BeanEditAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 8002894695517110179L;

/*public*/ BeanEditAction::BeanEditAction(QString s,QObject *parent) :
  QAction(s,parent){
    //super(s);
 common();
}

///*public*/ BeanEditAction() {
//    super("Bean Edit");
//}

/*private*/ void BeanEditAction::common()
{
 userNameField = new JTextField(20);
 commentField = new JTextArea(3, 30);
 commentFieldScroller = new QScrollArea(/*commentField*/);
 commentFieldScroller->setWidget(commentField);
 bei =  QList<BeanItemPanel*>(/*5*/);
 selectedTab = NULL;
 detailsTab = new QTabWidget();
 log = new Logger("BeanEditAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 nbMan = (NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager");
 f = NULL;
}

/*public*/ void BeanEditAction::setBean(NamedBean* bean) {
    this->bean = bean;
}

/**
 * Call to create all the different tabs that will be added to the frame
 */
/*protected*/ void BeanEditAction::initPanels()
{
 basicDetails();
}

/*protected*/ void BeanEditAction::initPanelsFirst() {

}

/*protected*/ void BeanEditAction::initPanelsLast()
{
 usageDetails();
 propertiesDetails();
}


/**
 * Creates a generic panel that holds the basic bean information System
 * Name, User Name and Comment
 */
BeanItemPanel* BeanEditAction::basicDetails()
{
 BeanItemPanel* basic = new BeanItemPanel();

 basic->setName("Basic");
 QVBoxLayout* basicLayout;
 basic->setLayout(basicLayout = new QVBoxLayout); //(basic, BoxLayout.Y_AXIS));

 basic->addItem(new BeanEditItem(new QLabel(bean->getSystemName()), tr("System Name"), NULL));

 basic->addItem(new BeanEditItem(userNameField, tr("User Name"), NULL));

 basic->addItem(new BeanEditItem(commentFieldScroller, tr("Comment"), NULL));

//    basic->setSaveItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -1823311798750191527L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            saveBasicItems(e);
//        }
//    });
 basic->setSaveItem(new BasicSetSaveActionListener(this));
//    basic->setResetItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = 2590436299984618901L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            resetBasicItems(e);
//        }
//    });
 basic->setResetItem(new BasicSetResetActionListener(this));
 bei.append(basic);
 return basic;
}
BasicSetSaveActionListener::BasicSetSaveActionListener(BeanEditAction *act)
{
 this->act = act;
}
/*public*/ void BasicSetSaveActionListener::actionPerformed(ActionEvent* /*e*/) {
 act->saveBasicItems();
}
BasicSetResetActionListener::BasicSetResetActionListener(BeanEditAction *act)
{
 this->act = act;
}
/*public*/ void BasicSetResetActionListener::actionPerformed(ActionEvent* /*e*/) {
 act->resetBasicItems();
}

BeanItemPanel* BeanEditAction::usageDetails()
{
 BeanItemPanel* usage = new BeanItemPanel();

 usage->setName("Usage");
 usage->setLayout(new QVBoxLayout); //(usage, BoxLayout.Y_AXIS));

 usage->addItem(new BeanEditItem(NULL, NULL, tr("Provides an indication as to where %1 is used within your panel.").arg( bean->getDisplayName())));

 QStringList listeners =  QStringList();
 foreach (QString ref, *bean->getListenerRefs())
 {
  if (!listeners.contains(ref))
  {
   listeners.append(ref);
  }
 }

//    QObjectList strArray =  QObjectList();
//    listeners.toArray(strArray);
 //JList<Object> list = new JList<Object>(strArray);
 QListWidget* list = new QListWidget();
 foreach(QString s, listeners)
  list->addItem(s);
//    list.setLayoutOrientation(JList.VERTICAL);
//    list.setVisibleRowCount(-1);
//    list.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
//    JScrollPane listScroller = new JScrollPane(list);
//    listScroller.setPreferredSize(new Dimension(250, 80));
//    listScroller.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black)));
 usage->addItem(new BeanEditItem(/*listScroller*/list, "Location", NULL));

 bei.append(usage);
 return usage;
}

BeanItemPanel* BeanEditAction::propertiesDetails()
{
 BeanItemPanel* properties = new BeanItemPanel();
 properties->setName(tr("Properties"));
 properties->addItem(new BeanEditItem(NULL, NULL, tr("These are custom properties (delete Name to remove entry) (DO NOT CHANGE unless you know what you're doing)")));
 QVBoxLayout* propertiesLayout;
 properties->setLayout(propertiesLayout = new QVBoxLayout); //(properties, BoxLayout.Y_AXIS));
 propertiesModel = new BeanPropertiesTableModel();
 QTableView* jtAttributes = new QTableView();
 jtAttributes->setModel(propertiesModel);
//    QScrollArea* jsp = new JScrollPane(jtAttributes);
 QSize tableDim =  QSize(400, 200);
//    jsp.setMinimumSize(tableDim);
//    jsp.setMaximumSize(tableDim);
//    jsp.setPreferredSize(tableDim);
 properties->addItem(new BeanEditItem(jtAttributes, "", NULL));
// properties->setSaveItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -5627203723098157467L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            propertiesModel.updateModel(bean);
//        }
//    });
 properties->setSaveItem(new PropertiesSetSaveActionListener(this));
//    properties->setResetItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -956489116413677732L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            propertiesModel.setModel(bean);
//        }
//    });
 properties->setResetItem(new PropertiesSetResetActionListener(this));

 bei.append(properties);
 return properties;
}

PropertiesSetSaveActionListener::PropertiesSetSaveActionListener(BeanEditAction *act)
{
 this->act = act;
}
/*public*/ void PropertiesSetSaveActionListener::actionPerformed(ActionEvent* e)
{
 act->propertiesModel->setModel(act->bean);
}
PropertiesSetResetActionListener::PropertiesSetResetActionListener(BeanEditAction *act)
{
 this->act = act;
}
/*public*/ void PropertiesSetResetActionListener::actionPerformed(ActionEvent* e) {
 act->propertiesModel->setModel(act->bean);
}

/*protected*/ void BeanEditAction::saveBasicItems(ActionEvent* e)
{
 if (bean->getUserName() == NULL && userNameField->text()!=(""))
 {
  renameBean(userNameField->text());
 }
 else if (bean->getUserName() != NULL && bean->getUserName()!=(userNameField->text()))
 {
  if (userNameField->text()==(""))
  {
   removeName();
  }
  else
  {
   renameBean(userNameField->text());
  }
 }
 bean->setComment(commentField->toPlainText());
}

/*protected*/ void BeanEditAction::resetBasicItems(ActionEvent* e) {
    userNameField->setText(bean->getUserName());
    commentField->setText(bean->getComment());
}

/*abstract*/ /*protected*/ QString BeanEditAction::helpTarget() {}



/*public*/ void BeanEditAction::setSelectedComponent(QWidget* c) {
    selectedTab = c;
}

/*public*/ void BeanEditAction::actionPerformed(ActionEvent* e)
{
 if (bean == NULL)
 {
  log->error("No bean set so unable to edit a NULL bean");  //IN18N
  return;
 }
 if (f == NULL)
 {
  f = new JmriJFrame("Edit " + getBeanType() + " " + bean->getDisplayName(), false, false);
  f->addHelpMenu(helpTarget(), true);
  //java.awt.Container containerPanel = f.getContentPane();
  QWidget* containerPanel = new QWidget;
  QVBoxLayout* containerPanelLayout;
  containerPanel->setLayout(containerPanelLayout = new QVBoxLayout);
  f->setCentralWidget(containerPanel);
  initPanelsFirst();
  initPanels();
  initPanelsLast();

  foreach (BeanItemPanel* bi, bei)
  {
   addToPanel(bi, bi->getListOfItems());
   detailsTab->addTab(bi, bi->getName());
  }

  containerPanelLayout->addWidget(detailsTab, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
  //QWidget* buttons = new QWidget();
  FlowLayout* buttonsLayout = new FlowLayout;
  QPushButton* applyBut = new QPushButton(tr("Apply"));
//  applyBut.addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          applyButtonAction(e);
//      }
//  });
  connect(applyBut, SIGNAL(clicked()), this, SLOT(applyButtonAction()));
  QPushButton* okBut = new QPushButton(tr("OK"));
//  okBut.addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          applyButtonAction(e);
//          f.dispose();
//      }
//  });
  connect(okBut, SIGNAL(clicked()), this, SLOT(On_okBut_clicked()));
  QPushButton* cancelBut = new QPushButton(tr("Cancel"));
//  cancelBut.addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          cancelButtonAction(e);
//      }
//  });
  connect(cancelBut, SIGNAL(clicked()), this, SLOT(cancelButtonAction()));
  buttonsLayout->addWidget(applyBut);
  buttonsLayout->addWidget(okBut);
  buttonsLayout->addWidget(cancelBut);
  containerPanelLayout->addLayout(buttonsLayout); //, BorderLayout.SOUTH);
 }
 foreach (BeanItemPanel* bi, bei)
 {
  bi->resetField();
 }
 if (selectedTab != NULL)
 {
  detailsTab->setCurrentWidget(selectedTab);
 }
 f->pack();
 f->setVisible(true);
}
void BeanEditAction::On_okBut_clicked()
{
 applyButtonAction(/*e*/);
 f->dispose();
}

/*protected*/ void BeanEditAction::applyButtonAction(ActionEvent* /*e*/) {
    save();
}

/*protected*/ void BeanEditAction::cancelButtonAction(ActionEvent* /*e*/) {
    f->dispose();
}

/**
 * Sets out the panel based upon the items passed in via the ArrayList
 */
/*protected*/ void BeanEditAction::addToPanel(QWidget* panel, QList<BeanEditItem*> items)
{
 QGridLayout* gbLayout = new QGridLayout();
 GridBagConstraints cL =  GridBagConstraints();
 GridBagConstraints cD =  GridBagConstraints();
 GridBagConstraints cR =  GridBagConstraints();
 cL.fill = GridBagConstraints::HORIZONTAL;
 cL.insets = new Insets(2, 0, 0, 15);
 cR.insets = new Insets(0, 10, 15, 15);
 cD.insets = new Insets(2, 0, 0, 0);
 cD.anchor = GridBagConstraints::NORTHWEST;
 cL.anchor = GridBagConstraints::NORTHWEST;

 int y = 0;
 QWidget* p = new QWidget();

 foreach (BeanEditItem* it, items)
 {
  if (it->getDescription() != NULL && it->getComponent() != NULL)
  {
   QLabel* decript = new QLabel(it->getDescription() + ":");
   decript->setAlignment(Qt::AlignLeft);
   if (it->getDescription()==(""))
   {
    decript->setText("");
   }
   cL.gridx = 0;
   cL.gridy = y;
   cL.ipadx = 3;

   //gbLayout.setConstraints(decript, cL);
   p->setLayout(gbLayout);
   gbLayout->addWidget(decript, cL.gridy, cL.gridx);

   cD.gridx = 1;
   cD.gridy = y;

   //gbLayout.setConstraints(it->getComponent(), cD);

   gbLayout->addWidget(it->getComponent(), cD.gridx, cD.gridy);

   cR.gridx = 2;
   cR.gridwidth = 1;
   cR.anchor = GridBagConstraints::WEST;

  }
  else
  {
   cR.anchor = GridBagConstraints::CENTER;
   cR.gridx = 0;
   cR.gridwidth = 3;
  }
  cR.gridy = y;
  if (it->getHelp() != NULL)
  {
   /*JTextPane*/JTextArea* help = new JTextArea();
   help->setText(it->getHelp());
   //gbLayout.setConstraints(help, cR);
   formatTextAreaAsLabel(help);
   gbLayout->addWidget(help, cR.gridy, cR.gridx);
  }
  y++;
 }
 if(panel->layout() == NULL)
  panel->setLayout(new QVBoxLayout);
 panel->layout()->addWidget(p);
}

void BeanEditAction::formatTextAreaAsLabel(JTextArea* pane)
{
// pane.setOpaque(false);
// pane.setEditable(false);
// pane.setBorder(NULL);
}

/*public*/ void BeanEditAction::save()
{
 foreach (BeanItemPanel* bi, bei)
 {
  bi->saveItem();
 }
}

/*static*/ bool BeanEditAction::validateNumericalInput(QString text)
{
 bool ret = true;
 if (text.length() != 0)
 {
//        try {
//            Integer.parseInt(text);
//        } catch (java.lang.NumberFormatException ex) {
//            return false;
//        }
  text.toInt(&ret);
 }
 return ret;
}



/*abstract*/ /*protected*/ QString BeanEditAction::getBeanType() {return "";}
/*abstract protected NamedBean getBySystemName(String name);*/

/*abstract*/ /*protected*/ NamedBean* BeanEditAction::getByUserName(QString name) {return NULL;}

/**
 * Generic method to change the user name of a Bean
 */
/*public*/ void BeanEditAction::renameBean(QString _newName)
{
 NamedBean* nBean = bean;
 QString oldName = nBean->getUserName();

 QString value = _newName;

 if (value==(oldName))
 {
  //name not changed.
  return;
 }
 else
 {
  NamedBean* nB = getByUserName(value);
  if (nB != NULL)
  {
   log->error("User name is not unique " + value); // NOI18N
   QString msg;
//            msg = java.text.MessageFormat.format(tr("WarningUserName"),
//                    new Object[]{("" + value)});
//            JOptionPane.showMessageDialog(NULL, msg,
//                    tr("WarningTitle"),
//                    JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(NULL, tr("Error"), tr("User Name \" %1 \" has already been used.").arg(value));
   return;
  }
 }

 nBean->setUserName(value);
 if (value!=(""))
 {
  if (oldName == NULL || oldName==(""))
  {
   if (!nbMan->inUse(nBean->getSystemName(), nBean))
   {
     return;
   }
//            String msg = java.text.MessageFormat.format(tr("UpdateToUserName"),
//                    new Object[]{getBeanType(), value, nBean.getSystemName()});
//            int optionPane = JOptionPane.showConfirmDialog(NULL,
//                    msg, tr("UpdateToUserNameTitle"),
//                    JOptionPane.YES_NO_OPTION);
//            if (optionPane == JOptionPane.YES_OPTION) {
   if(QMessageBox::question(NULL, tr("Update usage to UserName"), tr("Do you want to update references to this %1\nto use the UserName \"%2\" rather than its SystemName \"%3?\"").arg(getBeanType()).arg(value).arg(nBean->getSystemName()), QMessageBox::Yes | QMessageBox::No)!= QMessageBox::Yes)
   {
    //This will update the bean reference from the systemName to the userName
    try
    {
     nbMan->updateBeanFromSystemToUser(nBean);
    }
    catch (JmriException ex)
    {
     //We should never get an exception here as we already check that the username is not valid
    }
   }

  }
  else
  {
// TODO:   nbMan->renameBean(oldName, value, nBean);
  }

 }
 else
 {
  //This will update the bean reference from the old userName to the SystemName
  nbMan->updateBeanFromUserToSystem(nBean);
 }
}

/**
 * Generic method to remove the user name from a bean->
 */
/*public*/ void BeanEditAction::removeName()
{
// QString msg = java.text.MessageFormat.format(tr("UpdateToSystemName"),
//            new Object[]{getBeanType()});
//    int optionPane = JOptionPane.showConfirmDialog(NULL,
//            msg, tr("UpdateToSystemNameTitle"),
//            JOptionPane.YES_NO_OPTION);
//    if (optionPane == JOptionPane.YES_OPTION) {
 if(QMessageBox::question(NULL, tr("UpdateToSystemNameTitle"), tr("Do you want to update references to this %1\nto use the SystemName?").arg(getBeanType()),QMessageBox::Yes | QMessageBox::No)!= QMessageBox::Yes)
 {
  nbMan->updateBeanFromUserToSystem(bean);
 }
 bean->setUserName(NULL);
}

//At this stage we purely use this to allow the user to delete properties, but not add them, changing is possible but only for strings
//Based upon the code from the RosterMediaPane
//private static class BeanPropertiesTableModel extends AbstractTableModel {

//    /**
//     *
//     */
//    private static final long serialVersionUID = -7466799526127205872L;
//    Vector<KeyValueModel> attributes;
//    String titles[];
//    boolean wasModified;

//    private static class KeyValueModel {

        /*public*/ BeanPropertiesTableModel::KeyValueModel::KeyValueModel(QVariant k, QVariant v) {
            key = k;
            value = v;
        }
//        /*public*/ QVariant key, value;
//    }

/*public*/ BeanPropertiesTableModel::BeanPropertiesTableModel()
{
 titles = QStringList();
        titles.append(tr("Name"));
        titles.append(tr("Value"));
    }

    /*public*/ void BeanPropertiesTableModel::setModel(NamedBean* nb)
    {
     if (!nb->getPropertyKeys().isEmpty())
     {
      attributes =  QVector<KeyValueModel*>(nb->getPropertyKeys().size());
     QListIterator<QString> ite( nb->getPropertyKeys());
     while (ite.hasNext())
     {
      QString key = ite.next();
      KeyValueModel* kv = new KeyValueModel(QVariant(key), QVariant(nb->getProperty(key)));
      attributes.append(kv);
     }
    }
    else
    {
     attributes =  QVector<KeyValueModel*>(0);
    }
    _wasModified = false;
   }

/*public*/ void BeanPropertiesTableModel::updateModel(NamedBean* nb)
{
 if (!wasModified())
 {
  return; //No changed made
 }			// add and update keys
 for (int i = 0; i < attributes.size(); i++)
 {
  KeyValueModel* kv = attributes.at(i);
  if ((kv->key != QVariant()) && // only update if key value defined, will do the remove to
      ((nb->getPropertyKeys().isEmpty()) || (nb->getProperty(kv->key.toString()) == QVariant()) || (kv->value!=(nb->getProperty(kv->key.toString())))))
  {
   nb->setProperty(kv->key.toString(), kv->value);
  }
 }
 //remove undefined keys
 if (!nb->getPropertyKeys().isEmpty())
 {
  QListIterator<QString> ite( nb->getPropertyKeys());
  while (ite.hasNext())
  {
   if (!keyExist(ite.next())) // not very efficient algorithm!
   {
    //ite.remove();

   }
  }
 }
 _wasModified = false;
}

    /*private*/ bool BeanPropertiesTableModel::keyExist(QVariant k)
{
 if (k == QVariant())
 {
  return false;
 }
  for (int i = 0; i < attributes.size(); i++)
  {
   if (k==(attributes.at(i)->key))
   {
       return true;
   }
  }
  return false;
}

/*public*/ int BeanPropertiesTableModel::columnCount(const QModelIndex &/*parent*/) const
    {
        return 2;
    }

    /*public*/ int BeanPropertiesTableModel::rowCount(const QModelIndex &/*parent*/) const
{
        return attributes.size();
    }

/*public*/ QVariant  BeanPropertiesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return titles[section];
 return QVariant();
}

/*public*/ QVariant  BeanPropertiesTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
  if (row < attributes.size())
  {
   if (col == 0)
   {
    return attributes.at(row)->key;
   }
   if (col == 1)
   {
    return attributes.at(row)->value;
   }
  }
 }
 return QVariant();
}

/*public*/ bool BeanPropertiesTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 KeyValueModel* kv;
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();
  if (row < attributes.size()) // already exist?
  {
   kv = attributes.at(row);
  }
  else
  {
   kv = new KeyValueModel("", "");
  }

  if (col == 0) // update key
  //Force keys to be save as a single string with no spaces
  {
   if (!keyExist(( value).toString().replace("\\s", ""))) // if not exist
   {
       kv->key = ( value).toString().replace("\\s", "");
   } else {
       setValueAt(value.toString() + "-1", row, col); // else change key name
       return true;
   }
  }

  if (col == 1) // update value
  {
      kv->value = value;
  }
  if (row < attributes.size()) // existing one
  {
      attributes.replace(row, kv);
  } else {
      attributes.insert(row, kv); // new one
  }
  if ((col == 0) && (kv->key==(""))) {
      attributes.remove(row); // actually maybe remove
  }
  _wasModified = true;
  fireTableCellUpdated(row, col);
 }
 return false;
}

/*public*/ Qt::ItemFlags BeanPropertiesTableModel::flags(const QModelIndex &index) const
{
 return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*public*/ bool BeanPropertiesTableModel::wasModified() {
    return _wasModified;
}
//};
