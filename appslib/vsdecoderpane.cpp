#include "vsdecoderpane.h"
#include "file.h"
#include "logger.h"
#include "fileutil.h"
#include "gridbagconstraints.h"
#include <QGridLayout>
#include "vsdecoderframe.h"
#include "vsdecodermanager.h"
#include "vsdconfigpanel.h"
#include "propertychangelistener.h"
#include "propertychangeevent.h"
#include "vsdecoder.h"
#include <QTabWidget>
#include "locoaddress.h"
#include "rosterentry.h"
#include "dcclocoaddress.h"
#include "vsdecoderevent.h"
#include <QSlider>
#include "jtogglebutton.h"
#include <QStatusBar>
#include "jtogglebutton.h"
#include "vsdoptionpanel.h"
#include "vsdsoundspanel.h"
#include "physicallocation.h"
#include "rosterentry.h"

//VSDecoderPane::VSDecoderPane(QWidget *parent) :
//  JmriPanel(parent)
//{
//}
/**
 * Virtual Sound Decoder for playing sounds off of LocoNet messages. Based on
 * the LocoMon tool by Bob Jacobsen
 *
 * @author	Mark Underwood Copyright (C) 2011
 * @version $Revision: 28746 $
 */
//@SuppressWarnings("serial")
///*public*/ class VSDecoderPane extends JmriPanel {

    ///*private*/ static final ResourceBundle vsdBundle = VSDecoderBundle.bundle();

/*public*/ /*static*/ /*final*/ QMap<VSDecoderPane::PropertyChangeID, QString> VSDecoderPane::PCIDMap = QMap<VSDecoderPane::PropertyChangeID, QString>();

//    static {
//        Map<PropertyChangeID, String> aMap = new HashMap<PropertyChangeID, String>();
//        PCIDMap.insert(PropertyChangeID.ADDRESS_CHANGE, "AddressChange");
//        PCIDMap.insert(PropertyChangeID.PROFILE_SELECT, "ProfileSelect");
//        PCIDMap.insert(PropertyChangeID.MUTE, "Mute");
//        PCIDMap.insert(PropertyChangeID.VOLUME_CHANGE, "VolumeChange");
//        PCIDMap = Collections.unmodifiableMap(aMap);
//    }


    /*final*/ /*static*/ QString VSDecoderPane::BASICPANEL = "Basic";
    /*final*/ /*static*/ QString VSDecoderPane::COMBOPANEL = "Sounds";
    /*final*/ /*static*/ QString VSDecoderPane::OPTIONPANEL = "Options";


    /*private*/ /*static*/ QString VSDecoderPane::VSDecoderFileLocation = NULL;

///*private*/ List<JMenu> menuList;
/**
 * Create a new VSDecoderPane
 */
/*public*/ VSDecoderPane::VSDecoderPane(VSDecoderFrame* p)  :
JmriPanel(p)
{
 //super();
 parent = p;
 decoder_mgr = VSDecoderManager::instance();
 log = new Logger("VSDecoderPane");
 if(PCIDMap.isEmpty())
 {
  PCIDMap.insert(ADDRESS_CHANGE, "AddressChange");
  PCIDMap.insert(MUTE, "Mute");
  PCIDMap.insert(VOLUME_CHANGE, "VolumeChange");
 }
}

/**
 * getFrame() Get this Pane's parent Frame
 */
/*public*/ VSDecoderFrame* VSDecoderPane::getFrame() {
    return (parent);
}

/**
 * getHelpTarget()
 *
 * Return a reference to the help file
 */
/*public*/ QString VSDecoderPane::getHelpTarget() {
    return "package.jmri.jmrix.vsdecoder.VSDecoderPane";
}

/**
 * getTitle()
 *
 * Return a suggested title for the enclosing frame.
 */
/*public*/ QString VSDecoderPane::getTitle() {
    return tr("Virtual Sound Decoder");
}

/**
 * getDefaultVSDecoderFolder()
 *
 * Return a string default default path for the VSD files
 */
/*public*/ /*static*/ QString VSDecoderPane::getDefaultVSDecoderFolder() {
    if (VSDecoderFileLocation == NULL) {
        return FileUtil::getUserFilesPath() + "vsdecoder" + File::separator;
    }
    return VSDecoderFileLocation;
}

/**
 * init() : does nothing. Here to satisfy the parent class
 */
/*public*/ void VSDecoderPane::init() {
    // Does nothing.  Here for completeness.
}

/**
 * initContext() : does nothing. Here to satisfy the parent class
 */
/*public*/ void VSDecoderPane::initContext(QObject* /*context*/) {
    // Does nothing.  Here for completeness.
}

/**
 * initComponents()
 *
 * initialzies the GUI components.
 */
/*public*/ void VSDecoderPane::initComponents()
{
 log->debug("initComponents()");
 //buildMenu();

//        setLayout(new GridBagLayout());
//        setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
 QGridLayout* g = new QGridLayout(this);

 // Add the tabbed pane to the VSDecoderPane.  The tabbedPane will contain all the other panes.
 tabbedPane = new QTabWidget();
 GridBagConstraints gbc1 = GridBagConstraints();
 gbc1.gridx = 0;
 gbc1.gridy = 0;
 gbc1.fill = GridBagConstraints::BOTH;
 gbc1.anchor = GridBagConstraints::CENTER;
 gbc1.weightx = 1.0;
 gbc1.weighty = 1.0;
 //this.add(tabbedPane, gbc1);
 g->addWidget(tabbedPane, gbc1.gridy, gbc1.gridx, gbc1.rowSpan(),gbc1.colSpan());

 //-------------------------------------------------------------------
 // configPanel
 // The configPanel holds the stuff for addressing and configuration.
 configPanel = new VSDConfigPanel(decoder_id, this);
 tabbedPane->addTab( configPanel,"Config");
#if 1
 //-------------------------------------------------------------------
 // soundsPanel
 // The optionPanel holds controls for selecting sound options.
 optionPanel = new VSDOptionPanel(decoder_id, this);

 tabbedPane->addTab(optionPanel, "Options");

 //-------------------------------------------------------------------
 // soundsPanel
 // The soundsPanel holds buttons for specific sounds.
 soundsPanel = new VSDSoundsPanel(decoder_id, this);
 tabbedPane->addTab(soundsPanel, "Sounds");

 //-------------------------------------------------------------------
 // volumePanel
 // The volumePanel holds the master volume and mute controls.
 volumePanel = new QWidget();
 //volumePanel.setLayout(new BorderLayout(10, 0));
 QHBoxLayout* volumePanelLayout = new QHBoxLayout(volumePanel);
//        TitledBorder title = BorderFactory.createTitledBorder(BorderFactory.createLoweredBevelBorder(), "Volume");
//        title.setTitlePosition(TitledBorder.DEFAULT_POSITION);
//        volumePanel.setBorder(title);

 volume = new QSlider(/*0, 100*/);
 volume->setMinimum(0);
 volume->setMaximum(100);
//        volume.setMinorTickSpacing(10);
//        volume.setPaintTicks(true);
 volume->setValue(80);
 volume->resize(QSize(200, 20));
//        volume.addChangeListener(new ChangeListener() {
//            /*public*/ void stateChanged(ChangeEvent e) {
//                volumeChange(e);
//            }
//        });
 connect(volume, SIGNAL(valueChanged(int)), this, SLOT(volumeChange()));
 volumePanelLayout->addWidget(volume, /*BorderLayout.LINE_START*/0, Qt::AlignLeft);

 mute_button = new JToggleButton("Mute");

//        mute_button.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                muteButtonPressed(e);
//            }

//        });
 connect(mute_button, SIGNAL(clicked()), this, SLOT(muteButtonPressed()));
 volumePanelLayout->addWidget(mute_button, /*BorderLayout.LINE_END*/0, Qt::AlignRight);

 GridBagConstraints gbc2 =  GridBagConstraints();
 gbc2.gridx = 0;
 gbc2.gridy = 1;
 gbc2.fill = GridBagConstraints::BOTH;
 gbc2.anchor = GridBagConstraints::CENTER;
 gbc2.weightx = 1.0;
 gbc2.weighty = 0.1;
 g->addWidget(volumePanel, gbc2.gridy, gbc2.gridx, gbc2.rowSpan(), gbc2.colSpan());

 //-------------------------------------------------------------------
 // statusBar
 // The statusBar shows decoder status.
 statusBar = new QStatusBar();
 statusBar->showMessage("Status: No decoder assigned");
 GridBagConstraints gbc3 = GridBagConstraints();
 gbc3.gridx = 0;
 gbc3.gridy = 2;
 gbc3.fill = GridBagConstraints::BOTH;
 gbc3.anchor = GridBagConstraints::PAGE_END;
 gbc3.weightx = 1.0;
 gbc3.weighty = 0.1;
 g->addWidget(statusBar, gbc3.gridy, gbc3.gridx, gbc3.rowSpan(), gbc3.colSpan());
#endif
 //-------------------------------------------------------------------
 // Pack and set visible
 //parent->pack();
 parent->adjustSize();
 parent->setVisible(true);
}

// PROPERTY CHANGE EVENT FUNCTIONS
/**
 * Handle a mute button press event
 */
// NOTE: should this be /*public*/???
/*public*/ void VSDecoderPane::muteButtonPressed(JActionEvent* /*e*/) {
    JToggleButton* b = /*(JToggleButton) e.getSource()*/mute_button;
    log->debug(tr("Mute button pressed. value = ") +( b->isSelected()?"yes":"No"));
    firePropertyChange(MUTE, !b->isSelected(), b->isSelected());
    // do something.
}

/**
 * Handle a volume slider change
 */
// NOTE: should this be /*public*/???
/*public*/ void VSDecoderPane::volumeChange(ChangeEvent* /*e*/) {
    //JSlider v = (JSlider) e.getSource();
    log->debug("Volume slider moved. value = " + volume->value());
    firePropertyChange(VOLUME_CHANGE, volume->value(), volume->value());
}
#if 0
    // VSDecoderManager Events
    /**
     * Add a listener for this Pane's property change events
     */
/*public*/ void addPropertyChangeListener(PropertyChangeListener* listener) {

        List<PropertyChangeListener> l = Arrays.asList(listenerList.getListeners(PropertyChangeListener.class));
        if (!l.contains(listener)) {
            listenerList.add(PropertyChangeListener.class, listener);
        }

    }

    /**
     * Remove a listener
     */
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener) {
        listenerList.remove(PropertyChangeListener.class, listener);
    }
#endif
/**
 * Fire a property change from this object
 */
// NOTE: should this be /*public*/???
/*public*/ void VSDecoderPane::firePropertyChange(PropertyChangeID id, QVariant oldProp, QVariant newProp) {
 QString pcname;

 // map the property change ID
 pcname = PCIDMap.value(id);
 // Fire the actual PropertyChangeEvent
 firePropertyChange(new PropertyChangeEvent(this, pcname, oldProp, newProp));
}

/**
 * Fire a property change from this object
 */
void VSDecoderPane::firePropertyChange(PropertyChangeEvent* evt) {
    //Object[] listeners = listenerList.getListenerList();

//     foreach (PropertyChangeListener* l , listenerList.getListeners("PropertyChangeListener")) {
//            l.propertyChange(evt);
//        }
 emit notifyProperyChange(evt);
}

/**
 * getDecoder()
 *
 * Looks up the currently referenced decoder and returns it.
 */
/*public*/ VSDecoder* VSDecoderPane::getDecoder() {
    VSDecoder* d = VSDecoderManager::instance()->getVSDecoderByID(decoder_id);
    //addPropertyChangeListener(d);

    return (d);
}

/**
 * getDecoder(String)
 *
 * Looks up a decoder profile by name and returns that decoder.
 */
/*public*/ VSDecoder* VSDecoderPane::getDecoder(QString profile) {
    //@SuppressWarnings("deprecation")
    VSDecoder* d = VSDecoderManager::instance()->getVSDecoder(profile);
    //addPropertyChangeListener(d);

    return (d);
}

/**
 * setDecoder()
 *
 * set the Decoder ID and update the soundsPanel
 */
/*public*/ void VSDecoderPane::setDecoder(VSDecoder* dec)
{
    if (dec != NULL) {
        // Store the new decoder
        decoder_id = dec->getID();
        log->debug("Decoder ID = " + decoder_id + " Decoder = " /*+ dec->metaObject()->className()*/);
        // Register the decoder as a listener on our frame... so it can react
        // to the window closing
//            parent.addWindowListener(new WindowListener() {
//                /*public*/ void windowActivated(WindowEvent e) {
//                }

//                /*public*/ void windowClosed(WindowEvent e) {
//                }

//                /*public*/ void windowClosing(WindowEvent e) {
//                    VSDecoderManager.instance().getVSDecoderByID(decoder_id).windowChange(e);
//                }

//                /*public*/ void windowDeactivated(WindowEvent e) {
//                }

//                /*public*/ void windowDeiconified(WindowEvent e) {
//                }

//                /*public*/ void windowIconified(WindowEvent e) {
//                }

//                /*public*/ void windowOpened(WindowEvent e) {
//                }
//            });
        // Register ourselves as an event listener to the decoder
//            dec.addEventListener(new VSDecoderListener() {
//                /*public*/ void eventAction(VSDecoderEvent e) {
//                    decoderEventAction(e);
//                }
//            });
        connect(dec, SIGNAL(notify(VSDecoderEvent*)), this, SLOT(decoderEventAction(VSDecoderEvent*)));
#if 1
        // Update the status bar
        if (dec->getPosition() != NULL)
        {
            statusBar->showMessage("Location: " + dec->getPosition()->toString());
        } else {
            statusBar->showMessage("Location: unknown");
        }
        // Update the sounds pane
        tabbedPane->removeTab(tabbedPane->indexOf(soundsPanel));
        soundsPanel = new VSDSoundsPanel(decoder_id, this);
        tabbedPane->addTab( soundsPanel, "Sounds");
        tabbedPane->update();
        //tabbedPane->repaint();
#endif
    }

}

/**
* Handle an event from the VSDecoder
*/
/*protected*/ void VSDecoderPane::decoderEventAction(VSDecoderEvent* e)
{
 // Update the status bar...
 if (e->getType() == VSDecoderEvent::LOCATION_CHANGE)
 {
  if (e->getData() != QVariant())
  {
  PhysicalLocation* p = VPtr<PhysicalLocation>::asPtr( e->getData());
   statusBar->showMessage("Location:" + p->toString());
  }
  else
  {
   statusBar->showMessage("Location: unknown");
  }
 }
}

/**
 * setAddress()
 *
 * Update the Decoder's address...
 */
/*public*/ void VSDecoderPane::setAddress(LocoAddress* a)
{
 if (a != NULL)
 {
  log->debug("Pane Set Address: " + a->toString());
  firePropertyChange(ADDRESS_CHANGE, QVariant(), VPtr<LocoAddress>::asQVariant(a));

  //VSDecoder decoder = VSDecoderManager.instance().getVSDecoderByID(decoder_id);
  //if (decoder != NULL) {
  //decoder.setAddress(a);
  //decoder.enable();
  ///}
     this->setTitle((DccLocoAddress*)a);
 }
}

/**
 * setTitle();
 *
 * Update the window title with the given address.
 */
// SHould this be /*public*/?
//@Deprecated
/*public*/ void VSDecoderPane::setTitle(DccLocoAddress* a)
{
 if (a != NULL) {
     parent->setTitle("VSDecoder - " + a->toString());
 }
}
#if 0
// New version
/*public*/ void setTitle(LocoAddress a) {
    if (a != NULL) {
        parent.setTitle("VSDecoder - " + a.toString());
    }
}

/**
 * Handle window close event
 */
/*public*/ void windowClosing(WindowEvent e) {
    log->debug("VSDecoderPane windowClosing() called...");
}
#endif
