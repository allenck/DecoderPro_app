#ifndef EDITCIRCUITPATHS_H
#define EDITCIRCUITPATHS_H
#include "editframe.h"
#include <QAbstractListModel>

class LengthPanel;
class JToggleButton;
class Path;
class ListSelectionEvent;
class JList;
class OPath;
class PathListModel;
class JTextField;
class Positionable;
class CircuitBuilder;
class OBlock;
class EditCircuitPaths : public EditFrame
{
    Q_OBJECT
public:
    //explicit EditCircuitPaths(QWidget *parent = 0);
    static int STRUT_SIZE;// = 10;
    static bool _firstInstance;// = true;
    static QPoint _loc;// = null;
    static QSize _dim;// = null;
    /*public*/ static /*final*/ QString TEST_PATH;// = "TEST_PATH";
    /*public*/ EditCircuitPaths(QString _title, CircuitBuilder* parent, OBlock* block);
    /*public*/ QString getClassName();


public slots:
    /*public*/ void valueChanged(ListSelectionEvent* e = 0);


signals:

public slots:
private:
    /*private*/ OBlock*          _block;
    /*private*/ CircuitBuilder*  _parent;
    // mouse selections of track icons that define the path
    /*private*/ QList<Positionable*>* _pathGroup;// = new ArrayList<Positionable>();
    /*private*/ QList<Positionable*>* _savePathGroup;// = new ArrayList<>();

    /*private*/ JTextField*  _pathName;// = new JTextField();
//    /*private*/ QList*       _pathList;
    /*private*/ PathListModel* _pathListModel;
    /*private*/ OPath* _currentPath;
    /*private*/ LengthPanel* _lengthPanel;
    JList* _pathList;

    /*private*/ bool _pathChange;// = false;
    /*private*/ JTextField* _length;// = new JTextField();
    /*private*/ JToggleButton* _units;
    /*private*/ JPanel* makeContentPanel();
    /*private*/ void clearPath(bool);
    /*private*/ QList<Positionable *> *showPath(OPath* path);
    /*private*/ QString checkForSavePath();
    /*private*/ void clearListSelection();
    /*private*/ void addNewPath(bool prompt);
    /*private*/ OPath* getBlockPath(QString name);\
    Logger* log;
    /*private*/ OPath* makeOPath(QString name, QList<Positionable*>* pathGp, bool showMsg);
    /*private*/ QString findErrors();
    /*private*/ QList<Positionable*>* makePathGroup(OPath* path);
    /*private*/ bool setPathLength(OPath* path);
    /*private*/ static bool pathsEqual(OPath* p1, OPath* p2);
    /*private*/ void changePathNameInIcons(QString name, OPath* path);
    /*private*/ bool okPath(Positionable* pos);
    /*private*/ bool pathIconsEqual(QList<Positionable*>* pathGp1, QList<Positionable*>* pathGp2);
    /*private*/ QString checkIcons(QString name, QList<Positionable*>* pathGp);

private slots:
    /*private*/ void changePathName();
    /*private*/ void deletePath();

protected:
    /*protected*/ QList<Positionable*>* getPathGroup();
    /*protected*/ OBlock* getBlock();
    /*protected*/ void updateSelections(bool noShift, Positionable* selection);
    /*protected*/ void updatePath();

protected slots:
    /*protected*/ void closingEvent(bool);
friend class PathListModel;
friend class CircuitBuilder;

};
class PathListModel : public QAbstractListModel
{
 Q_OBJECT
    EditCircuitPaths* parent;
public:
    PathListModel(EditCircuitPaths* parent);

    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ void dataChange();
    /*public*/ Path* getSelectedValue();
};

#endif // EDITCIRCUITPATHS_H
