#include "zeroconfserviceevent.h"
#include "loggerfactory.h"
#include "zeroconfservice.h"

//ZeroConfServiceEvent::ZeroConfServiceEvent()
//{

//}
/**
 *
 * @author rhwood
 */
// /*public*/ class ZeroConfServiceEvent : public EventObject {

    /*private*/ /*static*/ /*final*/ Logger* ZeroConfServiceEvent::log = LoggerFactory::getLogger("ZeroConfServiceEvent");

    /*protected*/ ZeroConfServiceEvent::ZeroConfServiceEvent(ZeroConfService* service, JmDNS* dns) : EventObject(service) {
        //super(service);
        this->dns = dns;
        this->service = service;
    }

    /**
     * @return the service
     */
    /*public*/ ZeroConfService* ZeroConfServiceEvent::getService() {
        return this->service;
    }

    /**
     * @return the JmDNS server
     */
    /*public*/ JmDNS* ZeroConfServiceEvent::getDNS() {
        return this->dns;
    }

    /**
     * @return the address or null if there is an IO exception.
     */
    /*public*/ InetAddress* ZeroConfServiceEvent::getAddress() {
        try {
            return this->dns->getInetAddress();
        } catch (IOException* ex) {
            log->error("Unable to get interface address.", ex);
            return nullptr;
        }
    }


