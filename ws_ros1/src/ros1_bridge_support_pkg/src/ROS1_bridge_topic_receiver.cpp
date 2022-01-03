/*
# TERMINALE 1 : 
rostopic pub /custom_topic_out ros1_bridge_support_pkg/MyCustomMessage "value_boolean: false
value_integer: 0
value_float: 0.0
value_string: ''" 
# TERMINALE 2 :
rostopic echo /bridge_topic/custom_topic_out
*/

#include "ros/ros.h"
#include <string>
#include <vector>

#include "ros1_bridge_support_pkg/MyCustomMessage.h"
// from ROS2
//    PUB : pubblico quanto ricevuto da ROS2 al nodo che usa il topic
//    IN : il nodo vede il topic come ingresso
#define PUB_CUSTOM_IN "/custom_topic_a"
// to ROS2
//    SUB : leggo le informazioni da trasmettere a ROS2
//    OUT : il nodo vede il topic come output
#define SUB_CUSTOM_OUT "/custom_topic_b"
/*
bool value_boolean
int32 value_integer
float32 value_float
string value_string
*/
#include "std_msgs/String.h"
/*
string data
*/
#include "ros1_bridge_support_pkg/MyCustomService.h"
#define SERVICE_CUSTOM "/my_custom_service"
/*
int32 index
string mystery_word
---
bool guessed
*/

#define NODE_NAME "ros1_bridge_support_topic_receiver"
#define BRIDGE_TOPIC_NAME_PREFIX "/bridge_topic"
#define BRIDGE_SERVICE_NAME_PREFIX "/bridge_service"
#define QUEUE_SZ_DEFAULT 100
#define WAITING_DELAY 0.01

#define LOGSQUARE( str ) "[" << str << "] "
#define OUTLABEL LOGSQUARE( NODE_NAME )
#define OUTLOG( msg ) ROS_INFO_STREAM( OUTLABEL << msg )
#define OUTERR( msg ) OUTLOG( "ERROR: " << msg )
#define SS( this_string ) std::string( this_string )
#define SSS( this_thing ) std::to_string( this_thing )

#define BRIDGE_MSG( topic ) OUTLOG( "bridge topic: " << LOGSQUARE( BRIDGE_TOPIC_NAME_PREFIX << topic ) << " (ROS2) --> (ROS1)" << LOGSQUARE( topic ) )

namespace str_tools
{
	/// @brief split a string using a separator 
	///    @return this function returns an empty vector if the string is not well-formed
	/// @bug empty string results in one field missing!
	/// @todo how about empty strings? Suppose you have many string fields, ...empty...
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
	
	// cast the message 'MyCustomMessage'
	std::string cast_message( const ros1_bridge_support_pkg::MyCustomMessage::ConstPtr& msg )
	{
		std::string str = "";
		
		str += cast_tools::cast_field( msg->value_boolean );
		str += SSS( msg->value_integer ) + " ";
		str += SSS( msg->value_float ) + " ";
		str += cast_tools::cast_field( msg->value_string, false );
		
		return str;
	}
	
	// cast-back the message 'MyCustomMessage' from string to type
	ros1_bridge_support_pkg::MyCustomMessage cast_back_message( const std_msgs::String::ConstPtr& msg )
	{
		// split the message
		std::vector<std::string> content = str_tools::pack_split( msg->data, ' ' );
		
		// cast field by field
		ros1_bridge_support_pkg::MyCustomMessage rmsg;
		rmsg.value_boolean = cast_tools::cast_back_field( content[0] );
		rmsg.value_integer = atoi( content[1].c_str( ) );
		rmsg.value_float = atof( content[2].c_str( ) );
		rmsg.value_string = content[3];
		
		return rmsg;
	}
	
	// cast the service request 'MyCustomService'
	std::string cast_service_request( ros1_bridge_support_pkg::MyCustomService::Request &req )
	{
		std::string str = "";
		
		str += SSS( req.index ) + " ";
		str += cast_tools::cast_field( req.mystery_word, false );
		
		return str;
	}
	
	// cast back the service response 'MyCustomService'
	ros1_bridge_support_pkg::MyCustomService::Response cast_back_service_response( std::string &msg )
	{
		std::vector< std::string > content = str_tools::pack_split( msg, ' ' );
		
		OUTLOG( "HERE! CAST BACK! array size: " << content.size( ) );
		ros1_bridge_support_pkg::MyCustomService::Response res;
		res.guessed = cast_tools::cast_back_field( content[0] );
		OUTLOG( "HERE! after CAST BACK!" );
		return res;
	}
}

// vedi
//    https://answers.ros.org/question/232068/call-to-publish-on-an-invalid-publisher/
//    https://stackoverflow.com/questions/37502096/ros-binding-a-callback-function-and-a-object-member-to-a-subscriber-node
//    http://wiki.ros.org/roscpp_tutorials/Tutorials/UsingClassMethodsAsCallbacks
// Purtroppo ROS1 non permette il binding come in ROS2, quindi la funzione
//     viene eseguita in un contesto diverso da quello di definizione. 
template<typename Topic_type>
class bridge_topic
{
public:
	bridge_topic( ) { }
	
	ros::Publisher pub;
	ros::Subscriber sub;
	
	// "OUT BRIDGE" : from ROS1 to ROS2 (cast)
	void bridge_cbk_out( const ros1_bridge_support_pkg::MyCustomMessage::ConstPtr& msg )
	{
		// cast-back the message
		std_msgs::String rmsg;
		rmsg.data = cast_tools::cast_message( msg );
		
		// publish the message
		this->pub.publish( rmsg );
	}
	
	// "IN BRIDGE" : from ROS2 to ROS1 (cast back)
	void bridge_cbk_in( const std_msgs::String::ConstPtr& msg )
	{
		// cast-back the message
		Topic_type rmsg = cast_tools::cast_back_message( msg );
		
		// publish the message
		this->pub.publish( rmsg );
	}
};

template< typename serviceT >
class bridge_service
{
public:
	bridge_service( ) { }
	
	// first topic from ROS2
	ros::Subscriber topic_in;
	// second topic to ROS2
	ros::Publisher topic_out;
	// request from endpoint
	ros::ServiceServer service_in; 
	
	// callback service from endpoint
	bool service_in_callback(
		typename serviceT::Request &req,
		typename serviceT::Response &res
		)
	{
		OUTLOG( "ROS1 BRIDGE REQUEST" );
		
		// set the pending request and reset the response (use a specific cast method)
		this->pending_request = req;
		this->response_string = "";
		
		// cast the request to string
		std_msgs::String req_str;
		req_str.data = cast_tools::cast_service_request( req );
		
		// send the request to ROS2 through topic_out 
		topic_out.publish( req_str );
		
		// wait for a responde from ROS2 (don't use sleep!!!)
		OUTLOG( "waiting for a response from ROS2..." );
		waiting_response = true;
		while( waiting_response ) 
		{
			( ros::Duration( WAITING_DELAY ) ).sleep( );
			ros::spinOnce( );
			
			OUTLOG( "waiting..." );
			
			/// @todo some break condition here? (maximum time?)
		}
		OUTLOG( "got a response from ROS2 -> [" << response_string << "]" );
		
		// cast back the message to response and write it (use a specific cast-back method)
		res = cast_tools::cast_back_service_response( response_string );
		
		return true;
	}
	
	// callback service subscriber
	// precisamente il caso in oggetto:
	//    https://stackoverflow.com/questions/49059435/segmentation-fault-core-dumped-ros-c-arrow
	void topic_in_callback( const std_msgs::String::ConstPtr& res )
	{
		if( waiting_response )
		{
			// store the message into the class variable
			response_string = res->data;
			
			waiting_response = false;
		}
	}
	
private:
	// pending request
	typename serviceT::Request pending_request;
	// waiting for a response from ROS2
	bool waiting_response = false;
	// the response as string
	std::string response_string;
};

class ros1_bridge_topic_receiver
{
public:
	ros1_bridge_topic_receiver( ) // using static mapping
	{
		// bridge the custom topic
		OUTLOG( "--- TOPIC from ROS2: " << PUB_CUSTOM_IN );
		make_link_topic_in<ros1_bridge_support_pkg::MyCustomMessage>( &my_custom_topic_in, PUB_CUSTOM_IN );
		OUTLOG( "--- TOPIC to ROS2: " << SUB_CUSTOM_OUT );
		make_link_topic_out<ros1_bridge_support_pkg::MyCustomMessage>( &my_custom_topic_out, SUB_CUSTOM_OUT );
		
		OUTLOG( "--- SERVICE to ROS2: " << SERVICE_CUSTOM );
		make_link_service_out<ros1_bridge_support_pkg::MyCustomService>( &my_custom_service_out, SERVICE_CUSTOM );
		
		OUTLOG( "online!" );
	}
	
	void spin( ) { ros::spin( ); }

private:
	// node handle
	ros::NodeHandle nh;
	
	// --- LINK METHODS ---
	
	/// create a "bridge in" topic
	/// @note 'out' topic as 'sub' from the end node and 'pub' to bridge
	template< typename Ttopic >
	void make_link_topic_in( bridge_topic< Ttopic >* br_class, std::string pub_topic )
	{
		OUTLOG( "subscription to " << str_tools::get_name_of_topic( pub_topic ) );
		br_class->sub = nh.subscribe( 
			str_tools::get_name_of_topic( pub_topic ), 
			QUEUE_SZ_DEFAULT, 
			&bridge_topic< Ttopic >::bridge_cbk_in, br_class 
			);
		
		OUTLOG( "publisher on " << pub_topic );
		br_class->pub = nh.advertise<Ttopic>( 
			pub_topic, 
			QUEUE_SZ_DEFAULT 
			);
	}
	
	/// create a "bridge out" topic
	/// @note 'in' topic as 'sub' from bridge and 'pub' to the end node
	template< typename Ttopic >
	void make_link_topic_out( bridge_topic< Ttopic >* br_class, std::string sub_topic )
	{
		OUTLOG( "subscription to " << sub_topic );
		br_class->sub = nh.subscribe( 
			sub_topic, 
			QUEUE_SZ_DEFAULT, 
			&bridge_topic< Ttopic >::bridge_cbk_out, 
			br_class 
			);
		
		OUTLOG( "publisher on " << str_tools::get_name_of_topic( sub_topic ) );
		br_class->pub = nh.advertise< std_msgs::String >( 
			str_tools::get_name_of_topic( sub_topic ),
			QUEUE_SZ_DEFAULT 
			);
	}
	
	/// create a "bridge out" service
	template< typename serviceT >
	void make_link_service_out( bridge_service< serviceT >* br_class, std::string service_name )
	{
		// out publisher -- request
		OUTLOG( "publisher on " << str_tools::get_name_of_service_request( service_name ) );
		br_class->topic_out = nh.advertise<std_msgs::String>(
			str_tools::get_name_of_service_request( service_name ),
			QUEUE_SZ_DEFAULT
			);
		
		// in subscriber -- response
		OUTLOG( "subscription to " << str_tools::get_name_of_service_response( service_name ) );
		br_class->topic_in = nh.subscribe(
			str_tools::get_name_of_service_response( service_name ),
			QUEUE_SZ_DEFAULT,
			&bridge_service< serviceT >::topic_in_callback,
			br_class
			);
		
		// in service from endpoint
		OUTLOG( "creating 'in' service " << service_name );
		br_class->service_in = nh.advertiseService(
			service_name,
			&bridge_service< serviceT >::service_in_callback,
			br_class
			);
	}
	
	// --- TOPICS AND SERVICES ---
	
	bridge_topic<ros1_bridge_support_pkg::MyCustomMessage> my_custom_topic_in;
	bridge_topic<ros1_bridge_support_pkg::MyCustomMessage> my_custom_topic_out;
	
	bridge_service<ros1_bridge_support_pkg::MyCustomService> my_custom_service_out;
};

int main( int argc, char* argv[] )
{
	ros::init( argc, argv, NODE_NAME );
	
	OUTLOG( "online!" );
	( ros1_bridge_topic_receiver( ) ).spin( );
	
	return 0;
}
