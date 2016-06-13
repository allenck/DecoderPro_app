#ifndef FNMAPPANELESU_H
#define FNMAPPANELESU_H

#include <QWidget>

class VariableTableModel;
class QDomElement;
class RosterEntry;
class CvTableModel;
class FnMapPanelESU : public QWidget
{
    Q_OBJECT
public:
    //explicit FnMapPanelESU(QWidget *parent = 0);
    /*public*/ FnMapPanelESU(VariableTableModel* v, QList<int>* varsUsed, QDomElement model, RosterEntry* rosterEntry, CvTableModel* cvModel, QWidget *parent = 0);

signals:

public slots:
#if 0
    // columns
final int firstCol = 0;
final int firstOut = 2;

int currentCol = firstCol;

// rows
static final int HINTS_ROW = 0;
static final int MOVE_ARROWS_TOP_ROW = 1;
static final int BLOCK_NAME_ROW = 1;
static final int FIRST_ROW = BLOCK_NAME_ROW + 2;
static final int ROW_LABEL_ROW = FIRST_ROW - 1;

static final int MAX_ROWS = 40;

int currentRow = FIRST_ROW;

static final int PI_CV = 16;
static final int SI_START_CV = 2;
static final int SI_CV_MODULUS = 16;
static final int START_CV = 257;
static final int CV_MODULUS = 256;
static final int BIT_MODULUS = 8;

GridBagLayout gl = null;
GridBagConstraints cs = null;
VariableTableModel _varModel;

/**
 * Titles for blocks of items
 */
final String[] outBlockName = new String[] {"Input Conditions","Physical Outputs","Logical Outputs","Sounds"};

/**
 * Number of items per block
 */
final int[] outBlockLength = new int[] {36,16,16,24};

/**
 * Number of bits per block item
 */
final int[] outBlockItemBits = new int[] {2,1,1,1};

final int[] outBlockStartCol = new int[outBlockLength.length]; // Starting column column of block
final int[] outBlockUsed = new int[outBlockLength.length]; // Number of used items per block
final JTextField[][] summaryLine = new JTextField[MAX_ROWS][outBlockLength.length];

/**
 * <p>Default column labels.
 * <dl>
 *  <dt>Two rows are available for column labels</dt>
 *   <dd>Use the '|' character to designate a row break</dd>
 * </dl></p>
 * <p>Item labels can be overridden by the "output" element of the "model" element from the decoder definition file.</p>
 */
final String[] itemDescESU = new String[] {"Motion|Drive|Stop","Direction|Forward|Reverse"
    ,"F0","F1","F2","F3","F4","F5","F6","F7","F8","F9"
    ,"F10","F11","F12","F13","F14","F15","F16","F17","F18","F19"
    ,"F20","F21","F22","F23","F24","F25","F26","F27","F28"
    ,"Wheel Sensor","Sensor 1","Sensor 2","Sensor 3","Sensor 4"
    ,"Head light[1]","Rear light[1]","Aux 1[1]","Aux 2[1]","Aux 3","Aux 4","Aux 5","Aux 6","Aux 7","Aux 8","Aux 9","Aux 10","Head light[2]","Rear light[2]","Aux 1[2]","Aux 2[2]"
    ,"Momentum off","Shunt mode","Dynamic brake","Uncouple Cycle","|","Fire box","Dim lights","Grade cross","Smoke gen","Notch up","Notch down","Sound fade","Brk sql off","Doppler effect","Volume & mute","Shift mode"
    ,"Sound slot 1","Sound slot 2","Sound slot 3","Sound slot 4","Sound slot 5","Sound slot 6","Sound slot 7","Sound slot 8","Sound slot 9","Sound slot 10","Sound slot 11","Sound slot 12"
    ,"Sound slot 13","Sound slot 14","Sound slot 15","Sound slot 16","Sound slot 17","Sound slot 18","Sound slot 19","Sound slot 20","Sound slot 21","Sound slot 22","Sound slot 23","Sound slot 24"
};

final int MAX_ITEMS = itemDescESU.length;
final String[] itemLabel = new String[MAX_ITEMS];
final String[][] itemName = new String[MAX_ITEMS][3];
final boolean[] itemIsUsed = new boolean[MAX_ITEMS];
final int iVarIndex[][] =new int[MAX_ITEMS][MAX_ROWS];

   // default values
int numItems = MAX_ITEMS;
int numRows = MAX_ROWS;

// for row moves
int selectedRow = -1;
final JRadioButton rowButton[];
#endif
};

#endif // FNMAPPANELESU_H
