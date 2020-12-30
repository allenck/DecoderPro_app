#include "vsdcontrol.h"
#include <QLabel>
#include <QBoxLayout>
#include <QMap>
#include "vsdconfig.h"
#include "locoaddress.h"
#include "gridbagconstraints.h"
#include "box.h"
#include <QBoxLayout>
#include <QPushButton>
#include "insets.h"
#include <QVariant>
#include "propertychangeevent.h"
#include "soundevent.h"
#include "logger.h"
#include "vsdconfigdialog.h"
#include "enginesoundevent.h"
#include "vsdoptionsdialog.h"
#include <QApplication>

//VSDControl::VSDControl(QWidget *parent) :
//  QWidget(parent)
//{
//}

/**
 * Virtual Sound Decoder for playing sounds off of LocoNet messages. Based on
 * the LocoMon tool by Bob Jacobsen
 *
 * @author	Mark Underwood Copyright (C) 2011
 * @version $Revision: 21510 $
 */
//@SuppressWarnings("serial")
// /*public*/ class VSDControl extends QWidget*{

    ///*private*/ static final ResourceBundle rb = VSDSwingBundle.bundle();


 /*public*/ /*static*/ /*final*/ QMap<VSDControl::PropertyChangeID, QString> VSDControl::PCIDMap = QMap<VSDControl::PropertyChangeID, QString>();

//    static {
//        Map<PropertyChangeID, String> aMap = new HashMap<PropertyChangeID, String>();
//        PCIDMap.insert(PropertyChangeID.ADDRESS_CHANGE, "AddressChange"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.CONFIG_CHANGE, "ConfigChange"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.OPTION_CHANGE, "OptionChange"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.PROFILE_SELECT, "ProfileSelect"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.HORN, "HornSound"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.BELL, "BellSound"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.NOTCH, "EngineNotch"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.COUPLER, "CouplerSound"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.BRAKE, "BrakeSound"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.ESTART, "EngineStart"); // NOI18N
//        PCIDMap.insert(PropertyChangeID.DELETE, "DeleteDecoder"); // NOI18N
//        PCIDMap = Collections.unmodifiableMap(aMap);
//    }


/**
 * Constructor
 */
/*public*/ VSDControl::VSDControl(QWidget *parent) :
  QFrame(parent) {
    //super();
 common();
 initComponents("");
}

/**
 * Constructor
 *
 * @param title (String) : Window title
 */
/*public*/ VSDControl::VSDControl(QString title, QWidget *parent) :
  QFrame(parent) {
   // super();
    address = title;
    config = new VSDConfig();
    common();
    initComponents(title);
}

/*public*/ VSDControl::VSDControl(VSDConfig* c, QWidget *parent)
 : QFrame(parent)
{
    //super();
    config = c;
    address = config->getLocoAddress()->toString();
    common();
    initComponents(address);
}
void VSDControl::common()
{
 if(PCIDMap.isEmpty())
 {
          PCIDMap.insert(ADDRESS_CHANGE, "AddressChange"); // NOI18N
          PCIDMap.insert(CONFIG_CHANGE, "ConfigChange"); // NOI18N
          PCIDMap.insert(OPTION_CHANGE, "OptionChange"); // NOI18N
          PCIDMap.insert(PROFILE_SELECT, "ProfileSelect"); // NOI18N
          PCIDMap.insert(HORN, "HornSound"); // NOI18N
          PCIDMap.insert(BELL, "BellSound"); // NOI18N
          PCIDMap.insert(NOTCH, "EngineNotch"); // NOI18N
          PCIDMap.insert(COUPLER, "CouplerSound"); // NOI18N
          PCIDMap.insert(BRAKE, "BrakeSound"); // NOI18N
          PCIDMap.insert(ESTART, "EngineStart"); // NOI18N
          PCIDMap.insert(_DELETE, "DeleteDecoder"); // NOI18N

 }
 this->setObjectName("VSDControl");
 soundsPanelLayout = NULL;
 log = new Logger("VSDControl");
}

/*static*/ /*public*/ QWidget* VSDControl::generateBlank()
{
 VSDControl* temp = new VSDControl("");
 QLabel* jl = new QLabel(tr("No Active Decoders"));
 jl->setMinimumSize(temp->sizeHint());
 jl->resize(temp->sizeHint());
 jl->setAlignment(Qt::AlignCenter);
 QFrame*jp = new QFrame();
 jp->setObjectName("Blank");
 QVBoxLayout* jpLayout = new QVBoxLayout;
 jp->setLayout(jpLayout);
 jpLayout->addWidget(jl, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
 jl->setMinimumSize(temp->sizeHint());
 jp->resize(temp->sizeHint());
//        jp.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createRaisedBevelBorder(),
//                BorderFactory.createLoweredBevelBorder()));
 jp->setFrameStyle(QFrame::StyledPanel);
 jp->setFrameShadow(QFrame::Raised);
 temp->deleteLater();
 return (jp);
}

/*private*/ GridBagConstraints VSDControl::setConstraints(int x, int y) {
    return (setConstraints(x, y, GridBagConstraints::HORIZONTAL, new Insets(2, 2, 2, 2), GridBagConstraints::LINE_START));
}
/*
 private GridBagConstraints VSDControl::setConstraints(int x, int y, int fill) {
 return(setConstraints(x, y, fill, new Insets(2,2,2,2), GridBagConstraints::LINE_START));
 }
 */

/*private*/ GridBagConstraints VSDControl::setConstraints(int x, int y, int fill, Insets* ins, int anchor)
{
  GridBagConstraints gbc1 = GridBagConstraints();
  gbc1.insets = ins;
  gbc1.gridx = x;
  gbc1.gridy = y;
  gbc1.weightx = 100.0;
  gbc1.weighty = 100.0;
  gbc1.gridwidth = 1;
  gbc1.anchor = anchor;
  gbc1.fill = fill;

  return (gbc1);
}

  /**
   * Initialize the GUI components
   */
/*protected*/ void VSDControl::initComponents(QString title)
{
 if(PCIDMap.isEmpty())
 {
  PCIDMap.insert(ADDRESS_CHANGE, "AddressChange"); // NOI18N
  PCIDMap.insert(CONFIG_CHANGE, "ConfigChange"); // NOI18N
  PCIDMap.insert(OPTION_CHANGE, "OptionChange"); // NOI18N
  PCIDMap.insert(PROFILE_SELECT, "ProfileSelect"); // NOI18N
  PCIDMap.insert(HORN, "HornSound"); // NOI18N
  PCIDMap.insert(BELL, "BellSound"); // NOI18N
  PCIDMap.insert(NOTCH, "EngineNotch"); // NOI18N
  PCIDMap.insert(COUPLER, "CouplerSound"); // NOI18N
  PCIDMap.insert(BRAKE, "BrakeSound"); // NOI18N
  PCIDMap.insert(ESTART, "EngineStart"); // NOI18N
  PCIDMap.insert(_DELETE, "DeleteDecoder"); // NOI18N
 }
 // TODO:
        // Create the border.
        // Could make this a titled border with the loco address as the title...
        //tb = BorderFactory.createEtchedBorder(EtchedBorder.LOWERED);
//        tb = BorderFactory.createCompoundBorder(BorderFactory.createRaisedBevelBorder(),
//                BorderFactory.createLoweredBevelBorder());

//        this.setBorder(tb);
 this->setFrameShadow(QFrame::Raised);
 this->setFrameStyle(QFrame::StyledPanel);

    //this.setLayout(new GridBagLayout());
 QGridLayout* thisLayout = new QGridLayout(this);

 // Create the buttons and slider
 soundsPanel = new QWidget();
 soundsPanel->setObjectName("SoundsPanel");
 soundsPanelLayout = new QGridLayout(soundsPanel);
 soundsPanelLayout->setObjectName("soundsPanelLayout");
 //soundsPanel.setLayout(new GridBagLayout());
 addressLabel = new QLabel(address);

 configPanel = new QWidget();
 //configPanel.setLayout(new BoxLayout(configPanel, BoxLayout.PAGE_AXIS));
 QVBoxLayout* configPanelLayout = new QVBoxLayout(configPanel);
 configButton = new QPushButton(tr("Config"));
 optionButton = new QPushButton(tr("Options"));
 deleteButton = new QPushButton(tr("Delete"));
 configPanelLayout->addWidget(configButton); // maybe don't allow this anymore.
 configPanelLayout->addWidget(Box::createHorizontalGlue());
 configPanelLayout->addWidget(optionButton);
 configPanelLayout->addWidget(Box::createHorizontalGlue());
 configPanelLayout->addWidget(deleteButton);

 QWidget* alPanel = new QWidget();
 //alPanel.setLayout(new BoxLayout(alPanel, BoxLayout.PAGE_AXIS));
 QVBoxLayout * alPanelLayout = new QVBoxLayout(alPanel);
 alPanelLayout->addWidget(addressLabel);
 alPanelLayout->addWidget(new QLabel(config->getProfileName()));

 // Add them to the panel
//        this.add(alPanel, new GridBagConstraints(0, 0, 1, 2, 100.0, 100.0,
//                GridBagConstraints.LINE_START,
//                GridBagConstraints.NONE,
//                new Insets(2, 2, 2, 2),
//                0, 0));
 GridBagConstraints gb = GridBagConstraints(0, 0, 1, 2, 100.0, 100.0,
                                                                GridBagConstraints::LINE_START,
                                                                GridBagConstraints::NONE,
                                                                new Insets(2, 2, 2, 2),
                                                                0, 0);
 thisLayout->addWidget(alPanel, gb.gridy, gb.gridx, gb.rowSpan(),gb.colSpan());
 thisLayout->addWidget(soundsPanel, 1, 0);
 thisLayout->addWidget(configPanel, 1, 1);

//        optionButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                optionButtonPressed(e);
//            }

//        });
 connect(optionButton, SIGNAL(clicked()), this, SLOT(optionButtonPressed()));
//        configButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                configButtonPressed(e);
//            }

//        });
 connect(configButton, SIGNAL(clicked()), this, SLOT(configButtonPressed()));
//        deleteButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                deleteButtonPressed(e);
//            }
//
//        });

 connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonPressed()));
 this->setVisible(true);
}

 /**
  * Add buttons for the selected Profile's defined sounds
  */
 /*public*/ void VSDControl::addSoundButtons(QList<SoundEvent*> elist)
 {
#if 1 // TODO:
  //soundsPanel->removeAll();
  QObjectList ol = soundsPanelLayout->children();
  foreach (QObject* o, ol)
  {
   if(qobject_cast<QWidget*>(o) != NULL)
   {
    soundsPanelLayout->removeWidget((QWidget*)o);
    delete o;
   }
  }

//  soundsPanelLayout = new QGridLayout(soundsPanel);
//  soundsPanelLayout->setObjectName("soundsPanelLayout");
  GridBagConstraints gbc =  GridBagConstraints();
  gbc.gridy = 1;
  gbc.gridx = 1;
  gbc.gridwidth = elist.size() - 1;
  gbc.fill = GridBagConstraints::NONE;
  gbc.anchor = GridBagConstraints::LINE_START;

  foreach (SoundEvent* e,  elist)
  {
   if (e->getButton() != NULL)
   {
    log->debug(tr("adding button ") + e->getButton()->metaObject()->className() );
    QWidget* jc = e->getButton();
    log->debug("button-label = "+ ((QAbstractButton*)jc)->text());
    if(qobject_cast<QPushButton*>(jc))
     log->debug("button label: " + ((QPushButton*)jc)->text());
    // Force the EngineSoundEvent to the second row.
    //if (e instanceof EngineSoundEvent) {
    if(qobject_cast<EngineSoundEvent*>(e) != NULL)
    {
      soundsPanelLayout->addWidget((QWidget*)e->getEnginePane(), 1, gbc.gridx,1,3);
    }
    else
    {
     gbc.gridy = 0;
     soundsPanelLayout->addWidget(jc, 0, gbc.gridx++/*, gbc.rowSpan(), gbc.colSpan()*/);
    }
   }
   if(e->getEnginePane() != NULL)
   {
    soundsPanelLayout->addWidget((QWidget*)e->getEnginePane(), 1, 0,1,3);
   }
   qApp->processEvents();
  }
#endif
 }

/**
 * Handle "Option" button presses
 */
/*protected*/ void VSDControl::optionButtonPressed(JActionEvent* /*e*/) {
    log->debug("(" + address + ") Option Button Pressed");

    VSDOptionsDialog* d = new VSDOptionsDialog(this, tr("Options") + " " + this->address);
//        d.addPropertyChangeListener(new PropertyChangeListener() {
//            /*public*/ void propertyChange(PropertyChangeEvent event) {
//                log.debug("property change name " + event.getPropertyName() + " old " + event.getOldValue() + " new " + event.getNewValue());
//                optionsDialogPropertyChange(event);
//            }

//        });
    connect(d, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(optionsDialogPropertyChange(PropertyChangeEvent*)));
}

/**
 * Handle "Config" button presses
 */
/*protected*/ void VSDControl::configButtonPressed(JActionEvent* /*e*/) {
    log->debug("(" + address + ") Config Button Pressed");
    VSDConfigDialog* d = new VSDConfigDialog(this, tr("ConfigDialogTitlePrefix") + " " + this->address, config);
//        d.addPropertyChangeListener(new PropertyChangeListener() {
//            /*public*/ void propertyChange(PropertyChangeEvent event) {
//                log.debug("property change name " + event.getPropertyName() + " old " + event.getOldValue() + " new " + event.getNewValue());
//                configDialogPropertyChange(event);
//            }

//        });
    connect(d, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(configDialogPropertyChange(PropertyChangeEvent*)));
}

/**
 * Handle "Delete" button presses
 */
/*protected*/ void VSDControl::deleteButtonPressed(JActionEvent* /*e*/) {
    log->debug("(" + address + ") Delete Button Pressed");
    firePropertyChange(_DELETE, address, address);
}

/**
 * Callback for the Config Dialog
 */
/*protected*/ void VSDControl::configDialogPropertyChange(PropertyChangeEvent* event) {
    log->debug("internal config dialog handler");
    firePropertyChange(CONFIG_CHANGE, event->getOldValue(), event->getNewValue());
}

/**
 * Callback for the Config Dialog
 */
/*protected*/ void VSDControl::optionsDialogPropertyChange(PropertyChangeEvent* event) {
    log->debug("internal options dialog handler");
    firePropertyChange(OPTION_CHANGE, event->getOldValue(), event->getNewValue());
}
#if 0
// VSDecoderManager Events
/**
 * Add a listener for this Pane's property change events
 */
/*public*/ void addPropertyChangeListener(PropertyChangeListener listener) {
    List<PropertyChangeListener> l = Arrays.asList(listenerList.getListeners(PropertyChangeListener.class));
    if (!l.contains(listener)) {
        listenerList.add(PropertyChangeListener.class, listener);
    }
}

/**
 * Remove a listener
 */
/*public*/ void removePropertyChangeListener(PropertyChangeListener listener) {
    listenerList.remove(PropertyChangeListener.class, listener);
}
#endif
/**
 * Fire a property change from this object
 */
// NOTE: should this be /*public*/???
/*public*/ void VSDControl::firePropertyChange(PropertyChangeID id, QVariant oldProp, QVariant newProp) {
    QString pcname;

    // map the property change ID
    pcname = PCIDMap.value(id);
    // Fire the actual PropertyChangeEvent
    firePropertyChange(new PropertyChangeEvent(this, pcname, oldProp, newProp));
}

/**
 * Fire a property change from this object
 */
void VSDControl::firePropertyChange(PropertyChangeEvent* evt) {
    //Object[] listeners = listenerList.getListenerList();

//        for (PropertyChangeListener l : listenerList.getListeners(PropertyChangeListener.class)) {
//            l.propertyChange(evt);
//        }
 emit propertyChange(evt);
}

