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

#define BRIDGE_MSG( topic ) OUTLOG( "bridge topic: " << LOGSQUARE( BRIDGE_TOPIC_NAME_PREFIX << topic ) << " (ROS2) --> (ROS1)" << LOGSQUARE( topic ) )

namespace str_tools
{
	/// @brief split a string using a separator 
	///    @return this function returns an empty vector if the string is not well-formed
	std::vector<std::string> string_split( std::string str, char separator )
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
	// cast-back the message 'MyCustomMessage' from string to type
	ros1_bridge_support_pkg::MyCustomMessage cast_back_my_custom_message(
		const std_msgs::String::ConstPtr& msg )
	{
		// split the message
		std::vector<std::string> content = str_tools::string_split( msg->data, ' ' );
		
		// cast field by field
		ros1_bridge_support_pkg::MyCustomMessage rmsg;
		rmsg.value_boolean = ( content[0] == "1" ? true : false );
		rmsg.value_integer = atoi( content[1].c_str( ) );
		rmsg.value_float = atof( content[2].c_str( ) );
		/// @bug also a string value is split using this cast-back method!!!!
		rmsg.value_string = content[3];
		
		return rmsg;
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
	
	// subscription callback
	void bridge_cbk( const std_msgs::String::ConstPtr& msg )
	{
		// cast-back the message
		Topic_type rmsg = cast_tools::cast_back_my_custom_message( msg );
		
		// publish the message
		this->pub.publish( rmsg );
	}
	
	// publisher
	ros::Subscriber sub;
	
	// subscriber
	ros::Publisher pub;
};

class ros1_bridge_topic_receiver
{
public:
	ros1_bridge_topic_receiver( )
	{
		// bridge the custom topic
		BRIDGE_MSG( PUB_CUSTOM );
		make_link_topic<ros1_bridge_support_pkg::MyCustomMessage>( 
			&my_custom_topic, PUB_CUSTOM, str_tools::get_name_of_topic( PUB_CUSTOM ) );
		
		OUTLOG( "online!" );
	}
	
	void spin( ) { ros::spin( ); }

private:
	// node handle
	ros::NodeHandle nh;
	
	// make the link
	template< typename Ttopic >
	void make_link_topic( bridge_topic<Ttopic>* br, std::string pub_topic, std::string sub_topic )
	{
		OUTLOG( "subscription to " << sub_topic );
		br->sub = nh.subscribe( sub_topic, QUEUE_SZ_DEFAULT, &bridge_topic<Ttopic>::bridge_cbk, br );
		
		OUTLOG( "publisher on " << pub_topic );
		br->pub = nh.advertise<Ttopic>( pub_topic, QUEUE_SZ_DEFAULT );
	}
	
	bridge_topic<ros1_bridge_support_pkg::MyCustomMessage> my_custom_topic;
};

int main( int argc, char* argv[] )
{
	ros::init( argc, argv, NODE_NAME );
	
	OUTLOG( "online!" );
	( ros1_bridge_topic_receiver( ) ).spin( );
	
	return 0;
}
