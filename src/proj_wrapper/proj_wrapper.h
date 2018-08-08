//
//
//

#ifndef OL_PROJ_WRAPPER_H
#define OL_PROJ_WRAPPER_H

#include <string>
#include <memory>
#include <map>

namespace ol {
namespace pj {

class Context;
class Pj; /* projection */
typedef std::shared_ptr<Pj> proj_t;

typedef std::map<std::string, std::string> props_t;

class Proj4 {
    std::unique_ptr<Context> m_ctx;
public:
    Proj4();
    ~Proj4();

    proj_t parse(std::string const &text);
    props_t properties(proj_t projection) const;
};

}
}

#endif // OL_PROJ_WRAPPER_H
