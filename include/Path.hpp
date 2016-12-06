#ifndef PATH_HPP
#define PATH_HPP

class Path {
public:
    static const char *walkPath;
    static const char *carPath;
};

const char *Path::walkPath = "../data/walkMap.json";
const char *Path::carPath = "../data/carMap.json";


#endif
