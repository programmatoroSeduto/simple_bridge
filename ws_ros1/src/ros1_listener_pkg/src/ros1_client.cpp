#include "ros/ros.h"
#include "std_srvs/SetBool.h"
#include <string>

#define NODE_NAME "ros1_client"
#define SERVICE_BOOL "/bridge_simple_test/service_bool"

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLABEL LOGSQUARE( NODE_NAME )
#define OUTLOG( msg ) ROS_INFO_STREAM( OUTLABEL << msg )
#define OUTERR( msg ) OUTLOG( "ERROR: " << msg )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )



class client_class
{
public:
	client_class( )
	{
		// richiedi il servizio
		cl = nh.serviceClient<std_srvs::SetBool>( SERVICE_BOOL );
		if( !cl.waitForExistence( ros::Duration( 5.00 ) ) )
			OUTERR( "impossibile contattare il servizio " << LOGSQUARE( SERVICE_BOOL ) );
	}
	
	void spin( )
	{
		// spin forever...
		while( true )
		{
			std_srvs::SetBool msg;
			last = !last;
			msg.request.data = last;
			
			cl.call( msg );
		}
	}

private:
	// node handle
	ros::NodeHandle nh;
	
	// client handle
	ros::ServiceClient cl;
	
	// last message 
	bool last = false;
};




int main( int argc, char* argv[] )
{
	ros::init( argc, argv, NODE_NAME );
	
	OUTLOG( "Online!" );
	( client_class( ) ).spin( );
	
	return 0;
}
