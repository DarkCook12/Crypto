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

    // Обёртки: настрой тут ОДИН из двух режимов — JAR или класс:
    QString JavaExtentions::javaExePath()
    {
#ifdef Q_OS_WIN
        return "C:/Program Files/Java/jdk-25/bin/java.exe";
#else
        return "java";
#endif
    }

    QString JavaExtentions::jarPath(int  number_operation)
    {
        if(number_operation == 1){
            return QCoreApplication::applicationDirPath() + "/analyzer.jar"; //sign.jar
        }
        else if(number_operation == 2){
            return QCoreApplication::applicationDirPath() + "/analyzer.jar"; // check.jar
        }
        else if(number_operation == 3){
            return QCoreApplication::applicationDirPath() + "/analyzer.jar"; // generate_keys
        }
        return 0;
    }

    // ---- Вариант А: запуск JAR с Main-Class ----
    QStringList JavaExtentions::argsSign_Jar(const QString& file)  { return { "-jar", jarPath(1), "sign",  file }; } // добавить файл с параметрами и ключами static QStringList argsSign_Jar(const QString& file)  { return { "-jar", jarPath(), "sign",  file, params, keys }; }
    QStringList JavaExtentions::argsCheck_Jar(const QString& file) { return { "-jar", jarPath(2), "check", file }; } // добавить файл с параметрами и ключами static QStringList argsCheck_Jar(const QString& file) { return { "-jar", jarPath(), "check", file, params, keys }; }
    QStringList JavaExtentions::argsKeys_Jar()                     { return { "-jar", jarPath(3), "keys"       }; } // придумать как должно работать

    // ---- Вариант Б: запуск по классу (если нет Main-Class в JAR) ----
    // static QStringList argsSign_Cls (const QString& file){ return { "", jarPath(), "", "sign",  file }; }
    // static QStringList argsCheck_Cls(const QString& file){ return { "", jarPath(), "", "check", file }; }
    // static QStringList argsKeys_Cls()                    { return { "-", jarPath(), "Main", "keys"       }; }

    bool JavaExtentions::parseJson(const QString& json, QJsonObject* out, QString* error) // подумать над парсингом и как это выводить
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
