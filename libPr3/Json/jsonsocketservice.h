#ifndef JSONSOCKETSERVICE_H
#define JSONSOCKETSERVICE_H

#include <QObject>
#include <QLocale>
#include "jsonconnection.h"
#include "jsonexception.h"

class JsonNode;
/**
 * Interface for all JSON Services.
 *
 * @author Randall Wood
 */
/*public*/ /*abstract*/ class JsonSocketService : public QObject
{
 Q_OBJECT
protected:
    /*protected*/ /*final*/ JsonConnection* connection;

    /*protected*/ JsonSocketService(JsonConnection* connection, QObject* parent = 0) : QObject(parent) {
        this->connection = connection;
    }
public:
    /**
     * Handle an inbound message.
     *
     * @param type   The service type. If the implementing service responds to
     *               multiple types, it will need to use this to handle data
     *               correctly.
     * @param data   JSON data. The contents of this will depend on the
     *               implementing service.
     * @param locale The locale of the client, which may be different than the
     *               locale of the JMRI server.
     * @throws java.io.IOException Thrown if the service cannot send a response.
     *                             This will cause the JSON Server to close its
     *                             connection to the client if open.
     * @throws jmri.JmriException  Thrown if the request cannot be handled.
     *                             Throwing this will cause the JSON Server to
     *                             pass a 500 UnsupportedOperation message to
     *                             the client.
     * @throws JsonException       Thrown if the service needs to pass an error
     *                             message back to the client.
     */
    /*public*/ /*abstract*/ virtual  void onMessage(QString /*type*/, QJsonObject /*data*/, QLocale /*locale*/) throw (IOException, JmriException, JsonException) {}

    /**
     * Handle a request for a list of objects.
     *
     * @param type   The service type. If the implementing service responds to
     *               multiple types, it will need to use this to handle data
     *               correctly.
     * @param data   JSON data. The contents of this will depend on the
     *               implementing service.
     * @param locale The locale of the client, which may be different than the
     *               locale of the JMRI server.
     * @throws java.io.IOException Thrown if the service cannot send a response.
     *                             This will cause the JSON Server to close its
     *                             connection to the client if open.
     * @throws jmri.JmriException  Thrown if the request cannot be handled.
     *                             Throwing this will cause the JSON Server to
     *                             pass a 500 UnsupportedOperation message to
     *                             the client.
     * @throws JsonException       If the service needs to pass an error message
     *                             back to the client.
     */
    /*public*/ /*abstract*/ virtual  void onList(QString /*type*/, /*JsonNode*/QJsonObject /*data*/, QLocale /*locale*/) throw (IOException, JmriException, JsonException) {}

    /**
     * Perform any teardown required when closing a connection.
     */
    /*public*/ /*abstract*/ virtual  void onClose() {}

    /**
     * @return the connection
     */
    /*public*/ JsonConnection* getConnection() {
        return connection;
    }
 friend class SensorListener;
 friend class TurnoutListener;
 friend class JsonRosterListener;
 friend class BlockListener;
 friend class LightListener;
 friend class LayoutBlockListener;
};
#endif // JSONSOCKETSERVICE_H
