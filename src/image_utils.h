#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H
#include <vector>
#include <QString>
#include <map>
#include <iostream>
#include <QDir>
#include <QStringList>
#include <fstream>

class image_utils
{
public:
    image_utils();
    static unsigned npos;
    static std::map<std::string, bool> images;
    static std::map<std::string, bool>::iterator get_map_from_index(int n);
    static void list_dir(QString Path);
    static void write_result();
    static float get_result();
    static int get_error();
    static std::vector<std::string> entered;
    static bool fileExists(std::string file);
    static bool already_entered(std::string str);
};

#endif // IMAGE_UTILS_H
