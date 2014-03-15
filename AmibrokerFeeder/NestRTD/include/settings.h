#ifndef NESTRTD_SETTINGS_H
#define NESTRTD_SETTINGS_H

#include <string>
#include <vector>

class Settings{

public:
    void loadSettings();

    std::string rtd_server_prog_id;
    int         bar_period;                                               // In milliseconds
    std::string time_format;
    std::string csv_path;                                                 // path for csv file to be sent to Amibroker - Use ram drive
    std::string ab_db_path;
        
    struct Scrip {
        std::string topic_name;                                           // Scrip Name = Topic 1
        std::string ticker;                                               // Ticker Alias sent to Amibroker                        
        std::string topic_LTP;                                            // Topic 2 for each field
        std::string topic_LTT;                        
        std::string topic_vol_today;
        std::string topic_OI; 
    };

    std::vector<Scrip> scrips_array;                                      // RTD Topics for each scrip
    int                no_of_scrips;
};


#endif

