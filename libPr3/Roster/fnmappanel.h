#ifndef FNMAPPANEL_H
#define FNMAPPANEL_H

#include "jpanel.h"
#include <QtXml>
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include "logger.h"
#include "libPr3_global.h"

class VariableTableModel;
class LIBPR3SHARED_EXPORT FnMapPanel : public JPanel
{
    Q_OBJECT
public:
   //explicit FnMapPanel(QWidget *parent = 0);
    /*public*/ FnMapPanel(VariableTableModel* v, QList<int>* varsUsed, QDomElement model, QWidget* parent = 0);
    void saveAt(int row, int column, QWidget* j);
    void saveAt(int row, int column, QWidget* j, int anchor);
    void labelAt(int row, int column, QString name);
    void labelAt(int row, int column, QString name, int anchor);
    /*public*/ void dispose();

signals:

public slots:
private:
    // GridBayLayout column numbers
    int fnNameCol = 0;
    int firstOutCol = 1;

    // GridBayLayout row numbers
    int outputNameRow = 0;
    int outputNumRow = 1;
    int outputLabelRow = 2;
    int firstFnRow = 3;

    // Some limits and defaults
    int highestFn = 28;
    int highestSensor = 28;
    int numFn = 14;  // include FL(f) and FL(r) in the total
    int numOut = 20;
    int maxFn = 30;  // include FL(f) and FL(r) in the total; update list of names if you update this
    int maxOut = 40; // update list of names if you update this

    /*final*/ QVector<QString> outName = QVector<QString>(maxOut);
    /*final*/ QVector<QString> outLabel = QVector<QString>(maxOut);
    /*final*/ QVector<bool> outIsUsed = QVector<bool>(maxOut);

    /*final*/ QVector<QString> fnExtraList = {"STOP", "DRIVE", "FWD", "REV", "FL"};
    /*final*/ QVector<QString> fnVariantList = {"", "(f)", "(r)"};

    QList<QString> fnList;
    GridBagLayout* gl = NULL;
    GridBagConstraints* cs = NULL;
    VariableTableModel* _varModel = nullptr;
    static Logger* log;
protected:
    /*protected*/ void configOutputs(QDomElement model);

};

#endif // FNMAPPANEL_H
