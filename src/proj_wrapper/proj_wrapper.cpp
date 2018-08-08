//
// yyk 2018
//

#include "proj_wrapper.h"

#include <stdio.h>
#include <proj.h>
#include <stdexcept>

namespace ol {
namespace pj {

class Pj;
class Context {
public:
    PJ_CONTEXT * C;

    Context() : C(proj_context_create())
    {
        if (C == 0)
            throw std::runtime_error("cannot create context");
    }

    ~Context()
    {
        proj_context_destroy(C);
    }

    Pj *Context::create(const char *text);
};

class Pj {
public:
    PJ * P;

    Pj() : P() {}
    Pj(Context *ctx, const char *text) : P(proj_create(ctx->C, text))
    {
        if (0 == P) {
            int err = proj_context_errno(ctx->C);
            std::string s = proj_errno_string(err);
            throw std::runtime_error("cannot create PJ: " + s);
        }
    }

    ~Pj() 
    {
        if (P)
            proj_destroy(P);
    }
};

Pj *Context::create(const char *text)
{
    return new Pj(this, text);
}


} // namespace
} // namespace

using namespace ol::pj;

Proj4::Proj4() : m_ctx(new Context())
{

}

Proj4::~Proj4()
{

}

ol::pj::proj_t
Proj4::parse(std::string const &text)
{
    return proj_t(m_ctx->create(text.c_str()));
}

#include <sstream>
#include <iterator>
#include <vector>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(std::string const &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

ol::pj::props_t 
Proj4::properties(proj_t projection) const
{
    props_t r;
    if (projection == 0 || projection->P == 0)
        return r;

    auto info = proj_pj_info(projection->P);
    //-info
    //    +id	0x0000003d83a0ae8e "lcc"	const char *
    //    +description	0x00007ffe0cd2c2d0 "Lambert Conformal Conic\n\tConic, Sph&Ell\n\tlat_1= and lat_2= or lat_0"	const char *
    //    +definition	0x0000003d83a04c80 "proj=lcc lat_1=29.3 lat_2=30.7 lat_0=28.66666666666667 lon_0=-91.33333333333333 x_0=609601.2192024384 y_0=0 ellps=clrk66 datum=NAD27 to_meter=0.3048006096012192 no_defs nadgrids=@conus,@alaska,@ntv2_0...	const char *
    //    has_inverse	1	int
    //    accuracy - 1.0000000000000000	double

    std::vector<std::string> params = split(info.definition, ' ');
    for (auto s : params) {
        auto pos = s.find('=');
        if (pos == std::string::npos)
            r[s] = "1";
        else
            r[s.substr(0, pos)] = s.substr(pos + 1);
    }
    return r;
}
