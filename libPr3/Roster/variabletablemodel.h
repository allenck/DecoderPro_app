#ifndef VARIABLETABLEMODEL_H
#define VARIABLETABLEMODEL_H
#include <QVector>
#include <QStringList>
#include "jlabel.h"
#include "cvtablemodel.h"
#include "variablevalue.h"
#include <QtXml>
#include "exceptions.h"
#include "qualifieradder.h"
#include "tablecelleditor.h"
#include "tablecellrenderer.h"
#include <QPixmap>
#include "vptr.h"
#include <qstyleditemdelegate.h>
#include <QPainter>

class CompositeVariableValue;
class DecoderFile;
class EnumVariableValue;
class JActionEvent;
class LIBPR3SHARED_EXPORT VariableTableModel : public AbstractTableModel
{
    Q_OBJECT
public:
 enum COLUMNS
 {
  ROWNUM_COLUMN = 0,
  AND_COLUMN = 1,
  NOT_COLUMN = 2,
  DESCRIPTION_COLUMN = 3,
  STATE_COLUMN = 4,
  TRIGGERS_COLUMN = 5,
  EDIT_COLUMN = 6,
  DELETE_COLUMN = 7
 };
    explicit VariableTableModel(QObject *parent = 0);
    /*public*/ VariableTableModel(JLabel *status, QStringList h, CvTableModel* cvModel, /*IndexedCvTableModel* iCvModel,*/ QObject *parent = 0);
    /*public*/ int rowCount(const QModelIndex &parent) const override;
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ QString getColumnName(int col) const  override;
    /*public*/ QString getColumnClass(int col) const  override;
    /*public*/ bool isCellEditable(int row, int col) const override;
    /*public*/ VariableValue* getVariable(int row);
    /*public*/ QString getLabel(int row);
    /*public*/ QString getItem(int row);
    /*public*/ QString getCvName(int row);
    /*public*/ QString getValString(int row);
    /*public*/ void setIntValue(int row, int val);
    /*public*/ void setState(int row, int val);
    /*public*/ int getState(int row) ;
    /*public*/ QWidget* getRep(int row, QString format);
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ void setRow(int row, QDomElement e, DecoderFile *df = nullptr);
    void reportBogus() ;
    /*public*/ void setConstant(QDomElement e) ;
    /*public*/ void newDecVariableValue(QString name, QString CV, QString mask,
                                    bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly);
    /*public*/ void actionPerformed(JActionEvent* /*e*/);
    /*public*/ void read(int i);
    /*public*/ void write(int i);
    /*public*/ void configDone() ;
    /*public*/ bool fileDirty() ;
    /*public*/ void setFileDirty(bool b);
    /*public*/ bool decoderDirty();
    /*public*/ VariableValue* findVar(QString name);
    /*public*/ int findVarIndex(QString name);
    /*public*/ void dispose();
//    /*public*/  QVector<CvValue*> allIndxCvVector();
//    /*public*/  QMap<QString, CvValue*>* allIndxCvMap();
    /**
     * Gives access to the programmer used to reach these Indexed CVs,
     * so you can check on mode, capabilities, etc.
     * @return Programmer object for the Indexed CVs
     */
    /*public*/ Programmer* getProgrammer() ;
    /*public*/ void setProgrammer(Programmer* p) ;
    /*public*/ void resetStatus(int newStatus);
    /*public*/ int getRowCount() const;

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
    Logger* log;
    /*private*/ QStringList headers;// = NULL;

    /*private*/ QVector<VariableValue*>* rowVector;// = new Vector<VariableValue>();  // vector of Variable items
    /*private*/ CvTableModel* _cvModel = nullptr;          // reference to external table model
    /*private*/ QVector<QPushButton*>* _writeButtons;// = new QVector<QPushButton*>();
    /*private*/ QVector<QPushButton*>* _readButtons;// = new QVector<QPushButton*>();
    /*private*/ JLabel* _status = nullptr;
    /*private*/ bool _fileDirty;
 protected:
    /*protected*/ void processModifierElements(QDomElement e, VariableValue* v);
    /*protected*/ bool setDefaultValue(QDomElement e, VariableValue* v);
    /*protected*/ VariableValue* processCompositeVal(QDomElement child, QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item);
    /*protected*/ VariableValue* processDecVal(QDomElement child, QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item) throw (NumberFormatException);
    /*protected*/ VariableValue* processEnumVal(QDomElement child, QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item) throw (NumberFormatException);
    /*protected*/ VariableValue* processHexVal(QDomElement child, QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item) throw (NumberFormatException) ;
    /*protected*/ VariableValue* processLongAddressVal(QString CV, bool readOnly, bool infoOnly, bool writeOnly, QString name, QString comment, bool opsOnly, QString mask, QString item) ;
    /*protected*/ VariableValue* processShortAddressVal(QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item, QDomElement child) ;
    /*protected*/ VariableValue* processSpeedTableVal(QDomElement child, QString CV, bool readOnly, bool infoOnly, bool writeOnly, QString name, QString comment, bool opsOnly, QString mask, QString item) throw (NumberFormatException) ;
    /*protected*/ VariableValue* processSplitVal(QDomElement child, QString CV, bool readOnly, bool infoOnly, bool writeOnly, QString name, QString comment, bool opsOnly, QString mask, QString item) throw (NumberFormatException) ;
    /*protected*/ void setButtonsReadWrite(bool readOnly, bool infoOnly, bool writeOnly, QPushButton* bw, QPushButton* br, int row);
    /*protected*/ void setToolTip(QDomElement e, VariableValue* v);
    /*protected*/ void handleENumValChildren(QDomElement e, EnumVariableValue* var);
    /*protected*/ /*transient*/ /*volatile*/ DecoderFile* _df = nullptr;
    /*protected*/ void handleCompositeValChildren(QDomElement e, CompositeVariableValue* var);
};

class VTQualifierAdder : public QualifierAdder
{
    Q_OBJECT
    VariableValue* v;
public:
    VTQualifierAdder(VariableValue* v);
protected:
   /*protected*/ Qualifier* createQualifier(VariableValue* var, QString relation, QString value);
   /*protected*/ void addListener(PropertyChangeListener* qc) ;

};



#endif // VARIABLETABLEMODEL_H
