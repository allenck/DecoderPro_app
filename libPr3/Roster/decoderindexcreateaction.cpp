#include "decoderindexcreateaction.h"
#include "decoderindexfile.h"

DecoderIndexCreateAction::DecoderIndexCreateAction(QObject *parent) :
  JmriAbstractAction(tr("Create Decoder Index"), parent)
{
 common();
}
/**
 * Update the decoder index and store
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2011
 * @version	$Revision: 28746 $
 * @see jmri.jmrit.XmlFile
 */
///*public*/ class DecoderIndexCreateAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 4750974443596415652L;

/*public*/ DecoderIndexCreateAction::DecoderIndexCreateAction(QString s, WindowInterface* wi) :
  JmriAbstractAction(s,wi) {
 //super(s, wi);
 common();
}

/*public*/ DecoderIndexCreateAction::DecoderIndexCreateAction(QString s, QIcon i, WindowInterface* wi ) :
  JmriAbstractAction(s,i,wi) {
 //super(s, i, wi);
 common();
}

/*public*/ DecoderIndexCreateAction::DecoderIndexCreateAction(QString s, QObject *parent) :
  JmriAbstractAction(s, parent){
 //super(s);
 common();
}
void DecoderIndexCreateAction::common()
{
 increment = false;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void DecoderIndexCreateAction::setIncrement(bool increment) {
    this->increment = increment;
}

//@Override
/*public*/ void DecoderIndexCreateAction::actionPerformed(ActionEvent* /*e*/) {
 DecoderIndexFile::forceCreationOfNewIndex(increment);
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* DecoderIndexCreateAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
