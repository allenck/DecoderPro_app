#include "sprogupdateaction.h"

using namespace Sprog;

/**
 * Swing action to create and register a SprogIIUpdateFrame object
 *
 * @author	Andrew crosland Copyright (C) 2004
 */
///*abstract*/ /*public*/ class SprogUpdateAction extends AbstractAction {


/*public*/ SprogUpdateAction::SprogUpdateAction(QString s,SprogSystemConnectionMemo* memo, QWidget* frame) : AbstractAction(s, frame)
{
    //super(s);
    _memo = memo;
}

