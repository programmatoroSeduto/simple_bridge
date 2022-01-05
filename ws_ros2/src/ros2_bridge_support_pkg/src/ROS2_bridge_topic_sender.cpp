// clear && ./build.sh && source ./install/setup.sh
// ros2 run ros2_bridge_support_pkg ROS2_bridge_topic_sender



#include "rclcpp/rclcpp.hpp"
#include <string>
#include <memory>
using std::placeholders::_1;
using std::placeholders::_2;

#include "ros2_bridge_support_pkg/msg/my_custom_message.hpp"
// to ROS1
//    SUB : leggo il messaggio dal nodo che ha bisogno di trasmettere a ROS1
//    OUT : il nodo che usa il topic trasmette al bridge il messaggio
#define SUB_CUSTOM_OUT "/custom_topic_a"
// from ROS1
//    PUB : devo pubblicare ciò che mi arriva dal bridge al nodo che usa questo topic
//    IN : il nodo vede questo topic come ingresso
#define PUB_CUSTOM_IN "/custom_topic_b"
/*
bool value_boolean
int32 value_integer
float value_float
string value_string
*/
#include "std_msgs/msg/string.hpp"
/*
string data
*/
#include "ros2_bridge_support_pkg/srv/my_custom_service.hpp"
#define CLIENT_CUSTOM "/my_custom_service"
#define SERVICE_CUSTOM_OUT "/my_custom_service_second"
/*
int32 index
string mystery_word
---
bool guessed
*/

#define NODE_NAME "ros2_bridge_support_topic_sender"
#define BRIDGE_TOPIC_NAME_PREFIX "/bridge_topic"
#define BRIDGE_SERVICE_NAME_PREFIX "/bridge_service"
#define QUEUE_SZ_DEFAULT 100
#define WAITING_DELAY 0.01

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLOG( msg_stream ) RCLCPP_INFO_STREAM( rclcpp::get_logger( NODE_NAME ), msg_stream )
#define OUTERR( msg_err_stream ) RCLCPP_ERROR_STREAM( rclcpp::get_logger( NODE_NAME ), "ERROR: " << msg_err_stream )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )

#define BRIDGE_MSG_ROS2_ROS1( topic ) OUTLOG( "bridge topic: " << LOGSQUARE( topic ) << " (ROS2) --> (ROS1)" << LOGSQUARE( BRIDGE_TOPIC_NAME_PREFIX << topic ) )

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr interface;

namespace str_tools
{
	bool check_seq_at( std::string str_arg, std::string to_find, int i, bool check_end = false )
    {
        if( ((std::size_t)i) >= str_arg.length( ) ) return false;
        
        std::size_t next_idx = i + to_find.length( );
        std::string sub = str_arg.substr( i, to_find.length( ) );
        bool found = ( to_find == sub );
        
        if( check_end )
            return found && ( next_idx >= str_arg.length( ) );
        else
            return found;
    }
    
    // split a string using a separator 
    //    this function returns an empty vector if the string is not well-formed
    std::vector<std::string> pack_split( std::string str, char separator )
    {
    	std::vector<std::string> res;
    	std::string q = "";
    	bool force_no_sep = false;
    	
    	for( unsigned int i=0; i<str.length(); ++i )
    	{
    	    if( force_no_sep )
    	    {
    	        if( str_tools::check_seq_at( str, "/} ", i) || str_tools::check_seq_at( str, "/}", i, true) )
                {
                    // END OF A NON-EMPTY string
                    force_no_sep = false;
                    res.push_back( q );
                    q = "";
                    
                    ++i;
                }
                else
                    // continue reading
                    q += str[i];
    	        
    	    }
    		else if( str[i] == separator )
    		{
    		    // save the previous token
    			if( q != "" ) 
    			{
    			    res.push_back( q );
    			    q = "";
    			}
    		}
    		else if( str[i] == '/' )
            {
                if( str_tools::check_seq_at( str, "/{", i ) )
                {
                    if( str_tools::check_seq_at( str, "/{//} ", i) || str_tools::check_seq_at( str, "/{//}", i, true) )
                    {
                        // EMPTY STRING DETECTED
                        // insert a blank into the vector
                        res.push_back( "" );
                        
                        // jump to the next char (taking into accout the for loop)
                        i += 5;
                    }
                    else
                    {
                        // NON-EMPTY STRING DETECTED
                        // skip the group "/{" (taking into accout the for loop)
                        ++i;
                        
                        // enter in no-sep mode
                        force_no_sep = true;
                    }
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
	
	// generate the name of the topic for the service request
	std::string get_name_of_service_request( std::string serv_name )
	{
		return SS(BRIDGE_SERVICE_NAME_PREFIX) + serv_name + "_request";
	}
	
	// generate the name of the topic for the service response
	std::string get_name_of_service_response( std::string serv_name )
	{
		return SS(BRIDGE_SERVICE_NAME_PREFIX) + serv_name + "_response";
	}
}

namespace cast_tools
{
	// cast back a boolean
	bool cast_back_field( std::string pack )
	{
		return ( pack == "1" ? true : false );
	}
	
	/// @brief get a string type 
	/// @note the empty string generates a sequence /{//} which indicates a empty field
	std::string cast_field( std::string pack, bool use_sep = false, std::string sep = " " )
	{
		// generate the empty sequence if the string is empty
		pack = ( pack != "" ? pack : "/" );
		
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
	std::string cast_message( 
		const ros2_bridge_support_pkg::msg::MyCustomMessage::SharedPtr msg )
	{
		std::string str = "";
		
		str += cast_tools::cast_field( msg->value_boolean );
		str += SSS( msg->value_integer ) + " ";
		str += SSS( msg->value_float ) + " ";
		str += cast_tools::cast_field( msg->value_string, false );
		
		return str;
	}
	
	// cast back the message 'MyCustomMessage'
	ros2_bridge_support_pkg::msg::MyCustomMessage cast_back_message( 
		const std_msgs::msg::String::SharedPtr msg )
	{
		// split the message
		std::vector< std::string > content = str_tools::pack_split( msg->data, ' ' );
		
		// cast field by field
		ros2_bridge_support_pkg::msg::MyCustomMessage rmsg;
		rmsg.value_boolean = cast_tools::cast_back_field( content[0] );
		rmsg.value_integer = atoi( content[1].c_str( ) );
		rmsg.value_float = atof( content[2].c_str( ) );
		rmsg.value_string = content[3];
		
		return rmsg;
	}
	
	// cast the service request 'MyCustomService'
	// std::string cast_service_request( ros1_bridge_support_pkg::MyCustomService::Request &req )
	std::string cast_service_request( 
		const std::shared_ptr<ros2_bridge_support_pkg::srv::MyCustomService::Request> req )
	{
		std::string str = "";
		
		str += SSS( req->index ) + " ";
		str += cast_tools::cast_field( req->mystery_word, false );
		
		return str;
	}
	
	// cast back the service request of 'MyCustomService'
	//    Usa il dereference per scrivere nella risposta, vedi 
	//    https://www.cplusplus.com/reference/memory/shared_ptr/operator*/
	// chiama prima la make_shared, poi dereference e uguaglianza col ritorno della funzione
	ros2_bridge_support_pkg::srv::MyCustomService::Request cast_back_service_request(
		std::string &msg )
	{
		std::vector< std::string > content = str_tools::pack_split( msg, ' ' );
		
		ros2_bridge_support_pkg::srv::MyCustomService::Request req;
		req.index = atoi( content[0].c_str( ) );
		req.mystery_word = content[1];
		
		return req;
	}
	
	// cast the service response of 'MyCustomService'
	std::string cast_service_response( 
		const std::shared_ptr<ros2_bridge_support_pkg::srv::MyCustomService::Response> res )
	{
		return cast_tools::cast_field( res->guessed, false );
	}
	
	// cast back the service response 'MyCustomService'
	//    Usa il dereference per scrivere nella risposta, vedi 
	//    https://www.cplusplus.com/reference/memory/shared_ptr/operator*/
	ros2_bridge_support_pkg::srv::MyCustomService::Response cast_back_service_response( 
		std::string &msg )
	{
		std::vector< std::string > content = str_tools::pack_split( msg, ' ' );
		
		ros2_bridge_support_pkg::srv::MyCustomService::Response res;
		res.guessed = cast_back_field( content[0] );
		
		return res;
	}
}

/// representation of a topic in ROS2
template< typename topicT_pub, typename topicT_sub >
class bridge_topic
{
public:
	bridge_topic( ) { }

	typename rclcpp::Publisher< topicT_pub >::SharedPtr pub;
	typename rclcpp::Subscription< topicT_sub >::SharedPtr sub;
	
	// "OUT BRIDGE" : from ROS2 to ROS1 (cast)
	void bridge_cbk_out( const typename topicT_sub::SharedPtr msg ) const
	{
		// cast the message to string
		std_msgs::msg::String bridge_data;
		bridge_data.data = cast_tools::cast_message( msg );
		
		// publish the message
		this->pub->publish( bridge_data );
	}
	
	// "IN BRIDGE" : from ROS1 to ROS2 (cast back)
	void bridge_cbk_in( const std_msgs::msg::String::SharedPtr msg ) const
	{
		// cast back the message from string to message
		topicT_pub bridge_data = cast_tools::cast_back_message( msg );
		
		// publish the message
		this->pub->publish( bridge_data );
	}
};

/// representation of a service in ROS2 
template< typename serviceT >
class bridge_service
{
public:
	bridge_service( ) { }
	
	// first topic from ROS1
	rclcpp::Subscription< std_msgs::msg::String >::SharedPtr topic_in;
	// second topic to ROS1
	rclcpp::Publisher< std_msgs::msg::String >::SharedPtr topic_out;
	// call to endpoint ROS2
	typename rclcpp::Service< serviceT >::SharedPtr service_out;
	// callback from endpoint ROS2
	typename rclcpp::Client< serviceT >::SharedPtr service_in;
	
	// callback group for the subscriber
	rclcpp::callback_group::CallbackGroup::SharedPtr callback_group;
	// subscription options
	rclcpp::SubscriptionOptions subscription_options;
	
	/// @brief callback for the 'out' service from ROS2 endpoint to ROS1 endpoint
	/// @note 'out' means that the client runs in ROS2
	void service_out_callback(
		const std::shared_ptr< typename serviceT::Request > req,
		std::shared_ptr< typename serviceT::Response > res )
	{
		OUTLOG( "received a ROS2->ROS1 service request from ROS2" );
		
		// set the pending request and reset the response
		this->pending_request = *req;
		this->response_string = "";
		
		// cast the request to string
		std_msgs::msg::String req_str;
		req_str.data = cast_tools::cast_service_request( req );
		
		// send the request to ROS1 through topic_out 
		this->topic_out->publish( req_str );
		waiting_response = true;
		
		OUTLOG( "waiting a response from ROS1..." );
		// per le attese, vedi
		//    https://github.com/ros2/tutorials/blob/master/rclcpp_tutorials/src/topics/talker.cpp
		// (potrebbe non funzionare...)
		rclcpp::WallRate loop_rate(500);
		while( waiting_response )
		{
			loop_rate.sleep( );
		}
		OUTLOG( "got a response from ROS1 -> [" << response_string << "]" );
		
		// cast back the message and write it
		*res = cast_tools::cast_back_service_response( response_string );
	}
	
	/// subscriber which calls the endpoint
	/// @note 'in' i.e. the client runs in ROS1
	void service_in_callback(
		const std_msgs::msg::String::SharedPtr msg ) const
	{
		OUTLOG( "received a ROS1->ROS2 request from ROS1 endpoint" ); 
		OUTLOG( "with data: [" << msg->data << "]" );
		
		// cast back of the request
		auto req = std::make_shared<ros2_bridge_support_pkg::srv::MyCustomService::Request>( );
		*req = cast_tools::cast_back_service_request( msg-> data );
		
		// call the endpoint and get the result
		OUTLOG( "waiting for a response from the service..." );
		auto res_future = (service_in->async_send_request( req ));
		// synchronous request
		res_future.wait( );
		auto res = res_future.get( );
		
		// cast the response from the endpoint
		std_msgs::msg::String res_str;
		res_str.data = cast_tools::cast_service_response( res );
		
		// publish the response
		OUTLOG( "returning response: [" << res_str.data << "]" );
		this->topic_out->publish( res_str );
	}
	
	/// callback service subscriber
	void topic_in_callback(
		const std_msgs::msg::String::SharedPtr msg ) //const
	{
		if( waiting_response )
		{
			// store the message into the class variable
			this->response_string = msg->data;
			this->waiting_response = false;
		}
	}

private:
	// pending request
	typename serviceT::Request pending_request;
	// waiting for a response from ROS2
	bool waiting_response = false;
	// the response as string
	std::string response_string = "";
};

class ros2_bridge_topic_sender : public rclcpp::Node
{
public:
	ros2_bridge_topic_sender( ) : rclcpp::Node( NODE_NAME )  // using static mapping
	{
		interface = this->get_node_base_interface( );
		
		// 'in' topic as 'sub' from bridge and 'pub' to the end node
		OUTLOG( "TOPIC --- from ROS1: " << PUB_CUSTOM_IN );
		make_link_topic_in<ros2_bridge_support_pkg::msg::MyCustomMessage>(
			&my_custom_topic_in,
			PUB_CUSTOM_IN
		);
		
		// 'out' topic as 'pub' to bridge and 'sub' from the end node
		OUTLOG( "TOPIC --- to ROS1: " << PUB_CUSTOM_IN );
		make_link_topic_out<ros2_bridge_support_pkg::msg::MyCustomMessage>(
			&my_custom_topic_out,
			SUB_CUSTOM_OUT
		);
		
		// 'in' the client runs in ROS1
		OUTLOG( "SERVICE --- ROS2 service ROS1 client: " << CLIENT_CUSTOM );
		make_link_service_in<ros2_bridge_support_pkg::srv::MyCustomService>(
			&my_custom_service_in,
			CLIENT_CUSTOM
		);
		
		// 'out' the client runs in ROS2
		OUTLOG( "SERVICE --- ROS1 service ROS2 client: " << SERVICE_CUSTOM_OUT );
		make_link_service_out<ros2_bridge_support_pkg::srv::MyCustomService>(
			&my_custom_service_out,
			SERVICE_CUSTOM_OUT
		);
		
		OUTLOG( "online!" );
	}

private:
	// --- MAKE_LINK_TOPIC METHODS ---
	
	/// create a "bridge out" topic
	/// @note 'out' topic as 'sub' from the end node and 'pub' to bridge
	template< typename Ttopic >
	void make_link_topic_out( bridge_topic< std_msgs::msg::String, Ttopic >* br_class, std::string sub_topic )
	{
		// subscription
		//    https://answers.ros.org/question/308386/ros2-add-arguments-to-callback/
		OUTLOG( "subscription to " << sub_topic );
		br_class->sub = this->create_subscription< Ttopic >(
			sub_topic,
			QUEUE_SZ_DEFAULT,
			std::bind( &bridge_topic< std_msgs::msg::String, Ttopic >::bridge_cbk_out, br_class, _1 )
		);
		
		// publisher
		OUTLOG( "publisher on " << str_tools::get_name_of_topic( sub_topic ) );
		br_class->pub = this->create_publisher< std_msgs::msg::String >(
			str_tools::get_name_of_topic( sub_topic ), 
			QUEUE_SZ_DEFAULT 
		);
	}
	
	/// create a "bridge in" topic
	/// @note 'in' topic as 'sub' from bridge and 'pub' to the end node
	template< typename Ttopic >
	void make_link_topic_in( bridge_topic< Ttopic, std_msgs::msg::String >* br_class, std::string pub_topic )
	{
		// subscription
		//    https://answers.ros.org/question/308386/ros2-add-arguments-to-callback/
		OUTLOG( "subscription to " << str_tools::get_name_of_topic( pub_topic ) );
		br_class->sub = this->create_subscription< std_msgs::msg::String >(
			str_tools::get_name_of_topic( pub_topic ),
			QUEUE_SZ_DEFAULT,
			std::bind( &bridge_topic< Ttopic, std_msgs::msg::String >::bridge_cbk_in, br_class, _1 )
		);
		
		// publisher
		OUTLOG( "publisher on " << pub_topic );
		br_class->pub = this->create_publisher< Ttopic >(
			pub_topic,
			QUEUE_SZ_DEFAULT 
		);
	}
	
	/// create a "bridge in" service
	template< typename serviceT >
	void make_link_service_in( bridge_service< serviceT >* br_class, std::string service_name )
	{
		// new callback group
		// vedi 
		//    https://get-help.robotigniteacademy.com/t/how-to-link-callback-function-to-a-subscription/11043/3
		br_class->callback_group = this->create_callback_group(rclcpp::callback_group::CallbackGroupType::Reentrant);
		br_class->subscription_options.callback_group = br_class->callback_group;
		
		// in subscriber -- request
		// vedi anche
		//    https://docs.ros.org/en/foxy/Tutorials/Topics/Topic-Statistics-Tutorial.html
		OUTLOG( "subscription to " << str_tools::get_name_of_service_response( service_name ) );
		br_class->topic_in = this->create_subscription< std_msgs::msg::String >(
			str_tools::get_name_of_service_request( service_name ),
			10,  // THE NEW MAGIC NUMBER! (what does it mean '10'? Why especially '10'? Has it a name?)
			std::bind( &bridge_service< serviceT >::service_in_callback, br_class, _1 ),
			br_class->subscription_options
		);
		
		// out publisher -- response
		OUTLOG( "publisher on " << str_tools::get_name_of_service_request( service_name ) );
		br_class->topic_out = this->create_publisher< std_msgs::msg::String >(
			str_tools::get_name_of_service_response( service_name ),
			QUEUE_SZ_DEFAULT
		);
		
		// out service to endpoint
		OUTLOG( "creating 'in' service " << service_name );
		br_class->service_in = this->create_client< serviceT >( service_name );
	}
	
	/// create a "bridge out" service
	/// @todo maybe the label "out" is conceptually wrong...
	template< typename serviceT >
	void make_link_service_out( bridge_service< serviceT >* br_class, std::string service_name )
	{
		// new callback group
		br_class->callback_group = this->create_callback_group(rclcpp::callback_group::CallbackGroupType::Reentrant);
		br_class->subscription_options.callback_group = br_class->callback_group;
		
		// in subscriber -- response
		OUTLOG( "subscription to " << str_tools::get_name_of_service_response( service_name ) );
		br_class->topic_in = this->create_subscription< std_msgs::msg::String >(
			str_tools::get_name_of_service_response( service_name ),
			10,  
			std::bind( &bridge_service< serviceT >::topic_in_callback, br_class, _1 ),
			br_class->subscription_options
		);
		
		// out publisher -- request
		OUTLOG( "publisher on " << str_tools::get_name_of_service_request( service_name ) );
		br_class->topic_out = this->create_publisher< std_msgs::msg::String >(
			str_tools::get_name_of_service_request( service_name ),
			QUEUE_SZ_DEFAULT
		);
		
		// out service from endpoint
		OUTLOG( "creating 'out' service " << service_name );
		br_class->service_out = this->create_service< serviceT >(
			service_name,
			std::bind( &bridge_service< serviceT >::service_out_callback, br_class, _1, _2 )
		);
	}
	
	// --- CUSTOM TOPICs AND SERVICEs ---
	
	// topic class container
	bridge_topic<ros2_bridge_support_pkg::msg::MyCustomMessage, std_msgs::msg::String> my_custom_topic_in;
	bridge_topic<std_msgs::msg::String, ros2_bridge_support_pkg::msg::MyCustomMessage> my_custom_topic_out;
	
	bridge_service<ros2_bridge_support_pkg::srv::MyCustomService> my_custom_service_in;
	bridge_service<ros2_bridge_support_pkg::srv::MyCustomService> my_custom_service_out;
};

int main( int argc, char* argv[] )
{
	rclcpp::init( argc, argv );
	
	// rclcpp::spin( std::make_shared<ros2_bridge_topic_sender>( ) );
	auto node = std::make_shared<ros2_bridge_topic_sender>( );
	rclcpp::executors::MultiThreadedExecutor exec;
	exec.add_node(node);
	exec.spin( );
	
	rclcpp::shutdown( );
	return 0;
}
