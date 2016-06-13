#include "printrosteraction.h"
#include "jmripanel.h"
#include "rosterentry.h"
#include "roster.h"
#include "fileutil.h"
#include "imageicon.h"
#include "hardcopywriter.h"
#include <QImage>
#include "jlabel.h"
#include "namedicon.h"
#include "jmrijframe.h"

PrintRosterAction::PrintRosterAction(QObject *parent) :
  JmriAbstractAction(tr("Print Roster"), parent)
{
 common();
}
/**
 * Action to print a summary of the Roster contents
 * <P>
 * This uses the older style printing, for compatibility with Java 1.1.8 in
 * Macintosh MRJ
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @author Dennis Miller Copyright (C) 2005
 * @version $Revision: 28746 $
 */
///*public*/ class PrintRosterAction extends jmri.util.swing.JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -8641271368187099365L;

/*public*/ PrintRosterAction::PrintRosterAction(QString s, WindowInterface* wi)
 :  JmriAbstractAction(s, wi)
{
 //super(s, wi);
 common();
 isPreview = true;
}

/*public*/ PrintRosterAction::PrintRosterAction(QString s, QIcon i, WindowInterface* wi)
 :  JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
 isPreview = true;
}

/*public*/ PrintRosterAction::PrintRosterAction(QString actionName, JmriJFrame* frame, bool preview, QObject *parent)
 :  JmriAbstractAction(actionName, parent)
{
 //super(actionName);
 common();
 mFrame = frame;
 isPreview = preview;
}

void PrintRosterAction::common()
{
 log = new Logger("PrintRosterAction");
 mFrame = new JmriJFrame();
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void PrintRosterAction::setPreview(bool preview)
{
 isPreview = preview;
}


/*public*/ void PrintRosterAction::actionPerformed(ActionEvent* e)
{
 // obtain a HardcopyWriter to do this
 Roster* r = Roster::instance();
 QString title = "DecoderPro Roster";
 QString rosterGroup = r->getDefaultRosterGroup();
 // rosterGroup may legitimately be NULL
 // but getProperty returns NULL if the property cannot be found, so
 // we test that the property exists before attempting to get its value
// if (Beans.hasProperty(wi, "selectedRosterGroup")) {
//     rosterGroup = (String) Beans.getProperty(wi, "selectedRosterGroup");
// }
 if (rosterGroup == NULL)
 {
  title = title + " All Entries";
 }
 else
 {
  title = title + " Group " + rosterGroup + " Entires";
 }
 HardcopyWriter* writer = NULL;
// try {
 writer = new HardcopyWriter(mFrame, title, 10, .5, .5, .5, .5, isPreview);
// }
// catch (HardcopyWriter::PrintCanceledException ex)
// {
//     log->debug("Print cancelled");
//     return;
// }

 // add the image
 //ImageIcon* icon = new ImageIcon(FileUtil::findURL("resources/decoderpro.gif", FileUtil::INSTALLED));
 NamedIcon* icon = new NamedIcon(FileUtil::findURL("resources/decoderpro.gif", FileUtil::INSTALLED).toString(),QString());
 // we use an ImageIcon because it's guaranteed to have been loaded when ctor is complete
 writer->write(icon->getImage(), new JLabel(icon));
 //Add a number of blank lines, so that the roster entry starts below the decoderpro logo
 int height = icon->getImage().height();
 int blanks = (height - writer->getLineAscent()) / writer->getLineHeight();

 try
 {
  for (int i = 0; i < blanks; i++)
  {
   QString s = "\n";
   writer->write(s, 0, s.length());
  }
 }
 catch (IOException ex)
 {
  log->warn("error during printing: " + ex.getMessage());
 }

 // Loop through the Roster, printing as needed
 QList<RosterEntry*> l = r->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL); // take all
 log->debug("Roster list size: " + l.size());
 foreach (RosterEntry* re, l)
 {
  if (rosterGroup != NULL)
  {
   if (re->getAttribute(Roster::getRosterGroupProperty(rosterGroup)) != NULL
                 && re->getAttribute(Roster::getRosterGroupProperty(rosterGroup))==("yes"))
   {
    re->printEntry(writer);
   }
  }
  else
  {
   re->printEntry(writer);
  }
 }

 // and force completion of the printing
 writer->close();
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* PrintRosterAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}

/*public*/ void PrintRosterAction::setParameter(QString parameter, QString value)
{
 parameter = parameter.toLower();
 value = value.toLower();
 if (parameter==("ispreview"))
 {
  if (value==("true"))
  {
   isPreview = true;
  }
  else
  {
   isPreview = false;
  }
 }
}
