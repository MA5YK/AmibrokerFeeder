
#include "settings.h"
#include "misc_util.h"


void Settings::loadSettings(){

    csv_file_path          = MiscUtil::getINIString("CSVFolderPath",             "ABBackFill");
   // ab_db_path             = MiscUtil::getINIString("AbDbPath",                  "ABBackFill");
    vwap_file_path         = MiscUtil::getINIString("VWAPBackFillInputFilePath", "ABBackFill");
    data_table_file_path   = MiscUtil::getINIString("DTBackFillInputFilePath",   "ABBackFill");

    MiscUtil::createDirectory( csv_file_path );                            // If folder does not exist, create it
    csv_file_path.append("quotes.bfill");
}



