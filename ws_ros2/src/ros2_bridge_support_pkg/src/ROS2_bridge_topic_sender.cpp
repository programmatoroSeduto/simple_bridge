
#include "rclcpp/rclcpp.hpp"
#include <string>
#include <memory>
using std::placeholders::_1;

#include "ros2_bridge_support_pkg/msg/my_custom_message.hpp"
#define SUB_CUSTOM "/custom_topic"
/*
bool value_boolean
int32 value_integer
float value_float
string value_string
*/
#include "std_msgs/msg/string.hpp"
#define BRIDGE_TOPIC_NAME_PREFIX "/bridge_topic"
/*
string data
*/

#define NODE_NAME "ros2_bridge_support_topic_sender"
#define QUEUE_SZ_DEFAULT 100

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLOG( msg_stream ) RCLCPP_INFO_STREAM( this->get_logger( ), msg_stream )
#define OUTERR( msg_err_stream ) RCLCPP_ERROR_STREAM( this->get_logger( ), "ERROR: " << msg_err_stream )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )

#define BRIDGE_MSG( topic ) OUTLOG( "bridge topic: " << LOGSQUARE( topic ) << " (ROS2) --> (ROS1)" << LOGSQUARE( get_name_of_topic( topic ) ) )

class ros2_bridge_topic_sender : public rclcpp::Node
{
public:
	ros2_bridge_topic_sender( ) :
		rclcpp::Node( NODE_NAME )
	{
		// bridge for the custom topic
		BRIDGE_MSG( SUB_CUSTOM );
		make_bridge_custom_topic( );
		
		OUTLOG( "online!" );
	}

private:
	// --- GENERAL PURPOSE METHODS ---
	
	// generate the name of the topic on the bridge
	std::string get_name_of_topic( std::string topic_name )
		{ return SS(BRIDGE_TOPIC_NAME_PREFIX) + topic_name; }
	
	// --- CUSTOM TOPIC ---
	
	// input handler for custom topic
	rclcpp::Subscription<ros2_bridge_support_pkg::msg::MyCustomMessage>::SharedPtr sub_custom_topic;
	
	// bridge handler to custom topic
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr bridge_custom_topic;
	
	// cast the message 'MyCustomMessage' to string
	// per il const alla fine della funzione vedi
	// https://stackoverflow.com/questions/26963510/error-passing-const-as-this-argument-of-discards-qualifiers
	std::string cast_my_custom_message( 
		ros2_bridge_support_pkg::msg::MyCustomMessage::SharedPtr msg ) const
	{
		std::string str = "";
		
		str += ( msg->value_boolean ? "1" : "0" );
		str += " ";
		str += std::to_string( msg->value_integer );
		str += " ";
		str += std::to_string( msg->value_float );
		str += " ";
		str += msg->value_string;
		
		return str;
	}		
	
	// subscriber callback for custom topic
	void bridge_custom_topic_cbk( 
		const ros2_bridge_support_pkg::msg::MyCustomMessage::SharedPtr msg ) const
	{
		// cast the message to string
		std_msgs::msg::String bridge_data;
		bridge_data.data = cast_my_custom_message( msg );
		
		// publish the message
		bridge_custom_topic->publish( bridge_data );
	}
	
	// make the link
	void make_bridge_custom_topic( )
	{
		// subscription
		sub_custom_topic = this->create_subscription<ros2_bridge_support_pkg::msg::MyCustomMessage>(
			SUB_CUSTOM,
			QUEUE_SZ_DEFAULT,
			std::bind( &ros2_bridge_topic_sender::bridge_custom_topic_cbk, this, _1 )
		);
		
		// publisher
		bridge_custom_topic = this->create_publisher<std_msgs::msg::String>(
			get_name_of_topic( SUB_CUSTOM ), 
			QUEUE_SZ_DEFAULT 
		);
	}
};

int main( int argc, char* argv[] )
{
	rclcpp::init( argc, argv );
	
	rclcpp::spin( std::make_shared<ros2_bridge_topic_sender>( ) );
	
	rclcpp::shutdown( );
	return 0;
}
