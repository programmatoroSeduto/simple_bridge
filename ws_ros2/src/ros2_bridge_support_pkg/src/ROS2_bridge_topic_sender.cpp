
// clear && ./build.sh && source ./devel/setup.bash

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
#define OUTLOG( msg_stream ) RCLCPP_INFO_STREAM( rclcpp::get_logger( NODE_NAME ), msg_stream )
#define OUTERR( msg_err_stream ) RCLCPP_ERROR_STREAM( rclcpp::get_logger( NODE_NAME ), "ERROR: " << msg_err_stream )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )

#define BRIDGE_MSG_ROS2_ROS1( topic ) OUTLOG( "bridge topic: " << LOGSQUARE( topic ) << " (ROS2) --> (ROS1)" << LOGSQUARE( BRIDGE_TOPIC_NAME_PREFIX << topic ) )

namespace cast_tools
{
	// get a string type
	std::string field_to_str( std::string pack, bool use_sep = false, std::string sep = " " )
	{
		std::string str = "/{" + pack + "/}";
		
		if( use_sep ) str += sep;
		return str;
	}
	
	// bool type to string
	std::string field_to_str( bool pack, bool use_sep = false, std::string sep = " " )
	{
		std::string str = ( pack ? "1" : "0" );
		
		if( use_sep ) str += sep;
		return str;
	}
	
	// cast the message 'MyCustomMessage' to string
	std::string cast_message( const ros2_bridge_support_pkg::msg::MyCustomMessage::SharedPtr msg )
	{
		std::string str = "";
		
		str += cast_tools::field_to_str( msg->value_boolean );
		str += SSS( msg->value_integer ) + " ";
		str += SSS( msg->value_float ) + " ";
		str += cast_tools::field_to_str( msg->value_string, false );
		
		return str;
	}
}

template< typename topicT >
class bridge_topic_container
{
public:
	typename rclcpp::Subscription< topicT >::SharedPtr sub;
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub;
	
	void bridge_cbk( const typename topicT::SharedPtr msg ) const
	{
		// cast the message to string
		std_msgs::msg::String bridge_data;
		bridge_data.data = cast_tools::cast_message( msg );
		
		// publish the message
		this->pub->publish( bridge_data );
	}
};

class ros2_bridge_topic_sender : public rclcpp::Node
{
public:
	ros2_bridge_topic_sender( ) :
		rclcpp::Node( NODE_NAME )
	{
		// bridge for the custom topic
		BRIDGE_MSG_ROS2_ROS1( SUB_CUSTOM );
		make_bridge_ros2_to_ros1<ros2_bridge_support_pkg::msg::MyCustomMessage>( SUB_CUSTOM, &topic_my_custom_message );
		
		OUTLOG( "online!" );
	}

private:
	// --- GENERAL PURPOSE METHODS ---
	
	// generate the name of the topic on the bridge
	std::string get_name_of_topic( std::string topic_name )
		{ return SS(BRIDGE_TOPIC_NAME_PREFIX) + topic_name; }
	
	// subscriber callback
	template< typename msgT >
	void bridge_cbk( const typename msgT::SharedPtr msg, bridge_topic_container<msgT>& topic ) const
	{
		// cast the message to string
		std_msgs::msg::String bridge_data;
		bridge_data.data = cast_tools::cast_message( msg );
		
		// publish the message
		topic.pub->publish( bridge_data );
	}
	
	// make the link
	template<typename msgT>
	void make_bridge_ros2_to_ros1( std::string topic_name, bridge_topic_container<msgT>* rt )
	{
		// publisher
		rt->pub = this->create_publisher<std_msgs::msg::String>(
			get_name_of_topic( topic_name ), 
			QUEUE_SZ_DEFAULT 
		);
		
		// subscription
		//    https://answers.ros.org/question/308386/ros2-add-arguments-to-callback/
		// std::function<void(const typename msgT::SharedPtr msg)> fcn = std::bind( &ros2_bridge_topic_sender::bridge_cbk, this, _1, rt );
		rt->sub = this->create_subscription<ros2_bridge_support_pkg::msg::MyCustomMessage>(
			topic_name,
			QUEUE_SZ_DEFAULT,
			std::bind( &bridge_topic_container<msgT>::bridge_cbk, rt, _1 )
		);
	}
	
	// --- CUSTOM TOPIC ---
	
	// topic class container
	bridge_topic_container<ros2_bridge_support_pkg::msg::MyCustomMessage> topic_my_custom_message;
	

};

int main( int argc, char* argv[] )
{
	rclcpp::init( argc, argv );
	
	rclcpp::spin( std::make_shared<ros2_bridge_topic_sender>( ) );
	
	rclcpp::shutdown( );
	return 0;
}
