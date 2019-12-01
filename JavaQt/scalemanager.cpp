#include "scalemanager.h"
#include "scale.h"
#include "loggerfactory.h"
#include "qmap.h"
#include "scaleconfigxml.h"

ScaleManager::ScaleManager(QObject *parent) : QObject(parent)
{

}
/**
 * Create a list of layout scale objects and provide retrieval methods.
 * <p>
 * See {@link jmri.Scale Scale} for details of each scale object.
 *
 * @author Dave Sand Copyright (C) 2018
 * @since 4.13.6
 */
///*public*/ class ScaleManager {

    /*private*/ /*static*/ QMap<QString, Scale*> ScaleManager::_scaleMap = QMap<QString, Scale*>();

    /**
     * Load the hash map from ScaleData.xml.  The XML load process will load
     * the customized local copy if available, otherwise the program file will be used.
     */
    /*private*/ /*static*/ void ScaleManager::fillMap() {
     if (!ScaleConfigXML::doLoad())
     {
            // Create backup HO and N scales
            addScale("HO", "HO", 87.1);
            addScale("N", "N", 160.0);
     }
     log->debug("ScaleManager initialized");
    }

    /**
     * Create a scale instance and add it to the map.
     * @param scaleName The scale name, such as HO.
     * @param userName The user name.  By default the same as the scale name.
     * @param scaleRatio The ratio for the scale, such as 87.1.
     */
    /*public*/ /*static*/ void ScaleManager::addScale(QString scaleName, QString userName, double scaleRatio) {
        _scaleMap.insert(scaleName, new Scale(scaleName, scaleRatio, userName));
    }

    /**
     * Get the scale that corresponds to the supplied scale name, otherwise null.
     * @param name The scale name.
     * @return The selected scale or null.
     */
    /*public*/ /*static*/ Scale* ScaleManager::getScale(/*@Nonnull*/ QString name) {
        if (_scaleMap.isEmpty()) fillMap();
        return _scaleMap.value(name);
    }

    /**
     * Get a list of all scale entries sorted by user name.
     * @return The sorted scale list.
     */
    /*public*/ /*static*/ QList<Scale*> ScaleManager::getScales() {
        if (_scaleMap.isEmpty()) fillMap();
        QList<Scale*> list = QList<Scale*>();
        for (Scale* scale : _scaleMap.values()) {
            list.append(scale);
        }
        // TODO: Collections.sort(list, (o1, o2) -> o1.getUserName().compareTo(o2.getUserName()));
        return list;
    }

    /**
     * Get the scale that matches the user name, the scale name, or null.
     * The user names are searched first.  If not found then the scale name is used.
     * @param name The user name or scale name.
     * @return The selected scale or null.
     */
    /*public*/ /*static*/ Scale *ScaleManager::getScaleByName(/*@Nonnull*/ QString name) {
        if (_scaleMap.isEmpty()) fillMap();
        for (Scale* scale : _scaleMap.values()) {
            if (scale->getUserName() ==(name)) {
                return scale;
            }
        }
        return _scaleMap.value(name);
    }

    /*private*/ /*final*/ /*static*/ Logger* ScaleManager::log = LoggerFactory::getLogger("ScaleManager");
