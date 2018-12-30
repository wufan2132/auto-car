// Auto-generated. Do not edit!

// (in-package car_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let trajectory_point = require('./trajectory_point.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class trajectory {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.total_path_length = null;
      this.total_path_time = null;
      this.trajectory_path = null;
      this.absolute_time = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('total_path_length')) {
        this.total_path_length = initObj.total_path_length
      }
      else {
        this.total_path_length = 0.0;
      }
      if (initObj.hasOwnProperty('total_path_time')) {
        this.total_path_time = initObj.total_path_time
      }
      else {
        this.total_path_time = 0.0;
      }
      if (initObj.hasOwnProperty('trajectory_path')) {
        this.trajectory_path = initObj.trajectory_path
      }
      else {
        this.trajectory_path = [];
      }
      if (initObj.hasOwnProperty('absolute_time')) {
        this.absolute_time = initObj.absolute_time
      }
      else {
        this.absolute_time = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type trajectory
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [total_path_length]
    bufferOffset = _serializer.float64(obj.total_path_length, buffer, bufferOffset);
    // Serialize message field [total_path_time]
    bufferOffset = _serializer.float64(obj.total_path_time, buffer, bufferOffset);
    // Serialize message field [trajectory_path]
    // Serialize the length for message field [trajectory_path]
    bufferOffset = _serializer.uint32(obj.trajectory_path.length, buffer, bufferOffset);
    obj.trajectory_path.forEach((val) => {
      bufferOffset = trajectory_point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [absolute_time]
    bufferOffset = _serializer.float64(obj.absolute_time, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type trajectory
    let len;
    let data = new trajectory(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [total_path_length]
    data.total_path_length = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [total_path_time]
    data.total_path_time = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [trajectory_path]
    // Deserialize array length for message field [trajectory_path]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.trajectory_path = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.trajectory_path[i] = trajectory_point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [absolute_time]
    data.absolute_time = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.trajectory_path.forEach((val) => {
      length += trajectory_point.getMessageSize(val);
    });
    return length + 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car_msgs/trajectory';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '61de575059f17e8f9e68b40fc86fc888';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    
    float64 total_path_length
    float64 total_path_time
    
    trajectory_point[] trajectory_path
    
    float64 absolute_time
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    ================================================================================
    MSG: car_msgs/trajectory_point
    Header header
    
    float64 x
    float64 y
    float64 z
    float64 theta
    float64 kappa
    float64 s
    
    float64 speed
    float64 accel
    
    float64 relative_time
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new trajectory(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.total_path_length !== undefined) {
      resolved.total_path_length = msg.total_path_length;
    }
    else {
      resolved.total_path_length = 0.0
    }

    if (msg.total_path_time !== undefined) {
      resolved.total_path_time = msg.total_path_time;
    }
    else {
      resolved.total_path_time = 0.0
    }

    if (msg.trajectory_path !== undefined) {
      resolved.trajectory_path = new Array(msg.trajectory_path.length);
      for (let i = 0; i < resolved.trajectory_path.length; ++i) {
        resolved.trajectory_path[i] = trajectory_point.Resolve(msg.trajectory_path[i]);
      }
    }
    else {
      resolved.trajectory_path = []
    }

    if (msg.absolute_time !== undefined) {
      resolved.absolute_time = msg.absolute_time;
    }
    else {
      resolved.absolute_time = 0.0
    }

    return resolved;
    }
};

module.exports = trajectory;
