/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "masterthread.h"


#include <QTime>
#include <QVector>
#include <QDebug>

QT_USE_NAMESPACE

MasterThread::MasterThread(QObject *parent)
    : QThread(parent), waitTimeout(0), quit(false)
{
 serial = NULL;

}

//! [0]
MasterThread::~MasterThread()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}
//! [0]
void MasterThread::setSerial(QSerialPort *serial)
{
 this->serial = serial;
}
QSerialPort* MasterThread::Serial() { return serial;}

//! [1] //! [2]
//void MasterThread::transaction(const QString &portName, int waitTimeout, const QString &request)
//void MasterThread::transaction(const QString &portName, int waitTimeout, const QVector<char> &request)
void MasterThread::transaction(QSerialPort* serialIn, int waitTimeout, const QVector<char> &request)
{
    //! [1]
    QMutexLocker locker(&mutex);
    this->serialIn = serialIn;
    this->portName = serialIn->portName();
    this->waitTimeout = waitTimeout;
    this->request = QVector<char>();
    qDebug()<< QString("request count %1").arg(request.count());
    int count = request.count();
    for(int i=0; i < count; i++)
     this->request.append(request.at(i));
    //! [3]
    if (!isRunning())
        start();
    else
        cond.wakeOne();
}
//! [2] //! [3]

//! [4]
void MasterThread::run()
{
 bool currentPortNameChanged = false;
 quit=false;

 mutex.lock();
 //! [4] //! [5]
 //QString currentPortName;
 if (currentPortName != portName)
 {
  qDebug()<< QString(tr("Portname changed from %1 to %2 Line %3")).arg(currentPortName).arg(portName).arg(__LINE__);
  currentPortName = portName;
  currentPortNameChanged = true;
 }

 int currentWaitTimeout = waitTimeout;
 //QString currentRequest = request;
 QVector<char> currentRequest = request;
 mutex.unlock();
 //! [5] //! [6]
 //QSerialPort serial;

// while (!quit)
// {
  //![6] //! [7]
  if (currentPortNameChanged)
  {
   if(serial == NULL)
       serial = new QSerialPort();
   serial->close();
   serial->setPortName(currentPortName);

   if (!serial->open(QIODevice::WriteOnly))
   {
    emit error(tr("Can't open %1, error %2").arg(portName).arg(serial->errorString()));
    return;
   }

   if (!serial->setBaudRate(QSerialPort::Baud57600))
   {
    emit error(tr("Can't set baud rate 9600 baud to port %1, error code %2").arg(portName).arg(serial->errorString()));
    return;
   }

   if (!serial->setDataBits(QSerialPort::Data7))
   {
    emit error(tr("Can't set 8 data bits to port %1, error code %2")
                           .arg(portName).arg(serial->errorString()));
    return;
   }

   if (!serial->setParity(QSerialPort::OddParity)) {
    emit error(tr("Can't set no patity to port %1, error code %2")
                           .arg(portName).arg(serial->errorString()));
    return;
   }

   if (!serial->setStopBits(QSerialPort::OneStop)) {
    emit error(tr("Can't set 1 stop bit to port %1, error code %2")
                           .arg(portName).arg(serial->errorString()));
    return;
   }

   if (!serial->setFlowControl(QSerialPort::HardwareControl)) {
    emit error(tr("Can't set no flow control to port %1, error code %2")
                           .arg(portName).arg(serial->errorString()));
    return;
   }
  }
  while (!quit)
  {

  //! [7] //! [8]
  // write request
  //QByteArray requestData = currentRequest.toLocal8Bit();
  QVector<char> requestData = currentRequest;
  if(requestData.size()>0)
  {
   serial->write(requestData.constData());
   if (serial->waitForBytesWritten(waitTimeout))
   {
    // data successfully written!
    emit dataWritten(requestData);
    requestData.clear();
   //! [8] //! [10]
   // read response
//   if (serial->waitForReadyRead(currentWaitTimeout))
//   {
//    QByteArray responseData = serial->readAll();
//    while (serial->waitForReadyRead(10))
//    responseData += serial->readAll();

//    //QString response(responseData);
//    QByteArray response;
//    for(int i=0; i < responseData.size(); i++)
//      response.append( responseData.at(i));
//    //! [12]
//    emit this->response(response);
//    //! [10] //! [11] //! [12]
//    continue;
//   }
//   else
//   {
//    emit timeout(QString(tr("Wait read response timeout %1"))
//                         .arg(QTime::currentTime().toString()));
//    continue;
//   }
    //! [9] //! [11]
   }
   else
   {
    QString errmsg = (tr("Wait write request timeout %1 %2"))
                 .arg(QTime::currentTime().toString()).arg(serial->errorString());
    emit timeout(errmsg);
    qDebug() << errmsg;
//    continue;
   }
  }
  //! [9]  //! [13]
  mutex.lock();
  cond.wait(&mutex);
  if (currentPortName != portName)
  {
   qDebug()<< QString(tr("Portname changed from %1 to %2 Line %3")).arg(currentPortName).arg(portName).arg(__LINE__);
   currentPortName = portName;
   currentPortNameChanged = true;
  } else {
   currentPortNameChanged = false;
  }
  currentWaitTimeout = waitTimeout;
  currentRequest = request;
  mutex.unlock();
 }
 //! [13]
}
void MasterThread::setQuit() { quit = true;}
