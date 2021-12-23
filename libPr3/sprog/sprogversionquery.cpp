#include "sprogversionquery.h"
#include "loggerfactory.h"
#include "sprogreply.h"
#include "sprogserialdriveradapter.h"

using namespace Sprog;
/**
 * Get the firmware version of the attached SPROG.
 * <p>
 * Updated April 2016 by Andrew Crosland: look for the correct replies, which may
 * not be the very next message after a query is sent, due to slot manager
 * traffic. Add Pi-SPROG version decoding.
 *
 * @author	Andrew Crosland Copyright (C) 2012, 2016
 */
///*public*/ class SprogVersionQuery implements SprogListener {



/*public*/SprogVersionQuery::SprogVersionQuery(SprogSystemConnectionMemo* memo, QObject* parent) : QObject(parent)
{
 LONG_TIMEOUT = 2000;
 timer = NULL;
 _memo = NULL;

    if (log->isDebugEnabled()) {
        log->debug(QString("setting instance:" ) + QString(this->metaObject()->className()));
    }
    _memo = memo;
    tc = _memo->getSprogTrafficController();
    state = QueryState::IDLE;
}

/*protected*/ /*static*/ /*final*/ QVector<SprogVersionListener*>* SprogVersionQuery::versionListeners = new QVector<SprogVersionListener*>();

/*protected*/ /*synchronized*/ void SprogVersionQuery::addSprogVersionListener(SprogVersionListener* l) {
    // add only if not already registered
    if (l == NULL) {
        throw new NullPointerException();
    }
    if (!versionListeners->contains(l)) {
        versionListeners->append(l);
    }
    connect(this, SIGNAL(do_notifyVersion(SprogVersion*)), l, SLOT(notifyVersion(SprogVersion*)));
}

/*public*/ /*synchronized*/ void SprogVersionQuery::removeSprogVersionListener(SprogVersionListener* l) {
    if (versionListeners->contains(l))
    {
        versionListeners->removeOne(l);
        disconnect(this, SIGNAL(do_notifyVersion(SprogVersion*)), l, SLOT(notifyVersion(ver)));
    }
}

//@SuppressWarnings("unchecked")
/*private*/ /*synchronized*/ QVector<SprogVersionListener*>* SprogVersionQuery::getCopyOfListeners()
{
 return (QVector<SprogVersionListener*>*) (versionListeners);
}

/**
 * Return the SprogVersionQuery instance to use.
 *
 * @return The registered SprogVersionQuery instance for general use, if
 *         need be creating one.
 * @deprecated JMRI Since 4.4 instance() shouldn't be used, convert to JMRI multi-system support structure
 */
//@Deprecated
/*static*/ /*public*/ SprogVersionQuery* SprogVersionQuery::instance() {
    return NULL;
}

/*synchronized*/ /*public*/ void SprogVersionQuery::requestVersion(SprogVersionListener* l) {
 SprogMessage* m;
 if (log->isDebugEnabled())
 {
  log->debug("SprogVersion requested by " + QString(l->metaObject()->className()));
 }
 if (state == QueryState::DONE)
 {
     // Reply immediately
     l->notifyVersion(ver); // ACK should this be an 'emit'?
//  connect(this, SIGNAL(do_notifyVersion(SprogVersion*)), l, SLOT(notifyVersion(SprogVersion*)));
//  emit do_notifyVersion(ver);
//  disconnect(this, SIGNAL(do_notifyVersion(SprogVersion*)), l, SLOT(notifyVersion(SprogVersion*)));

     return;
 }
 // Remember this listener
 this->addSprogVersionListener(l);
 if (state == QueryState::IDLE) {
     // Kick things off with a blank message
     m = new SprogMessage(1);
     m->setOpCode(' ');
     tc->sendSprogMessage(m, (SprogListener*)this);
     state = QueryState::CRSENT;
     startLongTimer();
 }
}

/**
 * Notify all registered listeners of the SPROG version.
 *
 * @param v version to send notify to
 */
/*protected*/ /*synchronized*/ void SprogVersionQuery::notifyVersion(SprogVersion* v) {
    ver = v;
    for (SprogVersionListener* listener : *getCopyOfListeners()) {
        try {
      connect(this, SIGNAL(do_notifyVersion(SprogVersion*)), listener, SLOT(notifyVersion(SprogVersion*)));
      emit do_notifyVersion(ver);
      disconnect(this, SIGNAL(do_notifyVersion(SprogVersion*)), listener, SLOT(notifyVersion(SprogVersion*)));

            versionListeners->removeOne(listener);
        } catch (Exception e) {
            log->warn(QString("notify: During dispatch to ") + QString(listener->metaObject()->className()) + "\nException " + e.getMessage());
        }
    }

}

/**
 * SprogListener notify Message (not used).
 */
//@Override
/*public*/ void SprogVersionQuery::notifyMessage(SprogMessage* /*m*/) {
}   // Ignore

/**
 * SprogListener notifyReply listens to replies and looks for version reply.
 */
//@Override
/*synchronized*/ /*public*/ void SprogVersionQuery::notifyReply(SprogReply* m)
{
 SprogMessage* msg;
 SprogVersion* v;
 replyString = m->toString();
 switch (state)
 {
  case IDLE:
  {
   if (log->isDebugEnabled())
   {
      log->debug("reply in IDLE state");
   }
   break;
  }
  case CRSENT:
  {
   log->debug(tr("reply in CRSENT state %1").arg(replyString));
   if ((replyString.indexOf("P>")) >= 0)
   {
    stopTimer();
    msg = new SprogMessage(1);
    msg->setOpCode('?');
    tc->sendSprogMessage(msg, ((SprogListener*)this));
    state = QueryState::QUERYSENT;
    startLongTimer();
   }
   break;
  }
  case QUERYSENT:
  {
   log->debug(tr("reply in QUERYSENT state %1").arg(replyString));
   if (replyString.contains("SPROG"))
   {
    stopTimer();
    if(replyString.startsWith("\r\nP> ") && replyString.length() > 5)
     replyString = replyString.mid(5); // remove extraneous prompt ACK
    QStringList splits = replyString.split("\n");
    splits = splits[1].split(" ");
    int index = 1;
    log->debug("Elements in version reply: " + QString::number(splits.length()));
    log->debug(tr("First element: <%1>").arg(splits[0]));
    if (splits[0].contains("Pi-SPROG"))
    {
     log->debug(tr("Found a Pi-SPROG %1").arg(splits[index]));
     if (splits[1] == "Nano")
     {
             v = new SprogVersion(new SprogType(SprogType::PISPROGNANO), splits[2].mid(1));
     }
     else if (splits[1] == "One")
     {
             v = new SprogVersion(new SprogType(SprogType::PISPROGONE), splits[2].mid(1));
     }
     else
     {
      if (log->isDebugEnabled()) {
          log->debug(tr("Unrecognised Pi-SPROG %1").arg(splits[1]));
      }
      v = new SprogVersion(new SprogType(SprogType::NOT_RECOGNISED));
     }
    }
    else if (splits[0].contains("SPROG"))
    {
     log->debug(tr("Found a SPROG %1").arg(splits[index]));
     if (splits[index] == "3")
     {
             index += 2;
             v = new SprogVersion(new SprogType(SprogType::SPROG3), splits[index]);
     }
     else if(splits.at(index) == "IV")
     {
             index += 2;
             v = new SprogVersion(new SprogType(SprogType::SPROGIV), splits[index]);
     }
     else if(splits.at(index) == "5")
     {
             index += 2;
             v = new SprogVersion(new SprogType(SprogType::SPROG5), splits[index]);
     }
     else if(splits.at(index) == "Nano")
     {
             index += 2;
             v = new SprogVersion(new SprogType(SprogType::NANO), splits[index]);
     }
     else if(splits.at(index) == "Sniffer")
     {
             index += 2;
             v = new SprogVersion(new SprogType(SprogType::SNIFFER), splits[index]);
     }
     else if(splits.at(index) =="II")
     {
      index++;
      if (splits[index] == ("USB"))
      {
          index += 2;
          v = new SprogVersion(new SprogType(SprogType::SPROGIIUSB), splits[index]);
      } else {
          index++;
          v = new SprogVersion(new SprogType(SprogType::SPROGII), splits[index]);
      }
     }
     else if(splits.at(index) =="Ver")
     {
             index += 1;
             v = new SprogVersion(new SprogType(SprogType::SPROGV4), splits[index]);
     }
     else
     {
             log->debug(tr("Unrecognised SPROG %1").arg(splits[index]));
             v = new SprogVersion(new SprogType(SprogType::NOT_RECOGNISED));
             break;
     }
    }
    else
    {
     // Reply contained "SPROG" but couldn't be parsed
     log->warn(tr("Found an unknown SPROG %1").arg(splits[index]));
     v = new SprogVersion(new SprogType(SprogType::NOT_RECOGNISED));
    }

    // Correct for SPROG IIv3/IIv4 which are different hardware
    if ((v->sprogType->_sprogType == SprogType::SPROGII) && (v->getMajorVersion() == 3)) {
        v = new SprogVersion(new SprogType(SprogType::SPROGIIv3), v->sprogVersion);
    } else if ((v->sprogType->_sprogType == SprogType::SPROGII) && (v->getMajorVersion() >= 4)) {
        v = new SprogVersion(new SprogType(SprogType::SPROGIIv4), v->sprogVersion);
    }
    log->debug(tr("Found: %1").arg(v->toString()));
    notifyVersion(v);
    state = QueryState::DONE;
    break;
   }
   break;
  }
  case DONE:
      break;

  default: {
      log->error("Unknown case");
  }
 }
}

/**
 * Internal routine to handle a timeout.
 */
/*synchronized*/ /*protected*/ void SprogVersionQuery::timeout() {
    SprogVersion* v;
    switch (state) {
        case CRSENT:
            log->debug("Timeout no SPROG prompt");
            state = QueryState::IDLE;
            v = new SprogVersion(new SprogType(SprogType::TIMEOUT));
            notifyVersion(v);
            break;
        case QUERYSENT:
            log->debug("Timeout no SPROG found");
            state = QueryState::IDLE;
            v = new SprogVersion(new SprogType(SprogType::NOT_A_SPROG));
            notifyVersion(v);
            break;
        case DONE:
        case IDLE:
            log->error(tr("Timeout in unexpected state: %1").arg(state));
            break;
        default:
            log->warn(tr("Unhandled timeout state code: %1").arg(state));
            break;
    }
    int bytes = tc->bytesAvailable();
    log->debug(tr("%1 bytes").arg(bytes));
}

/**
 * Internal routine to restart timer with a long delay.
 */
/*protected*/ void SprogVersionQuery::startLongTimer() {
    restartTimer(LONG_TIMEOUT);
}

/**
 * Internal routine to stop timer, as all is well.
 */
/*protected*/ void SprogVersionQuery::stopTimer() {
    if (timer != NULL) {
        timer->stop();
    }
}

/**
 * Internal routine to handle timer starts {@literal &} restarts.
 *
 * @param delay timer delay
 */
/*protected*/ void SprogVersionQuery::restartTimer(int delay) {
    if (timer == NULL) {
        timer = new QTimer(); //delay, new java.awt.event.ActionListener() {
        connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                timeout();
//            }
//        });
    }
    timer->stop();
    timer->setInterval(delay);
    timer->setSingleShot(true);//setRepeats(false);
    timer->start();
}

/*private*/ /*final*/ /*static*/ Logger* SprogVersionQuery::log = LoggerFactory::getLogger("SprogVersionQuery");
