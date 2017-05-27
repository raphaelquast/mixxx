#ifndef MIXXX_UTIL_LOGGING_H
#define MIXXX_UTIL_LOGGING_H

#include <QtDebug>


namespace mixxx {

enum class LogLevel {
    Critical = 0,
    Warning = 1,
    Info = 2,
    Debug = 3,
    Default = Warning,
};

class Logging {
  public:
    // These are not thread safe. Only call them on Mixxx startup and shutdown.
    static void initialize(const QString& settingsPath,
                           LogLevel logLevel,
                           bool debugAssertBreak);
    static void shutdown();

    // Query the current log level
    static LogLevel logLevel() {
        return s_logLevel;
    }
    static bool enabled(LogLevel logLevel) {
        return s_logLevel >= logLevel;
    }
    static bool debugEnabled() {
        return enabled(LogLevel::Debug);
    }
    static bool infoEnabled() {
        return enabled(LogLevel::Info);
    }

  private:
    Logging() = delete;

    static LogLevel s_logLevel;
};

class Logger final {
public:
    Logger() = default;
    explicit Logger(const char* logContext);
    explicit Logger(const QString& logContext);

    QDebug log(QDebug stream) const {
        return stream << m_preambleChars.data();
    }

    QDebug debug() const {
        return log(qDebug());
    }

    bool debugEnabled() const {
        return Logging::debugEnabled();
    }

    QDebug info() const {
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        return log(qInfo());
#else
        // Qt4 does not support log level Info, use Debug instead
        return debug();
#endif
    }

    bool infoEnabled() const {
        return Logging::infoEnabled();
    }

    QDebug warning() const {
        return log(qWarning());
    }

    QDebug critical() const {
        return log(qCritical());
    }

private:
    QByteArray m_preambleChars;
};

}  // namespace mixxx

#endif /* MIXXX_UTIL_LOGGING_H */
