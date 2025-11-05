#include "crypto.h"
#include "JavaExtentions.h"
#include <QProcess>
#include <QCoreApplication>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

    QString JavaExtentions::runJavaProcess(const QString& javaExe,
                                  const QStringList& args,
                                  int timeoutMs,
                                  QString* stderrOut,
                                  int* exitCode)
    {
        QProcess p;
        p.start(javaExe, args);
        if (!p.waitForStarted(5000))
            return QStringLiteral("Не удалось запустить Java: %1").arg(javaExe);

        if (!p.waitForFinished(timeoutMs)) {
            p.kill();
            if (stderrOut) *stderrOut = QStringLiteral("Таймаут выполнения");
            if (exitCode)  *exitCode  = -1;
            return {};
        }
        if (stderrOut) *stderrOut = QString::fromUtf8(p.readAllStandardError());
        if (exitCode)  *exitCode  = p.exitCode();
        return QString::fromUtf8(p.readAllStandardOutput());
    }


    QString JavaExtentions::javaExePath()
    {
#ifdef Q_OS_WIN
        return "C:/Program Files/Java/jdk-25/bin/java.exe";
#else
        return "java";
#endif
    }

    QString JavaExtentions::jarPath()
    {
            return QCoreApplication::applicationDirPath() + "/analyzer.jar";
    }

    QStringList JavaExtentions::argsSign_Jar(const QString& file, const QString& keys_dir, const QString& params)  { return { "-jar", jarPath(), "sign", params, file, keys_dir }; }
    QStringList JavaExtentions::argsCheck_Jar(const QString& file, const QString& keys, const QString& params) { return { "-jar", jarPath(), "verify", file, keys, params }; }



    bool JavaExtentions::parseJson(const QString& json, QJsonObject* out, QString* error)
    {
        QJsonParseError pe{};
        auto doc = QJsonDocument::fromJson(json.toUtf8(), &pe);
        if (pe.error != QJsonParseError::NoError || !doc.isObject()) {
            if (error) *error = QStringLiteral("JSON parse error: %1\nRaw: %2").arg(pe.errorString(), json);
            return false;
        }
        *out = doc.object();
        return true;
    }
