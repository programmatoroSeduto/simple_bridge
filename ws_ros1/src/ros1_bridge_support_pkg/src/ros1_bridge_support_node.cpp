
#include "ros/ros.h"
#include <string>
#include <vector>

#include "std_msgs/String.h"
// put here the services and the topics...
// ...

#define NODE_NAME "ros1_bridge_support_node"
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
    bool check_seq_at( std::string str_arg, std::string to_find, int i, bool check_end = false )
    {
        if( i >= str_arg.length( ) ) return false;

        std::size_t next_idx = i + to_find.length( );
        std::string sub = str_arg.substr( i, to_find.length( ) );
        bool found = ( to_find == sub );

        if( check_end )
            return found && ( next_idx >= str_arg.length( ) );
        else
            return found;
    }

    /// split a string using a separator 
    /// @return this function returns an empty vector if the string is not well-formed
    /// @note nested messages using /{ and /} are not supported right now
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
    std::string 
    cast_field( std::string pack, bool use_sep = false, std::string sep = " " )
    {
        // generate the empty sequence if the string is empty
        pack = ( pack != "" ? pack : "/" );

        std::string str = "/{" + pack + "/}";

        if( use_sep ) str += sep;
        return str;
    }

    // bool type to string
    std::string 
    cast_field( bool pack, bool use_sep = false, std::string sep = " " )
    {
        std::string str = ( pack ? "1" : "0" );

        if( use_sep ) str += sep;
        return str;
    }
    
    /* TEMPLATE for topic mapping (message ???)
    // cast topic msg 
    std::string cast_message( const ???::ConstPtr& msg )
    { return "/{//}"; }

    // cast back topic msg
    void cast_back_message( const std_msgs::String::ConstPtr& msg, ???& msg_return )
    { }
    */

    /* TEMPLATE for service mapping (service ???)
    // cast the service request
    std::string cast_service_request( ???::Request* req )
    { return ""; }

    // cast back the service request
    void cast_back_service_request( std::string msg, ???::Request *req )
    { }

    // cast the service response
    std::string cast_service_response( ???::Response *res )
    { return ""; }

    // cast back the service response
    void cast_back_service_response( std::string msg, ???::Response *res )
    { }
    */
}

/// representation of a generic topic
template<typename Topic_type>
class bridge_topic
{
public:
    bridge_topic( ) { }

    ros::Publisher pub;
    ros::Subscriber sub;

    // "OUT BRIDGE" : from ROS1 to ROS2 (cast)
    void bridge_cbk_out( const typename Topic_type::ConstPtr& msg )
    {
        // cast-back the message
        std_msgs::String rmsg;
        // rmsg.data = cast_tools::cast_message< Topic_type >( msg );
        rmsg.data = cast_tools::cast_message( msg );

        // publish the message
        this->pub.publish( rmsg );
    }

    // "IN BRIDGE" : from ROS2 to ROS1 (cast back)
    void bridge_cbk_in( const std_msgs::String::ConstPtr& msg )
    {
        // cast-back the message
        Topic_type rmsg;
        // cast_tools::cast_back_message< Topic_type >( msg, rmsg );
        cast_tools::cast_back_message( msg, rmsg );

        // publish the message
        this->pub.publish( rmsg );
    }
};

/// representation of a generic service/client
template< typename serviceT >
class bridge_service
{
public:
    bridge_service( ) { }

    // first topic from ROS2
    ros::Subscriber topic_in;
    // second topic to ROS2
    ros::Publisher topic_out;
    // client in ROS1, service in ROS2
    ros::ServiceServer service_out; 
    // client in ROS2, service in ROS1
    ros::ServiceClient service_in;

    // callback service from endpoint
    bool service_out_callback(
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
        // req_str.data = cast_tools::cast_service_request< serviceT >( &req );
        req_str.data = cast_tools::cast_service_request( &req );

        // send the request to ROS2 through topic_out 
        topic_out.publish( req_str );

        // wait for a responde from ROS2 (don't use sleep!!!)
        OUTLOG( "waiting for a response from ROS2..." );
        waiting_response = true;
        while( waiting_response ) 
        {
            ( ros::Duration( WAITING_DELAY ) ).sleep( );
            ros::spinOnce( );

            // OUTLOG( "waiting..." );

            /// @todo some break condition here? (maximum time?)
        }
        OUTLOG( "got a response from ROS2 -> [" << response_string << "]" );

        // cast back the message to response and write it (use a specific cast-back method)
        // cast_tools::cast_back_service_response( response_string, &res );
        cast_tools::cast_back_service_response( response_string, &res );

        return true;
    }

    /// callback service to the endpoint
    void service_in_callback( const std_msgs::String::ConstPtr& msg )
    {
        OUTLOG( "received a ROS2->ROS1 request from ROS2 endpoint" ); 
        OUTLOG( "with data: [" << msg->data << "]" );

        // cast back the message
        serviceT srv;
        cast_tools::cast_back_service_request( msg->data, &srv.request );

        // call the service and get the response
        OUTLOG( "waiting for a response from the service..." );
        service_in.call( srv );

        // cast the message
        std_msgs::String res_str;
        res_str.data = cast_tools::cast_service_response( &srv.response );

        // and publish it
        OUTLOG( "returning response: [" << res_str.data << "]" );
        this->topic_out.publish( res_str );
    }

    // callback service subscriber
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

class ros1_bridge_support
{
public:
    ros1_bridge_support( ) // using static mapping
    {
        // @todo define here the static mapping
        // ...

        OUTLOG( "online!" );
    }

    void spin( ) 
    {
        ros::spin( ); 
    }

private:
    // node handle
    ros::NodeHandle nh;

    // put here the definitions of your services and topics
    // ...

    // --- LINK METHODS ---

    /// create a "bridge in" topic
    /// @note 'in' topic as 'sub' from bridge and 'pub' to the end node
    template< typename Ttopic >
    void make_link_topic_in( bridge_topic< Ttopic >* br_class, std::string pub_topic )
    {
        OUTLOG( "--- (in) TOPIC ROS2 to ROS1: " << pub_topic );

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
    /// @note 'out' topic as 'sub' from the end node and 'pub' to bridge
    template< typename Ttopic >
    void make_link_topic_out( bridge_topic< Ttopic >* br_class, std::string sub_topic )
    {
        OUTLOG( "--- (out) TOPIC ROS1 to ROS2: " << sub_topic );

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
    /// @note 'out' i.e. the client runs in ROS1
    template< typename serviceT >
    void make_link_service_out( bridge_service< serviceT >* br_class, std::string service_name )
    {
        OUTLOG( "--- (out) SERVICE client in ROS1 service in ROS2: " << service_name );

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
        OUTLOG( "creating 'out' service " << service_name );
        br_class->service_out = nh.advertiseService(
            service_name,
            &bridge_service< serviceT >::service_out_callback,
            br_class
        );
    }

    /// create a 'in' service
    /// @note 'in' i.e. the client runs in ROS2
    template< typename serviceT >
    void make_link_service_in( bridge_service< serviceT >* br_class, std::string service_name )
    {
        OUTLOG( "--- (in) SERVICE client in ROS2 service in ROS1: " << service_name );

        // in subscriber -- request
        OUTLOG( "subscription to " << str_tools::get_name_of_service_request( service_name ) );
        br_class->topic_in = nh.subscribe(
            str_tools::get_name_of_service_request( service_name ),
            QUEUE_SZ_DEFAULT,
            &bridge_service< serviceT >::service_in_callback,
            br_class
        );

        // out publisher -- response 
        OUTLOG( "publisher on " << str_tools::get_name_of_service_response( service_name ) );
        br_class->topic_out = nh.advertise<std_msgs::String>(
            str_tools::get_name_of_service_response( service_name ),
            QUEUE_SZ_DEFAULT
        );

        // out service to endpoint
        OUTLOG( "creating 'in' service " << service_name );
        br_class->service_in = nh.serviceClient< serviceT >(
            service_name
        );
    }
};

int main( int argc, char* argv[] )
{
    ros::init( argc, argv, NODE_NAME );

    OUTLOG( "online!" );
    ( ros1_bridge_support( ) ).spin( );

    return 0;
}
