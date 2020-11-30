#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QObject>
#include <QAbstractListModel>
#include "liblayouteditor_global.h"

class Manager;
class QTextEdit;
class MDefaultListModel;
class Logger;
//class JTextArea;
class LIBLAYOUTEDITORSHARED_EXPORT Maintenance : public QObject
{
    Q_OBJECT
public:
    explicit Maintenance(QObject *parent = 0);
    /*public*/ static void findOrphansPressed(QWidget* parent);
    static bool search(QString name, /*JTextArea*/QTextEdit* text);
    static QStringList getTypeAndNames(QString name);
    static void makeDialog(QWidget* component, QWidget* button, QWidget* parent, QString title);
    static bool testName(QString name, bool found, QStringList names, QString line1, QString line2,
                         QString line, QString tempText);
    /*public*/ static void findEmptyPressed(QWidget* parent);
    /*public*/ static void deviceReportPressed(QString devName, QWidget* parent);

signals:

public slots:
private:
    /*private*/ static QList<QString> getSystemNameList(Manager* mgr);

};

class MDefaultListModel : public QAbstractListModel
{
 Q_OBJECT
public:
    MDefaultListModel(QVector<QString>* display, QObject* parent = 0);
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
private:
    QVector<QString>* display;
};

#endif // MAINTENANCE_H
