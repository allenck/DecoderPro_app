#ifndef CVTABLEMODEL_H
#define CVTABLEMODEL_H
#include "abstracttablemodel.h"
#include <QLabel>
#include "programmer.h"
#include <QVector>
#include <QPushButton>
#include "cvvalue.h"

class JTable;
class QSignalMapper;
class LIBPR3SHARED_EXPORT CvTableModel : public AbstractTableModel
{
 Q_OBJECT
public:
//    CvTableModel(QObject *parent = 0);
//    /*public*/ QVector<CvValue*>* allCvVector();
    /*public*/ QLabel* getStatusLabel();
    /*public*/ CvTableModel(QLabel* status, Programmer* pProgrammer, QObject *parent = 0);
    /*public*/ Programmer* getProgrammer() const;
    /*public*/ void setProgrammer(Programmer* p);
    /*public*/ int rowCount(const QModelIndex &parent) const override;
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ QString getColumnName(int col) const override;
    /*public*/ QString getColumnClass(int col) const override;
    /*public*/ bool isCellEditable(int row, int col) const override;
    /*public*/ QString getName(int row);
    /*public*/ QString getValString(int row);
    /*public*/ CvValue* getCvByRow(int row) const;
    /*public*/ CvValue* getCvByNumber(QString number);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /*public*/ void addCV(QString s, bool readOnly, bool infoOnly, bool writeOnly) ;
    /*public*/ bool decoderDirty();
    /*public*/ void dispose();
    void configureTable(JTable*);
    /*public*/ QMap<QString, CvValue*>* allCvMap();
    /*public*/ void resetDecoderDirty(int newStatus);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

signals:
    //void modelChange(CvValue*, int);
private:
    /*private*/ int _numRows = 0;                // must be zero until Vectors are initialized
    static /*final*/ const int MAXCVNUM = 1024;
    /*private*/ QVector<CvValue*>* _cvDisplayVector;// = new QVector<CvValue*>();  // vector of CvValue objects, in display order
    /*private*/ QMap<QString, CvValue*>* _cvAllMap;// = new HashMap<String, CvValue>();
    /*private*/ Programmer* mProgrammer;
    int mapRow(int row);

    // Defines the columns
    /*private*/ static /*final*/ const int NUMCOLUMN   = 0;
    /*private*/ static /*final*/ const int VALCOLUMN   = 1;
    /*private*/ static /*final*/ const int STATECOLUMN = 2;
    /*private*/ static /*final*/ const int READCOLUMN  = 3;
    /*private*/ static /*final*/ const int WRITECOLUMN = 4;
    /*private*/ static /*final*/ const int COMPARECOLUMN = 5;

    /*private*/ static /*final*/ const int HIGHESTCOLUMN = COMPARECOLUMN+1;
    /*private*/ static /*final*/ const int HIGHESTNOPROG = STATECOLUMN+1;

    /*private*/ QLabel* _status;// = NULL;
    Logger* log;

 friend class PaneProgPane;
};

#endif // CVTABLEMODEL_H
