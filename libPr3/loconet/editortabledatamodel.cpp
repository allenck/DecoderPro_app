#include "editortabledatamodel.h"
#include "spjfile.h"
#include "logger.h"
#include "jtextfield.h"
#include <QTableView>
#include "jtextarea.h"
#include "jframe.h"
#include <QScrollArea>
#include "sdfbuffer.h"
#include "jmrijframe.h"
#include "wavbuffer.h"
#include <QSound>
#include "editorframe.h"
#include <QFileDialog>
#include "hardcopywriter.h"
#include <QComboBox>
#include "fileutil.h"
#include "file.h"

//EditorTableDataModel::EditorTableDataModel(QObject *parent) :
//  AbstractTableModel(parent)
//{
//}
/**
 * Table data model for display of Digitrax SPJ files
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2006
 * @author Dennis Miller Copyright (C) 2006
 * @version	$Revision: 28746 $
 */
///*public*/ class EditorTableDataModel extends javax.swing.table.AbstractTableModel {

/**
 *
 */

//static volatile ResourceBundle res = null;   // defer to first use


//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//        justification = "cache resource at 1st start, threading OK")
/*public*/ EditorTableDataModel::EditorTableDataModel(SpjFile* file, QObject *parent) :
  AbstractTableModel(parent){
    //super();
//    if (res == null) {
//        res = ResourceBundle.getBundle("jmri.jmrix.loconet.soundloader.Editor");
//    }
    this->file = file;
 log = new Logger("EditorTableDataModel");
}

/*public*/ int EditorTableDataModel::rowCount(const QModelIndex &parent) const
{
    // The 0th header is not displayed
    return file->numHeaders() - 1;
}

/*public*/ int EditorTableDataModel::columnCount(const QModelIndex &parent) const
{
 return NUMCOLUMN;
}

/*public*/ QVariant  EditorTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  switch (section)
  {
   case HEADERCOL:
       return tr("Number");
   case TYPECOL:
       return tr("Type");
   case HANDLECOL:
       return tr("Handle");
   case MAPCOL:
       return tr("Sound Name");
   case FILENAMECOL:
       return tr("File Name");
   case LENGTHCOL:
       return tr("Length");
   case PLAYBUTTONCOL:
       return tr("");
   case REPLACEBUTTONCOL:
       return tr("");

   default:
          return "unknown";
  }
 }
 return QVariant();
}

///*public*/ Class<?> getColumnClass(int col) {
//    switch (col) {
//        case HEADERCOL:
//        case HANDLECOL:
//            return Integer.class;
//        case LENGTHCOL:
//            return Float.class;
//        case MAPCOL:
//        case TYPECOL:
//        case FILENAMECOL:
//            return String.class;
//        case REPLACEBUTTONCOL:
//        case PLAYBUTTONCOL:
//            return JButton.class;
//        default:
//            return null;
//    }
//}

/*public*/ Qt::ItemFlags EditorTableDataModel::flags(const QModelIndex &index) const
{
    switch (index.column()) {
        case REPLACEBUTTONCOL:
        case PLAYBUTTONCOL:
            return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        default:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
}

/*public*/ QVariant EditorTableDataModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
  switch (col)
  {
   case HEADERCOL:
       return (row);
   case HANDLECOL:
       return (file->getHeader(row + 1)->getHandle());
   case MAPCOL:
       return file->getMapEntry(file->getHeader(row + 1)->getHandle());
   case FILENAMECOL:
       return file->getHeader(row + 1)->getName();
   case TYPECOL:
       return file->getHeader(row + 1)->typeAsString();
   case LENGTHCOL:
   {
    if (!file->getHeader(row + 1)->isWAV())
    {
     return QVariant();
    }
#if 1
    float rate = (new WavBuffer(file->getHeader(row + 1)->getByteArray()))->getSampleRate();
    if (rate == 0.0)
    {
     log->error("Rate should not be zero");
     return QVariant();
    }

    float time = file->getHeader(row + 1)->getDataLength() / rate;
    return QString::number(time,'g',3);
#else
    return QVariant();
#endif
   }
   case PLAYBUTTONCOL:
   {
       if (file->getHeader(row + 1)->isWAV())
       {
           return tr("Play");
       } else if (file->getHeader(row + 1)->isTxt()) {
           return tr("View");
       } else if (file->getHeader(row + 1)->isMap()) {
           return tr("View");
       } else if (file->getHeader(row + 1)->isSDF()) {
           return tr("View");
       } else {
        return QVariant();
       }
   }
   case REPLACEBUTTONCOL:
   {
       if (file->getHeader(row + 1)->isWAV()) {
           return tr("Replace");
       }
       if (file->getHeader(row + 1)->isSDF()) {
           return tr("Edit");
       } else {
        return QVariant();
       }
   }
   default:
   {
       log->error("internal state inconsistent with table requst for " + QString::number(row) + " " + col);
       return QVariant();
   }
  }
 }
 return QVariant();
}

/*public*/ int EditorTableDataModel::getPreferredWidth(int col) {
    JTextField* b;
    switch (col) {
        case TYPECOL:
            return  JTextField(8).getPreferredSize().width();
        case MAPCOL:
            return  JTextField(12).getPreferredSize().width();
        case HEADERCOL:
        case HANDLECOL:
            return  JTextField(3).getPreferredSize().width();
        case FILENAMECOL:
            return  JTextField(12).getPreferredSize().width();
        case LENGTHCOL:
            return  JTextField(5).getPreferredSize().width();
        case PLAYBUTTONCOL:
            b = new JTextField( data(index(1, PLAYBUTTONCOL), Qt::DisplayRole).toString());
     return b->getPreferredSize().width() + 30;
        case REPLACEBUTTONCOL:
            b = new JTextField( data(index(1, REPLACEBUTTONCOL), Qt::DisplayRole).toString());
     return b->getPreferredSize().width() + 30;
        default:
            log->warn("Unexpected column in getPreferredWidth: " + QString::number(col));
            return  JTextField(8).getPreferredSize().width();
    }
}

/*public*/ bool EditorTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();
  if (col == PLAYBUTTONCOL)
  {
   // button fired, handle
   if (file->getHeader(row + 1)->isWAV())
   {
    playButtonPressed(value, row, col);
    return true;
   }
   else if (file->getHeader(row + 1)->isTxt())
   {
    viewTxtButtonPressed(value, row, col);
    return true ;
   }
   else if (file->getHeader(row + 1)->isMap())
   {
    viewTxtButtonPressed(value, row, col);
    return true;
   }
   else if (file->getHeader(row + 1)->isSDF())
   {
    viewSdfButtonPressed(value, row, col);
    return true;
   }
  }
  else if (col == REPLACEBUTTONCOL)
  {
   // button fired, handle
   if (file->getHeader(row + 1)->isWAV())
   {
    replWavButtonPressed(value, row, col);
   }
   else if (file->getHeader(row + 1)->isSDF())
   {
    editSdfButtonPressed(value, row, col);
    return true ;
   }
  }
 }
 return false;
}

//// should probably be abstract and put in invoking GUI
//static JFileChooser chooser;  // shared across all uses

void EditorTableDataModel::replWavButtonPressed(QVariant value, int row, int col)
{
#if 0
    if (chooser == null) {
        chooser = new JFileChooser(FileUtil.getUserFilesPath());
    }
    chooser.rescanCurrentDirectory();
    int retVal = chooser.showOpenDialog(null);
    if (retVal != JFileChooser.APPROVE_OPTION) {
        return;  // give up if no file selected
    }
#endif
    QString fName = QFileDialog::getOpenFileName(NULL, tr("Select Sound file"), FileUtil::getUserFilesPath(), tr("Sound files: (*.wav)"));
    if (fName == "") return;
    // load file
    WavBuffer* buff;
    try {
        buff = new WavBuffer(/*chooser.getSelectedFile()*/new File(fName));
    } catch (Exception* e) {
        log->error("Exception loading file: " + e->getMessage());
        return;
    }
    // store to memory
    file->getHeader(row + 1)->setContent(buff->getByteArray(), buff->getDataStart(), buff->getDataSize());
    // update rest of header
    file->getHeader(row + 1)->setName(/*chooser.getSelectedFile().getName()*/fName);

    // mark table changes in other rows
    fireTableRowsUpdated(row, row);

}

// should probably be abstract and put in invoking GUI
void EditorTableDataModel::playButtonPressed(QVariant value, int row, int col)
{
 WavBuffer* b = new WavBuffer(file->getHeader(row+1)->getByteArray());
//    SoundUtil.playSoundBuffer(file.getHeader(row + 1).getByteArray());
 b->play();
}

// should probably be abstract and put in invoking GUI
// Also used to display the .map block
void EditorTableDataModel::viewTxtButtonPressed(QVariant value, int row, int col)
{
 QString content = QString(file->getHeader(row + 1)->getByteArray()->data());
 JFrame* frame = new JFrame();
 JTextArea* text = new JTextArea(/*content*/);
 text->setEditable(false);
// text->setFont(new Font("Monospaced", Font.PLAIN, text.getFont().getSize()));
 //frame.getContentPane().add(new JScrollPane(text));
 text->setPlainText(content);
 QScrollArea* scrollArea = new QScrollArea;
 frame->setCentralWidget(scrollArea);
 scrollArea->setWidget(text);
 scrollArea->setWidgetResizable(true);
 frame->pack();
 frame->setVisible(true);
}

// should probably be abstract and put in invoking GUI
void EditorTableDataModel::viewSdfButtonPressed(QVariant value, int row, int col)
{
 SdfBuffer* buff = new SdfBuffer(file->getHeader(row + 1)->getByteArray());
 QString content = buff->toString();
 JFrame* frame = new JmriJFrameX(tr("Sdf View"));
 JTextArea* text = new JTextArea(/*content*/);
 text->setEditable(false);
 text->setPlainText(content);
// text->setFont(new Font("Monospaced", Font.PLAIN, text.getFont().getSize()));
 //frame.getContentPane().add(new JScrollPane(text));
 QScrollArea* scrollArea = new QScrollArea;
 scrollArea->setWidgetResizable(true);
 frame->setCentralWidget(scrollArea);
 scrollArea->setWidget(text);
 frame->pack();
 frame->setVisible(true);
}

// should probably be abstract and put in invoking GUI
void EditorTableDataModel::editSdfButtonPressed(QVariant value, int row, int col)
{
 EditorFrame* sdfEditor
            = new EditorFrame(file->getHeader(row + 1)->getSdfBuffer());
 sdfEditor->setVisible(true);
}

/**
 * Configure a table to have our standard rows and columns. This is
 * optional, in that other table formats can use this table model. But we
 * put it here to help keep it consistent.
 *
 * @param table
 */
/*public*/ void EditorTableDataModel::configureTable(QTableView* table)
{
    // allow reordering of the columns
//    table.getTableHeader().setReorderingAllowed(true);

    // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
//    table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

  // resize columns as requested
//  for (int i = 0; i < table->columnCount(QModelIndex()); i++) {
//      int width = getPreferredWidth(i);
//      table->getColumnModel().getColumn(i).setPreferredWidth(width);
//  }
  table->resizeColumnsToContents();

  // have the value column hold a button
//  setColumnToHoldButton(table, PLAYBUTTONCOL, largestWidthButton(PLAYBUTTONCOL));
//  setColumnToHoldButton(table, REPLACEBUTTONCOL, largestWidthButton(REPLACEBUTTONCOL));
}
#if 0
/*public*/ QPushButton* largestWidthButton(int col) {
    JButton retval = new JButton("TTTT");
    if (col == PLAYBUTTONCOL) {
        retval = checkLabelWidth(retval, "ButtonPlay");
        retval = checkLabelWidth(retval, "ButtonView");
    } else if (col == REPLACEBUTTONCOL) {
        retval = checkLabelWidth(retval, "ButtonEdit");
        retval = checkLabelWidth(retval, "ButtonReplace");
    }
    return retval;
}

/*private*/ JButton checkLabelWidth(JButton now, String name) {
    JButton b = new JButton(tr(name));
    b.revalidate();
    if (b.getPreferredSize().width > now.getPreferredSize().width) {
        return b;
    } else {
        return now;
    }
}

/**
 * Service method to setup a column so that it will hold a button for it's
 * values
 *
 * @param table
 * @param column
 * @param sample Typical button, used for size
 */
void setColumnToHoldButton(JTable table, int column, JButton sample) {
    //TableColumnModel tcm = table.getColumnModel();
    // install a button renderer & editor
    ButtonRenderer buttonRenderer = new ButtonRenderer();
    table.setDefaultRenderer(JButton.class, buttonRenderer);
    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
    table.setDefaultEditor(JButton.class, buttonEditor);
    // ensure the table rows, columns have enough room for buttons
    table.setRowHeight(sample.getPreferredSize().height);
    table.getColumnModel().getColumn(column)
            .setPreferredWidth(sample.getPreferredSize().width + 30);
}
#endif
/*synchronized*/ /*public*/ void EditorTableDataModel::dispose()
{
}
#if 1
/**
 * Method to self print or print preview the table. Printed in equally sized
 * columns across the page with headings and vertical lines between each
 * column. Data is word wrapped within a column. Can handle data as strings,
 * comboboxes or booleans
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*public*/ void EditorTableDataModel::printTable(HardcopyWriter* w)
{
 // determine the column size - evenly sized, with space between for lines
 int columnSize = (w->getCharactersPerLine() - this->columnCount(QModelIndex()) - 1) / this->columnCount(QModelIndex());

 // Draw horizontal dividing line
 w->write(w->getCurrentLineNumber(), 0, w->getCurrentLineNumber(),
         (columnSize + 1) * this->columnCount(QModelIndex()));

 // print the column header labels
 QVector<QString> columnStrings =  QVector<QString>(this->columnCount(QModelIndex()));
 // Put each column header in the array
 for (int i = 0; i < this->columnCount(QModelIndex()); i++)
 {
  columnStrings[i] = this->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
 }
 w->setFontWeight(QFont::Bold);
 printColumns(w, columnStrings.toList(), columnSize);
 w->setFontWeight(QFont::Normal);
 w->write(w->getCurrentLineNumber(), 0, w->getCurrentLineNumber(),
         (columnSize + 1) * this->columnCount(QModelIndex()));

 // now print each row of data
 // create a base string the width of the column
 QString spaces = "";
 for (int i = 0; i < columnSize; i++)
 {
  spaces = spaces + " ";
 }
 for (int i = 0; i < this->rowCount(QModelIndex()); i++)
 {
  for (int j = 0; j < this->columnCount(QModelIndex()); j++)
  {
   //check for special, non string contents
   if (this->data(index(i,j),Qt::DisplayRole).toString() == "")
   {
    columnStrings[j] = spaces;
   }
//   else if (qobject_cast<QComboBox>(this->data(index(i, j),Qt::DisplayRole).toString() != NULL))
//   {
//    columnStrings.replace(j,((QComboBox*) this->data(index(i, j),Qt::DisplayRole)->currentText());
//   }
//   else if (qobject_cast<bool*>(this->data(index(i, j),Qt::DisplayRole).toString() )!= NULL)
//   {
//    columnStrings.replace(j,(this->data(index(i, j),Qt::DisplayRole).toString()));
//   }
//   else
   {
    columnStrings.replace(j, this->data(index(i, j),Qt::DisplayRole).toString());
   }
  }
  printColumns(w, columnStrings.toList(), columnSize);
  w->write(w->getCurrentLineNumber(), 0, w->getCurrentLineNumber(),
          (columnSize + 1) * this->columnCount(QModelIndex()));
 }
 w->close();
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*protected*/ void EditorTableDataModel::printColumns(HardcopyWriter* w, QStringList columnStrings, int columnSize)
{
 QString columnString = "";
 QString lineString = "";
 // create a base string the width of the column
 QString spaces = "";
 for (int i = 0; i < columnSize; i++) {
     spaces = spaces + " ";
 }
 // loop through each column
 bool complete = false;
 while (!complete)
 {
  complete = true;
  for (int i = 0; i < columnStrings.length(); i++)
  {
   // if the column string is too wide cut it at word boundary (valid delimiters are space, - and _)
   // use the intial part of the text,pad it with spaces and place the remainder back in the array
   // for further processing on next line
   // if column string isn't too wide, pad it to column width with spaces if needed
   if (columnStrings[i].length() > columnSize)
   {
    bool noWord = true;
    for (int k = columnSize; k >= 1; k--)
    {
     if (columnStrings.at(i).mid(k - 1, k)==(" ")
             || columnStrings.at(i).mid(k - 1, k)==("-")
             || columnStrings.at(i).mid(k - 1, k)==("_"))
     {
      columnString = columnStrings.at(i).mid(0, k)
              + spaces.mid(columnStrings.at(i).mid(0, k).length());
      columnStrings[i] = columnStrings.at(i).mid(k);
      noWord = false;
      complete = false;
      break;
     }
    }
    if (noWord)
    {
     columnString = columnStrings.at(i).mid(0, columnSize);
     columnStrings[i] = columnStrings.at(i).mid(columnSize);
     complete = false;
    }

   }
   else
   {
    columnString = columnStrings.at(i) + spaces.mid(columnStrings.at(i).length());
    columnStrings[i] = "";
   }
   lineString = lineString + columnString + " ";
}
try {
   w->write(lineString);
   //write vertical dividing lines
   for (int i = 0; i < w->getCharactersPerLine(); i = i + columnSize + 1)
   {
    w->write(w->getCurrentLineNumber(), i, w->getCurrentLineNumber() + 1, i);
   }
   lineString = "\n";
   w->write(lineString);
   lineString = "";
  } catch (IOException* e)
  {
   log->warn("error during printing: " + e->getMessage());
  }
 }
}
#endif
