#ifndef JMRIJFRAME_H
#define JMRIJFRAME_H

#include <QWidget>

class JmriJFrame : public QWidget
{
    Q_OBJECT
public:
    //explicit JmriJFrame(QWidget *parent = 0);
    /**
     * Creates a JFrame with standard settings, optional
     * save/restore of size and position.
     * @param saveSize - Set true to save the last known size
     * @param savePosition - Set true to save the last known location
     */
    /*public*/ JmriJFrame(bool saveSize, bool savePosition, QObject* parent=0);
    /**
     * Creates a JFrame with standard settings, including
     * saving/restoring of size and position.
     */
    /*public*/ JmriJFrame(QObject* parent=0) ;
    /**
     * Creates a JFrame with with given name plus standard settings, including
     * saving/restoring of size and position.
     * @param name - Title of the JFrame
     */
    /*public*/ JmriJFrame(QString name, QObject* parent=0) ;
    /**
     * Creates a JFrame with with given name plus standard settings, including
     * optional save/restore of size and position.
     * @param name - Title of the JFrame
     * @param saveSize - Set true to save the last knowm size
     * @param savePosition - Set true to save the last known location
     */
    /*public*/ JmriJFrame(QString name, bool saveSize, bool savePosition, QObject* parent=0);

signals:
    
public slots:
private:
 Logger log;
protected:
 /*protected*/ bool allowInFrameServlet;// = true;

};

#endif // JMRIJFRAME_H
