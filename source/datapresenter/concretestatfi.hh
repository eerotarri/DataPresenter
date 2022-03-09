#ifndef CONCRETESTATFI_HH
#define CONCRETESTATFI_HH

#include <vector>
#include <string>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class ConcreteStatfi : public QObject
{
    Q_OBJECT
public:
    explicit ConcreteStatfi(QObject *parent = nullptr);

public slots:

private slots:
    void post(QString location, QByteArray data);
    void readyRead();

private:
    QNetworkAccessManager manager_;

    /*!
     * \fn QByteArray ConcreteStatfi::generateQuery(std::string data, std::vector<int> years)
     * \brief Generates QByteArray formatted query for posting
     *
     *
    */
    QByteArray generateQuery(std::string data, std::vector<int> years);
    std::vector<double> arrayToVector(QJsonArray array);
};

#endif // CONCRETESTATFI_HH
