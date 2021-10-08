#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H
#include <vector>
#include <QString>


class image_utils
{
public:
    image_utils();

    static int hits;
    static int misses;
    inline static int npos;
    inline static std::vector<QString> wrong_images;
};

#endif // IMAGE_UTILS_H
