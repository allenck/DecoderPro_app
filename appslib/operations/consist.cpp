#include "consist.h"
#include "engine.h"
#include "logger.h"

//Consist::Consist(QObject *parent) :
//  RollingStockGroup(parent)
//{
//}
namespace Operations
{
/**
 * A consist is a group of engines that is managed as one engine
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2010
 * @version $Revision: 28746 $
 */
// /*public*/ class Consist extends RollingStockGroup {


 /*public*/ Consist::Consist(QString name, QObject *parent) :
     RollingStockGroup(name, parent)
 {
        //super(name);
  log = new Logger("Consist");
  //log->debug(tr("New Consist (%1)").arg(name));
  _consistNumber = 0;

  }

    /*public*/ QList<Engine*> Consist::getEngines() {
        QList<Engine*> engines = QList<Engine*>();
        foreach (RollingStock* rs, getGroup()) {
            engines.append((Engine*) rs);
        }
        return engines;
    }

    /*public*/ int Consist::getConsistNumber() {
        return _consistNumber;
    }

    /**
     *
     * @param number DCC address for this consist
     */
    /*public*/ void Consist::setConsistNumber(int number) {
        _consistNumber = number;
    }

    /*public*/ void Consist::dispose() {
        while (getGroup().size() > 0) {
            Engine* engine = (Engine*) getGroup().at(0);
            if (engine != NULL) {
                engine->setConsist(NULL);
            }
        }
        RollingStockGroup::dispose();
    }
}
