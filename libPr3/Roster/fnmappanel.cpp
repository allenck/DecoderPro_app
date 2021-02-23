#include "fnmappanel.h"
#include <QLabel>
#include "variabletablemodel.h"
#include "cvutil.h"
#include <QRegExp>
#include "loggerfactory.h"

//FnMapPanel::FnMapPanel(QWidget *parent) :
//    QFrame(parent)
//{
//}
/**
 * Provide a graphical representation of the NMRA S&RP mapping between cab functions
 * and physical outputs.
 *<P>
 * This is mapped via various definition variables.  A -1 means don't provide it. The
 * panel then creates a GridBayLayout: <dl>
 *  <DT>Column cvNum  	<DD> CV number (Typically 0)
 *  <DT>Column fnName  	<DD> Function name (Typically 1)
 *
 *  <DT>Row outputLabel	<DD> "output label" (Typically 0)
 *  <DT>Row outputNum	<DD> "output number" (Typically 1)
 *  <DT>Row outputName	<DD> "output name (or color)" (Typically 2)
 *
 *  <DT>Row firstFn     <DD> Row for first function, usually FL0.  Will go up from this,
 *							 with higher numbered functions in higher numbered columns.
 *  <DT>Column firstOut  <DD> Column for leftmost numbered output
 *</dl>
 *<P>
 * Although support for the "CV label column" is still here, its turned off now.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version			$Revision: 17977 $
 */
// /*public*/ class FnMapPanel extends JPanel {

/*public*/ FnMapPanel::FnMapPanel(VariableTableModel* v, QList<int>* varsUsed, QDomElement model, QWidget* parent)  : JPanel(parent)
{
 if (log->isDebugEnabled()) {
     log->debug("Function map starts");
 }
 _varModel = v;

 // Set up fnList array
 this->fnList = QList<QString>();
 //fnList.addAll(Arrays.asList(fnExtraList));
 foreach(QString s, fnExtraList)
  fnList.append(s);
 for (int i = 0; i <= highestFn; i++) {
     fnList.append("F" + QString::number(i));
 }
 for (int i = 0; i <= highestSensor; i++) {
     fnList.append("S" + QString::number(i));
 }

 numFn = fnList.size() * fnVariantList.length();

 // set up default names and labels
 QStringList labels = {tr("White"), tr("Yellow"), tr("Green"), tr("Vlt/Brwn")};
 for (int iOut = 0; iOut < maxOut; iOut++) {
     outName[iOut] = QString::number(iOut + 1);
     outIsUsed[iOut] = false;
     // get default labels, if any
     try {
         //outLabel[iOut] = tr("FnMapOutLabelDefault_" + (iOut + 1));
      outLabel[iOut] = labels[iOut];
     } catch (MissingResourceException e) {
         outLabel[iOut] = "";  // no default label specified
     }
 }

 // configure number of channels, arrays
 configOutputs(model);

 // initialize the layout
 gl = new GridBagLayout();
 cs = new GridBagConstraints();
 setLayout(gl);
 {
  QLabel* l = new QLabel("Output wire or operation");
  cs->gridy = outputNameRow;
  cs->gridx = 3;
  cs->gridwidth = GridBagConstraints::REMAINDER;
  //gl.setConstraints(l, cs);
  gl->addWidget(l, *cs);
  cs->gridwidth = 1;
 }

 labelAt(0, fnNameCol, tr("Description"), GridBagConstraints::LINE_START);

 // Loop through function names and output names looking for variables
 int row = firstFnRow;
 for (QString fnNameBase : fnList) {
  if ((row - firstFnRow) >= numFn) {
      break; // for compatibility with legacy defintions
  }
  for (QString fnDirVariant : fnVariantList) {
      QString fnNameString = fnNameBase + fnDirVariant;
//                log.info(fnNameString);
      bool rowIsUsed = false;
      for (int iOut = 0; iOut < numOut; iOut++) {
          // if column is not suppressed by blank headers
          if (outName[iOut] != ("") || outLabel[iOut] !=("")) {
              // find the variable using the output number or label
              // include an (alt) variant to enable Tsunami function exchange definitions
              QString searchNameBase = fnNameString + " controls output ";
              QList<QString> names = QList<QString>();
              if (outName[iOut] != (QString::number(iOut + 1))) {
                  names.append(searchNameBase + (iOut + 1));
                  names.append(searchNameBase + (iOut + 1) + "(alt)");
              }
              names.append(searchNameBase + outName[iOut]);
              names.append(searchNameBase + outName[iOut] + "(alt)");
              for (QString name : names) {
//                            log.info("Search name='" + name + "'");
                  int iVar = _varModel->findVarIndex(name);
                  if (iVar >= 0) {
                      if (log->isDebugEnabled()) {
                          log->debug(tr("Process var: %1 as index %2").arg(name).arg(iVar));
                      }
                      varsUsed->append((iVar));
                      VariableValue* var = _varModel->getVariable(iVar);
                      // Only single-bit (exactly two options) variables should use checkbox
                      // this really would be better fixed in EnumVariableValue
                      // done here to avoid side effects elsewhere
                      QString displayFormat = "checkbox";
                      if ((var->getMask() != "") && (((var->getMask().replace("X", "")).length()) != 1)) {
                          displayFormat = "";
                      }
                      QWidget* j = (_varModel->getRep(iVar, displayFormat));
                      j->setToolTip(CvUtil::addCvDescription((fnNameString + " "
                              + tr("controls output") + " "
                              + outName[iOut] + " " + outLabel[iOut]), var->getCvDescription(), var->getMask()));
                      int column = firstOutCol + iOut;
                      saveAt(row, column, j);
                      rowIsUsed = true;
                      outIsUsed[iOut] = true;
                  } else {
                      if (log->isDebugEnabled()) {
                          log->debug(tr("Did not find var: %1").arg(name));
                      }
                  }
              }
          }
      }
      QMap<QString, QString> fnMap  {
                                     {"FnMap_FL(f)", tr("Forward Headlight F0(f)")},
                                     {"FnMap_FL(r)", tr("Reverse Headlight F0(r)")},
                                     {"FnMap_HL", tr("Headlight")},
                                     {"FnMap_RL", tr("Rear light")},
                                     {"FnMap_A", tr("Aux")},
                                     {"FnMap_(f)", tr("(f)")},
                                     {"FnMap_(r)", tr("(r)")},
                                     {"FnMap_F", tr("Function")},
                                     {"FnMap_S", tr("Sensor")},
                                     {"FnMap_WS", tr("Wheel Sensor")},
                                     {"FnMap_RS", tr("Reserved")},
                                     {"FnMap_STATE", tr("State")},
                                     {"FnMap_STOP", tr("Stopped")},
                                     {"FnMap_DRIVE", tr("Moving")},
                                     {"FnMap_DIR", tr("Direction")},
                                     {"FnMap_FWD", tr("Forward")},
                                     {"FnMap_REV", tr("Reverse")}};
      if (rowIsUsed)
      {
       QRegExp rx("F\\d+");
       QRegExp rx2("S\\d+");
          //if (fnNameBase.matches("F\\d+"))
       if(rx.indexIn(fnNameBase)>=0)
       {
           fnNameString = tr("Function") + " " + fnNameBase.mid(1);
           if (fnDirVariant != ("")) {
               //fnNameString = fnNameString + tr("FnMap_" + fnDirVariant);
            fnNameString = fnNameString + fnMap.value(tr("FnMap_") + fnDirVariant);
           }
       }
       //else if (fnNameBase.matches("S\\d+"))
       else if(rx2.indexIn(fnNameBase)>= 0)
       {
              fnNameString = fnMap.value("FnMap_S") + " " + fnNameBase.mid(1);
              if (fnDirVariant != ("")) {
                  fnNameString = fnNameString + fnMap.value("FnMap_" + fnDirVariant);
              }
       }
       else {
                // See if we have a match for whole fnNameString
                  //fnNameString = tr("FnMap_" + fnNameString);
                  fnNameString = fnMap.value("FnMap_" + fnNameString, "");
           if(fnNameString == "") {
                   // Else see if we have a match for fnNameBase
                      fnNameString = fnMap.value("FnMap_" + fnNameBase);
                      if (fnDirVariant != ("")) { // Add variant
                          //fnNameString = fnNameString + tr("FnMap_" + fnDirVariant);
                       fnNameString = fnNameString + fnMap.value("FnMap_" + fnDirVariant);
                      }
              }
          }
          labelAt(row, fnNameCol, fnNameString, GridBagConstraints::LINE_START);
          row++;
      }

  }
 }
 if (log->isDebugEnabled()) {
     log->debug("Function map complete");
 }

 // label used outputs only
 for (int iOut = 0; iOut < numOut; iOut++) {
     if (outIsUsed[iOut]) {
         labelAt(outputNumRow, firstOutCol + iOut, outName[iOut]);
         labelAt(outputLabelRow, firstOutCol + iOut, outLabel[iOut]);
     }
 }

 // padding for the case of few outputs
 cs->gridwidth = GridBagConstraints::REMAINDER;
 labelAt(outputNumRow, firstOutCol + numOut, "");
}

void FnMapPanel::saveAt(int row, int column, QWidget* j) {
    this->saveAt(row, column, j, GridBagConstraints::CENTER);
}

void FnMapPanel::saveAt(int row, int column, QWidget* j, int anchor) {
    if (row < 0 || column < 0) {
        return;
    }
    cs = new GridBagConstraints();
    cs->gridy = row;
    cs->gridx = column;
    cs->anchor = anchor;
    gl->setConstraints( *cs);
    layout()->addWidget(j);
}


void FnMapPanel::labelAt(int row, int column, QString name) {
    this->labelAt(row, column, name, GridBagConstraints::CENTER);
}

void FnMapPanel::labelAt(int row, int column, QString name, int anchor) {
    if (row < 0 || column < 0) {
        return;
    }
    JLabel* t = new JLabel(" " + name + " ");
    saveAt(row, column, t, anchor);
}

/**
 * Use the "model" element from the decoder definition file
 * to configure the number of outputs and set up any that
 * are named instead of numbered.
 */
//@SuppressWarnings("unchecked")
/*protected*/ void FnMapPanel::configOutputs(QDomElement model)
{
 if (model.isNull())
 {
  log->debug("configOutputs was given a NULL model");
  return;
 }
 // get numOuts, numFns or leave the defaults
 QString a = model.attribute("numOuts");
 bool b;
// try {
 if (a!="") numOut = a.toInt(&b);
 if(!b)log->error("error handling decoder's numOuts value");
 a = model.attribute("numFns");
 //try {
 if (a!="") numFn = a.toInt(&b);
 if(!b)log->error("error handling decoder's numFns value");
 if (log->isDebugEnabled()) log->debug("numFns, numOuts "+QString::number(numFn)+","+QString::number(numOut));
 // take all "output" children
 QDomNodeList elemList = model.elementsByTagName("output");
 if (log->isDebugEnabled()) log->debug("output scan starting with "+QString::number(elemList.size())+" elements");
 for (int i=0; i<elemList.size(); i++)
 {
  QDomElement e = elemList.at(i).toElement();
  QString name = e.attribute("name");
  // if this a number, or a character name?
  //try {
  bool bOk;
  int outputNum = (name).toInt(&bOk);
  if(bOk)
  {
   // yes, since it was converted.  All we do with
   // these are store the label index (if it exists)
   //QString at = LocaleSelector.attributettribute(e, "label");
   QString at = e.attribute("label");
   if ( at!="" && outputNum<=numOut)
    outLabel.replace(outputNum-1, at);
  }
  else
  {
   // not a number, must be a name
   if (numOut<maxOut)
   {
    outName.replace(numOut, name);
    QString at;
    //if ((at=LocaleSelector.attributettribute(e, "label"))!=NULL)
    if((at=e.attribute("label"))!="")
     outLabel.replace(numOut,at);
    else
     outLabel.replace(numOut,"");
    numOut++;
   }
  }
 }
}

/** clean up at end */
/*public*/ void FnMapPanel::dispose() {
    //removeAll();
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* FnMapPanel::log = LoggerFactory::getLogger("FnMapPanel");
