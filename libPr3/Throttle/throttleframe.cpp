#include "throttleframe.h"
#include "fileutil.h"
#include "throttleframemanager.h"
#include "jfilechooser.h"
#include "loadxmlconfigaction.h"
#include "speedpanel.h"
#include "controlpanel.h"
#include "addresspanel.h"
#include "xmlfile.h"
#include "loggerfactory.h"
#include "functionbutton.h"
#include "throttlespreferences.h"
#include "throttleslistpanel.h"
#include "throttlestablemodel.h"
#include "joptionpane.h"
#include "storexmlconfigaction.h"

/**
 * Should be named ThrottlePanel but was already existing with that name and
 * don't want to break dependencies (particularly in Jython code)
 *
 * @author Glen Oberhauser
 * @author Andrew Berridge Copyright 2010
 */
///*public*/ class ThrottleFrame extends JDesktopPane implements ComponentListener, AddressListener {

#if 0
    /*private*/ static /*final*/ int NEXT_FRAME_KEY = KeyEvent.VK_RIGHT;
    /*private*/ static /*final*/ int PREV_FRAME_KEY = KeyEvent.VK_LEFT;

    /*private*/ static /*final*/ int ADDRESS_PANEL_INDEX = 0;
    /*private*/ static /*final*/ int CONTROL_PANEL_INDEX = 1;
    /*private*/ static /*final*/ int FUNCTION_PANEL_INDEX = 2;
    /*private*/ static /*final*/ int SPEED_DISPLAY_INDEX = 3;
    /*private*/ static /*final*/ int NUM_FRAMES = 4;

    /*private*/ JInternalFrame[] frameList;
    /*private*/ int activeFrame;
#endif

    /*private*/ /*static*/ /*final*/ QString ThrottleFrame::DEFAULT_THROTTLE_FILENAME = "JMRI_ThrottlePreference.xml";

    /*public*/ static QString ThrottleFrame::getDefaultThrottleFolder() {
        return FileUtil::getUserFilesPath() + "throttle" + File::separator;
    }

    /*public*/ static QString ThrottleFrame::getDefaultThrottleFilename() {
        return getDefaultThrottleFolder() + DEFAULT_THROTTLE_FILENAME;
    }

    /*public*/ ThrottleFrame::ThrottleFrame(ThrottleWindow* tw) {
        //super();
        throttleWindow = tw;
        initGUI();
        ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesListPanel().getTableModel().addThrottleFrame(this);
    }

    /*public*/ ThrottleWindow* ThrottleFrame::getThrottleWindow() {
        return throttleWindow;
    }

    /*public*/ ControlPanel* ThrottleFrame::getControlPanel() {
        return controlPanel;
    }

    /*public*/ FunctionPanel* ThrottleFrame::getFunctionPanel() {
        return functionPanel;
    }

    /*public*/ AddressPanel* ThrottleFrame::getAddressPanel() {
        return addressPanel;
    }

    /*public*/ RosterEntry* ThrottleFrame::getRosterEntry() {
        return addressPanel->getRosterEntry();
    }

    /*public*/ void ThrottleFrame::toFront() {
        if (throttleWindow == nullptr) {
            return;
        }
        throttleWindow->toFront(title);
    }

    /*public*/ SpeedPanel* ThrottleFrame::getSpeedPanel() {
        return speedPanel;
    }

    /**
     * Sets the location of a throttle frame on the screen according to x and y
     * coordinates
     *
     * @see java.awt.Component#setLocation(int, int)
     */
    //@Override
    /*public*/ void ThrottleFrame::setLocation(int x, int y) {
        if (throttleWindow == nullptr) {
            return;
        }
        throttleWindow->setLocation(QPoint(x, y));
    }

    /*public*/ void ThrottleFrame::setTitle(QString txt) {
        title = txt;
    }

    /*public*/ QString ThrottleFrame::getTitle() {
        return title;
    }

    /*private*/ void ThrottleFrame::saveThrottle(QString sfile) {
 // Save throttle: title / window position
 // as strongly linked to extended throttles and roster presence, do not save function buttons and background window as they're stored in the roster entry
 XmlFile* xf = new XmlFile()/*{}*/;   // odd syntax is due to XmlFile being abstract
 xf->makeBackupFile(sfile);
 File* file=new File(sfile);
 try
 {
  //The file does not exist, create it before writing
  File* parentDir=file->getParentFile();
  if(!parentDir->exists())
      if (!parentDir->mkdir()) // make directory and check result
          log->error("could not make parent directory");
  if (!file->createNewFile()) // create file, check success
      log->error("createNewFile failed");
 } catch (Exception exp) {
     log->error("Exception while writing the throttle file, may not be complete: "+exp.getMessage());
 }

 try {
     //QDomElement root = doc.createElement("throttle-config");
     QDomElement root;
//     root.setTagName("throttle-config");
//     QDomDocument doc = XmlFile::newDocument(root, XmlFile::dtdLocation+"throttle-config.dtd");
  doc = QDomDocument("throttle-config");
  QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
  doc.appendChild(xmlProcessingInstruction);
  xmlProcessingInstruction = doc.createProcessingInstruction("throttle-config", XmlFile::dtdLocation+"throttle-config.dtd");
  doc.appendChild(xmlProcessingInstruction);
    // add XSLT processing instruction
     // <?xml-stylesheet type="text/xsl" href="XSLT/throttle.xsl"?>
     QDomProcessingInstruction inst = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\" href=\"/xml/XSLT/throttle.xsl\"");

     doc.appendChild(inst);
     root = doc.createElement("throttle-config");
/*			java.util.Map<String,String> m = new java.util.HashMap<String,String>();
     m.put("type", "text/xsl");
     m.put("href", jmri.jmrit.XmlFile.xsltLocation+"throttle.xsl");
     ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m);
     doc.addContent(0,p);*/
     doc.appendChild(root);
     QDomElement throttleElement = getXml();
     // don't save the loco address or consist address
//			throttleElement.getChild("AddressPanel").removeChild("locoaddress");
//			throttleElement.getChild("AddressPanel").removeChild("locoaddress");
     if ((this->getRosterEntry() != NULL) && (getDefaultThrottleFolder()+ addressPanel->getRosterEntry()->getId().trimmed() +".xml")== (sfile))
         // don't save function buttons labels, they're in roster entry
         throttleElement.firstChildElement("FunctionPanel").removeAttribute("FunctionButton");

     root.appendChild(throttleElement);
     xf->writeXML(file, doc);
     setLastUsedSaveFile(sfile);
 }
 catch (Exception ex){
     log->warn("Exception while storing throttle xml: "+ex.getMessage());
 }
    }

    /*public*/ void ThrottleFrame::loadThrottle(QString sfile) {
 if (sfile == "")
 {
  JFileChooser* fileChooser = XmlFile::userFileChooser(tr("Xml files"), "xml");
  fileChooser->setCurrentDirectory(new File(getDefaultThrottleFolder()));
  fileChooser->setDialogType(JFileChooser::OPEN_DIALOG);
  File* file = LoadXmlConfigAction::getFile(fileChooser);
  if (file == NULL) return;
  sfile = file->getAbsolutePath();
  if (sfile == NULL) return;
 }

 bool switchAfter = false;
 if (! isEditMode) {
     switchMode();
     switchAfter = true;
 }
 XmlFile* xf = new XmlFile();   // odd syntax is due to XmlFile being abstract
 File* f=new File(sfile);

 try
 {
  if(!f->exists())
   throw  FileNotFoundException(tr("file %1 not found").arg(sfile));
  if(f->exists())
  {
     QDomElement root = xf->rootFromFile(f);
     QDomElement conf = root.firstChildElement("ThrottleFrame");
     // File looks ok
     setLastUsedSaveFile(sfile);
     // close all existing Jynstruments
#if 0
     Component[] cmps = getComponents();
     for (int i=0; i<cmps.length; i++) {
         try {
             if (cmps[i] instanceof JInternalFrame) {
                 JInternalFrame jyf = (JInternalFrame) cmps[i];
                 Component[] cmps2 = jyf.getContentPane().getComponents();
                 for (int j=0; j<cmps2.length; j++) {
                     if (cmps2[j] instanceof Jynstrument) {
                         ((Jynstrument)cmps2[j]).exit();
                         jyf.dispose();
                     }
                 }
             }
         } catch (Exception ex) {
             log.debug("Got exception (no panic) "+ex);
         }
     }
#endif
     // and finally load all preferences
     setXml(conf);
  }
 }
 catch (FileNotFoundException ex)
 {
//           if (log->isDebugEnabled())
  log->debug("Loading throttle exception: " + ex.getMessage());
 }
 catch (Exception ex) {
     if (log->isDebugEnabled())
         log->debug("Loading throttle exception: " + ex.getMessage());
 }

//    	checkPosition();
 if (switchAfter) {
     switchMode();
 }
 return ;
    }

/**
* Place and initialize the GUI elements.
* <ul>
* <li> ControlPanel
* <li> FunctionPanel
* <li> AddressPanel
* <li> SpeedPanel
* <li> JMenu
* </ul>
*/
/*private*/ void ThrottleFrame::initGUI() {
   /*final*/ ThrottlesPreferences* preferences =
       ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences();
   frameListener = new FrameListener();

   controlPanel = new ControlPanel();
//   controlPanel->setResizable(true);
//   controlPanel->setClosable(true);
//   controlPanel->setIconifiable(true);
//   controlPanel->setTitle(tr("Control Panel"));
//   controlPanel->pack();
//   controlPanel->setVisible(true);
//   controlPanel->setEnabled(false);
//   controlPanel->addInternalFrameListener(frameListener);
   controlPanel->setObjectName(QString::fromUtf8("controlPanel"));
   controlPanel->setWindowTitle(tr("Control Panel"));
   controlPanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
   this->addDockWidget(static_cast<Qt::DockWidgetArea>(Qt::LeftDockWidgetArea), controlPanel);
   connect(this, SIGNAL(throttleWindowupdate(PropertyChangeEvent*)), controlPanel, SLOT(propertyChange(PropertyChangeEvent*)));

   functionPanel = new FunctionPanel();
//   functionPanel->setResizable(true);
//   functionPanel->setClosable(true);
//   functionPanel->setIconifiable(true);
//   functionPanel->setTitle(tr("FunctionPanel"));

   // assumes button width of 54, height of 30 (set in class FunctionButton) with
   // horiz and vert gaps of 5 each (set in FunctionPanel class)
   // with 3 buttons across and 6 rows high
   int width = 3 * (FunctionButton::BUT_WDTH) + 2 * 3 * 5 + 10;   // = 192
   int height = 6 * (FunctionButton.BUT_HGHT) + 2 * 6 * 5 + 20; // = 240 (but there seems to be another 10 needed for some LAFs)

   if (preferences.isUsingIcons()) {
       width = FunctionButton.BUT_WDTH * 3 + 2 * 3 * 5 + 10;
       height = FunctionButton.BUT_IMG_SIZE * 2 + FunctionButton.BUT_HGHT * 4 + 2 * 6 * 5 + 20;
   }
//   functionPanel->setSize(width, height);
//   functionPanel->setLocation(controlPanel->getWidth(), 0);
//   functionPanel->setVisible(true);
//   functionPanel->setEnabled(false);
//   functionPanel->addInternalFrameListener(frameListener);
   functionPanel->setAllowedAreas(Qt::TopDockWidgetArea | Qt::RightDockWidgetArea);
   this->addDockWidget(static_cast<Qt::DockWidgetArea>(Qt::TopDockWidgetArea), functionPanel);
   connect(this, SIGNAL(throttleWindowupdate(PropertyChangeEvent*)), functionPanel, SLOT(propertyChange(PropertyChangeEvent*)));

   speedPanel = new SpeedPanel();
//   speedPanel->setResizable(true);
//   speedPanel->setVisible(false);
//   speedPanel->setClosable(true);
//   speedPanel->setIconifiable(true);
//   speedPanel->setTitle(Bundle.getMessage("ThrottleMenuViewSpeedPanel"));
//   speedPanel->pack();
   speedPanel->setAllowedAreas(Qt::AllDockWidgetAreas);
   this->addDockWidget(static_cast<Qt::DockWidgetArea>(Qt::BottomDockWidgetArea), speedPanel);

   addressPanel = new AddressPanel();
//   addressPanel->setResizable(true);
//   addressPanel->setClosable(true);
//   addressPanel->setIconifiable(true);
//   addressPanel->setTitle(Bundle.getMessage("ThrottleMenuViewAddressPanel"));
//   addressPanel->pack();
   //                if (addressPanel->getWidth()<functionPanel->getWidth()) {addressPanel->setSize(functionPanel->getWidth(),addressPanel->getHeight());}
//   addressPanel->setLocation(controlPanel->getWidth(), functionPanel->getHeight());
//   addressPanel->setVisible(true);
//   addressPanel->addInternalFrameListener(frameListener);
   addressPanel->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea);
   this->addDockWidget(static_cast<Qt::DockWidgetArea>(Qt::RightDockWidgetArea ), addressPanel,Qt::Horizontal);
   connect(this, SIGNAL(throttleWindowupdate(PropertyChangeEvent*)), addressPanel, SLOT(propertyChange(PropertyChangeEvent*)));

   functionPanel->setAddressPanel(addressPanel); // so the function panel can get access to the roster
   controlPanel->setAddressPanel(addressPanel);
   speedPanel->setAddressPanel(addressPanel);

   if (controlPanel->height() < functionPanel->height() + addressPanel->height()) {
       controlPanel->resize(controlPanel->width(), functionPanel->height() + addressPanel->height());
   }
   if (controlPanel->height() > functionPanel->height() + addressPanel->height()) {
       addressPanel->resize(addressPanel->width(), controlPanel->height() - functionPanel->height());
   }
   if (!(preferences->isUsingIcons())
           && (functionPanel->width() < addressPanel->width())) {
       functionPanel->resize(addressPanel->width(), functionPanel->height());
   }
   // SpotBugs flagged the following (apparently correctly) as a
   // useless control statement, so it has been commented out.
   //if (!(preferences.isUsingIcons())
   //        && (functionPanel->getWidth() < addressPanel->getWidth())) {
   //}

   speedPanel->resize(addressPanel->width() + controlPanel->width(), addressPanel->height() / 2);
   speedPanel->setLocation(0, controlPanel->height());

   addressPanel->addAddressListener(controlPanel);
   addressPanel->addAddressListener(functionPanel);
   addressPanel->addAddressListener(speedPanel);
   addressPanel->addAddressListener(this);
   addressPanel->addAddressListener(((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager")).getThrottlesListPanel().getTableModel());

//   add(controlPanel, PANEL_LAYER_FRAME);
//   add(functionPanel, PANEL_LAYER_FRAME);
//   add(addressPanel, PANEL_LAYER_FRAME);
//   add(speedPanel, PANEL_LAYER_FRAME);

   if (preferences->isUsingExThrottle()) {
       /*         if ( preferences.isUsingTransparentCtl() ) {
        setTransparent(functionPanel);
        setTransparent(addressPanel);
        setTransparent(controlPanel);
        }*/
       if (preferences->isUsingRosterImage()) {
           backgroundPanel = new BackgroundPanel();
           backgroundPanel->setAddressPanel(addressPanel); // reusing same way to do it than existing thing in functionPanel
//           addComponentListener(backgroundPanel); // backgroudPanel warned when desktop resized
           addressPanel->addAddressListener(backgroundPanel);
           addressPanel->setBackgroundPanel(backgroundPanel); // so that it's changeable when browsing through rosters
           add(backgroundPanel, BACKPANEL_LAYER);
       }
//       addComponentListener(this); // to force sub windows repositionning
   }

//   frameList = new JInternalFrame[NUM_FRAMES];
//   frameList[ADDRESS_PANEL_INDEX] = addressPanel;
//   frameList[CONTROL_PANEL_INDEX] = controlPanel;
//   frameList[FUNCTION_PANEL_INDEX] = functionPanel;
//   frameList[SPEED_DISPLAY_INDEX] = speedPanel;
//   activeFrame = ADDRESS_PANEL_INDEX;

   resize(QSize(qMax(controlPanel->width() + functionPanel->width(), controlPanel->width() + addressPanel->width()),
           qMax(addressPanel->height() + functionPanel->height(), controlPanel->height())));
#if 0
   // #JYNSTRUMENT# Bellow prepare drag'n drop receptacle:
   new URIDrop(this, new Listener() {
       @Override
       /*public*/ void URIsDropped(java.net.URI[] files) {
           if (isEditMode) {
               for (java.net.URI file : files) {
                   ynstrument(file.getPath());
               }
           }
       }
   });

   KeyListenerInstaller.installKeyListenerOnAllComponents(new FrameCyclingKeyListener(), this);
   try {
       addressPanel->setSelected(true);
   } catch (PropertyVetoException ex) {
       log.error("Error selecting InternalFrame: {}", ex.getMessage());
   }
#endif
}
#if 0
// #JYNSTRUMENT# here instantiate the Jynstrument, put it in a component, initialize the context and start it
/*public*/ JInternalFrame ynstrument(String path) {
   if (path == null) {
       return null;
   }
   Jynstrument it = JynstrumentFactory.createInstrument(path, this); // everything is there
   if (it == null) {
       log.error("Error while creating Jynstrument {}", path);
       return null;
   }
   setTransparentBackground(it);
   JInternalFrame newiFrame = new JInternalFrame(it.getClassName());
   newiFrame.add(it);
   newiFrame.addInternalFrameListener(frameListener);
   newiFrame.setDoubleBuffered(true);
   newiFrame.setResizable(true);
   newiFrame.setClosable(true);
   newiFrame.setIconifiable(true);
   newiFrame.getContentPane().addContainerListener(new ContainerListener() {
       @Override
       /*public*/ void componentAdded(ContainerEvent e) {
       }

       @Override
       /*public*/ void componentRemoved(ContainerEvent e) {
           Container c = e.getContainer();
           while ((!(c instanceof JInternalFrame)) && (!(c instanceof TranslucentJPanel))) {
               c = c.getParent();
           }
           c.setVisible(false);
           remove(c);
           repaint();
       }
   });
   newiFrame.pack();
   add(newiFrame, PANEL_LAYER_FRAME);
   newiFrame.setVisible(true);
   return newiFrame;
}

// make sure components are inside this frame bounds
/*private*/ void checkPosition(Component comp) {
   if ((this.getWidth() < 1) || (this.getHeight() < 1)) {
       return;
   }

   Rectangle pos = comp.getBounds();

   if (pos.width > this.getWidth()) { // Component largest than container
       pos.width = this.getWidth() - 2;
       pos.x = 1;
   }
   if (pos.x + pos.width > this.getWidth()) // Component to large
   {
       pos.x = this.getWidth() - pos.width - 1;
   }
   if (pos.x < 0) // Component to far on the left
   {
       pos.x = 1;
   }

   if (pos.height > this.getHeight()) { // Component higher than container
       pos.height = this.getHeight() - 2;
       pos.y = 1;
   }
   if (pos.y + pos.height > this.getHeight()) // Component to low
   {
       pos.y = this.getHeight() - pos.height - 1;
   }
   if (pos.y < 0) // Component to high
   {
       pos.y = 1;
   }

   comp.setBounds(pos);
}

/*public*/ void makeAllComponentsInBounds() {
   Component[] cmps = getComponents();
   for (Component cmp : cmps) {
       checkPosition(cmp);
   }
}

/*private*/ HashMap<Container, JInternalFrame> contentPanes;

/*private*/ static class TranslucentJPanel extends JPanel {

   /*private*/ /*final*/ Color TRANS_COL = new Color(100, 100, 100, 100);

   /*public*/ TranslucentJPanel() {
       super();
       setOpaque(false);
   }

   @Override
   /*public*/ void paintComponent(Graphics g) {
       g.setColor(TRANS_COL);
       g.fillRoundRect(0, 0, getSize().width, getSize().height, 10, 10);
       super.paintComponent(g);
   }
}

/*private*/ void playRendering() {
   Component[] cmps = getComponentsInLayer(PANEL_LAYER_FRAME);
   contentPanes = new HashMap<>();
   for (Component cmp : cmps) {
       if ((cmp instanceof JInternalFrame) && (cmp.isVisible())) {
           JInternalFrame jif = (JInternalFrame) cmp;
           Dimension cpSize = jif.getContentPane().getSize();
           Point cpLoc = jif.getContentPane().getLocationOnScreen();
           TranslucentJPanel pane = new TranslucentJPanel();
           pane.setLayout(new BorderLayout());
           contentPanes.put(pane, jif);
           pane.add(jif.getContentPane(), BorderLayout.CENTER);
           setTransparent(pane, true);
           jif.setContentPane(new JPanel());
           jif.setVisible(false);
           Point loc = new Point(cpLoc.x - this.getLocationOnScreen().x, cpLoc.y - this.getLocationOnScreen().y);
           add(pane, PANEL_LAYER_PANEL);
           pane.setLocation(loc);
           pane.setSize(cpSize);
       }
   }
}

/*private*/ void editRendering() {
   Component[] cmps = getComponentsInLayer(PANEL_LAYER_PANEL);
   for (Component cmp : cmps) {
       if (cmp instanceof JPanel) {
           JPanel pane = (JPanel) cmp;
           JInternalFrame jif = contentPanes.get(pane);
           jif.setContentPane((Container) pane.getComponent(0));
           setTransparent(jif, false);
           jif.setVisible(true);
           remove(pane);
       }
   }
}

/*public*/ void setEditMode(boolean mode) {
   if (mode == isEditMode)
       return;
   if (isVisible()) {
       if (!mode) {
           playRendering();
       } else {
           editRendering();
       }
       isEditMode = mode;
       willSwitch = false;
   } else {
       willSwitch = true;
   }
   throttleWindow.updateGUI();
}

/*public*/ boolean getEditMode() {
   return isEditMode;
}

/**
* @deprecated since 4.19.5; use {@link #setEditMode(boolean)} instead
*/
@Deprecated
/*public*/ void switchMode() {
   setEditMode(!isEditMode);
}
#endif
/**
* Handle my own destruction.
* <ol>
* <li> dispose of sub windows.
* <li> notify my manager of my demise.
* </ol>
*/
/*public*/ void ThrottleFrame::dispose() {
   log->debug(tr("Disposing %1").arg(getTitle()));
   addressPanel->removeAddressListener(this);
   ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesListPanel()->getTableModel()->removeThrottleFrame(this, addressPanel->getCurrentAddress());
   // check for any special disposing in InternalFrames
   controlPanel->destroy();
   functionPanel->destroy();
   speedPanel->destroy();
   // dispose of this last because it will release and destroy throttle.
   addressPanel->destroy();
}

/*public*/ void ThrottleFrame::saveRosterChanges() {
   RosterEntry* rosterEntry = addressPanel->getRosterEntry();
   if (rosterEntry == nullptr) {
       JOptionPane::showMessageDialog(this, tr("Select loco using roster menu in Address Panel"), tr("No roster entry selected"), JOptionPane::ERROR_MESSAGE);
       return;
   }
   if (JOptionPane::showConfirmDialog(this, tr("Update roster entry with function buttons changes?"), tr("Update roster entry"), JOptionPane::YES_NO_OPTION) != JOptionPane.YES_OPTION) {
       return;
   }
   functionPanel->saveFunctionButtonsToRoster(rosterEntry);
   controlPanel->saveToRoster(rosterEntry);
}
#if 0
/**
* An extension of InternalFrameAdapter for listening to the closing of of
* this frame's internal frames.
*
* @author glen
*/
class FrameListener extends InternalFrameAdapter {

   /**
    * Listen for the closing of an internal frame and set the "View" menu
    * appropriately. Then hide the closing frame
    *
    * @param e The InternalFrameEvent leading to this action
    */
   @Override
   /*public*/ void internalFrameClosing(InternalFrameEvent e) {
       if (e.getSource() == controlPanel) {
           throttleWindow.getViewControlPanel().setSelected(false);
           controlPanel->setVisible(false);
       } else if (e.getSource() == addressPanel) {
           throttleWindow.getViewAddressPanel().setSelected(false);
           addressPanel->setVisible(false);
       } else if (e.getSource() == functionPanel) {
           throttleWindow.getViewFunctionPanel().setSelected(false);
           functionPanel->setVisible(false);
       } else if (e.getSource() == speedPanel) {
           throttleWindow.getViewSpeedPanel().setSelected(false);
           speedPanel->setVisible(false);
       } else {
           try { // #JYNSTRUMENT#, Very important, clean the Jynstrument
               if ((e.getSource() instanceof JInternalFrame)) {
                   Component[] cmps = ((JInternalFrame) e.getSource()).getContentPane().getComponents();
                   int i = 0;
                   while ((i < cmps.length) && (!(cmps[i] instanceof Jynstrument))) {
                       i++;
                   }
                   if ((i < cmps.length) && (cmps[i] instanceof Jynstrument)) {
                       ((Jynstrument) cmps[i]).exit();
                   }
               }
           } catch (Exception exc) {
               if (log.isDebugEnabled()) {
                   log.debug("Got exception, can ignore :{}", exc);
               }
           }
       }
   }

   /**
    * Listen for the activation of an internal frame record this property
    * for correct processing of the frame cycling key.
    *
    * @param e The InternalFrameEvent leading to this action
    */
   @Override
   /*public*/ void internalFrameActivated(InternalFrameEvent e) {
       if (e.getSource() == controlPanel) {
           activeFrame = CONTROL_PANEL_INDEX;
       } else if (e.getSource() == addressPanel) {
           activeFrame = ADDRESS_PANEL_INDEX;
       } else if (e.getSource() == functionPanel) {
           activeFrame = FUNCTION_PANEL_INDEX;
       } else if (e.getSource() == functionPanel) {
           activeFrame = SPEED_DISPLAY_INDEX;
       }
   }
}
#endif
/**
* Collect the prefs of this object into XML Element
* <ul>
* <li> Window prefs
* <li> ControlPanel
* <li> FunctionPanel
* <li> AddressPanel
* <li> SpeedPanel
* </ul>
*
*
* @return the XML of this object.
*/
/*public*/ QDomElement ThrottleFrame::getXml() {
 QDomElement me =doc.createElement("ThrottleFrame");
 me.setAttribute("title", titleText);
 me.setAttribute("titleType", titleTextType);

 //java.util.ArrayList<Element> children = new java.util.ArrayList<Element>(1);
 //children.add(WindowPreferences.getPreferences(this));
 me.appendChild(WindowPreferences::getPreferences(this));
 if (!throttleFrames->isEmpty())
 {
  //ThrottleFrame* cf = this.getCurrentThrottleFrame();
  ThrottleWindow* cf = this;
  foreach (ThrottleWindow* tf, throttleFrames->values() )
  {
   //ThrottleFrame tf = tfi.next();
   if ((ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingExThrottle()) && (ThrottleFrameManager::instance()->getThrottlesPreferences()->isSavingThrottleOnLayoutSave()))
   {
    if(tf != this)
    {
     tf->toFront();
     tf->saveThrottle();
    }
   }
   QDomElement tfe = tf->getXmlFile();
   if (tfe == QDomElement()) {
       tfe = tf->getXml(tf);
   }
   //children.add(tfe);
   me.appendChild(tfe);
  }
  if (cf != NULL) {
      cf->toFront();
  }
 }
 me.appendChild(controlPanel->getXml());
 me.appendChild(functionPanel->getXml());
 me.appendChild(addressPanel->getXml());
 me.appendChild(speedPanel->getXml());

#ifdef SCRIPTING_ENABLED
 // Save Jynstruments
 QDomDocument doc = QDomDocument();
 if (throttleToolBar != NULL) {
     QObjectList cmps = throttleToolBar->children();
     if (!cmps.isEmpty()) {
         for (int i = 0; i < cmps.length(); i++) {
             try {
                 //if (cmps[i] instanceof Jynstrument)
           if(qobject_cast<Jynstrument*>(cmps.at(i)) != NULL)
                 {
                     Jynstrument* jyn = (Jynstrument*) cmps[i];
                     QDomElement elt = doc.createElement("Jynstrument");
                     elt.setAttribute("JynstrumentFolder", FileUtil::getPortableFilename(jyn->getFolder()));
                     QDomElement je = jyn->getXml();
//                     if (je != NULL) {
//                         java.util.ArrayList<Element> jychildren = new java.util.ArrayList<Element>(1);
//                         jychildren.add(je);
//                         elt.setContent(jychildren);
//                     }
//                     children.add(elt);
                     elt.appendChild(je);
                 }

             } catch (Exception ex) {
                 log->debug("Got exception (no panic) " + ex.getMessage());
             }
         }
     }
 }
#endif

 //me.setContent(children);
 return me;
}

/*public*/ QDomElement getXmlFile() {
   if (getLastUsedSaveFile() == null) { // || (getRosterEntry()==null))
       return null;
   }
   Element me = new Element("ThrottleFrame");
   me.setAttribute("ThrottleXMLFile", FileUtil.getPortableFilename(getLastUsedSaveFile()));
   return me;
}

/**
* Set the preferences based on the XML Element.
* <ul>
* <li> Window prefs
* <li> Frame title
* <li> ControlPanel
* <li> FunctionPanel
* <li> AddressPanel
* <li> SpeedPanel
* </ul>
*
* @param e The Element for this object.
*/
/*public*/ void ThrottleFrame::setXml(Element e) {
 if (e.attribute("title") != NULL) {
     setTitle(e.attribute("title"));
 }
 if (e.attribute("title") != NULL) {
     setTitleText(e.attribute("title"));
 }
 if (e.attribute("titleType") != NULL) {
     setTitleTextType(e.attribute("titleType"));
 }

 QDomElement window = e.firstChildElement("window");
 if (window != QDomElement()) {
     WindowPreferences::setPreferences(this, window);
 }

 QDomNodeList tfes = e.elementsByTagName("ThrottleFrame");
 if (/*(tfes != QDomElement()) &&*/ (tfes.size() > 0))
 {
  for (int i = 0; i < tfes.size(); i++)
  {
   ThrottleWindow* tf;
   if (i == 0) {
       tf = getCurrentThrottleFrame();
   } else {
       tf = addThrottleFrame();
   }
   tf->setXml(tfes.at(i).toElement());
  }
 }
#if 0
 QDomNodeList jinsts = e.elementsByTagName("Jynstrument");
 if ((jinsts != NULL) && (jinsts.size() > 0)) {
     for (int i = 0; i < jinsts.size(); i++) {
         Jynstrument jyn = ynstrument(FileUtil.getExternalFilename(jinsts.get(i).attributeValue("JynstrumentFolder")));
         if ((jyn != NULL) && (jinsts.get(i) != NULL)) {
             jyn.setXml(jinsts.get(i));
         }
     }
 }
#endif
 updateGUI();
}

/**
* setFrameTitle - set the frame title based on type, text and address
*/
/*public*/ void ThrottleFrame::setFrameTitle() {
   QString addr = tr("Throttle");
   if (addressPanel->getThrottle() != nullptr) {
       addr = addressPanel->getCurrentAddress()->toString();
   }
   if (getTitleTextType()==("address") ) {
       setTitle(addr);
   } else if (getTitleTextType() == ("text") ) {
       setTitle(getTitleText());
   } else if (getTitleTextType() == ("addressText") ) {
       setTitle(addr + " " + getTitleText());
   } else if (getTitleTextType() == ("textAddress") ) {
       setTitle(getTitleText() + " " + addr);
   }
   else if (getTitleTextType() == ("rosterID") )
   {
    if ((addressPanel->getRosterEntry() != NULL) && (addressPanel->getRosterEntry()->getId() != NULL)
            && (addressPanel->getRosterEntry()->getId().length() > 0)) {
        setTitle(addressPanel->getRosterEntry()->getId());
    } else {
        setTitle(addr);
    }
   }
}
#if 0
@Override
/*public*/ void componentHidden(ComponentEvent e) {
}

@Override
/*public*/ void componentMoved(ComponentEvent e) {
}

@Override
/*public*/ void componentResized(ComponentEvent e) {
//  checkPosition ();
}

@Override
/*public*/ void componentShown(ComponentEvent e) {
   throttleWindow.setCurrentThrottleFrame(this);
   if (willSwitch) {
       setEditMode(this.throttleWindow.getEditMode());
       repaint();
   }
   throttleWindow.updateGUI();
}
#endif
/*public*/ void ThrottleFrame::saveThrottle() {
   if (getRosterEntry() != nullptr) {
       saveThrottle(getDefaultThrottleFolder() + addressPanel->getRosterEntry()->getId().trimmed() + ".xml");
   } else if (getLastUsedSaveFile() != "") {
       saveThrottle(getLastUsedSaveFile());
   }
}

/*public*/ void ThrottleFrame::saveThrottleAs() {
   JFileChooser* fileChooser = XmlFile::userFileChooser(tr("XML files"), "xml");
   fileChooser->setCurrentDirectory(new File(getDefaultThrottleFolder()));
   fileChooser->setDialogType(JFileChooser::SAVE_DIALOG);
   File* file = StoreXmlConfigAction::getFileName(fileChooser);
   if (file == nullptr) {
       return;
   }
   saveThrottle(file->getAbsolutePath());
}
#if 0
/**
* A KeyAdapter that listens for the key that cycles through the
* JInternalFrames.
*
* @author glen
*/
class FrameCyclingKeyListener extends KeyAdapter {

   /**
    * Description of the Method
    *
    * @param e Description of the Parameter
    */
   @Override
   /*public*/ void keyReleased(KeyEvent e) {
       if (e.isControlDown() && e.getKeyCode() == NEXT_FRAME_KEY) {
           try {
               activeFrame = (activeFrame + 1) % NUM_FRAMES;
               frameList[activeFrame].setSelected(true);
           } catch (PropertyVetoException ex) {
               log.warn("Exception selecting internal frame:{}", ex.getMessage());
           }
       } else if (e.isControlDown() && e.getKeyCode() == PREV_FRAME_KEY) {
           try {
               activeFrame--;
               if (activeFrame < 0) {
                   activeFrame = NUM_FRAMES - 1;
               }
               frameList[activeFrame].setSelected(true);
           } catch (PropertyVetoException ex) {
               log.warn("Exception selecting internal frame:{}", ex.getMessage());
           }
       }
   }
}
#endif
//@Override
/*public*/ void ThrottleFrame::notifyAddressChosen(LocoAddress* l) {
}

//@Override
/*public*/ void ThrottleFrame::notifyAddressReleased(LocoAddress* la) {
   setLastUsedSaveFile(null);
   setFrameTitle();
   throttleWindow->updateGUI();
}

//@Override
/*public*/ void ThrottleFrame::notifyAddressThrottleFound(DccThrottle* throttle) {
   if ((((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences().isUsingExThrottle())
           && (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences().isAutoLoading())
           && (addressPanel != nullptr) && (addressPanel->getRosterEntry() != nullptr)
           && ((getLastUsedSaveFile() == "") || (getLastUsedSaveFile()!=(getDefaultThrottleFolder() + addressPanel->getRosterEntry()->getId().trimmed() + ".xml")))) {
       loadThrottle(getDefaultThrottleFolder() + addressPanel->getRosterEntry()->getId().trimmed() + ".xml");
   }
   setFrameTitle();
   throttleWindow->updateGUI();
}

//@Override
/*public*/ void ThrottleFrame::notifyConsistAddressChosen(int newAddress, bool isLong) {
}

//@Override
/*public*/ void ThrottleFrame::notifyConsistAddressReleased(int address, boolean isLong) {
}

//@Override
/*public*/ void ThrottleFrame::notifyConsistAddressThrottleFound(DccThrottle* throttle) {
}

/*public*/ QString ThrottleFrame::getLastUsedSaveFile() {
   return lastUsedSaveFile;
}

/*public*/ void ThrottleFrame::setLastUsedSaveFile(QString lusf) {
   lastUsedSaveFile = lusf;
   throttleWindow.updateGUI();
}

// some utilities to turn a component background transparent
/*public*/ /*static*/ void ThrottleFrame::setTransparentBackground(QObject* jcomp) {
 //if (jcomp instanceof JPanel) //OS X: Jpanel components are enough
 if(qobject_cast<QWidget*>(jcomp) != NULL)
 {
     //jcomp.setBackground(new Color(0, 0, 0, 0));
  QPalette pal = ((QWidget*)jcomp)->palette();
  pal.setColor(QPalette::Background, QColor(0,0,0,0));
  ((QWidget*)jcomp)->setPalette(pal);

 }
 setTransparentBackground(((QWidget*)jcomp)->children());}

/*public*/ /*static*/ void ThrottleFrame::setTransparentBackground(QObjectList comps) {
 for (QObject* comp : comps)
 {
  try {
//            if (comp instanceof JComponent)
   if(qobject_cast<QWidget*>(comp) != NULL)
   {
       setTransparentBackground((QWidget*) comp);
   }
  } catch (Exception e) {
      // Do nothing, just go on
  }
 }
}

// some utilities to turn a component background transparent
/*public*/ /*static*/ void ThrottleFrame::setTransparent(QWidget jcomp) {
   setTransparent(jcomp, true);
}

/*public*/ /*static*/ void ThrottleFrame::setTransparent(QWidget* jcomp, bool transparency) {
 //if (jcomp instanceof JPanel)
if(qobject_cast<QWidget*>(jcomp) != NULL)
 { //OS X: Jpanel components are enough
     //jcomp.setOpaque(!transparency);
  ((QWidget*)jcomp)->setWindowOpacity(transparency?0.0:1.0);
 }
 setTransparent(((QWidget*)jcomp)->children(), transparency);
}

/*private*/ /*static*/ void ThrottleWindow::setTransparent(QObjectList comps, bool transparency) {
    for (QObject* comp : comps) {
        try {
            //if (comp instanceof JComponent)
      if(qobject_cast<QWidget*>(comp)!= NULL)
            {
                setTransparent((QWidget*) comp, transparency);
            }
        } catch (Exception e) {
            // Do nothing, just go on
        }
    }
}

/*private*/ /*final*/ /*static*/ Logger* ThrottleFrame::log = LoggerFactory::getLogger("ThrottleFrame");
