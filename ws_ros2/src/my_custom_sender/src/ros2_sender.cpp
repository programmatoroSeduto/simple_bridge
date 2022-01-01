
#include "rclcpp/rclcpp.hpp"
#include <memory>
#include <chrono>
using namespace std::chrono_literals;

#include "ros2_bridge_support_pkg/msg/my_custom_message.hpp"
#define PUB_CUSTOM "/custom_topic"
/*
bool value_boolean
int32 value_integer
float value_float
string value_string
*/

#define NODE_NAME "ros2_sender"
#define QUEUE_SZ_DEFAULT 100
#define PUB_RATE 500ms

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLOG( msg_stream ) RCLCPP_INFO_STREAM( this->get_logger( ), msg_stream )
#define OUTERR( msg_err_stream ) RCLCPP_ERROR_STREAM( this->get_logger( ), "ERROR: " << msg_err_stream )

class ros2_sender : public rclcpp::Node
{
public:
	ros2_sender( ) :
		rclcpp::Node( NODE_NAME )
	{
		// publisher
		pub = this->create_publisher<ros2_bridge_support_pkg::msg::MyCustomMessage>(
			PUB_CUSTOM,
			QUEUE_SZ_DEFAULT
		);
		tm = this->create_wall_timer( PUB_RATE, 
			std::bind( &ros2_sender::pubtimed_sender, this ) );
		
		OUTLOG( "online!" );
	}
	
private:
	// timed publisher su custom topic
	void pubtimed_sender( void )
	{
		// invia il messaggio con campi "a caso"
		ros2_bridge_support_pkg::msg::MyCustomMessage msg;
		msg.value_boolean = false;
		msg.value_integer = 25;
		msg.value_float = 25.33;
		msg.value_string = "the best the best the best the best";

		OUTLOG( "send!" );
		pub->publish( msg );
	}
	
	// handle publisher
	rclcpp::Publisher<ros2_bridge_support_pkg::msg::MyCustomMessage>::SharedPtr pub;
	
	// handle wall_timer
	rclcpp::TimerBase::SharedPtr tm;
};

int main( int argc, char* argv[] )
{
	rclcpp::init( argc, argv );
	
	rclcpp::spin( std::make_shared<ros2_sender>( ) );
	
	rclcpp::shutdown( );
	return 0;
}
