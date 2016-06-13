#include "fnmappanel.h"
#include <QLabel>
#include "variabletablemodel.h"

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

/*public*/ FnMapPanel::FnMapPanel(VariableTableModel* v, QList<int>* varsUsed, QDomElement model, QFrame* parent)  : QFrame(parent)
{
 log = new Logger("FnMapPanel");
 cvNum = -1;
 fnName = 0;
 firstOut = 1;

 // rows
 outputName = 0;
 outputNum = 1;
 outputLabel = 2;
 firstFn = 3;

 // these will eventually be passed in from the ctor
 numFn = 14;  // include FL(f) and FL(r) in the total
 numOut = 20;
 maxFn = 30;  // include FL(f) and FL(r) in the total; update list of names if you update this
 maxOut = 40; // update list of names if you update this

 gl = NULL;
 cs = NULL;
 fnList << "FL(f)"<< "FL(r)"<< "F1"<< "F2"<< "F3"<< "F4"<< "F5"<< "F6"<< "F7"<< "F8"<< "F9"<< "F10"<<
                                           "F11"<< "F12"<< "F13"<< "F14"<< "F15"<< "F16"<< "F17"<< "F18"<< "F19"<< "F20"<<
                                           "F21"<< "F22"<< "F23"<< "F24"<< "F25"<< "F26"<< "F27"<< "F28" << "F29";

 outLabel << "White"<< "Yellow"<< "Green"<< "Vlt/Brwn"<< ""<< ""<< ""<< ""<< ""<< ""<<
                                            ""<< ""<< ""<< ""<< ""<<""<< ""<< ""<< ""<< ""<<
                                            ""<< ""<< ""<< ""<< ""<<""<< ""<< ""<< ""<< ""<<
                                            ""<< ""<< ""<< ""<< ""<<""<< ""<< ""<< ""<< "";

 outName << "1"<< "2"<< "3"<< "4"<< "5"<< "6"<< "7"<< "8"<< "9"<< "10"<<
                                           "11"<< "12"<< "13"<< "14"<< "15"<< "16"<< "17"<< "18"<< "19"<< "20"<<
                                           "21"<< "22"<< "23"<< "24"<< "25"<< "26"<< "27"<< "28"<< "29"<< "30"<<
                                           "31"<< "32"<< "33"<< "34"<< "35"<< "36"<< "37"<< "38"<< "39"<< "40"
               ;
 if (log->isDebugEnabled()) log->debug("Function map starts");
 _varModel = v;

 // configure number of channels, arrays
 configOutputs(model);

 // initialize the layout
 gl = new QGridLayout();
 cs = new GridBagConstraints();
 setLayout(gl);
 {
  QLabel* l = new QLabel("Output wire or operation");
  cs->gridy = outputName;
  cs->gridx = 3;
  cs->gridwidth = GridBagConstraints::REMAINDER;
  //gl.setConstraints(l, cs);
  gl->addWidget(l, cs->gridy, cs->gridx, cs->rowSpan(), cs->colSpan());
  cs->gridwidth = 1;
 }
 // dummy structure until we figure out how to convey CV numbers programmatically
 if (cvNum>=0)
 {
    labelAt( 0, 0, "CV");
    labelAt( firstFn   , cvNum, "33");
    labelAt( firstFn+ 1, cvNum, "34");
    labelAt( firstFn+ 2, cvNum, "35");
    labelAt( firstFn+ 3, cvNum, "36");
    labelAt( firstFn+ 4, cvNum, "37");
    labelAt( firstFn+ 5, cvNum, "38");
    labelAt( firstFn+ 6, cvNum, "39");
    labelAt( firstFn+ 7, cvNum, "40");
    labelAt( firstFn+ 8, cvNum, "41");
    labelAt( firstFn+ 9, cvNum, "42");
    labelAt( firstFn+10, cvNum, "43");
    labelAt( firstFn+11, cvNum, "44");
    labelAt( firstFn+12, cvNum, "45");
    labelAt( firstFn+13, cvNum, "46");
 }

 labelAt(0,fnName, "Description");

 labelAt( firstFn   , fnName, "Forward Headlight F0(F)");
 labelAt( firstFn+ 1, fnName, "Reverse Headlight F0(R)");
 if (numFn>2) labelAt( firstFn+ 2, fnName, "Function 1");
 if (numFn>3) labelAt( firstFn+ 3, fnName, "Function 2");
 if (numFn>4) labelAt( firstFn+ 4, fnName, "Function 3");
 if (numFn>5) labelAt( firstFn+ 5, fnName, "Function 4");
 if (numFn>6) labelAt( firstFn+ 6, fnName, "Function 5");
 if (numFn>7) labelAt( firstFn+ 7, fnName, "Function 6");
 if (numFn>8) labelAt( firstFn+ 8, fnName, "Function 7");
 if (numFn>9) labelAt( firstFn+ 9, fnName, "Function 8");
 if (numFn>10) labelAt( firstFn+10, fnName, "Function 9");
 if (numFn>11) labelAt( firstFn+11, fnName, "Function 10");
 if (numFn>12) labelAt( firstFn+12, fnName, "Function 11");
 if (numFn>13) labelAt( firstFn+13, fnName, "Function 12");
 if (numFn>14) labelAt( firstFn+14, fnName, "Function 13");
 if (numFn>15) labelAt( firstFn+15, fnName, "Function 14");
 if (numFn>16) labelAt( firstFn+16, fnName, "Function 15");
 if (numFn>17) labelAt( firstFn+17, fnName, "Function 16");
 if (numFn>18) labelAt( firstFn+18, fnName, "Function 17");
 if (numFn>19) labelAt( firstFn+19, fnName, "Function 18");
 if (numFn>20) labelAt( firstFn+20, fnName, "Function 19");
 if (numFn>21) labelAt( firstFn+21, fnName, "Function 20");
 if (numFn>22) labelAt( firstFn+22, fnName, "Function 21");
 if (numFn>23) labelAt( firstFn+23, fnName, "Function 22");
 if (numFn>24) labelAt( firstFn+24, fnName, "Function 23");
 if (numFn>25) labelAt( firstFn+25, fnName, "Function 24");
 if (numFn>26) labelAt( firstFn+26, fnName, "Function 25");
 if (numFn>27) labelAt( firstFn+27, fnName, "Function 26");
 if (numFn>28) labelAt( firstFn+28, fnName, "Function 27");
 if (numFn>29) labelAt( firstFn+29, fnName, "Function 28");

 // label outputs
 for (int iOut=0; iOut<numOut; iOut++)
 {
  labelAt( outputNum,   firstOut+iOut, outName[iOut]);
  labelAt( outputLabel, firstOut+iOut, outLabel[iOut]);
 }

 for (int iFn = 0; iFn < numFn; iFn++)
 {
  for (int iOut = 0; iOut < numOut; iOut++)
  {
   // find the variable using the output label
   QString name = fnList[iFn]+" controls output "+outName[iOut];
   int iVar = _varModel->findVarIndex(name);
   if (iVar>=0)
   {
    if (log->isDebugEnabled()) log->debug("Process var: "+name+" as index "+iVar);
    varsUsed->append((iVar));
    QWidget* j = (QWidget*)(_varModel->getRep(iVar, "checkbox"));
    int row = firstFn+iFn;
    int column = firstOut+iOut;
    saveAt(row, column, j);
   }
   else
   {
    if (log->isDebugEnabled()) log->debug("Did not find var: "+name);
   }
  }
 }
 if (log->isDebugEnabled()) log->debug("Function map complete");
}

void FnMapPanel::saveAt(int row, int column, QWidget* j) {
    if (row<0 || column<0) return;
    cs->gridy = row;
    cs->gridx = column;
    //gl.setConstraints(j, cs);
    //add(j);
    gl->addWidget(j,cs->gridy, cs->gridx, cs->rowSpan(), cs->colSpan());
}

void FnMapPanel::labelAt(int row, int column, QString name) {
    if (row<0 || column<0) return;
    QLabel* t = new QLabel(" "+name+" ");
    saveAt(row, column, t);
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
