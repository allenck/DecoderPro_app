#include "importrosterengines.h"
//#include<QMessageBox>
#include <enginemanager.h>
#include "rosterentry.h"
//#include "jmrijframe.h"
//#include <QBoxLayout>
#include "roster.h"
#include "engine.h"
#include "control.h"
#include <QMessageBox>
#include "instancemanager.h"

namespace Operations
{
/**
 * Import engines from the jmri Roster
 *
 * @author Daniel Boudreau Copyright (C) 2008
 *
 */
///*public*/ class ImportRosterEngines extends Thread {

 /*private*/ /*static*/ QString ImportRosterEngines::defaultEngineLength = tr("50");
 /*private*/ /*static*/ QString ImportRosterEngines::defaultEngineType = tr("Engine");
 /*private*/ /*static*/ QString ImportRosterEngines::defaultEngineHp = tr("2000");

 ImportRosterEngines::ImportRosterEngines(QObject *parent) : QObject(parent)
 {
  manager = ((EngineManager*)InstanceManager::getDefault("Operations::EngineManager"));
  log = new Logger("ImportRosterEngines");
//  textEngine = new QLabel();
//  textId = new QLabel();

 }


 // we use a thread so the status frame will work!
 /*public*/ void ImportRosterEngines::process() {

     // create a status frame
//     QWidget* ps = new QWidget();
//     ps->setLayout(new QHBoxLayout);
//     JmriJFrame* fstatus = new JmriJFrame(tr("TitleImportEngines"));
//     //fstatus.setLocationRelativeTo(NULL);
//     fstatus->resize(200, 100);

//     ps->layout()->addWidget(textEngine);
//     ps->layout()->addWidget(textId);
//     //fstatus.getContentPane().add(ps);
//     fstatus->getContentPane()->setLayout(new QHBoxLayout);
//     textEngine->setText(tr("AddEngine"));
//     textEngine->setVisible(true);
//     textId->setVisible(true);
//     fstatus->setVisible(true);

     // Now get engines from the JMRI roster
     int enginesAdded = 0;

     QList<RosterEntry*> engines = Roster::getDefault()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
     QString textId;

     foreach (RosterEntry* re, engines) {
         // add engines that have a road name and number
         if (re->getRoadName()!=("") && re->getRoadNumber()!=("")) {
             QString road = re->getRoadName();
             if (road.length() > Control::max_len_string_attibute) {
                 road = road.mid(0, Control::max_len_string_attibute);
             }
             textId= (road + " " + re->getRoadNumber());
             Engine* engine = (Engine*)manager->getByRoadAndNumber(road, re->getRoadNumber());
             if (engine == NULL) {
                 engine = (Engine*)manager->newRS(road, re->getRoadNumber());
                 QString model = re->getModel();
                 if (model.length() > Control::max_len_string_attibute) {
                     model = model.mid(0, Control::max_len_string_attibute);
                 }
                 engine->setModel(model);
                 // does this model already have a length?
                 if (engine->getLength()==(Engine::NONE)) {
                     engine->setLength(defaultEngineLength);
                 }
                 // does this model already have a type?
                 if (engine->getTypeName()==(Engine::NONE)) {
                     engine->setTypeName(defaultEngineType);
                 }
                 // does this model already have a hp?
                 if (engine->getHp()==(Engine::NONE)) {
                     engine->setHp(defaultEngineHp);
                 }
                 QString owner = re->getOwner();
                 if (owner.length() > Control::max_len_string_attibute) {
                     owner = owner.mid(0, Control::max_len_string_attibute);
                 }
                 engine->setOwner(owner);
                 enginesAdded++;
                 emit progress(textId);
             } else {
                 log->info("Can not add, engine number (" + re->getRoadNumber() + ") road (" + re->getRoadName() + ") already exists");
             }
         }
     }

     // kill status panel
//     fstatus->close();

//     if (enginesAdded > 0) {
//         JOptionPane.showMessageDialog(NULL,
//                 MessageFormat.format(tr("ImportEnginesAdded"), new Object[]{enginesAdded}),
//                 tr("SuccessfulImport"), JOptionPane.INFORMATION_MESSAGE);
//      QMessageBox::information(NULL, tr("Successful Import!"), tr("%1 locomotives added to operations roster").arg(enginesAdded));
//     } else {
//         JOptionPane.showMessageDialog(NULL,
//                 MessageFormat.format(tr("ImportEnginesAdded"), new Object[]{enginesAdded}),
//                 tr("ImportFailed"), JOptionPane.ERROR_MESSAGE);
//      QMessageBox::information(NULL, tr("Import Failed!"), tr("%1 locomotives added to operations roster").arg(enginesAdded));
//     }
     emit finished(enginesAdded);
 }
}
