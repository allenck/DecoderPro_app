#include "indicatortrackiconxml.h"
#include "indicatortrackicon.h"
#include "editor.h"

IndicatorTrackIconXml::IndicatorTrackIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
    log = new Logger("IndicatorTrackIconXml");
}
/**
 * Handle configuration for display.IndicatorTrackIconXml objects.
 *
 * @author Pete Cressman Copyright: Copyright (c) 2010
 * @version $Revision: 21338 $
 */
//public class IndicatorTrackIconXml extends PositionableLabelXml {

//    public IndicatorTrackIconXml() {
//    }

    /**
     * Default implementation for storing the contents of a
     * IndicatorTrackIcon
     * @param o Object to store, of type IndicatorTrackIcon
     * @return QDomElement containing the complete info
     */
    /*public*/ QDomElement IndicatorTrackIconXml::store(QObject* o) {

        IndicatorTrackIcon* p = (IndicatorTrackIcon*)o;
        if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

        QDomElement element = doc.createElement("indicatortrackicon");
        storeCommonAttributes((Positionable*)p, element);

        NamedBeanHandle<OBlock*>* b = p->getNamedOccBlock();
        if (b!=NULL) {
            element.appendChild(storeNamedBean("occupancyblock", b));
        }
        NamedBeanHandle<Sensor*>* s = p->getNamedOccSensor();
        if (b==NULL && s!=NULL) {		// only write sensor if no OBlock, don't write double sensing
            element.appendChild(storeNamedBean("occupancysensor", s));
        }
        /*
        s = p.getErrSensor();
        if (s!=NULL) {
            element.appendChild(storeBean("errorsensor", s));
        }
        */
        QDomElement elem = doc.createElement("showTrainName");
        QString show = "no";
        if (p->showTrain()) { show = "yes"; }
        elem.appendChild(doc.createTextNode(show));
        element.appendChild(elem);

        QMap<QString, NamedIcon*>* iconMap = p->getIconMap();
        QMapIterator<QString, NamedIcon*> it(*iconMap);
        elem = doc.createElement("iconmap");
        QString family = p->getFamily();
        if (family!="") {
            elem.setAttribute("family", family);
        }
        while (it.hasNext()) {
            //QHash<QString, NamedIcon*>* entry = it.next();
            it.next();
            elem.appendChild(storeIcon(it.key(), it.value()));
        }
        element.appendChild(elem);

        elem = doc.createElement("paths");
        QStringList paths = p->getPaths();
        if (!paths.isEmpty()) {
            for (int i=0; i<paths.size(); i++) {
                QDomElement e = doc.createElement("path");
                e.appendChild(doc.createTextNode(paths.at(i)));
                elem.appendChild(e);

            }
            element.appendChild(elem);
        }

        element.setAttribute("class", "jmri.jmrit.display.configurexml.IndicatorTrackIconXml");

        return element;
    }

    /*QDomElement storeBean(String elemName, NamedBean nb) {
        QDomElement elem = doc.createElement(elemName);
        elem.appendChild(nb.getSystemName());
        return elem;
    }*/
    template <class T>
    QDomElement IndicatorTrackIconXml::storeNamedBean(QString elemName, NamedBeanHandle<T>* nb) {
        QDomElement elem = doc.createElement(elemName);
        elem.appendChild(doc.createTextNode(nb->getName()));
        return elem;
    }

    /*public*/ bool IndicatorTrackIconXml::load(QDomElement element) throw (Exception) {
        log->error("Invalid method called");
        return false;
    }

    /**
     * Create a IndicatorTrackIcon, then add to a target JLayeredPane
     * @param element Top level QDomElement to unpack.
     * @param o  Editor as an Object
     */
    /*public*/ void IndicatorTrackIconXml::load(QDomElement element, QObject* o) throw (Exception){
        // create the objects
        Editor* p = (Editor*)o;

        l = new IndicatorTrackIcon(p);

        QDomElement elem = element.firstChildElement("iconmap");
        if (!elem.isNull()) {
            //@SuppressWarnings("unchecked")
            QDomNodeList status = elem.childNodes();
            if (status.size()>0) {
                for (int i=0; i<status.size(); i++) {
                    QString msg = "IndicatorTrack \""+l->getNameString()+"\" icon \""+status.at(i).toElement().tagName()+"\" ";
                    NamedIcon* icon = loadIcon(l, status.at(i).toElement().tagName(), elem,
                                              msg, p);
                    if (icon!=NULL) {
                        l->setIcon(status.at(i).toElement().tagName(), icon);
                    } else {
                        log-> info(msg+" removed for url= "+status.at(i).toElement().tagName());
                        return;
                    }
                }
            }
            QString attr = elem.attribute("family");
            if (attr!=NULL) {
                l->setFamily(attr);
            }
        }
        QDomElement name = element.firstChildElement("occupancyblock");
        if (!name.isNull()) {
            l->setOccBlock(name.text());
        }
        name = element.firstChildElement("occupancysensor");
        if (!name.isNull()) {
            l->setOccSensor(name.text());
        }
        /*
        name = element.getChild("errorsensor");
        if (name!=NULL) {
            l.setErrSensor(name.getText());
        }
       */
        l->setShowTrain(false);
        name = element.firstChildElement("showTrainName");
        if (!name.isNull()) {
            if ("yes"==(name.text())) l->setShowTrain(true);
        }

        elem = element.firstChildElement("paths");
        if (!elem.isNull()) {
            QStringList paths = QStringList();
            //@SuppressWarnings("unchecked")
            QDomNodeList pth = elem.childNodes();
            for (int i=0; i<pth.size(); i++) {
                paths.append(pth.at(i).toElement().text());
            }
            l->setPaths(paths);
        }

        l->updateSize();
//        p->putItem((Positionable*)l);
        // load individual item's option settings after editor has set its global settings
        loadCommonAttributes((Positionable*)l, Editor::TURNOUTS, element);
        p->putItem((Positionable*)l);
    }

    IndicatorTrackIcon* IndicatorTrackIconXml::getIcon() { return l;}
