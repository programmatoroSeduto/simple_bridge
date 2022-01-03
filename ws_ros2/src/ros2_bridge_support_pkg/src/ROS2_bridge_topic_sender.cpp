
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

namespace str_tools
{
	/// @brief split a string using a separator 
	///    @return this function returns an empty vector if the string is not well-formed
	std::vector<std::string> pack_split( std::string str, char separator )
	{
		std::vector<std::string> res;
		std::string q = "";
		bool force_no_sep = false;
		
		for( unsigned int i=0; i<str.length(); ++i )
		{
			if( force_no_sep )
			{
				if( (str[i] == '/') && ((i+1) < str.length()) && (str[i+1] == '}') )
				{
					// string field is over
					force_no_sep = false;
					i += 1;
				}
				else
					q += str[i];
			}
			else if( str[i] == separator )
			{
				// save the previous token
				if( q != "" ) res.push_back( q );
				q = "";
				
				if( 
					((i + 2) < str.length()) &&
					str[i+1] == '/' &&
					str[i+2] == '{'
					)
				{
					// reading a string field
					force_no_sep = true;
					
					// skip the group " /{"
					i += 2; 
				}
			}
			else
				q += str[i];
		}
		
		if( !force_no_sep )
		{
			if( q != "" ) res.push_back( q );
			return res;
		}
		else  // bad format
			return std::vector<std::string>( );
	}
	
	// generate the name of the topic on the bridge
	std::string get_name_of_topic( std::string topic_name )
	{
		return SS(BRIDGE_TOPIC_NAME_PREFIX) + topic_name; 
	}
}

namespace cast_tools
{
	// cast back a boolean
	bool cast_back_field( std::string pack )
	{
		return ( pack == "1" ? true : false );
	}
	
	// get a string type
	std::string cast_field( std::string pack, bool use_sep = false, std::string sep = " " )
	{
		std::string str = "/{" + pack + "/}";
		
		if( use_sep ) str += sep;
		return str;
	}
	
	// bool type to string
	std::string cast_field( bool pack, bool use_sep = false, std::string sep = " " )
	{
		std::string str = ( pack ? "1" : "0" );
		
		if( use_sep ) str += sep;
		return str;
	}
	
	// cast the message 'MyCustomMessage' to string
	std::string cast_message( const ros2_bridge_support_pkg::msg::MyCustomMessage::SharedPtr msg )
	{
		std::string str = "";
		
		str += cast_tools::cast_field( msg->value_boolean );
		str += SSS( msg->value_integer ) + " ";
		str += SSS( msg->value_float ) + " ";
		str += cast_tools::cast_field( msg->value_string, false );
		
		return str;
	}
	
	// cast back the message 'MyCustomMessage'
	// ... ( string to message )
}

template< typename topicT >
class bridge_topic
{
public:
	bridge_topic( ) { }

	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub;
	typename rclcpp::Subscription< topicT >::SharedPtr sub;
	
	// "OUT BRIDGE" : from ROS2 to ROS1 (cast)
	void bridge_cbk( const typename topicT::SharedPtr msg ) const
	{
		// cast the message to string
		std_msgs::msg::String bridge_data;
		bridge_data.data = cast_tools::cast_message( msg );
		
		// publish the message
		this->pub->publish( bridge_data );
	}
	
	// "IN BRIDGE" : from ROS1 to ROS2 (cast back)
	// ... (use methods override)
};

class ros2_bridge_topic_sender : public rclcpp::Node
{
public:
	ros2_bridge_topic_sender( ) :
		rclcpp::Node( NODE_NAME )
	{
		// out bridge for the custom topic
		BRIDGE_MSG_ROS2_ROS1( SUB_CUSTOM );
		make_link_topic_out<ros2_bridge_support_pkg::msg::MyCustomMessage>(
			&topic_my_custom_message, SUB_CUSTOM );
		
		OUTLOG( "online!" );
	}

private:
	// --- GENERAL PURPOSE METHODS ---
	
	// generate the name of the topic on the bridge
	std::string get_name_of_topic( std::string topic_name )
		{ return SS(BRIDGE_TOPIC_NAME_PREFIX) + topic_name; }
	
	// make the output link
	template< typename Ttopic >
	void make_link_topic_out( bridge_topic< Ttopic >* br_class, std::string sub_topic )
	{
		// publisher
		OUTLOG( "publisher on " << get_name_of_topic( sub_topic ) );
		br_class->pub = this->create_publisher< std_msgs::msg::String >(
			get_name_of_topic( sub_topic ), 
			QUEUE_SZ_DEFAULT 
		);
		
		// subscription
		//    https://answers.ros.org/question/308386/ros2-add-arguments-to-callback/
		OUTLOG( "subscription to " << sub_topic );
		br_class->sub = this->create_subscription< Ttopic >(
			sub_topic,
			QUEUE_SZ_DEFAULT,
			std::bind( &bridge_topic< Ttopic >::bridge_cbk, br_class, _1 )
		);
	}
	
	// --- CUSTOM TOPIC ---
	
	// topic class container
	bridge_topic<ros2_bridge_support_pkg::msg::MyCustomMessage> topic_my_custom_message;
};

int main( int argc, char* argv[] )
{
	rclcpp::init( argc, argv );
	
	rclcpp::spin( std::make_shared<ros2_bridge_topic_sender>( ) );
	
	rclcpp::shutdown( );
	return 0;
}
