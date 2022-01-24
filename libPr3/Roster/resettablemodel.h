#ifndef RESETTABLEMODEL_H
#define RESETTABLEMODEL_H
#include "abstracttablemodel.h"
#include "cvvalue.h"
#include <QPushButton>
#include <QtXml>
#include "actionevent.h"

class ProgrammingMode;
class LIBPR3SHARED_EXPORT ResetTableModel : public AbstractTableModel
{
    Q_OBJECT
public:
    //explicit ResetTableModel(QObject *parent = 0);
    /*public*/ ResetTableModel(QLabel* status, Programmer* pProgrammer, QObject *parent = 0);
    /*public*/ int rowCount(const QModelIndex &parent) const override;
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;
    QVariant dataAt(int row, int col) const;
    /*public*/ void setProgrammer(Programmer* p);
    /*public*/ void setRow(int row, QDomElement e, QDomElement p, QString model);
    /*public*/ void actionPerformed(JActionEvent* /*e*/);
    /*public*/ void dispose();
    /*public*/ int getRowCount() const override {return rowCount(QModelIndex());}
    /*public*/ int getColumnCount() const override{return columnCount(QModelIndex());}

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
    /*private*/ QList<QList<QString>*> modeVector = QList<QList<QString>*>(); // vector of related modes

    /*private*/ QVector<QPushButton*>* _writeButtons;// = new QVector<QPushButton*>();

    /*private*/ CvValue* _iCv = nullptr;
    /*private*/ QLabel* _status = nullptr;
    /*private*/ Programmer* mProgrammer = nullptr;
    /*private*/ QString _piCv;
    /*private*/ QString _siCv;
    /*private*/ ProgrammingMode* savedMode = nullptr;
    /*private*/ QString decoderModel;
    bool badModeOk(QString currentMode, QString resetModes, QString availableModes);
    bool opsResetOk();

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
