#ifndef FUNCTIONLABELSPANE_H
#define FUNCTIONLABELSPANE_H

#include <QWidget>
#include "logger.h"
#include <QFile>
#include "libPr3_global.h"

namespace Ui {
class FunctionLabelsPane;
}

class DropJLabel;
class HardcopyWriter;
class RosterEntry;
class LIBPR3SHARED_EXPORT FunctionLabelsPane : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionLabelsPane(RosterEntry* re, QWidget *parent = 0);
    ~FunctionLabelsPane();
    /*public*/ void makeBackupFile(QString name);
    /*public*/ QString backupFileName(QString name);
public slots:
    /*public*/ bool includeInPrint();
    /*public*/ void includeInPrint(bool inc);
    /*public*/ void printPane(HardcopyWriter* w);
    void onRightClick(DropJLabel*);

private:
    Ui::FunctionLabelsPane *ui;
    RosterEntry* re;
    Logger* log;
    bool print;
    // we're doing a manual allocation of position for
    // now, based on 28 labels
    // The references to maxfunction + 1 are due to F0
    /*private*/ /*final*/ int maxfunction;// = 28;

private slots:
    void on_lbl0_editingFinished();
    void on_lbl1_editingFinished();
    void on_lbl2_editingFinished();
    void on_lbl3_editingFinished();
    void on_lbl4_editingFinished();
    void on_lbl5_editingFinished();
    void on_lbl6_editingFinished();
    void on_lbl7_editingFinished();
    void on_lbl8_editingFinished();
    void on_lbl9_editingFinished();
    void on_lbl10_editingFinished();
    void on_lbl11_editingFinished();
    void on_lbl12_editingFinished();
    void on_lbl13_editingFinished();
    void on_lbl14_editingFinished();
    void on_lbl15_editingFinished();
    void on_lbl16_editingFinished();

    void OnIconOff0_changed(QString);
    void OnIconOff1_changed(QString);
    void OnIconOff2_changed(QString);
    void OnIconOff3_changed(QString);
    void OnIconOff4_changed(QString);
    void OnIconOff5_changed(QString);
    void OnIconOff6_changed(QString);
    void OnIconOff7_changed(QString);
    void OnIconOff8_changed(QString);
    void OnIconOff9_changed(QString);
    void OnIconOff10_changed(QString);
    void OnIconOff11_changed(QString);
    void OnIconOff12_changed(QString);
    void OnIconOff13_changed(QString);
    void OnIconOff14_changed(QString);
    void OnIconOff15_changed(QString);
    void OnIconOff16_changed(QString);
    void OnIconOn0_changed(QString);
    void OnIconOn1_changed(QString);
    void OnIconOn2_changed(QString);
    void OnIconOn3_changed(QString);
    void OnIconOn4_changed(QString);
    void OnIconOn5_changed(QString);
    void OnIconOn6_changed(QString);
    void OnIconOn7_changed(QString);
    void OnIconOn8_changed(QString);
    void OnIconOn9_changed(QString);
    void OnIconOn10_changed(QString);
    void OnIconOn11_changed(QString);
    void OnIconOn12_changed(QString);
    void OnIconOn13_changed(QString);
    void OnIconOn14_changed(QString);
    void OnIconOn15_changed(QString);
    void OnIconOn16_changed(QString);
    void on_btnSave_clicked();
protected:
    /*protected*/ QFile* findFile(QString name);

};

#endif // FUNCTIONLABELSPANE_H
