#ifndef  ABBACKFILL_SETTINGS_H
#define  ABBACKFILL_SETTINGS_H

#include <string>

class Settings{

public:
    std::string   csv_file_path;
    std::string   ab_db_path;
    std::string   vwap_file_path;
    std::string   data_table_file_path;

    void loadSettings();

};


#endif