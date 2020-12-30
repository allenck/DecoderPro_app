#include "audiotableaction.h"
#include "instancemanager.h"
#include "logger.h"
#include "beantableframe.h"
#include <QPushButton>
#include "audio.h"
#include "userpreferencesmanager.h"
#include "jtextfield.h"
#include "audiosourceframe.h"
#include "audiosourceframe.h"
#include "audiolistenerframe.h"
#include "audiotablepanel.h"
#include "audiotableframe.h"
#include "audiobufferframe.h"
#include <QMenuBar>
#include <QMenu>
#include <QList>
#include <QAction>
#include "systemnamecomparator.h"
#include "abstractaudiosource.h"

//AudioTableAction::AudioTableAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register an AudioTable GUI.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28746 $
 */
// /*public*/ class AudioTableAction extends AbstractTableAction {

/**
 *
 */
//private static final long serialVersionUID = 997606126554992440L;

//static final ResourceBundle rba = ResourceBundle.getBundle("jmri.jmrit.audio.swing.AudioTableBundle");

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame. Perhaps this should be changed?
 *
 * @param actionName
 */
/*public*/ AudioTableAction::AudioTableAction(QString actionName,QObject *parent) :
  AbstractTableAction(actionName, parent)
{
 //super(actionName);
 common();

 // disable ourself if there is no primary Audio manager available
 if (((AudioManager*)InstanceManager::getDefault("AudioManager")) == nullptr)
 {
  setEnabled(false);
 }
}

/**
 * Default constructor
 */
/*public*/ AudioTableAction::AudioTableAction(QObject *parent) :
  AbstractTableAction("Audio Table", parent)
{
 //this(tr("Audio Table"), parent);
 common();
}
void AudioTableAction::common()
{
 log = new Logger("AudioTableAction");
 bufferFrame = nullptr;
 sourceFrame = nullptr;
 listenerFrame = nullptr;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void AudioTableAction::addToFrame(BeanTableFrame* /*f*/)
{
 QPushButton* addSourceButton = new QPushButton(tr("Add Source..."));
 atp->addToBottomBox(addSourceButton);
// addSourceButton.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            addSourcePressed(e);
//        }
//    });
 connect(addSourceButton, SIGNAL(clicked()), this, SLOT(addSourcePressed()));
 QPushButton* addBufferButton = new QPushButton(tr("Add Buffer..."));
 atp->addToBottomBox(addBufferButton);
//    addBufferButton.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            addBufferPressed(e);
//        }
//    });
 connect(addBufferButton, SIGNAL(clicked()), this, SLOT(addBufferPressed()));
}

//@Override
/*public*/ void AudioTableAction::actionPerformed(JActionEvent * /*e*/)
{

 // create the JTable model, with changes for specific NamedBean
 createModel();

 // create the frame
// atf = new AudioTableFrame(atp, helpTarget());
// {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -7518952412034675558L;
// TODO:
//        /**
//         * Include "Add Source..." and "Add Buffer..." buttons
//         */
//        //@Override
//        void extras() {
//            addToFrame(NULL);
//        }
//    };
// setTitle();
// atf->pack();
// atf->setVisible(true);
}

/**
 * Create the JTable DataModels, along with the changes for the specific
 * case of Audio objects
 */
//@Override
/*protected*/ void AudioTableAction::createModel()
{
 // ensure that the AudioFactory has been initialised
 if (((AudioManager*)InstanceManager::getDefault("AudioManager"))->getActiveAudioFactory() == nullptr)
 {
  ((AudioManager*)InstanceManager::getDefault("AudioManager"))->init();
 }
 listener = new AudioListenerTableDataModel(this);
 buffers = new AudioBufferTableDataModel(this);
 sources = new AudioSourceTableDataModel(this);
 atp = new AudioTablePanel(listener, buffers, sources, helpTarget());
}

//@Override
/*public*/ QWidget* AudioTableAction::getPanel()
{
 createModel();
 return atp;
}

//@Override
/*protected*/ void AudioTableAction::setTitle() {
    atf->setTitle(tr("TitleAudioTable"));
}

//@Override
/*protected*/ QString AudioTableAction::helpTarget()
{
 return "package.jmri.jmrit.beantable.AudioTable";
}

//@Override
/*protected*/ void AudioTableAction::addPressed(ActionEvent* /*e*/)
{
 log->warn("This should not have happened");
}

void AudioTableAction::addSourcePressed(ActionEvent* /*e*/)
{
 if (sourceFrame == nullptr)
 {
  sourceFrame = new AudioSourceFrame(tr("Add Audio Source"), sources);
 }
 sourceFrame->updateBufferList();
 sourceFrame->resetFrame();
 sourceFrame->pack();
 sourceFrame->setVisible(true);
}

void AudioTableAction::addBufferPressed(ActionEvent* /*e*/)
{
 if (bufferFrame == nullptr)
 {
  bufferFrame = new AudioBufferFrame(tr("Add Audio Buffer"), buffers);
 }
 bufferFrame->resetFrame();
 bufferFrame->pack();
 bufferFrame->setVisible(true);
}

//@Override
/*public*/ void AudioTableAction::setMenuBar(BeanTableFrame* f)
{
 QMenuBar* menuBar = f->menuBar();

// ResourceBundle rbapps = ResourceBundle.getBundle("apps.AppsBundle");
 QList<QAction*> subElements = menuBar->actions();
 QMenu* fileMenu = nullptr;
 for (int i = 0; i < menuBar->actions().count(); i++)
 {
 //if (menuBar->actionAt(i) instanceof JMenu)
  if(qobject_cast<QMenu*>(menuBar->actions().at(i)) != nullptr)
  {
   if( ((QMenu*) menuBar->actions().at(i))->title()==(tr("File")))
   {
    fileMenu = (QMenu*) menuBar->actions().at(i);
   }
  }
 }

 if (fileMenu == nullptr) {
     return;
 }

 subElements = fileMenu->actions();
 for (int i = 0; i < subElements.length(); i++)
 {
  QList<QAction*> popsubElements = ((QMenu*)subElements.at(i))->actions();
  for (int x = 0; x < popsubElements.length(); x++)
  {
//   if (popsubElements[x] instanceof JMenuItem)
   if(qobject_cast<QMenu*>(popsubElements.at(x))!= nullptr)
   {
    if (((QMenu*) popsubElements[x])->title()==(tr("Print Table")))\
    {
     QMenu* printMenu = ((QMenu*) popsubElements[x]);
     fileMenu->removeAction((QAction*)printMenu);
     break;
    }
   }
  }
 }
 fileMenu->addAction(atp->getPrintItem());

}

/*protected*/ void AudioTableAction::editAudio(Audio* a)
{
// QThread* t;
// switch (a->getSubType())
// {
 QChar st = a->getSubType();
//        case Audio::LISTENER:
 if(st == Audio::LISTENER)
 {
  if (listenerFrame == nullptr)
  {
   listenerFrame = new AudioListenerFrame(tr("Add Audio Listener"), listener);
  }
  listenerFrame->populateFrame(a);
//  t = new Thread()
//  {
      //@Override
//      /*public*/ void run() {
  listenerFrame->pack();
  listenerFrame->setVisible(true);
  listenerFrame->toFront();
//      }
//  };
//  t = new AudioTableListenerThread(listenerFrame);
//            javax.swing.SwingUtilities.invokeLater(t);
//  t->start();
//            break;
 }
 else if(st == Audio::BUFFER)
 {
//    case Audio::BUFFER:
  if (bufferFrame == nullptr)
  {
   bufferFrame = new AudioBufferFrame(tr("Add/Edit Audio Buffer"), buffers);
  }
  bufferFrame->populateFrame(a);
//  t = new AudioTableBufferThread(bufferFrame);
//  {
//      //@Override
//      /*public*/ void run() {
   bufferFrame->pack();
   bufferFrame->setVisible(true);
   bufferFrame->toFront();
//      }
//  };
//            javax.swing.SwingUtilities.invokeLater(t);
//  t->start();
//            break;
 }
 else if(st == Audio::SOURCE)
 {
//        case Audio::SOURCE:
  if (sourceFrame == nullptr)
  {
   sourceFrame = new AudioSourceFrame(tr("Add Audio Source"), sources);
  }
  sourceFrame->updateBufferList();
  sourceFrame->populateFrame(a);
//  t = new AudioTableSourceThread(sourceFrame);
//  {
//      //@Override
//      /*public*/ void run() {
  sourceFrame->pack();
  sourceFrame->setVisible(true);
  sourceFrame->toFront();
//      }
//  };
//            javax.swing.SwingUtilities.invokeLater(t);
//  t->start();
//            break;
//        default:
//            throw new IllegalArgumentException();
 }
}

AudioTableListenerThread::AudioTableListenerThread(AudioListenerFrame *frame)
{
 this->frame = frame;
}
void AudioTableListenerThread::run()
{
 frame->pack();
 frame->setVisible(true);
}
AudioTableBufferThread::AudioTableBufferThread(AudioBufferFrame *frame)
{
 this->frame = frame;
}
void AudioTableBufferThread::run()
{
 frame->pack();
 frame->setVisible(true);
}
AudioTableSourceThread::AudioTableSourceThread(AudioSourceFrame *frame)
{
 this->frame = frame;
}
void AudioTableSourceThread::run()
{
 frame->pack();
 frame->setVisible(true);
}

//private static final Logger log = LoggerFactory.getLogger(AudioTableAction.class.getName());

/**
 * Define abstract AudioTableDataModel
 */
//abstract /*public*/ class AudioTableDataModel extends BeanTableDataModel implements PropertyChangeListener {

/**
 *
 */
//    private static final long serialVersionUID = 1263874422331471609L;


/*public*/ /*static*/ /*final*/ const int AudioTableDataModel::EDITCOL = BeanTableDataModel::NUMCOLUMN;

//@SuppressWarnings({"OverridableMethodCallInConstructor", "LeakingThisInConstructor"})
/*public*/ AudioTableDataModel::AudioTableDataModel(QChar subType, AudioTableAction* act) : BeanTableDataModel(act)
{
 // super();
 this->act = act;
 log = new Logger("AudioTableDataModel");
 this->subType = subType;
 //getManager()->addPropertyChangeListener(this);
AbstractManager* mgr = (AbstractManager*)getManager();
connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 updateSpecificNameList(subType);
}

//@Override
/*public*/ Manager* AudioTableDataModel::getManager() {
    return (Manager*)((AudioManager*)InstanceManager::getDefault("AudioManager"));
}
/*public int AudioTableDataModel::getDisplayDeleteMsg() { return InstanceManager.getDefault(jmri.UserPreferencesManager.class).getMultipleChoiceOption(getClassName(),"delete"); }
public void AudioTableDataModel::setDisplayDeleteMsg(int boo) { ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setMultipleChoiceOption(getClassName(), "delete", boo); }*/

//@Override
/*protected*/ QString AudioTableDataModel::getMasterClassName() {
 return "jmri.jmrit.beantable.AudioTableDataModel";
}

//@Override
/*public*/ NamedBean* AudioTableDataModel::getBySystemName(QString name) const {
    return ((AudioManager*)InstanceManager::getDefault("AudioManager"))->getBySystemName(name);
}

//@Override
/*public*/ NamedBean* AudioTableDataModel::getByUserName(QString name) {
    return ((AudioManager*)InstanceManager::getDefault("AudioManager"))->getByUserName(name);
}

/**
 * Update the NamedBean list for the specific sub-type
 *
 * @param subType Audio sub-type to update
 */
/*protected*/ /*synchronized*/ void AudioTableDataModel::updateSpecificNameList(QChar subType)
{
 // first, remove listeners from the individual objects
 if (!sysNameList.isEmpty())
 {
  for (int i = 0; i < sysNameList.size(); i++)
  {
   // if object has been deleted, it's not here; ignore it
   NamedBean* b = getBySystemName(sysNameList.at(i));
   if (b != nullptr)
   {
   // b.removePropertyChangeListener(this);
    disconnect(b);
   }
  }
 }
 sysNameList = ((AudioManager*)getManager())->getSystemNameList(subType);
 qSort(sysNameList.begin(), sysNameList.end(), SystemNameComparator::compare);
 // and add them back in
 for (int i = 0; i < sysNameList.size(); i++)
 {
  //getBySystemName(sysNameList.at(i))->addPropertyChangeListener(this);
  Audio* a = (Audio*)getBySystemName(sysNameList.at(i));
  connect(a->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 fireTableRowsUpdated(0, sysNameList.size()-1);
}

//@Override

/*public*/ int AudioTableDataModel::rowCount(const QModelIndex &parent) const
{
    return sysNameList.size();
}

//@Override
/*public*/ int AudioTableDataModel::columnCount(const QModelIndex &/*parent*/) const
{
 return EDITCOL + 1;
 }

//@Override
/*public*/ QVariant AudioTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  switch (section)
  {
   case VALUECOL:
    return "Description";
   case EDITCOL:
    return "";
   default:
    break;
  }
 }
 return BeanTableDataModel::headerData(section, orientation, role);
}

//    //@Override
//    /*public*/ Class<?> getColumnClass(int col) {
//        switch (col) {
//            case VALUECOL:
//                return String.class;
//            case EDITCOL:
//                return QPushButton.class;
//            case DELETECOL:
//                return (subType != Audio::LISTENER) ? QPushButton.class : String.class;
//            default:
//                return super.getColumnClass(col);
//        }
//    }

//@Override
/*public*/ QString AudioTableDataModel::getValue(QString systemName)  const
{
 Audio* m = ((AudioManager*)InstanceManager::getDefault("AudioManager"))->getBySystemName(systemName);
 return (m != nullptr) ? m->toString() : "";
}

//@Override
/*public*/ QVariant AudioTableDataModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  Audio* a;
  int row = index.row();
  int col = index.column();
  switch (col)
  {
   case SYSNAMECOL:  // slot number
       return sysNameList.at(row);
   case USERNAMECOL:  // return user name
       // sometimes, the TableSorter invokes this on rows that no longer exist, so we check
       a = (Audio*)getBySystemName(sysNameList.at(row));
       return (a != nullptr) ? a->getUserName() : "";
   case VALUECOL:
       a = (Audio*)getBySystemName(sysNameList.at(row));
       return (a != nullptr) ? getValue(a->getSystemName()) : "";
   case COMMENTCOL:
       a = (Audio*)getBySystemName(sysNameList.at(row));
       return (a != nullptr) ? a->getComment() : "";
   case DELETECOL:
       return (subType != Audio::LISTENER) ? tr("Delete") : "";
   case EDITCOL:
       return tr("Edit");
   default:
       log->error("internal state inconsistent with table requst for " + QString::number(row) + " " + QString::number(col));
       break;
  }
 }
 return BeanTableDataModel::data(index, role);
}

//@Override
/*public*/ bool AudioTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  Audio* a;
  int row = index.row();
  switch (index.column())
  {
   case EDITCOL:
    a = (Audio*)getBySystemName(sysNameList.at(row));
    act->editAudio(a);
    break;
   default:
    break;
  }
 }
 return BeanTableDataModel::setData(index, value, role);
}

//@Override
/*public*/ int AudioTableDataModel::getPreferredWidth(int col)
{
 switch (col)
 {
 case VALUECOL:
   return  JTextField(50).getPreferredSize().width();
 case EDITCOL:
  return  QPushButton(tr("Edit")).sizeHint().width();
 default:
  return BeanTableDataModel::getPreferredWidth(col);
 }
}

//@Override
/*public*/ Qt::ItemFlags AudioTableDataModel::flags(const QModelIndex &index) const
{
 Qt::ItemFlags f = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 switch (index.column())
 {
  case DELETECOL:
   return (subType != Audio::LISTENER) ? f | Qt::ItemIsEditable : Qt::NoItemFlags;
  case VALUECOL:
   return f;
  case EDITCOL:
   return f | Qt::ItemIsEditable ;
  default:
   break;
 }
 return BeanTableDataModel::flags(index);
}

//@Override
/*protected*/ void AudioTableDataModel::clickOn(NamedBean* t) {
    // Do nothing
}

//@Override
/*protected*/ void AudioTableDataModel::configValueColumn(JTable* table)
{
 // Do nothing
}

/*protected*/ void AudioTableDataModel::configEditColumn(JTable* table)
{
 // have the edit column hold a button
 setColumnToHoldButton(table, EDITCOL,
                new QPushButton(tr("Edit")));
}

//@Override
    /*protected*/ QString AudioTableDataModel::getBeanType()
{
  return "Audio";
}


/**
 * Specific AudioTableDataModel for Audio Listener sub-type
 */
///*public*/ class AudioListenerTableDataModel extends AudioTableDataModel {

/**
 *
 */
// /*private*/ static final long serialVersionUID = 2124461381030149588L;

AudioListenerTableDataModel::AudioListenerTableDataModel(AudioTableAction* act) : AudioTableDataModel(Audio::LISTENER, act)
{
 //super(Audio::LISTENER);
 this->act = act;
}

//@Override
/*protected*/ /*synchronized*/ void AudioListenerTableDataModel::updateNameList()
{
 updateSpecificNameList(Audio::LISTENER);
}
//};

/**
* Specific AudioTableDataModel for Audio Buffer sub-type
*/
///*public*/ class AudioBufferTableDataModel extends AudioTableDataModel {

/**
 *
 */
//    private static final long serialVersionUID = -8823961737671739012L;

AudioBufferTableDataModel::AudioBufferTableDataModel(AudioTableAction* act) :
 AudioTableDataModel(Audio::BUFFER, act)
{
 //super(Audio::BUFFER);
}

//@Override
/*protected*/ /*synchronized*/ void AudioBufferTableDataModel::updateNameList() {
    updateSpecificNameList(Audio::BUFFER);
}
//};

/**
 * Specific AudioTableDataModel for Audio Source sub-type
 */
///*public*/ class AudioSourceTableDataModel extends AudioTableDataModel {

/**
 *
 */
//    private static final long serialVersionUID = 8123546730548750171L;

AudioSourceTableDataModel::AudioSourceTableDataModel(AudioTableAction* act)
 : AudioTableDataModel(Audio::SOURCE, act)
{
 //super(Audio::SOURCE);
 this->act = act;
}
void AudioSourceTableDataModel::addToPopUp(QMenu *popup)
{
 popup->addSeparator();
 QAction* doPlay = new QAction("Play", this);
 popup->addAction(doPlay);
 connect(doPlay, SIGNAL(triggered()), this, SLOT(On_doPlay_triggered()));
 popup->addSeparator();
 QAction* doEdit = new QAction("Edit", this);
 popup->addAction(doEdit);
 connect(doEdit, SIGNAL(triggered()), this, SLOT(On_doEdit_triggered()));
 QAction* doDelete = new QAction("Delete", this);
 popup->addAction(doDelete);
 connect(doDelete, SIGNAL(triggered()), this, SLOT(On_doDelete_triggered()));
}
void AudioSourceTableDataModel::On_doPlay_triggered()
{
 /*final*/ NamedBean* t = getBySystemName(sysNameList.at(row));
 ((AbstractAudioSource*)t)->doPlay();
}

void AudioSourceTableDataModel:: On_doEdit_triggered()
{
 /*final*/ NamedBean* t = getBySystemName(sysNameList.at(row));
 act->editAudio((AbstractAudioSource*)t);
}

void AudioSourceTableDataModel:: On_doDelete_triggered()
{
 /*final*/ NamedBean* t = getBySystemName(sysNameList.at(row));
 deleteBean(row,1);
 //act->deleteAudio((AbstractAudioSource*)t);
}
//@Override
/*protected*/ /*synchronized*/ void AudioSourceTableDataModel::updateNameList() {
    updateSpecificNameList(Audio::SOURCE);
}
//};

//@Override
/*public*/ void AudioTableAction::setMessagePreferencesDetails()
{
    static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"))->setPreferenceItemDetails(getClassName(), "nullAudio", tr("Hide Null Audio Warning Message"));
    AbstractTableAction::setMessagePreferencesDetails();
}

//@Override
/*public*/ QString AudioTableAction::getClassDescription() {
    return tr("Audio Table");
}

//@Override
/*protected*/ QString AudioTableAction::getClassName() {
 return "jmri.jmrit.beantable.AudioTableAction";
}

