#ifndef MERGEPROMPT_H
#define MERGEPROMPT_H
#include "jdialog.h"
#include "windowadapter.h"
#include "abstracttablemodel.h"


class JTable;
class JmriJFrame;
class RosterSpeedProfile;
class MergePrompt : public JDialog
{
 Q_OBJECT
public:
 MergePrompt(QString name, QMap<QString, bool>* cand, QMap<QString, QMap<int, bool>*>* anomalies, QWidget* parent = nullptr);
 static /*public*/ QMap<int, bool>* validateSpeedProfile(RosterSpeedProfile* speedProfile, QString id);

public slots:
 void onMergeButton();
 void onNoMergeButton();
 void onCloseView();

private:
 static Logger * log;
 QMap<QString, bool>* _candidates;   // merge candidate choices
 QMap<QString, RosterSpeedProfile*>* _mergeProfiles;  // candidate's speedprofile
 QMap<QString, RosterSpeedProfile*>* _sessionProfiles;  // candidate's speedprofile
 QMap<QString, QMap<int, bool>*>* _anomalyMap;
 QWidget* _viewFrame;
 JTable* _mergeTable;
 JmriJFrame* _anomolyFrame;
 static int STRUT;// = 20;
 /*private*/ void noMerge();
 void showProfiles(QString id);

friend class MPWindowAdapter;
friend class MergeTableModel;
};

class MPWindowAdapter : public WindowAdapter
{
 MergePrompt* mp;
public:
 MPWindowAdapter(MergePrompt* mp) { this->mp = mp;}
 /*public*/ void windowClosing(QCloseEvent* /*e*/) {
     mp->noMerge();
     mp->dispose();
 }

};

class MergeTableModel : public AbstractTableModel
{
 Q_OBJECT

 QList<QMapIterator<QString, bool> > candidateArray;// = new ArrayList<>();
 MergePrompt* mp;
public:
    enum COLUMNS
    {
     MERGE_COL = 0,
     ID_COL = 1,
     VIEW_COL = 2,
     NUMCOLS = 3
    };
    MergeTableModel(QMap<QString, bool>* map, MergePrompt* mp);
    bool hasAnomaly(int row);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ int getRowCount() {return rowCount(QModelIndex());}
    /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

};

#endif // MERGEPROMPT_H
