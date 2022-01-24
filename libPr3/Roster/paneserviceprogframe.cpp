#include "paneserviceprogframe.h"
#include "progmodeselector.h"
#include "instancemanager.h"
#include "defaultprogrammermanager.h"
#include "programmingmode.h"

//PaneServiceProgFrame::PaneServiceProgFrame(QWidget *parent) :
//    PaneProgFrame(parent)
//{
//    log = new Logger("PaneServiceProgFrame");
//}
/**
 * Extend the PaneProgFrame to handle service mode operations.
 *<p>
 * If no programmer is provided, the programmer parts of the GUI are suppressed.
 *
 * @author	   Bob Jacobsen   Copyright (C) 2002, 2008
 * @version	   $Revision: 18480 $
 */
///*public*/ class PaneServiceProgFrame extends PaneProgFrame
//                         implements java.beans.PropertyChangeListener  {

/**
 * Provide the programming mode selection pane for inclusion
 */
/*protected*/ JPanel *PaneServiceProgFrame::getModePane()
{
 // ensure initialization, even if invoked in ctor
 if (modePane == NULL)
  modePane = new MyProgServiceModeComboBox(this);
 log->debug("invoked getModePane");
 return modePane;
}


/**
 * This invokes the parent ctor to do the real work. That will
 * call back to get the programming mode panel (provided) and to
 * hear if there is read mode (depends). Then, this sets the
 * programming mode for the service programmer based on what's
 * in the decoder file.
 *
 * @param decoderFile XML file defining the decoder contents
 * @param r RosterEntry for information on this locomotive
 * @param name
 * @param file
 */
/*public*/ PaneServiceProgFrame::PaneServiceProgFrame(DecoderFile* decoderFile, RosterEntry* r, QString name, QString file, Programmer* pProg, QWidget *parent)
    : PaneProgFrame(decoderFile, r, name, file, pProg, false, parent)
{
 //super(decoderFile, r, name, file, pProg, false);
 log = new Logger("PaneServiceProgFrame");

// // set the programming mode
// if (pProg != NULL)
//  if (InstanceManager::programmerManagerInstance() != NULL)
//  {
//   // go through in preference order, trying to find a mode
//   // that exists in both the programmer and decoder.
//   // First, get attributes. If not present, assume that
//   // all modes are usable
//   QDomElement programming = QDomElement();
//   bool paged = true;
//   bool directbit= true;
//   bool directbyte= true;
//   bool _register= true;
//   if (decoderRoot != QDomElement()
//           && (programming = decoderRoot.firstChildElement("decoder").firstChildElement("programming"))!= QDomElement())
//   {
//    QString a;
//    if ( (a = programming.attribute("paged")) != "" )
//     if (a==("no")) paged = false;
//    if ( (a = programming.attribute("direct")) != "" )
//    {
//     if (a==("no")) { directbit = false; directbyte = false; }
//     else if (a==("bitOnly")) { directbit = true; directbyte = false; }
//     else if (a==("byteOnly")) { directbit = false; directbyte = true; }
//    }
//    if ( (a = programming.attribute("register")) != "" )
//     if (a==("no")) _register = false;
//   }

//   // is the current mode OK?
//   ProgrammingMode* currentMode = mProgrammer->getMode();
//   log->debug(QString("XML specifies modes: P ")+(paged?"true":"false")+" DBi "+(directbit?"true":"false")+" Dby "+(directbyte?"true":"false")+" R "+(_register?"true":"false")+" now "+(currentMode->getStandardName()));

//   // find a mode to set it to
//   if (mProgrammer->hasMode(DefaultProgrammerManager::DIRECTBITMODE)&&directbit)
//    mProgrammer->setMode(DefaultProgrammerManager::DIRECTBITMODE);
//   else if (mProgrammer->hasMode(DefaultProgrammerManager::DIRECTBYTEMODE)&&directbyte)
//    mProgrammer->setMode(DefaultProgrammerManager::DIRECTBYTEMODE);
//   else if (mProgrammer->hasMode(Programmer::PAGEMODE)&&paged)
//    mProgrammer->setMode(DefaultProgrammerManager::PAGEMODE);
//   else if (mProgrammer->hasMode(Programmer::REGISTERMODE)&&_register)
//    mProgrammer->setMode(DefaultProgrammerManager::REGISTERMODE);
//   else log->warn("No acceptable mode found, leave as found");

// }
// else
// {
//   log->error("Can't set programming mode, no programmer instance");
// }
 //installComponents();
 pack();

 if (log->isDebugEnabled()) log->debug("PaneServiceProgFrame \""+name
                                        +"\" constructed");
}

/**
 * local dispose, which also invokes parent. Note that
 * we remove the components (removeAll) before taking those
 * apart.
 */
/*public*/ void PaneServiceProgFrame::dispose()
{

 if (log->isDebugEnabled()) log->debug("dispose local");
    //super.dispose();
}

PaneServiceProgFrame::MyProgServiceModeComboBox::MyProgServiceModeComboBox(PaneServiceProgFrame* frame, QWidget* parent)
 : ProgServiceModeComboBox(QBoxLayout::LeftToRight, parent)
{
 this->frame = frame;
}
/*public*/ Programmer* PaneServiceProgFrame::MyProgServiceModeComboBox::getProgrammer()
{
 return frame->mProgrammer;
}
/*protected*/ QList<GlobalProgrammerManager*> PaneServiceProgFrame::MyProgServiceModeComboBox::getMgrList()
{
 return QList<GlobalProgrammerManager*>();
}
/*public*/ QString PaneServiceProgFrame::getClassName()
{
 return "jmri.jmrit.symbolicprog.tabbedframe.PaneServiceProgFrame";
}
