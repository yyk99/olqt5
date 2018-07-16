#ifndef OL_FORMAT_FORMATTYPE_H
#define OL_FORMAT_FORMATTYPE_H
/**
 * @module ol/format/FormatType
 */
namespace ol {
namespace format {

/**
 * @enum {string}
 */
struct FormatType {
public:
    enum _type {
        ARRAY_BUFFER, // 'arraybuffer',
        JSON, // 'json',
        TEXT, // 'text',
        XML, // 'xml'
    };
};

}
}

#endif // OL_FORMAT_FORMATTYPE_H
