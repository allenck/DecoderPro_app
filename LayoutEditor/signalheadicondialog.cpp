#include "signalheadicondialog.h"
#include "loggerfactory.h"
#include "familyitempanel.h"
#include "signalheaditempanel.h"

/**
 * This class is used when FamilyItemPanel classes add or modify icon sets
 * families.
 * @author Pete Cressman Copyright (c) 2018
 */
///*public*/ class SignalHeadIconDialog extends IconDialog {

/*public*/ SignalHeadIconDialog::SignalHeadIconDialog(QString type, QString family, FamilyItemPanel* parent, QMap<QString, NamedIcon*>* iconMap)
 : IconDialog(type, family, parent, iconMap)
{
    //super(type, family, parent, iconMap);
}

//@Override
/*protected*/ void SignalHeadIconDialog::makeDoneButtonPanel(JPanel* buttonPanel, QMap<QString, NamedIcon*>* iconMap) {
    if (iconMap != nullptr) {
        QMap<QString, NamedIcon*>* map = ((SignalHeadItemPanel*)_parent)->getFilteredIconMap(iconMap);
        _iconMap = IconDialog::clone(map);
        IconDialog::makeDoneButtonPanel(buttonPanel, tr("Done"));
    } else {
        _iconMap = ItemPanel::makeNewIconMap(_type);
        IconDialog::makeDoneButtonPanel(buttonPanel, tr("Add New Icon Set"));
    }
    log->debug(tr("_iconMap size = %1").arg(_iconMap->size()));
}

/*private*/ /*final*/ /*static*/ Logger* SignalHeadIconDialog::log = LoggerFactory::getLogger("SignalHeadIconDialog");
