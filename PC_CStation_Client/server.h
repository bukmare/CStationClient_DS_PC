#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QNetworkSession>
#include <QtNetwork>
#include <stdlib.h>
#include "./abstractserver.h"
#include "./classes/clientaction.h"
#include "./classes/clientsensor.h"
#include "./classes/clientSensors/clientsensoractivity.h"
#include "./classes/clientSensors/clientsensorbtnactivity.h"
#include "./classes/clientActions/clientactionreset.h"
#include "./classes/clientActions/clientactionconfig.h"

class Server : public AbstractServer
{
    Q_OBJECT

public:
    Server();
    ~Server();
    void Reset();
    void StartServer();
    void StopServer();
    void ConfigurationMode();
    bool SendData(QString message);

    int getRemotePort() const;
    void setRemotePort(int value);
    QString getRemoteIPAddress() const;
    void setRemoteIPAddress(const QString &value);
    int getDeviceId() const;
    void setDeviceId(int value);
    int getLocalPort() const;
    void setLocalPort(int value);

    void setSendingInterval(unsigned seconds);

    QMap<QString, ClientSensor *> *clientSensors();
    QMap<QString, ClientAction *> *clientActions();

signals:

private slots:
    void sessionOpened();
    void recieveConnection();
    void recieveData();
    void clientDisconnected();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void displayError(QAbstractSocket::SocketError socketError);
    void sendingTimeout();
    void sensorInitiateDataSending(QString message);

private:
    bool is_init_connection;
    bool is_config_mode;
    int remote_port = 0;
    int local_port = 0;
    int device_id = 0;
    QString remoteIPAddress;
    QTcpSocket *remote_server_socket;
    QMap<quint32, QTcpSocket *> *sockets;
    QMap<QString, ClientSensor *> *sensors;
    QMap<QString, ClientAction *> *actions;

    QString thisIPAddress;
    QTcpServer *tcpServer;
    QNetworkSession *networkSession;

    QTimer *shotTimer;

    QTcpSocket *getRemoteSocket();
    void sendSensorsInfo();
    void sendActionsInfo();
    void initSensors();
};

#endif
