#ifndef NAMECOMPONENTCHOOSER_H
#define NAMECOMPONENTCHOOSER_H

#include <QObject>

class NameComponentChooser : public QObject
{
 Q_OBJECT
public:
 explicit NameComponentChooser(QObject *parent = nullptr);
 /*public*/ NameComponentChooser(QString name);

signals:

public slots:
};

#endif // NAMECOMPONENTCHOOSER_H
