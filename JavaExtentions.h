#ifndef JAVAEXTENTIONS_H
#define JAVAEXTENTIONS_H
#include <crypto.h>
#include <QProcess>
#include <QCoreApplication>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
class JavaExtentions {
public:
    static QString runJavaProcess(const QString& javaExe, const QStringList& args,int timeoutMs,QString* stderrOut, int* exitCode);
    static QString javaExePath();
    static QString jarPath(int  number_operation);
    static QStringList argsSign_Jar(const QString& file);
    static QStringList argsCheck_Jar(const QString& file);
    static QStringList argsKeys_Jar();
    static bool parseJson(const QString& json, QJsonObject* out, QString* error);
};

#endif // JAVAEXTENTIONS_H
