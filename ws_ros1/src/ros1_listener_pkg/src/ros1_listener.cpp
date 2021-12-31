#include "ros/ros.h"
#include "std_msgs/String.h"

#include <string>

#define NODE_NAME "ros1_listener"
#define SUB_TOPIC_STRING "/bridge_simple_test/topic_string"

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLABEL LOGSQUARE( NODE_NAME )
#define OUTLOG( msg ) ROS_INFO_STREAM( OUTLABEL << msg )
#define OUTERR( msg ) OUTLOG( "ERROR: " << msg )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )

class subscriber_class
{
public:
	subscriber_class( )
	{
		// subscription
		sub_ = nh.subscribe( SUB_TOPIC_STRING, 100, &subscriber_class::listener_cbk, this );
	}
	
	void spin( )
	{
		// simple spin
		ros::spin( );
	}

private:
	// listener callback
	void listener_cbk( const std_msgs::StringConstPtr& msg )
	{
		++ msg_count;
		OUTLOG( LOGSQUARE( msg_count ) << "Message content: " << msg->data );
	}
	
	// node handle
	ros::NodeHandle nh;
	
	// subscription handle
	ros::Subscriber sub_;
	
	// msg counter
	int msg_count = 0;
};

int main( int argc, char* argv[] )
{
	ros::init( argc, argv, NODE_NAME );
	
	OUTLOG( "Online!" );
	( subscriber_class( ) ).spin( );
	
	return 0;
}
