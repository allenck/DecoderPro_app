#include "lememoryiconxml.h"
#include "lememoryicon.h"
#include "positionablepopuputil.h"
#include "instancemanager.h"
#include "editor.h"
#include "layouteditor.h"
#include "abstractmemory.h"

/**
 * Handle configuration for display.layoutEditor.MemoryIcon objects. Adapter
 * needs to find a class here
 *
 * @author Pete Cressman Copyright: Copyright (c) 2010
 */
//@SuppressFBWarnings(value = "NM_SAME_SIMPLE_NAME_AS_SUPERCLASS", justification="Cannot rename for user data compatiblity reasons.")
// For explanation of annotation, see layoutEditor.MemoryIcon
//public class MemoryIconXml extends jmri.jmrit.display.configurexml.MemoryIconXml {
LEMemoryIconXml::
    /*public*/ LEMemoryIconXml(QObject* parent) : MemoryIconXml(parent) {
    }
//}
