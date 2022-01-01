;; Auto-generated. Do not edit!


(when (boundp 'ros1_bridge_support_pkg::MyCustomMessage)
  (if (not (find-package "ROS1_BRIDGE_SUPPORT_PKG"))
    (make-package "ROS1_BRIDGE_SUPPORT_PKG"))
  (shadow 'MyCustomMessage (find-package "ROS1_BRIDGE_SUPPORT_PKG")))
(unless (find-package "ROS1_BRIDGE_SUPPORT_PKG::MYCUSTOMMESSAGE")
  (make-package "ROS1_BRIDGE_SUPPORT_PKG::MYCUSTOMMESSAGE"))

(in-package "ROS")
;;//! \htmlinclude MyCustomMessage.msg.html


(defclass ros1_bridge_support_pkg::MyCustomMessage
  :super ros::object
  :slots (_value_boolean _value_integer _value_float _value_string ))

(defmethod ros1_bridge_support_pkg::MyCustomMessage
  (:init
   (&key
    ((:value_boolean __value_boolean) nil)
    ((:value_integer __value_integer) 0)
    ((:value_float __value_float) 0.0)
    ((:value_string __value_string) "")
    )
   (send-super :init)
   (setq _value_boolean __value_boolean)
   (setq _value_integer (round __value_integer))
   (setq _value_float (float __value_float))
   (setq _value_string (string __value_string))
   self)
  (:value_boolean
   (&optional (__value_boolean :null))
   (if (not (eq __value_boolean :null)) (setq _value_boolean __value_boolean)) _value_boolean)
  (:value_integer
   (&optional __value_integer)
   (if __value_integer (setq _value_integer __value_integer)) _value_integer)
  (:value_float
   (&optional __value_float)
   (if __value_float (setq _value_float __value_float)) _value_float)
  (:value_string
   (&optional __value_string)
   (if __value_string (setq _value_string __value_string)) _value_string)
  (:serialization-length
   ()
   (+
    ;; bool _value_boolean
    1
    ;; int32 _value_integer
    4
    ;; float32 _value_float
    4
    ;; string _value_string
    4 (length _value_string)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _value_boolean
       (if _value_boolean (write-byte -1 s) (write-byte 0 s))
     ;; int32 _value_integer
       (write-long _value_integer s)
     ;; float32 _value_float
       (sys::poke _value_float (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; string _value_string
       (write-long (length _value_string) s) (princ _value_string s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _value_boolean
     (setq _value_boolean (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; int32 _value_integer
     (setq _value_integer (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _value_float
     (setq _value_float (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; string _value_string
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _value_string (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get ros1_bridge_support_pkg::MyCustomMessage :md5sum-) "c00790425d14a25b56563df5c8c07bbd")
(setf (get ros1_bridge_support_pkg::MyCustomMessage :datatype-) "ros1_bridge_support_pkg/MyCustomMessage")
(setf (get ros1_bridge_support_pkg::MyCustomMessage :definition-)
      "## file 'MyCustomMessage.msg'

bool value_boolean
int32 value_integer
float32 value_float
string value_string

")



(provide :ros1_bridge_support_pkg/MyCustomMessage "c00790425d14a25b56563df5c8c07bbd")


