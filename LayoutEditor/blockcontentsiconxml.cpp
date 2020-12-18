#include "blockcontentsiconxml.h"
#include "loggerfactory.h"
#include "leblockcontentsicon.h"
#include "positionablepopuputil.h"
#include "editor.h"
#include "instancemanager.h"
#include "blockmanager.h"
#include "layouteditor.h"

/**
 * Handle configuration for display.BlockContentsIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004
 */
// /*public*/ class BlockContentsIconXml extends PositionableLabelXml {

/*public*/ BlockContentsIconXml::BlockContentsIconXml(QObject* parent) : PositionableLabelXml(parent){
}

/**
 * Default implementation for storing the contents of a BlockContentsIcon
 *
 * @param o Object to store, of type BlockContentsIcon
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement BlockContentsIconXml::store(QObject* o) {

    BlockContentsIcon* p = (BlockContentsIcon*) o;

    QDomElement element = doc.createElement("BlockContentsIcon");

    // include attributes
    element.setAttribute("blockcontents", p->getNamedBlock()->getName());
    storeCommonAttributes(p, element);
    storeTextInfo(p, element);

    //If the fixed width option is not set and the justification is not left
    //Then we need to replace the x, y values with the original ones.
    if (p->getPopupUtility()->getFixedWidth() == 0 && p->getPopupUtility()->getJustification() != 0) {
        element.setAttribute("x", p->getOriginalX());
        element.setAttribute("y", p->getOriginalY());
    }
    element.setAttribute("selectable", (p->isSelectable() ? "yes" : "no"));

    element.setAttribute("class", "jmri.jmrit.display.configurexml.BlockContentsIconXml");
    if (p->getDefaultIcon() != NULL) {
        element.setAttribute("defaulticon", p->getDefaultIcon()->getURL());
    }

    // include contents
    QMap<QString, NamedIcon*>* map = p->getMap();
    if (map != NULL) {

        QMapIterator<QString, NamedIcon*> iterator(*map);

        while (iterator.hasNext()) {
            //java.util.Map.Entry<String, NamedIcon> mi = iterator.next();
         iterator.next();
            QString key = iterator.key();
            QString value = iterator.value()->getName();

            QDomElement e2 = doc.createElement("blockstate");
            e2.setAttribute("value", key);
            e2.setAttribute("icon", value);
            element.appendChild(e2);
        }
    }
    return element;
}

/**
 * Load, starting with the BlockContentsIcon element, then all the
 * value-icon pairs
 *
 * @param element Top level QDomElement to unpack.
 * @param o       an Editor as an Object
 */
//@Override
/*public*/ void BlockContentsIconXml::load(QDomElement element, QObject* o) throw (Exception){

    Editor* ed = NULL;
    BlockContentsIcon* l;
    if (qobject_cast<LayoutEditor*>(o) != NULL) {
        ed = (LayoutEditor*) o;
        l = new LEBlockContentsIcon("   ", (LayoutEditor*) ed);
    } else if (qobject_cast<Editor*>(o) != NULL) {
        ed = (Editor*) o;
        l = new BlockContentsIcon("", ed);
    } else {
        log->error(QString("Unrecognizable class - ") + o->metaObject()->className());
        return;
    }

    QString name;
    QString attr = element.attribute("blockcontents");
    if (attr == NULL) {
        log->error("incorrect information for a block contents; must use block name");
        ed->loadFailed();
        return;
    } else {
        name = attr;
    }

    loadTextInfo(l, element);

    Block* m = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(name);
    if (m != NULL) {
        l->setBlock(name);
    } else {
        log->error("Block named '" + attr + "' not found.");
        ed->loadFailed();
    }

    QString a = element.attribute("selectable");
    if (a != NULL && a == ("yes")) {
        l->setSelectable(true);
    } else {
        l->setSelectable(false);
    }

    // get the icon pairs
    QDomNodeList items = element.elementsByTagName("blockstate");
    for (int i = 0; i < items.size(); i++) {
        // get the class, hence the adapter object to do loading
        QDomElement item = items.at(i).toElement();
        QString iconName = item.attribute("icon");
        NamedIcon* icon = NamedIcon::getIconByName(iconName);
        if (icon == NULL) {
            icon = ed->loadFailed("Memory " + name, iconName);
            if (icon == NULL) {
                log->info("Memory \"" + name + "\" icon removed for url= " + iconName);
            }
        }
        if (icon != NULL) {
            QString keyValue = item.attribute("value");
            l->addKeyAndIcon(icon, keyValue);
        }
    }
    ed->putItem(l);
    // load individual item's option settings after editor has set its global settings
    loadCommonAttributes(l, Editor::MEMORIES, element);
    int x = 0;
    int y = 0;
    try {
    bool bok;
        x = element.attribute("x").toInt(&bok);
        if(!bok) throw DataConversionException();
        y = element.attribute("y").toInt(&bok);
        if(!bok) throw DataConversionException();
    } catch (DataConversionException e) {
        log->error("failed to convert positional attribute");
    }
    l->setOriginalLocation(x, y);
    l->displayState();
}

/*private*/ /*final*/ /*static*/ Logger* BlockContentsIconXml::log = LoggerFactory::getLogger("BlockContentsIconXml");
