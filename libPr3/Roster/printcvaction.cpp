#include "printcvaction.h"
#include "imageicon.h"
#include "hardcopywriter.h"
#include "exceptions.h"
#include "paneprogframe.h"
#include "rosterentry.h"
#include "cvtablemodel.h"
#include <QVector>
#include "cvtablemodel.h"
#include "jlabel.h"

//PrintCvAction::PrintCvAction(QObject *parent) :
//    QAction(parent)
//{
//}
/**
 * Action to print the information in the CV table.
 * <P>
 * This uses the older style printing, for compatibility with Java 1.1.8 in
 * Macintosh MRJ
 *
 * @author		Bob Jacobsen   Copyright (C) 2003; D Miller Copyright 2003, 2005
 * @version             $Revision: 28013 $
 */
///*public*/ class PrintCvAction  extends AbstractAction {

/**
 *
 */
// private static final long serialVersionUID = -834651924896005111L;

/*public*/ PrintCvAction::PrintCvAction(QString actionName, CvTableModel* pModel, PaneProgFrame* pParent, bool preview, RosterEntry* pRoster) : QAction(actionName, (QObject*)pParent)
{
 //super(actionName);
 TABLE_COLS = 3;
 mModel = pModel;
 mFrame = pParent;
 isPreview = preview;
 mRoster = pRoster;
 log = new Logger("PrintCvAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


/*public*/ void PrintCvAction::printInfoSection(HardcopyWriter* w)
{
 ImageIcon* icon = new ImageIcon(/*ClassLoader.getSystemResource*/ ":/resources/decoderpro.gif", "resources/decoderpro.gif");
 // we use an ImageIcon because it's guaranteed to have been loaded when ctor is complete
 w->write(icon->getImage(), new JLabel());
 w->setFontStyle(QFont::StyleNormal);
 w->setFontWeight(QFont::Bold);
 //Add a number of blank lines
 int height = icon->getImage().height();
 int blanks = (height-w->getLineAscent())/w->getLineHeight();

 try
 {
  for(int i = 0; i<blanks; i++)
  {
   QString s = "\n";
   w->write(s,0,s.length());
  }
 }
 catch (IOException e)
 {
  log->warn("error during printing: "+e.getMessage());
 }
 mRoster->printEntry(w);
 w->setFontStyle(QFont::StyleNormal);
 w->setFontWeight(QFont::Normal);
}

/*public*/ void PrintCvAction::actionPerformed(ActionEvent* /*e*/)
{

 // obtain a HardcopyWriter to do this
 HardcopyWriter* writer = NULL;
 try
 {
  writer = new HardcopyWriter(mFrame, mFrame->getRosterEntry()->getId(), 10, .8, .5, .5, .5, isPreview);

  // print the decoder info section, etc
  printInfoSection(writer);
  QString s = "\n\n";
  writer->write(s, 0, s.length());

  //Initialize some variables to define the CV table size
  int cvCount = mModel->rowCount(QModelIndex());
  int tableLeft = 1, tableRight = TABLE_COLS*22+1, tableTopRow = 0, tableBottomRow = 0, tableHeight = cvCount/TABLE_COLS;
  if (cvCount%TABLE_COLS > 0) tableHeight++;

  /*Start drawing the table of CVs. Set up the table with 4 columns of CV/Value
  pairs and Draw the table borders and lines.  Each column width is
  16 characters, including the starting vertical line, but not the
  ending one.  Therefore the total table width is 64+1 characters
  The colummn headings take 2 lines
  4 columns of 20 gives 80 CVs possible. NMRA specs only define about 70 CVs
  including all the optional ones plus some Manufacturer ones.  80 should be
  enough, although more can be added by increasing the tableHeight value
  */

  //Set the top row and draw top line to start the table of CVs
  tableTopRow = writer->getCurrentLineNumber();
  writer->write(tableTopRow,tableLeft,tableTopRow,tableRight);

  //set the bottom of the table
  tableBottomRow = tableTopRow + tableHeight + 2;

  //Draw vertical lines for columns
  for (int i=1; i<76; i=i+22)
  {
   writer->write(tableTopRow,i,tableBottomRow,i);
  }

  //Draw remaining horizontal lines
  writer->write(tableTopRow+2,tableLeft,tableTopRow+2,tableRight);
  writer->write(tableBottomRow,tableLeft,tableBottomRow,tableRight);

  writer->setFontStyle(QFont::StyleNormal);  //set font to Bold
  writer->setFontWeight(QFont::Bold);
  // print a simple heading
  s = "         Value                  Value                   Value";
  writer->write(s, 0, s.length());
  s = "\n";
  writer->write(s,0,s.length());
  s = "    CV  Dec Hex            CV  Dec Hex             CV  Dec Hex";
  writer->write(s, 0, s.length());
  s = "\n";
  writer->write(s,0,s.length());
  writer->setFontStyle(QFont::StyleNormal); //set font back to Normal
  writer->setFontWeight(QFont::Normal);

  //create an array to hold CV/Value strings to allow reformatting and sorting
  //Same size as the table drawn above (4 columns*tableHeight; heading rows
  //not included

  QStringList cvStrings = (QStringList) (new QVector<QString>(TABLE_COLS*tableHeight, ""))->toList();

  //blank the array
  //  for (int i=0; i < cvStrings.length; i++) cvStrings[i] = "";

  // get each CV and value
  for (int i=0; i<mModel->rowCount(QModelIndex()); i++)
  {

   CvValue* cv = mModel->getCvByRow(i);
   int value = cv->getValue();

   //convert and pad numbers as needed
   //String numString = String.format("%12s",cv.number());
   QString numString = QString("%1").arg(cv->number().toInt(),6);
   QString valueString = QString("%1").arg(value, 3);
   QString valueStringHex = QString::number(value,16).toUpper();
   if (value < 16)
    valueStringHex = "0" + valueStringHex;

//   for (int j = 1; j < 3; j++)
//   {
//    if (valueString.length() < 3) valueString = " " + valueString;
//   }
   //Create composite string of CV and its decimal and hex values
   s =  numString + "  " + valueString + "  " + valueStringHex + " ";

   //populate printing array - still treated as a single column
   cvStrings.replace(i, s);
  }

  //sort the array in CV order (just the members with values)
  QString temp;
  bool swap = false;
  do
  {
   swap = false;
   for (int i = 0; i < mModel->rowCount(QModelIndex()) - 1; i++)
   {
    if ( cvSortOrderVal(cvStrings.at(i + 1).mid(0,7).trimmed()) < cvSortOrderVal(cvStrings.at(i).mid(0,7).trimmed()) )
    {
     temp = cvStrings.at(i + 1);
     cvStrings.replace(i + 1,cvStrings.at(i));
     cvStrings.replace(i, temp);
     swap = true;
    }
   }
  }
  while (swap == true);

  //Print the array in three columns
  for (int i = 0; i < tableHeight; i++)
  {
   s = cvStrings[i] + "       " + cvStrings[i + tableHeight] + "        " + cvStrings[i + tableHeight * 2];
   writer->write(s, 0, s.length());
   s = "\n";
   writer->write(s,0,s.length());}
  //write an extra character to work around the
  //last character truncation bug with HardcopyWriter
  s=" \n";
  writer->write(s, 0, s.length());
 }
 catch (IOException ex1)
 {
  log->error("IO exception while printing");
  return;
 }
// catch (HardcopyWriter.PrintCanceledException ex2)
// {
//  log.debug("Print cancelled");
//  return;
// }

 writer->close();
}
/**
 * Returns a representation of a CV name as a long integer sort order value.
 * The value itself is not meaningful, but is used in comparisons when sorting.
 */
/*public*/ /*static*/ long PrintCvAction::cvSortOrderVal(QString cvName)
{
 /*final*/ int MAX_CVMNUM_SPACE = 1200;

 QStringList cvNumStrings = cvName.split(QRegExp("\\."));
 long sortVal = 0;
 for (int i=0; i < (cvNumStrings.length()); i++)
 {
  sortVal = (sortVal * MAX_CVMNUM_SPACE) +
                cvNumStrings[i].toInt();
 }
 return sortVal;
}
