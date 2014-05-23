#ifndef  ABBACKFILL_READER_H
#define  ABBACKFILL_READER_H
  
#include <string>
#include <fstream>

class Reader{

public:
    Reader();
    ~Reader();

    bool parseVWAPToCsv     ( const std::string &vwap_file, const std::string &csv_file_path  );
    bool parseDataTableToCsv( const std::string &dt_file,   const std::string &csv_file_path  );    
    void closeOutput();

private:
    std::ifstream    fin;
    std::ofstream    fout;    

    Reader( const Reader& );
    Reader operator=(const Reader& );
        
    bool setUpInputStream  ( const std::string &in_file  );
    void setUpOutputStream ( const std::string &out_file  );
    void changeHHFrom12To24( std::string &time ); 
    
};

#endif