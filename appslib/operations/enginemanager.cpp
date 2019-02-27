#include "enginemanager.h"
#include "logger.h"
#include "engine.h"
#include "consist.h"
#include "logger.h"
#include "operationssetupxml.h"
#include "enginemanagerxml.h"
#include "control.h"
#include "xml.h"
#include "stringutil.h"
#include <QComboBox>
#include "instancemanager.h"

//EngineManager::EngineManager(QObject *parent) :
//  RollingStockManager(parent)
//{
//}
namespace Operations
{
/**
 * Manages the engines.
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version	$Revision: 29493 $
 */
///*public*/ class EngineManager extends RollingStockManager {


/*public*/ /*static*/ /*final*/ QString EngineManager::CONSISTLISTLENGTH_CHANGED_PROPERTY = "ConsistListLength"; // NOI18N

/*public*/ EngineManager::EngineManager(QObject *parent) :
  RollingStockManager(parent)
{
_consistHashTable = QHash<QString, Consist*>();   	// stores Consists by number
log = new Logger("EngineManger");        setProperty("InstanceManagerAutoDefault", "true");
setProperty("InstanceManagerAutoInitialize", "true");

 }

 /**
  * record the single instance *
  */
// /*private*/ /*static*/ EngineManager* EngineManager::_instance = nullptr;

 /*public*/ /*static*/ /*synchronized*/ EngineManager* EngineManager::instance()
 {
  return static_cast<EngineManager*>(InstanceManager::getDefault("EngineManager"));
 }

 /**
  * @return requested Engine object or NULL if none exists
  */
 /*public*/ Engine* EngineManager::getById(QString id) {
     return (Engine*) RollingStockManager::getById(id);
 }

 /*public*/ Engine* EngineManager::getByRoadAndNumber(QString engineRoad, QString engineNumber) {
     QString engineId = Engine::createId(engineRoad, engineNumber);
     return getById(engineId);
 }

 /**
  * Finds an existing engine or creates a new engine if needed requires
  * engine's road and number
  *
  * @param engineRoad
  * @param engineNumber
  * @return new engine or existing engine
  */
 /*public*/ Engine* EngineManager::newEngine(QString engineRoad, QString engineNumber) {
     Engine* engine = getByRoadAndNumber(engineRoad, engineNumber);
     if (engine == nullptr) {
         engine = new Engine(engineRoad, engineNumber);
         _register(engine);
     }
     return engine;
 }

    /**
     * Creates a new consist if needed
     *
     * @param name of the consist
     * @return consist
     */
    /*public*/ Consist* EngineManager::newConsist(QString name) {
        Consist* consist = getConsistByName(name);
        if (consist == nullptr) {
            consist = new Consist(name);
            int oldSize = _consistHashTable.size();
            _consistHashTable.insert(name, consist);
            setDirtyAndFirePropertyChange(CONSISTLISTLENGTH_CHANGED_PROPERTY, oldSize, (_consistHashTable.size()));
        }
        return consist;
    }

    /*public*/ void EngineManager::deleteConsist(QString name) {
        Consist* consist = getConsistByName(name);
        if (consist != nullptr) {
            consist->dispose();
            int oldSize = _consistHashTable.size();
            _consistHashTable.remove(name);
            setDirtyAndFirePropertyChange(CONSISTLISTLENGTH_CHANGED_PROPERTY, oldSize, (_consistHashTable.size()));
        }
    }

    /*public*/ Consist* EngineManager::getConsistByName(QString name) {
        return _consistHashTable.value(name);
    }

    /*public*/ void EngineManager::replaceConsistName(QString oldName, QString newName) {
        Consist* oldConsist = getConsistByName(oldName);
        if (oldConsist != nullptr) {
            Consist* newConsist = new Consist(newName);
            // keep the lead engine
            Engine* leadEngine = (Engine*) oldConsist->getLead();
            leadEngine->setConsist(newConsist);
            foreach (Engine* engine, oldConsist->getEngines()) {
                engine->setConsist(newConsist);
            }
        }
    }

    /**
     * Creates a combo box containing all of the consist names
     *
     * @return a combo box with all of the consist names
     */
    /*public*/ QComboBox* EngineManager::getConsistComboBox() {
        QComboBox* box = new QComboBox();
        box->addItem(NONE);
        foreach (QString name, getConsistNameList()) {
            box->addItem(name);
        }
        return box;
    }

    /*public*/ void EngineManager::updateConsistComboBox(QComboBox* box) {
        box->clear();
        box->addItem(NONE);
        foreach (QString name, getConsistNameList()) {
            box->addItem(name);
        }
    }

    /*public*/ QStringList EngineManager::getConsistNameList() {
        QVector<QString> names = QVector<QString>(_consistHashTable.size());
        QStringList out = QStringList();
        QStringListIterator en(_consistHashTable.keys());
        int i = 0;
        while (en.hasNext()) {
            names.replace(i++, en.next());
        }
        StringUtil::sort(names.toList());
        foreach (QString name, names) {
            out.append(name);
        }
        return out;
    }

    /*public*/ int EngineManager::getConsistMaxNameLength() {
        int maxLength = 0;
        foreach (QString name, getConsistNameList()) {
            if (name.length() > maxLength) {
                maxLength = name.length();
            }
        }
        return maxLength;
    }

    /**
     * Sort by engine model
     *
     * @return list of engines ordered by engine model
     */
/*public*/ QList<RollingStock*>* EngineManager::getByModelList() {
    return getByList(getByRoadNameList(), BY_MODEL);
}

/**
 * Sort by engine consist
 *
 * @return list of engines ordered by engine consist
 */
/*public*/ QList<RollingStock*>* EngineManager::getByConsistList() {
    return getByList(getByRoadNameList(), BY_CONSIST);
}

/*public*/ QList<RollingStock*>* EngineManager::getByHpList() {
        return getByList(getByModelList(), BY_HP);
    }

    // The special sort options for engines
    /*private*/ /*static*/ /*final*/ int EngineManager::BY_MODEL = 4;
    /*private*/ /*static*/ /*final*/ int EngineManager::BY_CONSIST = 5;
    /*private*/ /*static*/ /*final*/ int EngineManager::BY_HP = 13;
#if 0
    // add engine options to sort comparator
    //@Override
    /*public*/ java.util.Comparator<RollingStock> getComparator(int attribute) {
        switch (attribute) {
            case BY_MODEL:
                return (e1,e2) -> (((Engine) e1).getModel().compareToIgnoreCase(((Engine) e2).getModel()));
            case BY_CONSIST:
                return (e1,e2) -> (((Engine) e1).getConsistName().compareToIgnoreCase(((Engine) e2).getConsistName()));
            case BY_HP:
                return (e1,e2) -> (((Engine) e1).getHpInteger() - ((Engine) e2).getHpInteger());
            default:
                return super.getComparator(attribute);
        }
    }

#endif
    /**
     * return a list available engines (no assigned train) engines are ordered
     * least recently moved to most recently moved.
     *
     * @param train
     * @return Ordered list of engines not assigned to a train
     */
    /*public*/ QList<Engine*> EngineManager::getAvailableTrainList(Train* train) {
        // now build list of available engines for this route
        QList<Engine*> out = QList<Engine*>();
        // get engines by moves list
        foreach (RollingStock* rs, *getByMovesList()) {
            Engine* engine = (Engine*) rs;
            if (engine->getTrack() != nullptr && (engine->getTrain() == nullptr || engine->getTrain() == train)) {
                out.append(engine);
            }
        }
        return out;
    }

    /**
     * Returns a list of locos sorted by blocking number for a train. This
     * returns a list of consisted locos in the order that they were entered in.
     */
    /*public*/ QList<Engine*>* EngineManager::getByTrainBlockingList(Train* train) {
        return castListToEngine(getByList(RollingStockManager::getByTrainList(train), BY_BLOCKING));
    }

    /*private*/ QList<Engine*>* EngineManager::castListToEngine(QList<RollingStock*>* list) {
        QList<Engine*>* out = new QList<Engine*>();
        foreach (RollingStock* rs, *list) {
            out->append((Engine*) rs);
        }
        return out;
    }

    /**
     * Get a list of engine road names.
     *
     * @return List of engine road names.
     */
    /*public*/ QStringList EngineManager::getEngineRoadNames(QString model) {
        QStringList names = QStringList();
        QStringListIterator en(_hashTable.keys());
        while (en.hasNext()) {
            Engine* engine = getById(en.next ());
            if ((engine->getModel()==(model) || model==(NONE))
                    && !names.contains(engine->getRoadName())) {
                names.append(engine->getRoadName());
            }
        }
        //java.util.Collections.sort(names);
        return names;
    }

    //@Override
    /*public*/ void EngineManager::dispose() {
        foreach (QString consistName, getConsistNameList()) {
            deleteConsist(consistName);
        }
        RollingStockManager::dispose();
    }

 /*public*/ void EngineManager::load(QDomElement  root)
 {
        // new format using elements starting version 3.3.1
 if (root.firstChildElement(Xml::NEW_CONSISTS) != QDomElement()) {
            //@SuppressWarnings("unchecked")
            QDomNodeList consists = root.firstChildElement(Xml::NEW_CONSISTS).elementsByTagName(Xml::CONSIST);
            if (log->isDebugEnabled()) {
                log->debug(tr("Engine manager sees %1 consists").arg(consists.size()));
            }
            QString a;
            for (int i = 0; i < consists.count(); i++)
            {
                 QDomElement consist  = consists.at(i).toElement();
                if ((a = consist.attribute (Xml::NAME)) != "") {
                    newConsist(a);
                }
            }
        } // old format
        else if (root.firstChildElement(Xml::CONSISTS) != QDomElement()) {
            QString names = root.firstChildElement(Xml::CONSISTS).text();
            if (names!=(NONE)) {
                QStringList consistNames = names.split("%%"); // NOI18N
                if (log->isDebugEnabled()) {
                    log->debug(tr("consists: %1").arg(names));
                }
                foreach (QString name, consistNames) {
                    newConsist(name);
                }
            }
        }

 if (root.firstChildElement(Xml::ENGINES) != QDomElement()) {
            //@SuppressWarnings("unchecked")
            QDomNodeList engines = root.firstChildElement(Xml::ENGINES).elementsByTagName(Xml::ENGINE);
            if (log->isDebugEnabled()) {
                log->debug(tr("readFile sees %1 engines").arg(engines.size()));
            }
            for(int i = 0; i < engines.count(); i ++)
            {
             QDomElement  e =engines.at(i).toElement();
                _register(new Engine(e));
            }
        }
    }

    /**
     * Create an XML element to represent this Entry. This member has to remain
     * synchronized with the detailed DTD in operations-engines.dtd.
     *
     */
    /*public*/ void EngineManager::store(QDomElement  root, QDomDocument doc) {
//    	root.addContent(new QDomElement (Xml::OPTIONS));	// nothing to store under options

 QDomElement  values;
        QStringList names = getConsistNameList();
        if (Control::backwardCompatible)
        {
//         values = QDomElement();
//           values.setTagName(Xml::CONSISTS);
         values = doc.createElement(Xml::CONSISTS);
            root.appendChild(values);
            QString consistNames;
            foreach (QString name, names)
            {
             if(consistNames != "")
              consistNames.append("%%");
             consistNames.append(name); //= name + "%%"; // NOI18N
            }
            QDomText t = QDomText();
            t.setData(consistNames);
            values.appendChild(t);

        }
        // new format using elements
//        QDomElement  consists = QDomElement();
//        consists.setTagName(Xml::NEW_CONSISTS);
        QDomElement consists = doc.createElement(Xml::NEW_CONSISTS);
        foreach (QString name, names) {
//            QDomElement  consist = QDomElement();
//            consist.setTagName(Xml::CONSIST);
         QDomElement consist = doc.createElement(Xml::CONSIST);
            consist.setAttribute(Xml::NAME, name);
            consists.appendChild(consist);
        }
        root.appendChild(consists);

//        values = QDomElement();
//        values.setTagName(Xml::ENGINES);
        values = doc.createElement(Xml::ENGINES);
        root.appendChild(values);
        // add entries
        foreach (RollingStock* rs, *getByRoadNameList())
        {
            Engine* eng = (Engine*) rs;
            values.appendChild(eng->store(doc));
        }
    }

    /*public*/ void EngineManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
        // Set dirty
        EngineManagerXml::instance()->setDirty(true);
        RollingStockManager::firePropertyChange(p, old, n);
    }
 //@Override
 /*public*/ void EngineManager::initialize() {
  static_cast<OperationsSetupXml*>(InstanceManager::getDefault("OperationsSetupXml")); // load setup
  //static_cast<EngineManagerXml*>(InstanceManager::getDefault("EngineManagerXml", InstanceManager::InitializationState::Done)); // load routes
 }

}
