#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <string>
#include <memory>
#include <chrono>
using namespace std::chrono_literals;

#define NODE_NAME "ros2_publisher"
#define PUB_TOPIC_STRING "/bridge_simple_test/topic_string"

#define OUTLOG( msg_stream ) RCLCPP_INFO_STREAM( this->get_logger( ), msg_stream )



class ros2_publisher_class : public rclcpp::Node
{
public:
	ros2_publisher_class( ):
		rclcpp::Node( NODE_NAME )
	{
		pub_ = this->create_publisher<std_msgs::msg::String>( PUB_TOPIC_STRING, 100 );
		tm_  = this->create_wall_timer( 2s, std::bind( &ros2_publisher_class::timed_publisher_cbk, this ) );
	}
	
private:
	// timed callback
	void timed_publisher_cbk( void )
	{
		std_msgs::msg::String s;
		s.data = "hello! ciao! guthenthag!";
		++ c;
		OUTLOG( "sending message no." << c << " with content '" << s.data << "' ..." );
		
		pub_->publish( s );
	}
	
	// timer-base handle
	rclcpp::TimerBase::SharedPtr tm_;
	
	// publisher handle
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	
	// counter
	int c = 0;
};



int main( int argc, char* argv[ ] )
{
	rclcpp::init( argc, argv );
	
	RCLCPP_INFO_STREAM( rclcpp::get_logger( NODE_NAME ), "Online!" );
	rclcpp::spin( std::make_shared<ros2_publisher_class>( ) );
	
	rclcpp::shutdown( );
	return 0;
}
