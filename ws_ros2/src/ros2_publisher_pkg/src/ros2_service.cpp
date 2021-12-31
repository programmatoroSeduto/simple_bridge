#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"
#include <string>
#include <memory>
#include <chrono>
#include <functional>
using std::placeholders::_1;
using std::placeholders::_2;
using namespace std::chrono_literals;

#define NODE_NAME "ros2_publisher"
#define SERVICE_BOOL "/bridge_simple_test/service_bool"

#define OUTLOG( msg_stream ) RCLCPP_INFO_STREAM( this->get_logger( ), msg_stream )



class ros2_service_class : public rclcpp::Node
{
public:
	ros2_service_class( ) :
		rclcpp::Node( NODE_NAME )
	{
		serv_ = this->create_service<std_srvs::srv::SetBool>(
			SERVICE_BOOL,
			std::bind( &ros2_service_class::service_cbk, this, _1, _2 ) );
	}
	
private:
	// service callback
	void service_cbk( 
		const std::shared_ptr<std_srvs::srv::SetBool::Request> req,
		std::shared_ptr<std_srvs::srv::SetBool::Response> res )
	{
		OUTLOG( "received: '" << ( req->data ? "true" : "false" ) << "'" );
		
		res->success = true;
		res->message = "";
	}
	
	// service handle
	rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr serv_;
};



int main( int argc, char* argv[ ] )
{
	rclcpp::init( argc, argv );
	
	RCLCPP_INFO_STREAM( rclcpp::get_logger( NODE_NAME ), "Online!" );
	rclcpp::spin( std::make_shared<ros2_service_class>( ) );
	
	rclcpp::shutdown( );
	return 0;
}
