#ifndef DBCONNECTIONSETTINGS_H
#define DBCONNECTIONSETTINGS_H

#include <QDialog>

class QLineEdit;
class DBConnectionSettings : public QDialog
{
public:
    DBConnectionSettings(QWidget* parent);

private:
    QLineEdit* connection;
    QLineEdit* hostname;
    QLineEdit* port;
    QLineEdit* username;
    QLineEdit* password;
    QLineEdit* worlddb;

    QString origConnectionName;
    QString origHostName;
    QString origPort;
    QString origWorldDB;
    QString origUsername;
    QString origPassword;

public slots:
    void done(int);
};

#endif // DBCONNECTIONSETTINGS_H
