#ifndef AUDIOTABLEACTION_H
#define AUDIOTABLEACTION_H

#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include <QThread>
#include "libtables_global.h"

class AudioManager;
class Audio;
class BeanTableFrame;
class Logger;
class AudioTableDataModel;
class AudioSourceFrame;
class AudioBufferFrame;
class AudioListenerFrame;
class AudioTableFrame;
class AudioTablePanel;
class LIBTABLESSHARED_EXPORT AudioTableAction : public AbstractTableAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit AudioTableAction(QObject *parent = 0);
 ~AudioTableAction() {}
 AudioTableAction(const AudioTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
 Q_INVOKABLE /*public*/ AudioTableAction(QString actionName,QObject *parent);
 /*public*/ void addToFrame(BeanTableFrame* f);
 /*public*/ QWidget* getPanel();
 /*public*/ void setMenuBar(BeanTableFrame* f);
 Q_INVOKABLE /*public*/ void setMessagePreferencesDetails();
 Q_INVOKABLE /*public*/ QString getClassDescription();

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* /*e*/ = 0) override;

private:
 AudioTableDataModel* listener;
 AudioTableDataModel* buffers;
 AudioTableDataModel* sources;

 AudioSourceFrame* sourceFrame;
 AudioBufferFrame* bufferFrame;
 AudioListenerFrame* listenerFrame;

 AudioTableFrame* atf;
 AudioTablePanel* atp;
 Logger * log;
private slots:
 void addSourcePressed(ActionEvent* /*e*/ = 0);
 void addBufferPressed(ActionEvent* /*e*/ = 0);
 void common();
protected:
 /*protected*/ void createModel();
 /*protected*/ void setTitle();
 /*protected*/ QString helpTarget();
protected slots:
 /*protected*/ void addPressed(ActionEvent* e = 0);
 /*protected*/ void editAudio(Audio* a);
 /*protected*/ QString getClassName();

 friend class AudioTableDataModel;
 friend class AudioSourceTableDataModel;
};
Q_DECLARE_METATYPE(AudioTableAction)
/**
 * Define abstract AudioTableDataModel
 */
/*abstract*/ /*public*/ class AudioTableDataModel : public  BeanTableDataModel //implements PropertyChangeListener
{
 Q_OBJECT
/**
 *
 */
//private static final long serialVersionUID = 1263874422331471609L;

QChar subType;
AudioTableAction* act;
/*public*/ static /*final*/ const int EDITCOL;// = NUMCOLUMN;
/*public*/ AudioTableDataModel(QChar subType, AudioTableAction* act);
/*public*/ Manager* getManager();
 /*public*/ void setDisplayDeleteMsg(int boo);
/*public*/ NamedBean* getBySystemName(QString name) const;
/*public*/ NamedBean* getByUserName(QString name);
/*public*/ int rowCount(const QModelIndex &parent) const;
/*public*/ int columnCount(const QModelIndex &parent) const;
/*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
/*public*/ QString getValue(QString systemName) const ;
/*public*/ QVariant data(const QModelIndex &index, int role) const;
/*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
/*public*/ int getPreferredWidth(int col);
/*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
private:
 Logger* log;
protected:
/*protected*/ QString getMasterClassName();
/*protected*/ /*synchronized*/ void updateSpecificNameList(QChar subType);
/*protected*/ void clickOn(NamedBean* t);
/*protected*/ void configValueColumn(JTable* table);
/*protected*/ void configEditColumn(JTable* table);
/*protected*/ QString getBeanType();
 friend class AudioListenerTableDataModel;
 friend class AudioSourceTableDataModel;
 friend class AudioBufferTableDataModel;
 friend class AudioTablePanel;
};

/**
* Specific AudioTableDataModel for Audio Listener sub-type
*/
/*public*/ class AudioListenerTableDataModel : public AudioTableDataModel
{
 Q_OBJECT
 AudioTableAction* act;
/**
 *
 */
//private static final long serialVersionUID = 2124461381030149588L;
public:
AudioListenerTableDataModel(AudioTableAction* act);
protected:
/*protected*/ /*synchronized*/ void updateNameList();
};

/**
* Specific AudioTableDataModel for Audio Buffer sub-type
*/
/*public*/ class AudioBufferTableDataModel : public AudioTableDataModel
{
Q_OBJECT
/**
 *
 */
//private static final long serialVersionUID = -8823961737671739012L;
public:
AudioBufferTableDataModel(AudioTableAction* act);
protected:
/*protected*/ /*synchronized*/ void updateNameList();
};

/**
* Specific AudioTableDataModel for Audio Source sub-type
*/
/*public*/ class AudioSourceTableDataModel : public  AudioTableDataModel
{
 Q_OBJECT
/**
 *
 */
//private static final long serialVersionUID = 8123546730548750171L;
public:
AudioSourceTableDataModel(AudioTableAction* act);
void addToPopUp(QMenu *popup);
public slots:
 void On_doPlay_triggered();
 void On_doEdit_triggered();
 void On_doDelete_triggered();

protected:
/*protected*/ /*synchronized*/ void updateNameList();
};

class AudioTableListenerThread : public QThread
{
 Q_OBJECT
 AudioListenerFrame* frame;
 public:
 AudioTableListenerThread(AudioListenerFrame* frame);
 /*public*/ void run();

};
class AudioTableBufferThread : public QThread
{
 Q_OBJECT
 AudioBufferFrame* frame;
 public:
 AudioTableBufferThread(AudioBufferFrame* frame);
 /*public*/ void run();

};
class AudioTableSourceThread : public QThread
{
 Q_OBJECT
 AudioSourceFrame* frame;
 public:
 AudioTableSourceThread(AudioSourceFrame* frame);
 /*public*/ void run();

};


#endif // AUDIOTABLEACTION_H
