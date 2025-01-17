#include "sources/soundsource.h"

#include "util/logger.h"

namespace mixxx {

namespace {

const Logger kLogger("SoundSource");

inline QUrl validateUrl(QUrl url) {
    DEBUG_ASSERT(url.isValid());
    VERIFY_OR_DEBUG_ASSERT(url.isLocalFile()) {
        kLogger.warning()
                << "Unsupported URL:"
                << url.toString();
    }
    return url;
}

} // anonymous namespace

/*static*/ QString SoundSource::getFileExtensionFromUrl(const QUrl& url) {
    return validateUrl(url).toString().section(".", -1).toLower().trimmed();
}

SoundSource::SoundSource(const QUrl& url, const QString& type)
        : AudioSource(validateUrl(url)),
          MetadataSourceTagLib(getLocalFileName()),
          m_type(type) {
}

} // namespace mixxx
