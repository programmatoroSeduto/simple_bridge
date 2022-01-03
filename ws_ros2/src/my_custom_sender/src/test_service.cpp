
#include "rclcpp/rclcpp.hpp"

#include <string>
#include <memory>
#include <functional>
using std::placeholders::_1;
using std::placeholders::_2;

#include "ros2_bridge_support_pkg/srv/my_custom_service.hpp"
/*
int32 index
string mystery_word
---
bool guessed
*/

#define NODE_NAME "test_service"
#define SERVICE_CUSTOM "/my_custom_service"

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLOG( msg_stream ) RCLCPP_INFO_STREAM( rclcpp::get_logger( NODE_NAME ), msg_stream )
#define OUTERR( msg_err_stream ) RCLCPP_ERROR_STREAM( rclcpp::get_logger( NODE_NAME ), "ERROR: " << msg_err_stream )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )

class test_service : public rclcpp::Node
{
public:
	test_service( ) : rclcpp::Node( NODE_NAME )
	{
		serv = this->create_service<ros2_bridge_support_pkg::srv::MyCustomService>(
			SERVICE_CUSTOM,
			std::bind( &test_service::service_callback, this, _1, _2 )
		);
	}

private:
	// callback of the service
	void service_callback(
		const std::shared_ptr<ros2_bridge_support_pkg::srv::MyCustomService::Request> req,
		std::shared_ptr<ros2_bridge_support_pkg::srv::MyCustomService::Response> res
	)
	{
		OUTLOG( "replying to a request" );
		std::string str = req->mystery_word + SSS(req->index);
		OUTLOG( "you said... " << str );
		res->guessed = ( str == solution );
		OUTLOG( "replying... " );
	}
	
	// service handle
	rclcpp::Service<ros2_bridge_support_pkg::srv::MyCustomService>::SharedPtr serv;
	
	// the solution
	std::string solution = "ciao500";
};

int main( int argc, char* argv[ ] )
{
	rclcpp::init( argc, argv );
	
	rclcpp::spin( std::make_shared<test_service>( ) );
	
	rclcpp::shutdown( );
	return 0;
}
