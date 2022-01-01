#include "ros/ros.h"
#include <string>
#include <vector>

#include "ros1_bridge_support_pkg/MyCustomMessage.h"
#define PUB_CUSTOM "/custom_topic"
/*
bool value_boolean
int32 value_integer
float32 value_float
string value_string
*/
#include "std_msgs/String.h"
#define BRIDGE_TOPIC_NAME_PREFIX "/bridge_topic"
/*
string data
*/

#define NODE_NAME "ros1_bridge_support_topic_receiver"
#define QUEUE_SZ_DEFAULT 100

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLABEL LOGSQUARE( NODE_NAME )
#define OUTLOG( msg ) ROS_INFO_STREAM( OUTLABEL << msg )
#define OUTERR( msg ) OUTLOG( "ERROR: " << msg )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )

#define BRIDGE_MSG( topic ) OUTLOG( "bridge topic: " << LOGSQUARE( get_name_of_topic( topic ) ) << " (ROS2) --> (ROS1)" << LOGSQUARE( topic ) )

class ros1_bridge_topic_receiver
{
public:
	ros1_bridge_topic_receiver( )
	{
		// bridge the custom topic
		BRIDGE_MSG( PUB_CUSTOM );
		make_bridge_custom_topic( );
		
		OUTLOG( "online!" );
	}
	
	void spin( )
	{
		ros::spin( );
	}

private:
	// --- GENERAL PURPOSE METHODS ---
	
	// node handle
	ros::NodeHandle nh;
	
	// generate the name of the topic on the bridge
	std::string get_name_of_topic( std::string topic_name )
		{ return SS(BRIDGE_TOPIC_NAME_PREFIX) + topic_name; }
	
	// split a string using a separator
	std::vector<std::string> string_split( std::string str, char separator )
	{
		std::vector<std::string> res;
		std::string q = "";
		
		for( unsigned int i=0; i<str.length(); ++i )
		{
			if( str[i] == separator )
			{
				if( q != "" ) res.push_back( q );
				q = "";
			}
			else
				q += str[i];
		}
		if( q != "" ) res.push_back( q );
		
		return res;
	}
	
	// --- CUSTOM TOPIC ---
	
	// bridge handler from custom topic
	ros::Subscriber bridge_custom_topic;
	
	// outut handler  to custom topic
	ros::Publisher pub_custom_topic;
	
	// cast-back the message 'MyCustomMessage' from string to type
	ros1_bridge_support_pkg::MyCustomMessage cast_back_my_custom_message(
		const std_msgs::StringConstPtr& msg )
	{
		// split the message
		std::vector<std::string> content = string_split( msg->data, ' ' );
		
		// cast field by field
		ros1_bridge_support_pkg::MyCustomMessage rmsg;
		rmsg.value_boolean = ( content[0] == "1" ? true : false );
		rmsg.value_integer = atoi( content[1].c_str( ) );
		rmsg.value_float = atof( content[2].c_str( ) );
		rmsg.value_string = content[3];
		
		return rmsg;
	}
	
	// listener callback for custom topic
	void bridge_custom_topic_cbk( const std_msgs::StringConstPtr& msg )
	{
		// cast-back the message
		ros1_bridge_support_pkg::MyCustomMessage rmsg = 
			cast_back_my_custom_message( msg );
		
		// publish the message
		pub_custom_topic.publish( rmsg );
	}
	
	// make the link
	void make_bridge_custom_topic( )
	{
		// subscription
		bridge_custom_topic = nh.subscribe( 
			get_name_of_topic( PUB_CUSTOM ),
			QUEUE_SZ_DEFAULT,
			&ros1_bridge_topic_receiver::bridge_custom_topic_cbk,
			this 
		);
		
		// publisher
		pub_custom_topic = nh.advertise<ros1_bridge_support_pkg::MyCustomMessage>(
			PUB_CUSTOM,
			QUEUE_SZ_DEFAULT
		);
	}
};

int main( int argc, char* argv[] )
{
	ros::init( argc, argv, NODE_NAME );
	
	OUTLOG( "online!" );
	( ros1_bridge_topic_receiver( ) ).spin( );
	
	return 0;
}
