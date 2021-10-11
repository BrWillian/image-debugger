#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H
#include <vector>
#include <QString>
#include <map>
#include <iostream>
#include <QDir>
#include <QStringList>
#include <filesystem>
#include <fstream>

class image_utils
{
public:
    image_utils();
    inline static unsigned npos;
    inline static std::map<std::string, bool> images;
    static std::map<std::string, bool>::iterator get_map_from_index(int n);
    static void list_dir(QString Path);
    static void write_result();
    static float get_result();
    static int get_error();

};

#endif // IMAGE_UTILS_H
