#ifndef RESETTABLEMODEL_H
#define RESETTABLEMODEL_H
#include "abstracttablemodel.h"
#include "cvvalue.h"
#include <QPushButton>
#include <QtXml>
#include "actionevent.h"

class LIBPR3SHARED_EXPORT ResetTableModel : public AbstractTableModel
{
    Q_OBJECT
public:
    //explicit ResetTableModel(QObject *parent = 0);
    /*public*/ ResetTableModel(QLabel* status, Programmer* pProgrammer, QObject *parent = 0);
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    QVariant dataAt(int row, int col) const;
    /*public*/ void setProgrammer(Programmer* p);
    /*public*/ void setPiCv(QString piCv) ;
    /*public*/ void setSiCv(QString siCv);
    /*public*/ void setRow(int row, QDomElement e);
    /*public*/ void setIndxRow(int row, QDomElement e);
    /*public*/ void actionPerformed(ActionEvent* /*e*/);
    /*public*/ void indexedWrite() ;
    /*public*/ void dispose();

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
    /*private*/ QStringList* headers;// = {"Label", "Name",
//                                "PI", "PIvalue",
//                                "SI", "SIvalue",
//                                "CV", "Value",
//                                "Write", "State"};

    /*private*/ QVector<CvValue*>* rowVector;//   = new QVector<CvValue>(); // vector of Reset items
    /*private*/ QVector<QString>* labelVector;// = new QVector<QString>(); // vector of related labels

    /*private*/ QVector<QPushButton*>* _writeButtons;// = new QVector<QPushButton*>();

    /*private*/ CvValue* _iCv;// = NULL;
    /*private*/ QLabel* _status;// = NULL;
    /*private*/ Programmer* mProgrammer;
    /*private*/ QString _piCv;
    /*private*/ QString _siCv;
protected:
    /*protected*/ void performReset(int row);
    /*private*/ int _progState;// = 0;
    /*private*/ static /*final*/ const int IDLE = 0;
    /*private*/ static /*final*/ const int WRITING_PI = 1;
    /*private*/ static /*final*/ const int WRITING_SI = 2;
    /*private*/ static /*final*/ const int WRITING_CV = 3;
 Logger* log;
 friend class FactoryResetAction;
};

#endif // RESETTABLEMODEL_H
