#ifndef INDEXEDCVTABLEMODEL_H
#define INDEXEDCVTABLEMODEL_H
#include <QVector>
#include "abstracttablemodel.h"
#include <QLabel>
#include "cvvalue.h"
#include "QPushButton"
#include <QEvent>

class QTableView;
class AbstractTableModel;
class LIBPR3SHARED_EXPORT IndexedCvTableModel : public AbstractTableModel
{
    Q_OBJECT
public:
    explicit IndexedCvTableModel(QObject *parent = 0);
    static /*final*/ const int MAXCVNUM = 512;
    /*public*/ QLabel* getStatusLabel();
    /*public*/  QVector<CvValue*>* allIndxCvVector();
    /*public*/ IndexedCvTableModel(QLabel* status, Programmer* pProgrammer, QObject *parent = 0);
    /*public*/ CvValue* getMatchingIndexedCV(QString name);
    /*public*/ Programmer* getProgrammer();
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ QString getColumnClass(int col);
    /*public*/ bool isCellEditable(int row, int col);
    /*public*/ QString getName(int row);
    /*public*/ QString getValString(int row);
    /*public*/ int getCvByName(QString name);
    /*public*/ CvValue* getCvByRow(int row);
    /*public*/ CvValue* getCvByNumber(int row);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ void setValueAt(QVariant value, int row, int col);
    /*public*/ void actionPerformed(QEvent e);
    /*public*/ void indexedRead();
    /*public*/ void indexedWrite();
    /*public*/ void indexedCompare();
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ int addIndxCV(QString cvName,
                         QString piCv, int piVal,
                         QString siCv, int siVal,
                         QString iCv,
                         bool readOnly, bool infoOnly, bool writeOnly);
    /*public*/ bool decoderDirty();
    /*public*/ void dispose();
    void setTable(QTableView*);

    /*public*/ void setProgrammer(Programmer* p);
    /*public*/  QMap<QString, CvValue*>* allIndxCvMap();
    /*public*/ int getRowCount() {return rowCount(QModelIndex());}
    /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

signals:

public slots:
private:
    /*private*/ int _numRows;// = 0;                // must be zero until Vectors are initialized
    /*private*/ QVector<CvValue*>* _indxCvDisplayVector;// = new QVector<CvValue>();  // vector of CvValue objects, in display order
    /*private*/ QVector<CvValue*>* _indxCvAllVector;// = new Vector<CvValue>(MAXCVNUM + 1);  // vector of all possible indexed CV objects
    /*private*/ QMap<QString, CvValue*>* _indxCvAllMap;// = new QMap<QString, CvValue*>();  // All existing indexed CV objects
    /*private*/ QVector<QPushButton*>* _indxWriteButtons;// = new Vector<QPushButton*>();
    /*private*/ QVector<QPushButton*>* _indxReadButtons;// = new Vector<QPushButton*>();
    /*private*/ QVector<QPushButton*>* _indxCompareButtons;// = new Vector<QPushButton*>();
//    /*private*/ Vector _indxToolTipText = new Vector();
    /*private*/ Programmer* mProgrammer;

    // Defines the columns
    /*private*/ static /*final*/ const int NAMECOLUMN   = 0;
    /*private*/ static /*final*/ const int PICOLUMN     = 1;
    /*private*/ static /*final*/ const int SICOLUMN     = 2;
    /*private*/ static /*final*/ const int CVCOLUMN     = 3;
    /*private*/ static /*final*/ const int VALCOLUMN    = 4;
    /*private*/ static /*final*/ const int STATECOLUMN  = 5;
    /*private*/ static /*final*/ const int READCOLUMN   = 6;
    /*private*/ static /*final*/ const int WRITECOLUMN  = 7;
    /*private*/ static /*final*/ const int COMPARECOLUMN  = 8;
    /*private*/ static /*final*/ const int HIGHESTCOLUMN = COMPARECOLUMN + 1;

    /*private*/ QLabel* _status;// = null;
    /*private*/ int _row;
    /*private*/ int _progState;// = 0;
    /*private*/ static /*final*/ const int IDLE = 0;
    /*private*/ static /*final*/ const int WRITING_PI4R = 1;
    /*private*/ static /*final*/ const int WRITING_PI4W = 2;
    /*private*/ static /*final*/ const int WRITING_SI4R = 3;
    /*private*/ static /*final*/ const int WRITING_SI4W = 4;
    /*private*/ static /*final*/ const int READING_CV = 5;
    /*private*/ static /*final*/ const int WRITING_CV = 6;
    /*private*/ static /*final*/ const int WRITING_PI4C = 7;
    /*private*/ static /*final*/ const int WRITING_SI4C = 8;
    /*private*/ static /*final*/ const int COMPARE_CV = 9;

    /**
     * Count number of retries done
     */
    /*private*/ int retries;// = 0;

    /**
     * Define maximum number of retries of read/write operations before moving on
     */
    /*private*/ static /*final*/ const int RETRY_MAX = 2;
    QTableView* _table;
 Logger* log;
};

#endif // INDEXEDCVTABLEMODEL_H
