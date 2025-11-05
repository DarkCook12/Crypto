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
    static QString jarPath();
    static QStringList argsSign_Jar(const QString& file, const QString& keys_dir, const QString& params );
    static QStringList argsCheck_Jar(const QString& file, const QString& keys, const QString& params);
    static bool parseJson(const QString& json, QJsonObject* out, QString* error);
};

#endif // JAVAEXTENTIONS_H
