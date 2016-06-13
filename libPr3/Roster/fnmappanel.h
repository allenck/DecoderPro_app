#ifndef FNMAPPANEL_H
#define FNMAPPANEL_H

#include <QFrame>
#include <QtXml>
#include <QGridLayout>
#include "gridbagconstraints.h"
#include "logger.h"
#include "libPr3_global.h"

class VariableTableModel;
class LIBPR3SHARED_EXPORT FnMapPanel : public QFrame
{
    Q_OBJECT
public:
   //explicit FnMapPanel(QWidget *parent = 0);
    /*public*/ FnMapPanel(VariableTableModel* v, QList<int>* varsUsed, QDomElement model, QFrame* parent = 0);
    void saveAt(int row, int column, QWidget* j);
    void labelAt(int row, int column, QString name);
    /*public*/ void dispose();

signals:

public slots:
private:
    // columns
    int cvNum;// = -1;
    int fnName;// = 0;
    int firstOut;// = 1;

    // rows
    int outputName;// = 0;
    int outputNum;// = 1;
    int outputLabel;// = 2;
    int firstFn;// = 3;

    // these will eventually be passed in from the ctor
    int numFn;// = 14;  // include FL(f) and FL(r) in the total
    int numOut;// = 20;
    int maxFn;// = 30;  // include FL(f) and FL(r) in the total; update list of names if you update this
    int maxOut;// = 40; // update list of names if you update this

    QGridLayout* gl;// = NULL;
    GridBagConstraints* cs;// = NULL;
    VariableTableModel* _varModel;
    Logger* log;
    QStringList fnList;
    QStringList outLabel;
    QStringList outName;
protected:
    /*protected*/ void configOutputs(QDomElement model);

};

#endif // FNMAPPANEL_H
