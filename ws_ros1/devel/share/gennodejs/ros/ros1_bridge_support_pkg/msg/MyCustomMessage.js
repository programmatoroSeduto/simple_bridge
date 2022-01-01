// Auto-generated. Do not edit!

// (in-package ros1_bridge_support_pkg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class MyCustomMessage {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.value_boolean = null;
      this.value_integer = null;
      this.value_float = null;
      this.value_string = null;
    }
    else {
      if (initObj.hasOwnProperty('value_boolean')) {
        this.value_boolean = initObj.value_boolean
      }
      else {
        this.value_boolean = false;
      }
      if (initObj.hasOwnProperty('value_integer')) {
        this.value_integer = initObj.value_integer
      }
      else {
        this.value_integer = 0;
      }
      if (initObj.hasOwnProperty('value_float')) {
        this.value_float = initObj.value_float
      }
      else {
        this.value_float = 0.0;
      }
      if (initObj.hasOwnProperty('value_string')) {
        this.value_string = initObj.value_string
      }
      else {
        this.value_string = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MyCustomMessage
    // Serialize message field [value_boolean]
    bufferOffset = _serializer.bool(obj.value_boolean, buffer, bufferOffset);
    // Serialize message field [value_integer]
    bufferOffset = _serializer.int32(obj.value_integer, buffer, bufferOffset);
    // Serialize message field [value_float]
    bufferOffset = _serializer.float32(obj.value_float, buffer, bufferOffset);
    // Serialize message field [value_string]
    bufferOffset = _serializer.string(obj.value_string, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MyCustomMessage
    let len;
    let data = new MyCustomMessage(null);
    // Deserialize message field [value_boolean]
    data.value_boolean = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [value_integer]
    data.value_integer = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [value_float]
    data.value_float = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [value_string]
    data.value_string = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.value_string);
    return length + 13;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros1_bridge_support_pkg/MyCustomMessage';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c00790425d14a25b56563df5c8c07bbd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    ## file 'MyCustomMessage.msg'
    
    bool value_boolean
    int32 value_integer
    float32 value_float
    string value_string
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MyCustomMessage(null);
    if (msg.value_boolean !== undefined) {
      resolved.value_boolean = msg.value_boolean;
    }
    else {
      resolved.value_boolean = false
    }

    if (msg.value_integer !== undefined) {
      resolved.value_integer = msg.value_integer;
    }
    else {
      resolved.value_integer = 0
    }

    if (msg.value_float !== undefined) {
      resolved.value_float = msg.value_float;
    }
    else {
      resolved.value_float = 0.0
    }

    if (msg.value_string !== undefined) {
      resolved.value_string = msg.value_string;
    }
    else {
      resolved.value_string = ''
    }

    return resolved;
    }
};

module.exports = MyCustomMessage;
