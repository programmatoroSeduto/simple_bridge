
#include "ros/ros.h"

#include "ros1_bridge_support_pkg/MyCustomMessage.h"
#define SUB_CUSTOM "/custom_topic_a"
/*
bool value_boolean
int32 value_integer
float value_float
string value_string
*/

#define NODE_NAME "ros1_receiver"
#define QUEUE_SZ_DEFAULT 100

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLABEL LOGSQUARE( NODE_NAME )
#define OUTLOG( msg ) ROS_INFO_STREAM( OUTLABEL << msg )
#define OUTERR( msg ) OUTLOG( "ERROR: " << msg )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )

class ros1_receiver
{
public:
	ros1_receiver( )
	{
		// subscription
		sub_custom_topic = nh.subscribe(
			SUB_CUSTOM,
			QUEUE_SZ_DEFAULT,
			&ros1_receiver::listener_cbk,
			this 
		);
		
		OUTLOG( "online!" );
	}
	
	void spin( )
	{
		ros::spin( );
	}

private:
	// sbscription callback
	void listener_cbk( const ros1_bridge_support_pkg::MyCustomMessageConstPtr& msg )
	{
		++ msg_count;
		OUTLOG( "[" << msg_count << "] received --> { " 
			<< "value_boolean:" << SSS( msg->value_boolean ) << ", "
			<< "value_integer:" << msg->value_integer << ", "
			<< "value_float:" << msg->value_float << ", "
			<< "value_string:'" << msg->value_string << "'}" );
	}
	
	// ROS1 node handle
	ros::NodeHandle nh;
	
	// subscription handle
	ros::Subscriber sub_custom_topic;
	
	// messages counter
	int msg_count = 0;
};

int main( int argc, char* argv[] )
{
	ros::init( argc, argv, NODE_NAME );
	
	( ros1_receiver( ) ).spin( );
	
	return 0;
}
