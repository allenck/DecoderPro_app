#ifndef MATRIXSIGNALMAST_H
#define MATRIXSIGNALMAST_H
#include "abstractsignalmast.h"
#include "namedbeanhandle.h"

class Turnout;
class MatrixSignalMast : public AbstractSignalMast
{
 Q_OBJECT
public:
 /*public*/ MatrixSignalMast(QString systemName, QString userName, QObject* parent = nullptr);
 /*public*/ MatrixSignalMast(QString systemName, QObject* parent = nullptr);
 ~MatrixSignalMast() {dispose();}
 /*public*/ void setBitsForAspect(QString aspect, QByteArray bitArray);
 /*public*/ QByteArray getBitsForAspect(QString aspect);
 /*public*/ void setAspect(QString aspect);
 /*public*/ void setLit(bool newLit);
 /*public*/ void setUnLitBits(/*@Nonnull*/ QByteArray bits);
 /*public*/ void setUnLitBits(/*@Nonnull*/ QString bitString);
 /*@Nonnull*/ /*public*/ QByteArray getUnLitBits();
 /*@Nonnull*/ /*public*/ QString getUnLitChars();
 /*@CheckForNull*/ /*public*/ Turnout* getOutputBean(int colnum); // as bean
 /*@CheckForNull*/ /*public*/ NamedBeanHandle<Turnout*>* getOutputHandle (int colnum);
 /*@Nonnull*/ /*public*/ QString getOutputName(int colnum);
 /*public*/ void setBitstring(/*@Nonnull*/ QString aspect, /*@Nonnull*/ QString bitString);
 /*public*/ void setBitstring(QString aspect, QByteArray bitArray);
 /*@Nonnull*/ /*public*/ QString getBitstring(/*@Nonnull*/ QString aspect);
 /*@Nonnull*/ /*public*/ QStringList getOutputs(); // provide to xml
 /*public*/ void setOutput(/*@Nonnull*/ QString colname, /*@Nonnull*/ QString turnoutname) ;
 /*public*/ void updateOutputs (QByteArray bits);
 /*public*/ void resetPreviousStates(bool boo);
 /*public*/ bool resetPreviousStates();
 /*public*/ static int getLastRef();
 /*public*/ void setBitNum(int number);
 /*public*/ void setBitNum(QByteArray bits);
 /*public*/ int getBitNum();
 /*public*/ void setAspectDisabled(QString aspect);
 /*public*/ void dispose();
 /*public*/ QString className();
 /*public*/ void setMatrixMastCommandDelay(int delay);
 /*public*/ int getMatrixMastCommandDelay();

public slots:
 /*public*/ void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException
);

private:
 static Logger* log;
 static QString errorChars;// = "nnnnnn";
 static QString emptyChars;// = "000000"; // default starting value
 /*private*/ static /*final*/ QString mastType;// = "IF$xsm";
 void common();
 QByteArray errorBits;// = errorChars.toCharArray();
 QByteArray emptyBits;// = emptyChars.toCharArray();
 /*private*/ QMap<QString, QByteArray> aspectToOutput;// = new HashMap<String, char[]>(16); // "Clear" - 01001 char[] pairs
 /*private*/ QByteArray unLitBits;
 bool _resetPreviousStates = false;
 bool isTurnoutUsed(Turnout* t);
 static int lastRef;// = 0;
 /*private*/ int mastBitNum = 6;
 int mDelay = 0;

protected:
 /*protected*/ void configureFromName(QString systemName);
 /*protected*/ QMap<QString, NamedBeanHandle<Turnout*>*> outputsToBeans;// = new QMap<QString, NamedBeanHandle<Turnout*>*>(/*6*/); // output# - bean pairs
 /*protected*/ static void setLastRef(int newVal);

 friend class MatrixSignalMastTest;
};

#endif // MATRIXSIGNALMAST_H
