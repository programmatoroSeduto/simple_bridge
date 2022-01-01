; Auto-generated. Do not edit!


(cl:in-package ros1_bridge_support_pkg-msg)


;//! \htmlinclude MyCustomMessage.msg.html

(cl:defclass <MyCustomMessage> (roslisp-msg-protocol:ros-message)
  ((value_boolean
    :reader value_boolean
    :initarg :value_boolean
    :type cl:boolean
    :initform cl:nil)
   (value_integer
    :reader value_integer
    :initarg :value_integer
    :type cl:integer
    :initform 0)
   (value_float
    :reader value_float
    :initarg :value_float
    :type cl:float
    :initform 0.0)
   (value_string
    :reader value_string
    :initarg :value_string
    :type cl:string
    :initform ""))
)

(cl:defclass MyCustomMessage (<MyCustomMessage>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MyCustomMessage>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MyCustomMessage)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros1_bridge_support_pkg-msg:<MyCustomMessage> is deprecated: use ros1_bridge_support_pkg-msg:MyCustomMessage instead.")))

(cl:ensure-generic-function 'value_boolean-val :lambda-list '(m))
(cl:defmethod value_boolean-val ((m <MyCustomMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros1_bridge_support_pkg-msg:value_boolean-val is deprecated.  Use ros1_bridge_support_pkg-msg:value_boolean instead.")
  (value_boolean m))

(cl:ensure-generic-function 'value_integer-val :lambda-list '(m))
(cl:defmethod value_integer-val ((m <MyCustomMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros1_bridge_support_pkg-msg:value_integer-val is deprecated.  Use ros1_bridge_support_pkg-msg:value_integer instead.")
  (value_integer m))

(cl:ensure-generic-function 'value_float-val :lambda-list '(m))
(cl:defmethod value_float-val ((m <MyCustomMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros1_bridge_support_pkg-msg:value_float-val is deprecated.  Use ros1_bridge_support_pkg-msg:value_float instead.")
  (value_float m))

(cl:ensure-generic-function 'value_string-val :lambda-list '(m))
(cl:defmethod value_string-val ((m <MyCustomMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros1_bridge_support_pkg-msg:value_string-val is deprecated.  Use ros1_bridge_support_pkg-msg:value_string instead.")
  (value_string m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MyCustomMessage>) ostream)
  "Serializes a message object of type '<MyCustomMessage>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'value_boolean) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'value_integer)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'value_float))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'value_string))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'value_string))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MyCustomMessage>) istream)
  "Deserializes a message object of type '<MyCustomMessage>"
    (cl:setf (cl:slot-value msg 'value_boolean) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'value_integer) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'value_float) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'value_string) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'value_string) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MyCustomMessage>)))
  "Returns string type for a message object of type '<MyCustomMessage>"
  "ros1_bridge_support_pkg/MyCustomMessage")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MyCustomMessage)))
  "Returns string type for a message object of type 'MyCustomMessage"
  "ros1_bridge_support_pkg/MyCustomMessage")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MyCustomMessage>)))
  "Returns md5sum for a message object of type '<MyCustomMessage>"
  "c00790425d14a25b56563df5c8c07bbd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MyCustomMessage)))
  "Returns md5sum for a message object of type 'MyCustomMessage"
  "c00790425d14a25b56563df5c8c07bbd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MyCustomMessage>)))
  "Returns full string definition for message of type '<MyCustomMessage>"
  (cl:format cl:nil "## file 'MyCustomMessage.msg'~%~%bool value_boolean~%int32 value_integer~%float32 value_float~%string value_string~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MyCustomMessage)))
  "Returns full string definition for message of type 'MyCustomMessage"
  (cl:format cl:nil "## file 'MyCustomMessage.msg'~%~%bool value_boolean~%int32 value_integer~%float32 value_float~%string value_string~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MyCustomMessage>))
  (cl:+ 0
     1
     4
     4
     4 (cl:length (cl:slot-value msg 'value_string))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MyCustomMessage>))
  "Converts a ROS message object to a list"
  (cl:list 'MyCustomMessage
    (cl:cons ':value_boolean (value_boolean msg))
    (cl:cons ':value_integer (value_integer msg))
    (cl:cons ':value_float (value_float msg))
    (cl:cons ':value_string (value_string msg))
))
