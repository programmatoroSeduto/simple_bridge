#include "ros/ros.h"

#include <string>
#include <vector>

#include "ros1_bridge_support_pkg/MyCustomService.h"
/*
int32 index
string mystery_word
---
bool guessed
*/

#define NODE_NAME "test_ros1_service"

#define SERVICE_CUSTOM "/my_custom_service_second"

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLABEL LOGSQUARE( NODE_NAME )
#define OUTLOG( msg ) ROS_INFO_STREAM( OUTLABEL << msg )
#define OUTERR( msg ) OUTLOG( "ERROR: " << msg )


class test_service
{
public:
	// costruttore
	test_service( )
	{
		// service 
		serv = nh.advertiseService( SERVICE_CUSTOM, &test_service::cbk, this );
	}

	// funzione spin
	void spin( )
	{
		ros::spin( );
	}
	
private:
	// service callback
	bool cbk( 
		ros1_bridge_support_pkg::MyCustomService::Request &req, 
        ros1_bridge_support_pkg::MyCustomService::Response &res ) 
	{ 
		OUTLOG( "received {index=" << req.index << ", mystery_word='" << req.mystery_word << "'}" );
		res.guessed = true;
		return true;
	}
	
	// service handle
	ros::ServiceServer serv;

	// ROS1 node handle
	ros::NodeHandle nh;
};


int main( int argc, char* argv[] )
{
	ros::init( argc, argv, NODE_NAME );
	
	OUTLOG( "Online!" );
	( test_service( ) ).spin( );
	
	return 0;
}
