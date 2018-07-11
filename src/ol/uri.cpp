//
//
//

#include "uri.h"

std::string encodeURIComponent(std::string const &s)
{
    return s;
}

std::string join(std::vector<std::string> const &v, std::string const &d)
{
    if (v.size() == 0)
        return std::string();
    if (v.size() == 1)
        return v.front();
    std::string r = v.front();
    for (int i = 1; i != v.size(); ++i) {
        r += d;
        r += v[i];
    }
    return r;
}

std::string olqt::appendParams(std::string uri, std::vector<std::tuple<std::string, std::string>> const & params)
{
    //export function appendParams(uri, params) {
    //  const keyParams = [];
    std::vector<std::string> keyParams;

    //  // Skip any null or undefined parameter values
    //  Object.keys(params).forEach(function(k) {
    //    if (params[k] !== null && params[k] !== undefined) {
    //      keyParams.push(k + '=' + encodeURIComponent(params[k]));
    //    }
    //  });
    for (auto const &p : params) {
        keyParams.push_back(std::get<0>(p) + "=" + encodeURIComponent(std::get<1>(p)));
    }

    //  const qs = keyParams.join('&');
    std::string qs = join(keyParams, "&");
    //  // remove any trailing ? or &
    //  uri = uri.replace(/[?&]$/, '');
    //  // append ? or & depending on whether uri has existing parameters
    //  uri = uri.indexOf('?') === -1 ? uri + '?' : uri + '&';
    uri = uri.find('?') == -1 ? uri + '?' : uri + '&';
    //  return uri + qs;
    return uri + qs;
    //}
}
