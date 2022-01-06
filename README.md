# ROS1 BRIDGE SUPPORT -- an extension for ROS1 BRIDGE

*Francesco Ganci*, 2022

This repository contains a overlay of the ROS1 BRIDGE which can map custom messages and services between ROS1 and ROS2 using the vanilla version of the bridge.

**ATTENTION! The bridge is meant to be customized, thhen compiled**. If you try to compile it immediately after the download, the compilation will fail, because first of all you have to modify it. Please refer to the *HOW TO* section below in this readme. THe code nside this respository is just a base for building and using the ROS1 BRIDGE. 

## Prerequisites and depts

Before building and running this package, I suggest you to un-source all your distros.

The code here is compatible only with **ROS1 noetic** and **ROS2 foxy**. You don't need to clone the bridge, because there's a script inside for downloading a clean version of the bridge.

[Here](https://github.com/ros2/ros1_bridge.git) you can find the official vanilla code of the ROS1 BRIDGE.

# Well, what is this?

This package contains a ready-to-use setup for using the ROS BRIDGE, as well as two packages, one in ROS1, and the other in ROS2, which let the packages to bridge communicate with custom messages and services with the *vanilla version of the bridge.*

## How does it work?

The principle is quite easy: all the messages and services are transmitted between ROS1 and ROS2 *using standard strings and topics*. Informations are serialized into strings (in the code, this operation is called *cast*), then sent to the other side using strings, then it is recomposed (in the code, this operation is called *cast back*) and returned to the end-point. This mechanism is extended in order to map also the services with a particular “protocol”.

It is an overlay, so *you don’t need to recompile the bridge* each time you add a new message to the system. Another advantage is that the bridge is more reliable and it works always as you might expect, since you have not to recompile it, so there’s no risk to introduce issues due to hidden bugs in the code. *The mapping of standard strings through topics works fine* always, depending on the status of the official repository. 

There are also some relevant disadvantages you should take into account:

- for each message you add, the code of the bridge support must be directly altered
- currently the package implements a *static bridge*, so there is no way to dynamically map a topic or a service
- transforming numbers in strings and “casting back” them could cause issues on numerical precision
- the loss of performances is the most relevant disadvantage: using sockets instead is a lot more efficient than using the bridge

Also note that, for mapping the standard topics, you can directly use the bridge, without passing through the overlay. If you need a quick solution, this is what’s right for you. 

# Glossary of the code

Before putting your hands on the code of the bridge support, you should take into account some names you can encounter in the code:

- **Cast** : it denotes the serialization of a message into a string.
- **Cast-back** : to “cast back” a message means to recompose the original message from the string.
- **cast rules** : the set of functions the bridge uses to serialize and de-serialize the messages
- **in-topic** : the end point is a subscriber that waits for a message from the bridge
- **out-topic** : the end point is a publisher to a node beyond the bridge
- **out-service** : the client runs in “this” framework. For example, if you’re working in ROS1, a service from ROS1 and ROS2 is a *out-service*. The ‘out’ service sends the request and waits for an answer from the other side.
- **in-service** : the client runs in the other framework. the in-service listens for a request and, when it arrives, calls the service and returns the response.

# Structure of the code

Here are some main ideas under the code:

- the structures of the two ends of the bridge support *must have almost the same interface*. Due to this principle, each end has the same names of the functions. Using the same structure for each end has a huge technical advantage: most of the code can be *copied and pasted* between the nodes, with few modifications.
- each topic/service can be mapped using only one instruction in the main constructor of the node. The callbacks are the same for each topic/service, just generalized using C++ class templates and function templates.
- there’s a neat distinction between what is needed to elaborate a message (the casting rules) and which topics/services use them.

## Namespace str_tools

The namespace `str_tools` contains some common utilities to perform an elaboration upon a message. The methods in this namespace are the basis for the casting rules, and more. In general, if you need some particular eaboration upon strings, you can add the methods you need here. 

Here are some methods and macros you can find there.

### Function pack_split

The most helpful function is this:

```cpp
// split a string using a separator
std::vector<std::string> pack_split( std::string str, char separator )
```

It has a simple purpose: it breaks down the string using a separator. See this example:

```cpp
std::string str = "hello world";
std::vector<std::string> pack_split( str, ' ' );
// "hello world" -> ["hello", "world"]
```

**Remember that the preferred separator is the space**. It has some particular behaviours:

- sequence of separators only are ignored
- when the string is not well formed, the function returns an empty array
- the empty string is denoted with the sequence `/{//}`; in general the function doesn’t return empty cells in the array, except for the empty strings
- the method reads the content between `/{` and `/}` as one long token

Using this function makes extremely simple to cast back the message: simply assign the end message field by field, or also, token by token in this case. 

The function works along with this:

```cpp
// exact string matching starting from the current index
bool check_seq_at( std::string str_arg, std::string to_find, int i, bool check_end = false )
```

I suggest you to not use this function. Here is how it behaves:

- the method in general returns if the given pattern in `to_find` starts or not from the given index
- the answer is `false` if there’s no pattern starting from the index, or the index is invalid
- the last parameter can check also if the pattern ends the string. See this example:
    
    ```cpp
    check_seq_at("hello", "ll", 2); // true
    check_seq_at("hello", "ll", 2, true); // FALSE because "ll" doesn't end the string
    check_seq_at("hello", "lo", 3, true) // true
    ```
    

### Names of the streams

In order to transfer the messages from one framework to another, the node creates some names starting from the names of the topics or services to map. Services are mapped using two topics starting with `/bridge_service`, and the topics with `/bridge_topic`.

## Namespace cast_tools

the namespace `cast_tools` contains the cast rules employed to elaborate the messages and services during the data transmissions. Here it is used a lot the *overloading of functions* in order to make the code as general as possible. Here are some general methods:

```cpp
// cast back a boolean value
bool cast_back_field( std::string pack )

// cast a string
//    "hello to everyone" -> "{/hello to everyone/}"
//    empty string ""     -> "/{//}"
std::string cast_field( std::string pack, bool use_sep = false, std::string sep = " " )

// cast a boolean value
std::string cast_field( bool pack, bool use_sep = false, std::string sep = " " )
// note the second argument: if true, the method adds the separator at the end of the string
```

Unfortunately ROS1 and ROS2 have their peculiarities to take into account when you go and write your cast rules. Just remembber these names:

- the rules `cast_message()` take the message and return the string representation of the message; the final “message” indicates that they are used for dealing with topics.
- the rules `cast_back_message()` take the string and return the message
- there are also the rules regarding the services: `cast_service_request()`, `cast_service_response()`, `cast_back_service_request()`, and `cast_back_service_response()`.

There are some useful macros and methods for casting and casting back the fields beyond the ones before:

```cpp
// string constructor macro
SS( "string or sequence of chars" ) // -> std::string

// something to string (possibly the most useful macro you can use)
SSS( 7.14 ) // -> std::string
SSS( "already string -> becomes a string" )

// cast with the separator
str += SSS( value ) + " ";
// typically
str += SSS( msg->value_integer ) + " ";

// cast back
atoi( content[1].c_str( ) )
atof( content[2].c_str( ) )
```

Feel free to reuse the interface I provide in the following sections.

### cast rules in ROS1

for topics:

```cpp
// your message type is pkg::Msg

// cast the message 'pkg::Msg'
std::string cast_message( const pkg::Msg::ConstPtr& msg )
{
	std::string str = "";
	
	// str += SSS( msg->value ) + " ";
	// ...
	
	return str;
}

// cast-back the message 'pkg::Msg'
pkg::Msg cast_back_message( const std_msgs::String::ConstPtr& msg )
{
	// split the message
	std::vector<std::string> content = str_tools::pack_split( msg->data, ' ' );
	
	// cast field by field
	pkg::Msg rmsg;
	
	// rmsg.value = content[3];
	// ...
	
	return rmsg;
}
```

for services:

```cpp
// yout service type is pkg::Srv

// cast the service request 'pkg::Srv'
std::string cast_service_request( pkg::Srv::Request &req )
{
	std::string str = "";
	
	// str += SSS( req.index ) + " ";
	// ...
	
	return str;
}

// cast back the service request of 'pkg::Srv'
pkg::Srv::Request cast_back_service_request( std::string msg )
{
	std::vector< std::string > content = str_tools::pack_split( msg, ' ' );
	
	pkg::Srv::Request req;
	
	// req.value = atoi( content[0].c_str( ) );
	// ...
	
	return req;
}

// cast the service response 'pkg::Srv'
std::string cast_service_response( pkg::Srv::Response &res )
{
	std::string str = "";
	
	// str += SSS( res.index ) + " ";
	// ...
	
	return str;
}

// cast back the service response 'pkg::Srv'
pkg::Srv::Response cast_back_service_response( std::string msg )
{
	std::vector< std::string > content = str_tools::pack_split( msg, ' ' );
	
	pkg::Srv::Response res;
	// res.field = content[0];
	// ...
	
	return res;
}
```

### cast rules in ROS2

for topics:

```cpp
// your message type is pkg::msg::Msg

// cast the message pkg::msg::Msg to string
std::string cast_message( const pkg::msg::Msg::SharedPtr msg )
{
	std::string str = "";
	
	// str += SSS( msg->value ) + " ";
	// ...
	
	return str;
}

// cast back the message pkg::msg::Msg
pkg::msg::Msg cast_back_message( const std_msgs::msg::String::SharedPtr msg )
{
	// split the message
	std::vector< std::string > content = str_tools::pack_split( msg->data, ' ' );
	
	// cast field by field
	pkg::msg::Msg rmsg;
	// rmsg.value = atoi( content[1].c_str( ) );
	// ...
	
	return rmsg;
}
```

for services:

```cpp
// yout service type is pkg::srv::Srv

// cast the service request pkg::srv::Srv
std::string cast_service_request( const std::shared_ptr<pkg::srv::Srv::Request> req )
{
	std::string str = "";
	
	// str += SSS( req->index ) + " ";
	// ...
	
	return str;
}

// cast back the service request of pkg::srv::Srv
pkg::srv::Srv::Request cast_back_service_request( std::string &msg )
{
	std::vector< std::string > content = str_tools::pack_split( msg, ' ' );
	
	pkg::srv::Srv::Request req;
	
	// req.index = atoi( content[0].c_str( ) );
	// ...
	
	return req;
}

// cast the service response of pkg::srv::Srv
std::string cast_service_response( const std::shared_ptr<pkg::srv::Srv::Response> res )
{
	std::string str = "";
	
	// str += SSS( res->index ) + " ";
	// ...
	
	return str;
}

// cast back the service response pkg::srv::Srv
pkg::srv::Srv::Response cast_back_service_response( std::string &msg )
{
	std::vector< std::string > content = str_tools::pack_split( msg, ' ' );
	
	pkg::srv::Srv::Response res;
	
	// res.guessed = cast_back_field( content[0] );
	// ...
	
	return res;
}
```

## Bridge Topic Class

Each topic is represented by a class called `bridge_topic`. The two versions of the classes are slightly different in ROS1 and in ROS2, but the structure is the same:

- both these implementations have a publisher and a subscriber; one channel is dependent by the other one.
- The class implements a subscriber which publishes what is received.

These topics are instantiated in the main class using these functions:

```cpp
// open a channel from this framework to the other
template< typename Ttopic >
void make_link_topic_out( bridge_topic< Ttopic >* br_class, std::string sub_topic )

// open a channel from the other framework to this one
template< typename Ttopic >
void make_link_topic_in( bridge_topic< Ttopic >* br_class, std::string pub_topic )
```

*The functions for opening the channels have the same name in both the frameworks*, but note that the template of the class changes: ROS2 requires 2 template classes instead of only one. 

```cpp
// side ROS2
bridge_topic<publihser_type, subscriber_type> my_custom_topic;
// in topic (ROS1 to ROS2)
bridge_topic<pkg::msg::Msg, std_msgs::msg::String> my_custom_topic_in;
// out topic
bridge_topic<std_msgs::msg::String, pkg::msg::Msg> my_custom_topic_out;

// side ROS1 - only one type is required
bridge_topic<pkg::Msg> my_custom_topic;
```

## Bridge Service Class

Each service or client is represented by the class `bridge_service` which contains all you need in order to manage a service or client. As seen before, the class is created and then instanciated in the main class using special methods:

```cpp
// the class in ROS2
bridge_service<pkg::srv::Srv> my_custom_service;
// the class in ROS1
bridge_service<pkg::Srv> my_custom_service;

// create a out service
template< typename serviceT >
void make_link_service_out( bridge_service< serviceT >* br_class, std::string service_name )

// create a in service
template< typename serviceT >
void make_link_service_in( bridge_service< serviceT >* br_class, std::string service_name )
```

# HOW TOs

## Build the entire project

I suggest you to put the content of this repository in the  `/root` folder, in order to use all the scripts along with the project.

1. clone this repository into the */root* folder.
    
    ```bash
    git clone https://github.com/programmatoroSeduto/simple_bridge.git /root
    ```
    
2. go inside the folder */root/simple_bridge/shell* and from there run the script **shell_build.sh**. Remember to make all the files executable. The script also downloads and compiles the bridge: it requires 5 minutes on my PC, but it could require much time.
    
    ```bash
    # chmod +x /root/simple_bridge/shell/*
    
    # complete build process
    source /root/simple_bridge/shell/shell_build.sh
    
    # workspaced only
    source /root/simple_bridge/shell/shell_build_ws_only.sh
    ```
    

The scripts also writes some logs you can read from the folder */root/simple_bridge/logs*. 

## Build everything except the bridge

If you only need to build the workspaces without the bridge, you can use the script */root/simple_bridge/shell/shell_build_ws_only.sh*. This script also generates the logs in the main folder. 

## Build one workspace

Each workspace has its (very basic) build script which first deletes the last build, and then does build the project. 

```bash
# build the bridge only
source /root/simple_bridge/ws_bridge/build.sh

# build ROS1 only
source /root/simple_bridge/ws_ros1/build.sh

# build ROS2 only
source /root/simple_bridge/ws_ros2/build.sh
```

## Add some cast rules

See the patterns I wrote above: using them simplifies a lor the development of these rules. 

1. first of all, create the interfaces. I suggest you to put them in the folder of the bridge support package if possible, otherwise remember to add the dependency by the other package which contains the messages you want to bridge. There must be the same interface in both the frameworks. 
2. write the cast rules for ROS2, using the patterns above mentioned, then copy and paste in the code of the bridge, namespace `cast_tools`
3. then, rewrite them using the ROS1 pattern and put them in the main node under the namespace `cast_tools`
4. finally compile the bridge support package on each framework. 

## Add a topic to the static mapping

*BEFORE STARTING, MAKE SURE THE NODES HAVE THE ADEQUATE CAST RULES.*

let’s consider the case of *a topic from ROS1 to ROS2*; the topic is a ‘*out’ topic* wrt ROS1 and a ‘*in’ topic* wrt ROS2.  

1. go into the ROS1 bridge support package, in the main constructor of the node
2. define the class `bridge_topic<pkg::Msg>` anywhere you want (the best is to define it *inside the class* as member)
3. then, use the function `make_link_topic_out<>()` because it is a ‘out’ topic wrt ROS1
4. now, go into te ROS1 bridge support pakcage and open the main node; go into the constructor
5. remember that a out topic in ROS1 is a ‘in’ topic wrt ROS2. So, define the class `bridge_topic<pkg::msg::Msg, std_msgs::msg::String>` anywhere you want (again, I suggest to define it as a class *private* member). Remember to swap the templates if you’re defining a ‘in’ topic wrt ROS2. 
6. create the link using `make_link_topic_in<>()`
7. in the end, compile the two workspaces. 

The steps for adding a topic in the inverse direction, from ROS2 to ROS1, are pretty much the same, with the difference that now the topic is a ‘in’ topic for ROS1 and a ‘out’ topic for ROS2. 

## Add a service to the static mapping

*BEFORE STARTING, MAKE SURE THE NODES HAVE THE ADEQUATE CAST RULES.*

Let’s consider a service in ROS2 and a client in ROS1, so we’re defining a *‘in’ service* wrt ROS2 and a *‘out’* service wrt ROS1. Here are the steps to follow, very similar to the ones for creating a topic:

1. go into the ROS1 bridge support package, in the main constructor of the node
2. define the class `bridge_service<pkg::Srv>` anywhere you want (the best is to define it *inside the class* as member)
3. then, use the function `make_link_service_out<>()` because it is a ‘out’ service wrt ROS1
4. now, go into te ROS1 bridge support pakcage and open the main node; go into the constructor
5. remember that a ‘out’ service in ROS1 is a ‘in’ service wrt ROS2. So, define the class `bridge_service<pkg::srv::Srv>` anywhere you want (again, I suggest to define it as a class *private* member)
6. create the link `make_link_service_in<>()`
7. finally, compile the workspaces.
