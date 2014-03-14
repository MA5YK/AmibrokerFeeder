#ifndef  AMIBROKER_FEED_H
#define  AMIBROKER_FEED_H

#include <OAIdl.h>
#include <string>

/**
 *	All Functions including Constructor and Destructor MUST be called in same thread
 *		CoInitialize() is per thread
 */
class Amibroker{

public:
	Amibroker( const std::string &in_ab_db_path,  const std::string &in_quotes_file_name,  const std::string &in_quotes_format  );	 
   ~Amibroker();																	 
   
   void setVisible( int is_visible );    
   void import	  ();
   void refreshAll();    
   void saveDB	  ();   
   void loadDB	  (); 
   
   void setQuotesFileName( const std::string &in_quotes_file_name ){ quotes_file_name = in_quotes_file_name;  };
   void setQuotesFormat  ( const std::string &in_quotes_format    ){ quotes_format	  = in_quotes_format;	  };


private:
	Amibroker( const Amibroker& );
	Amibroker operator=(const Amibroker& );
	
	std::string		ab_db_path;
	std::string		quotes_file_name;
	std::string		quotes_format;	  

	IDispatch		*amiBrokerDispatch;
	DISPID			dispid_visible, dispid_save_db, dispid_load_db, dispid_import, dispid_refresh_all;
		
	DISPID getDispid  ( WCHAR * name );	
	void   setProperty( DISPID dispid, VARIANT &input );
	void   dispatch   ( DISPID dispid, WORD wFlag, VARIANT &result );
	void   dispatch   ( DISPID dispid, WORD wFlag, DISPPARAMS &args, VARIANT  &result  );		   

};

#endif
