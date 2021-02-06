#include "vsdmanagerframe.h"
#include "vsdecodermanager.h"
#include <QBoxLayout>
#include "vsdcontrol.h"
#include "QPushButton"
#include "jtogglebutton.h"
#include <QSlider>
#include "vsdconfigdialog.h"
#include "propertychangeevent.h"
#include "vsdconfig.h"
#include "propertychangelistener.h"
#include "helputil.h"
#include <QMenuBar>
#include <QLabel>
#include "actionevent.h"
#include "vsdcontrol.h"
#include "rosterentry.h"
#include "vsdecoder.h"
#include "windowmenu.h"
#include <QCloseEvent>
#include "loadvsdfileaction.h"
#include "vsdpreferencesaction.h"

//VSDManagerFrame::VSDManagerFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
#if 0
/**
 * class VSDManagerFrame
 *
 * Main frame for the new GUI VSDecoder Manager Frame
 */

/*
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2011
 * @version			$Revision: 21510 $
 */
//import java.awt.Dimension;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//import java.awt.event.KeyEvent;
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//import java.util.ArrayList;
//import java.util.Arrays;
//import java.util.Collections;
//import java.util.HashMap;
//import java.util.List;
//import java.util.Map;
//import java.util.ResourceBundle;
//import javax.swing.BoxLayout;
//import javax.swing.QPushButton;
//import javax.swing.JLabel;
//import javax.swing.JMenu;
//import javax.swing.JMenuBar;
//import javax.swing.QWidget;
//import javax.swing.JSlider;
//import javax.swing.JToggleButton;
//import javax.swing.event.ChangeEvent;
//import javax.swing.event.ChangeListener;
//import javax.swing.event.EventListenerList;
//import jmri.jmrit.vsdecoder.LoadVSDFileAction;
//import jmri.jmrit.vsdecoder.LoadXmlVSDecoderAction;
//import jmri.jmrit.vsdecoder.SoundEvent;
//import jmri.jmrit.vsdecoder.StoreXmlVSDecoderAction;
//import jmri.jmrit.vsdecoder.VSDConfig;
//import jmri.jmrit.vsdecoder.VSDecoder;
//import jmri.jmrit.vsdecoder.VSDecoderManager;
//import jmri.util.JmriJFrame;
//import jmri.util.WindowMenu;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

//@SuppressWarnings("serial")
// /*public*/ class VSDManagerFrame extends JmriJFrame {

    ///*private*/ static final ResourceBundle rb = VSDSwingBundle.bundle();

#endif
/*public*/ /*static*/ /*final*/QMap<VSDManagerFrame::PropertyChangeID, QString> VSDManagerFrame::PCIDMap = QMap<VSDManagerFrame::PropertyChangeID, QString>();
#if 0
    static {
        Map<PropertyChangeID, String> aMap = new HashMap<PropertyChangeID, String>();
        PCIDMap.insert(PropertyChangeID.MUTE, "VSDMF:Mute");
        PCIDMap.insert(PropertyChangeID.VOLUME_CHANGE, "VSDMF:VolumeChange");
        PCIDMap.insert(PropertyChangeID.ADD_DECODER, "VSDMF:AddDecoder");
        PCIDMap.insert(PropertyChangeID.REMOVE_DECODER, "VSDMF:RemoveDecoder");
        PCIDMap.insert(PropertyChangeID.CLOSE_WINDOW, "VSDMF:CloseWindow");
        PCIDMap = Collections.unmodifiableMap(aMap);
    }

    // Map of Mnemonic KeyEvent values to GUI Components
    /*private*/ static final Map<String, Integer> Mnemonics = new HashMap<String, Integer>();

    static {
        // Menu
        Mnemonics.put("FileMenu", KeyEvent.VK_F);
        Mnemonics.put("EditMenu", KeyEvent.VK_E);
        // Other GUI
        Mnemonics.put("MuteButton", KeyEvent.VK_M);
        Mnemonics.put("AddButton", KeyEvent.VK_A);
        Mnemonics.put("CloseButton", KeyEvent.VK_C);

    }

    /*protected*/ EventListenerList listenerList = new javax.swing.event.EventListenerList();

#endif

///*private*/ List<JMenu> menuList;
/**
 * Constructor
 */
/*public*/ VSDManagerFrame::VSDManagerFrame(QWidget *parent) :
  JmriJFrame(false, false, parent) {
    //super(false, false);
    config = new VSDConfig();
    //this->addPropertyChangeListener((PropertyChangeListener*)VSDecoderManager::instance());
    connect(VSDecoderManager::instance(), SIGNAL(fireEvent(VSDManagerEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    log = new Logger("VSDManagerFrame");
    initGUI();
    if(PCIDMap.isEmpty())
    {
     PCIDMap.insert(MUTE, "VSDMF:Mute");
     PCIDMap.insert(VOLUME_CHANGE, "VSDMF:VolumeChange");
     PCIDMap.insert(ADD_DECODER, "VSDMF:AddDecoder");
     PCIDMap.insert(REMOVE_DECODER, "VSDMF:RemoveDecoder");
     PCIDMap.insert(CLOSE_WINDOW, "VSDMF:CloseWindow");
    }
}

/*public*/ void VSDManagerFrame::initComponents() {
    //this.initGUI();
}

/**
 * Build the GUI components
 */
/*public*/ void VSDManagerFrame::initGUI() {
 if(PCIDMap.isEmpty())
 {
  PCIDMap.insert(MUTE, "VSDMF:Mute");
  PCIDMap.insert(VOLUME_CHANGE, "VSDMF:VolumeChange");
  PCIDMap.insert(ADD_DECODER, "VSDMF:AddDecoder");
  PCIDMap.insert(REMOVE_DECODER, "VSDMF:RemoveDecoder");
  PCIDMap.insert(CLOSE_WINDOW, "VSDMF:CloseWindow");

 }
    log->debug("initGUI");
    this->setTitle(tr("Virtual Sound Decoder Manager"));
    this->buildMenu();
    //this.setLayout(new BoxLayout(this.getContentPane(), BoxLayout.PAGE_AXIS));
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    decoderPane = new QWidget();
    decoderPaneLayout = new QVBoxLayout(decoderPane);
    decoderPane->setLayout(decoderPaneLayout);
    decoderBlank = VSDControl::generateBlank();
    decoderPaneLayout->addWidget(decoderBlank);

    volumePane = new QWidget();
    QHBoxLayout* volumePaneLayout = new QHBoxLayout;
    volumePane->setLayout(/*new BoxLayout(volumePane, BoxLayout.LINE_AXIS)*/volumePaneLayout);
    JToggleButton* muteButton = new JToggleButton(tr("Mute"));
    QPushButton* addButton = new QPushButton(tr("Add"));
    QPushButton* closeButton = new QPushButton(tr("Close"));
    volume = new QSlider(Qt::Horizontal/*0, 100*/);
    volume->setMaximum(0);
    volume->setMaximum(100);
//        volume.setMinorTickSpacing(10);
//        volume.setPaintTicks(true);
    volume->setValue(80);
    volume->resize( QSize(200, 20));
    volume->setToolTip(tr("Adjust master volume for all VSDecoders"));
//        volume.addChangeListener(new ChangeListener() {
//            /*public*/ void stateChanged(ChangeEvent e) {
//                volumeChange(e);
//            }
//        });
    connect(volume, SIGNAL(valueChanged(int)), this, SLOT(volumeChange()));
    volumePaneLayout->addWidget(new QLabel(tr("Volume:")));
    volumePaneLayout->addWidget(volume);
    volumePaneLayout->addWidget(muteButton);
    muteButton->setToolTip(tr("Mute all VSDecoders"));
    //muteButton->setMnemonic(Mnemonics.get("MuteButton"));
    muteButton->setText(tr("Mute"));
//        muteButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                muteButtonPressed(e);
//            }
//        });
    connect(muteButton, SIGNAL(clicked()), this, SLOT(muteButtonPressed()));
    volumePaneLayout->addWidget(addButton);
    addButton->setToolTip(tr("Add a new VSDecoder"));
    //addButton->setMnemonic(Mnemonics.get("Add"));
    addButton->setText(tr("Add"));
//        addButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addButtonPressed(e);
//            }
//        });
    connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonPressed()));
    volumePaneLayout->addWidget(closeButton);
    closeButton->setToolTip(tr("Close this window and shut down all VSDecoders"));
    //closeButton->setMnemonic(Mnemonics.get("CloseButton"));
    closeButton->setText(tr("Close"));
//        closeButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                closeButtonPressed(e);
//            }
//        });
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonPressed()));

    centralWidgetLayout->addWidget(decoderPane);
    centralWidgetLayout->addWidget(volumePane);

    log->debug("pane size + " + QString::number(decoderPane->sizeHint().width()) + " "+ QString::number(decoderPane->sizeHint().height()));
    //this->pack();
    this->adjustSize();
    this->setVisible(true);

    log->debug("done...");
}

/**
 * Handle "Close" button press
 */
/*protected*/ void VSDManagerFrame::closeButtonPressed(JActionEvent* /*e*/) {
 firePropertyChange(CLOSE_WINDOW, QVariant(), QVariant());
    dispose();
}

/**
 * Handle "Mute" button press
 */
/*protected*/ void VSDManagerFrame::muteButtonPressed(JActionEvent* e) {
    JToggleButton* b = (JToggleButton*) e->getSource();
    log->debug("Mute button pressed. value = " + b->isSelected());
    firePropertyChange(MUTE, !b->isSelected(), b->isSelected());
}

/**
 * Handle "Add" button press
 */
/*protected*/ void VSDManagerFrame::addButtonPressed(JActionEvent* /*e*/) {
    log->debug("Add button pressed");
    config = new VSDConfig(); // Create a new Config for the new VSDecoder.
    // Do something here.  Create a new VSDecoder and add it to the window.
    VSDConfigDialog* d = new VSDConfigDialog(decoderPane, tr("Configure New VSDecoder"), config);
//        d.addPropertyChangeListener(new PropertyChangeListener() {
//            /*public*/ void propertyChange(PropertyChangeEvent event) {
//                log->debug("property change name " + event.getPropertyName() + " old " + event.getOldValue() + " new " + event.getNewValue());
//                addButtonPropertyChange(event);
//            }

//        });
    connect(d, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(addButtonPropertyChange(PropertyChangeEvent*)));
    firePropertyChange(ADD_DECODER, QVariant(), QVariant());
}

/**
 * Callback for the Config Dialog
 */
/*protected*/ void VSDManagerFrame::addButtonPropertyChange(PropertyChangeEvent* event)
{
 log->debug("internal config dialog handler");
 log->debug("New Config: " + config->toString());
 VSDecoder* newDecoder = VSDecoderManager::instance()->getVSDecoder(config);
 if (newDecoder == NULL) {
     log->debug("no New Decoder constructed!" + config->toString());
     return;
 }
 // Need to add something here... if this Control already exists, don't
 // create a new one.
 VSDControl* newControl = new VSDControl(config);
 // Set the Decoder to listen to PropertyChanges from the control
// TODO:        newControl->addPropertyChangeListener(newDecoder);
 this->addPropertyChangeListener((PropertyChangeListener*)newDecoder);
 // Set US to listen to PropertyChanges from the control (mainly for DELETE)
//        newControl.addPropertyChangeListener(new PropertyChangeListener() {
//            /*public*/ void propertyChange(PropertyChangeEvent event) {
//                log->debug("property change name " + event.getPropertyName() + " old " + event.getOldValue() + " new " + event.getNewValue());
//                vsdControlPropertyChange(event);
//            }
//        });
 connect(newControl, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(newControlPropertyChange(PropertyChangeEvent*)));
// if (decoderPane->isAncestorOf(decoderBlank))
// {
//     decoderPaneLayout->removeWidget(decoderBlank);
// }
 QObjectList ol = decoderPane->children();
 foreach(QObject* o, ol)
 {
  if(o->objectName() == "Blank")
  {
   decoderPaneLayout->removeWidget((QWidget*)o);
   o->deleteLater();
  }
 }
 newControl->addSoundButtons( QList<SoundEvent*>(newDecoder->getEventList()));
 decoderPaneLayout->addWidget(newControl);
 //debugPrintDecoderList();
 decoderPane->update();
 decoderPane->repaint();

 this->adjustSize();
 //this.setVisible(true);
 // Do we need to make newControl a listener to newDecoder?
 //firePropertyChange(PropertyChangeID.ADD_DECODER, NULL, newDecoder);
}

/**
 * Handle property change event from one of the VSDControls
 */
/*protected*/ void VSDManagerFrame::vsdControlPropertyChange(PropertyChangeEvent* event) {
    QString property = event->getPropertyName();
    if (property==(VSDControl::PCIDMap.value(VSDControl::_DELETE))) {
        QString ov = event->getOldValue().toString();
        QString nv =  event->getNewValue().toString();
        VSDecoder* vsd = VSDecoderManager::instance()->getVSDecoderByAddress(nv);
        if (vsd == NULL) {
            log->debug("VSD is NULL.");
        }
        this->removePropertyChangeListener((PropertyChangeListener*)vsd);
        log->debug("vsdControlPropertyChange: ID = " + PCIDMap.value(REMOVE_DECODER) + " Old " + ov + " New " + nv);
        firePropertyChange(REMOVE_DECODER, ov, nv);
        decoderPaneLayout->removeWidget((VSDControl*)event->getSource());
        if (decoderPaneLayout->count() == 0) {
            decoderPaneLayout->addWidget(decoderBlank);
        }
        //debugPrintDecoderList();
        decoderPane->update();
        this->pack();
        this->setVisible(true);
    }
}
#if 0
/**
 * (Debug only) Print the decoder list
 */
/*
 /*private*/ void debugPrintDecoderList() {
 log->debug("Printing Decoder Lists from VSDManagerFrame...");
 VSDecoderManager.instance().debugPrintDecoderList();
 }
 */
#endif
/**
 * Handle volume slider change
 */
/*protected*/ void VSDManagerFrame::volumeChange(ChangeEvent* e) {
    //JSlider v = (JSlider) e.getSource();
    log->debug("Volume slider moved. value = " + volume->value());
    firePropertyChange(VOLUME_CHANGE, volume->value(), volume->value());
}

/*private*/ void VSDManagerFrame::buildMenu() {
    QMenu* fileMenu = new QMenu(tr("File"));
    //fileMenu.setMnemonic(Mnemonics.get("FileMenu"));

    fileMenu->addAction(new LoadVSDFileAction(tr("Load VSD File"),this));

    QMenu* editMenu = new QMenu(tr("Edit"));
    //editMenu.setMnemonic(Mnemonics.get("EditMenu"));

    editMenu->addAction(new VSDPreferencesAction(tr("VSDecoderEditMenuPreferences"),this));

//        fileMenu->getItem(1).setEnabled(false); // disable XML store
//        fileMenu.getItem(2).setEnabled(false); // disable XML load

    menuList = QList<QMenu*>(/*3*/);

    menuList.append(fileMenu);
    menuList.append(editMenu);

    this->setMenuBar(new QMenuBar());
    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(editMenu);
    this->addHelpMenu("package.jmri.jmrit.vsdecoder.swing.VSDManagerFrame", true); // Fix this... needs to be help for the new frame

}

/**
 * Add a standard help menu, including window specific help item.
 *
 * @param ref    JHelp reference for the desired window-specific help page
 * @param direct true if the help menu goes directly to the help system,
 *               e.g. there are no items in the help menu
 *
 * WARNING: BORROWED FROM JmriJFrame.
 */
/*public*/ void VSDManagerFrame::addHelpMenu(QString ref, bool direct) {
    // only works if no menu present?
    QMenuBar* bar = menuBar();
    if (bar == NULL) {
        bar = new QMenuBar();
    }
    // add Window menu
    bar->addMenu(new WindowMenu(this)); // * GT 28-AUG-2008 Added window menu
    // add Help menu
    HelpUtil::helpMenu(bar, ref, direct);
    setMenuBar(bar);
}

/**
 * Handle window close event
 */
/*public*/ void VSDManagerFrame::windowClosing(QCloseEvent e) {
    // Call the superclass function
    //super.windowClosing(e);

    log->debug("VSDecoderFrame windowClosing() called... " /*+ e.toString()*/);

    log->debug("Calling decoderPane.windowClosing() directly "  /*+e.toString()*/);
    //decoderPane.windowClosing(e);
}

// VSDecoderManager Events
/**
 * Add a listener for this Pane's property change events
 */
/*public*/ void VSDManagerFrame::addPropertyChangeListener(PropertyChangeListener* listener)
{
#if 0
    QList<PropertyChangeListener> l = Arrays.asList(listenerList.getListeners(PropertyChangeListener.class));
    if (!l.contains(listener)) {
        listenerList.add(PropertyChangeListener.class, listener);
    }
#endif
}

/**
 * Remove a listener
 */
/*public*/ void VSDManagerFrame::removePropertyChangeListener(PropertyChangeListener* listener) {
    if (listener == NULL) {
        log->warn("No listener!");
    }
#if 0
    listenerList.remove(PropertyChangeListener.class, listener);
#endif
}

/**
 * Fire a property change from this object
 */
// NOTE: should this be /*public*/???
/*public*/ void VSDManagerFrame::firePropertyChange(PropertyChangeID id, QVariant oldProp, QVariant newProp) {
    // map the property change ID
    QString pcname = PCIDMap.value(id);
    PropertyChangeEvent* pce = new PropertyChangeEvent(this, pcname, oldProp, newProp);
    // Fire the actual PropertyChangeEvent
    log->debug("Firing property change: " + pcname);
    firePropertyChange(pce);
}

/**
 * Fire a property change from this object
 */
void VSDManagerFrame::firePropertyChange(PropertyChangeEvent* evt)
{
 if(evt == NULL)
 {
  log->warn("EVT is NULL!!");
 }
#if 0
    for (PropertyChangeListener l : listenerList.getListeners(PropertyChangeListener.class)) {
        l.propertyChange(evt);
    }
#endif
 emit notifyPropertyChange(evt);
}


/*public*/ void VSDManagerFrame::propertyChange(PropertyChangeEvent* event) {
    log->debug("property change name " + event->getPropertyName() + " old " + event->getOldValue().toString() + " new " + event->getNewValue().toString());
    addButtonPropertyChange(event);
}

/*public*/ void VSDManagerFrame::newControlPropertyChange(PropertyChangeEvent* event) {
    log->debug("property change name " + event->getPropertyName() + " old " + event->getOldValue().toString() + " new " + event->getNewValue().toString());
    vsdControlPropertyChange(event);
}

/*public*/ QString VSDManagerFrame::getClassName()
{
 return "jmri.jmrit.vsdecoder.swing.VSDManagerFrame";
}
