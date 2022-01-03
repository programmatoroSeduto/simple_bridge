
#include "ros/ros.h"

#include <string>

#include "ros1_bridge_support_pkg/MyCustomService.h"
/*
int32 index
string mystery_word
---
bool guessed
*/

#define NODE_NAME "test_client"
#define CLIENT_CUSTOM "/my_custom_service"

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLABEL LOGSQUARE( NODE_NAME )
#define OUTLOG( msg ) ROS_INFO_STREAM( OUTLABEL << msg )
#define OUTERR( msg ) OUTLOG( "ERROR: " << msg )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )

class test_client
{
public:
	test_client( ) 
	{ 
		// require the service client
		sc = nh.serviceClient<ros1_bridge_support_pkg::MyCustomService>( CLIENT_CUSTOM );
		sc.waitForExistence( );
		
		OUTLOG( "online!" );
	}
	
	void spin( ) 
	{
		while( ros::ok( ) && !find_solution_rand( ) )
			ros::spinOnce( );
		
		OUTLOG( "closing..." );
	}
	
private:
	// node handle
	ros::NodeHandle nh;
	
	// call the service
	bool find_solution_rand( )
	{
		// solution: "ciao500" ... 
		ros1_bridge_support_pkg::MyCustomService msg;
		msg.request.index = rand( );
		msg.request.mystery_word = "ciao";
		
		OUTLOG( "trying with " << msg.request.mystery_word << msg.request.index );
		sc.call( msg );
		
		if( msg.response.guessed )
		{
			OUTLOG( "AHAHAH SOLUTION FOUND!" );
			return true;
		}
		else
		{
			OUTLOG( "...wrong solution" );
			return false;
		}
	}
	
	// client
	ros::ServiceClient sc;
};

int main( int argc, char* argv[] )
{
	ros::init( argc, argv, NODE_NAME );
	
	(test_client( )).spin( );
	
	return 0;
}
