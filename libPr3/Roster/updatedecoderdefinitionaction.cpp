#include "updatedecoderdefinitionaction.h"
#include "roster.h"
#include "rosterentry.h"
#include "decoderfile.h"
#include "decoderindexfile.h"
#include "instancemanager.h"

UpdateDecoderDefinitionAction::UpdateDecoderDefinitionAction(QObject *parent) :
  JmriAbstractAction(tr("Update Decoder Definition"), parent)
{
}
/**
 * Update the decoder definitions in the roster
 *
 * @author	Bob Jacobsen Copyright (C) 2013
 * @version	$Revision: 29335 $
 * @see jmri.jmrit.XmlFile
 */
///*public*/ class UpdateDecoderDefinitionAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -2751913119792322837L;

/*public*/ UpdateDecoderDefinitionAction::UpdateDecoderDefinitionAction(QString s, WindowInterface* wi, QObject *parent) :
  JmriAbstractAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ UpdateDecoderDefinitionAction::UpdateDecoderDefinitionAction(QString s, QIcon i, WindowInterface* wi, QObject *parent) :
  JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/*public*/ UpdateDecoderDefinitionAction::UpdateDecoderDefinitionAction(QString s, QObject *parent) :
  JmriAbstractAction(s, parent)
{
 //super(s);
 log = new Logger("UpdateDecoderDefinitionAction");
 common();
}

void UpdateDecoderDefinitionAction::common()
{
 log = new Logger("UpdateDecoderDefinitionAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void UpdateDecoderDefinitionAction::actionPerformed(ActionEvent* /*e*/)
{
 QList<RosterEntry*> list = Roster::getDefault()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);

foreach (RosterEntry* entry, list)
{
  QString family = entry->getDecoderFamily();
  QString model = entry->getDecoderModel();

  // check if replaced
  QList<DecoderFile*> decoders = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList(NULL, family, NULL, NULL, NULL, model);
  log->info("Found " + QString::number(decoders.size()) + " decoders matching family \"" + family + "\" model \"" + model + "\" from roster entry \"" + entry->getId() + "\"");

  QString replacementFamily = NULL;
  QString replacementModel = NULL;

  foreach (DecoderFile* decoder, decoders)
  {
   if (decoder->getReplacementFamily() != NULL || decoder->getReplacementModel() != NULL)
   {
    log->info("   Recommended replacement is family \"" + decoder->getReplacementFamily() + "\" model \"" + decoder->getReplacementModel() + "\"");
   }
   replacementFamily = (decoder->getReplacementFamily() != NULL) ? decoder->getReplacementFamily() : replacementFamily;
   replacementModel = (decoder->getReplacementModel() != NULL) ? decoder->getReplacementModel() : replacementModel;
  }

  if (replacementModel != NULL && replacementFamily != NULL)
  {
   log->info("   *** Will update");

   // change the roster entry
   entry->setDecoderFamily(replacementFamily);
   entry->setDecoderModel(replacementModel);

   // write it out (not bothering to do backup?)
   entry->updateFile();
  }
 }

 // write updated roster
 Roster::getDefault()->makeBackupFile(Roster::getDefault()->getRosterIndexPath());
 try {
     Roster::getDefault()->writeFile(Roster::getDefault()->getRosterIndexPath());
 } catch (IOException ex) {
     Logger::error("Exception while writing the new roster file, may not be complete: " + ex.getMessage());
 }
 // use the new one
 Roster::getDefault()->reloadRosterFile();
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* UpdateDecoderDefinitionAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
