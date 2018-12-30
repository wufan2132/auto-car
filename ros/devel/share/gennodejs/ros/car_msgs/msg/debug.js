// Auto-generated. Do not edit!

// (in-package car_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let lon_debug = require('./lon_debug.js');
let lat_debug = require('./lat_debug.js');
let mpc_debug = require('./mpc_debug.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class debug {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.ts = null;
      this.lon_debug_msg = null;
      this.lat_debug_msg = null;
      this.mpc_debug_msg = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('ts')) {
        this.ts = initObj.ts
      }
      else {
        this.ts = 0.0;
      }
      if (initObj.hasOwnProperty('lon_debug_msg')) {
        this.lon_debug_msg = initObj.lon_debug_msg
      }
      else {
        this.lon_debug_msg = new lon_debug();
      }
      if (initObj.hasOwnProperty('lat_debug_msg')) {
        this.lat_debug_msg = initObj.lat_debug_msg
      }
      else {
        this.lat_debug_msg = new lat_debug();
      }
      if (initObj.hasOwnProperty('mpc_debug_msg')) {
        this.mpc_debug_msg = initObj.mpc_debug_msg
      }
      else {
        this.mpc_debug_msg = new mpc_debug();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type debug
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [ts]
    bufferOffset = _serializer.float64(obj.ts, buffer, bufferOffset);
    // Serialize message field [lon_debug_msg]
    bufferOffset = lon_debug.serialize(obj.lon_debug_msg, buffer, bufferOffset);
    // Serialize message field [lat_debug_msg]
    bufferOffset = lat_debug.serialize(obj.lat_debug_msg, buffer, bufferOffset);
    // Serialize message field [mpc_debug_msg]
    bufferOffset = mpc_debug.serialize(obj.mpc_debug_msg, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type debug
    let len;
    let data = new debug(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [ts]
    data.ts = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [lon_debug_msg]
    data.lon_debug_msg = lon_debug.deserialize(buffer, bufferOffset);
    // Deserialize message field [lat_debug_msg]
    data.lat_debug_msg = lat_debug.deserialize(buffer, bufferOffset);
    // Deserialize message field [mpc_debug_msg]
    data.mpc_debug_msg = mpc_debug.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += lon_debug.getMessageSize(object.lon_debug_msg);
    length += lat_debug.getMessageSize(object.lat_debug_msg);
    length += mpc_debug.getMessageSize(object.mpc_debug_msg);
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car_msgs/debug';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a486330156a1499098fce50f1c4ae2b4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float64 ts
    lon_debug lon_debug_msg
    lat_debug lat_debug_msg
    mpc_debug mpc_debug_msg
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
    MSG: car_msgs/lon_debug
    Header header
    
    float64 station_reference
    float64 station_error
    float64 station_error_limited
    float64 preview_station_error
    float64 station_out
    
    float64 speed_reference
    float64 speed_error
    float64 speed_controller_input_limited
    float64 preview_speed_reference
    float64 preview_speed_error
    float64 speed_out
    
    float64 preview_acceleration_reference
    float64 acceleration_cmd_closeloop
    float64 acceleration_cmd
    float64 acceleration_lookup
    float64 speed_lookup
    float64 calibration_value
    float64 throttle_cmd
    float64 brake_cmd
    bool is_full_stop
    float64 slope_offset_compensation
    float64 current_station
    float64 path_remain
    
    
    ================================================================================
    MSG: car_msgs/lat_debug
    Header header
    
    float64 lateral_error
    float64 ref_heading
    float64 heading
    float64 heading_error
    float64 heading_error_rate
    float64 lateral_error_rate
    float64 curvature
    float64 steer_angle
    float64 steer_angle_feedforward
    float64 steer_angle_lateral_contribution
    float64 steer_angle_lateral_rate_contribution
    float64 steer_angle_heading_contribution
    float64 steer_angle_heading_rate_contribution
    float64 steer_angle_feedback
    float64 steering_position
    float64 ref_speed
    float64 steer_angle_limited
    ================================================================================
    MSG: car_msgs/mpc_debug
    Header header
    
    float64 lateral_error
    float64 ref_heading
    float64 heading
    float64 heading_error
    float64 heading_error_rate
    float64 lateral_error_rate
    float64 curvature
    float64 steer_angle
    float64 steer_angle_feedforward
    float64 steer_angle_lateral_contribution
    float64 steer_angle_lateral_rate_contribution
    float64 steer_angle_heading_contribution
    float64 steer_angle_heading_rate_contribution
    float64 steer_angle_feedback
    float64 steering_position
    float64 ref_speed
    float64 steer_angle_limited
    float64 station_reference
    float64 station_error
    float64 speed_reference
    float64 speed_error
    float64 acceleration_reference
    bool is_full_stop
    float64 station_feedback
    float64 speed_feedback
    float64 acceleration_cmd_closeloop
    float64 acceleration_cmd
    float64 acceleration_lookup
    float64 speed_lookup
    float64 calibration_value
    float64 matrix_q_updated1     # matrix_q_updated_ size 6 repeated
    float64 matrix_q_updated2     # matrix_q_updated_ size 6 repeated
    float64 matrix_q_updated3     # matrix_q_updated_ size 6 repeated
    float64 matrix_q_updated4     # matrix_q_updated_ size 6 repeated
    float64 matrix_q_updated5     # matrix_q_updated_ size 6 repeated
    float64 matrix_q_updated6     # matrix_q_updated_ size 6 repeated
    float64 matrix_r_updated1     # matrix_r_updated_ size 2  repeated
    float64 matrix_r_updated2     # matrix_r_updated_ size 2  repeated
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new debug(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.ts !== undefined) {
      resolved.ts = msg.ts;
    }
    else {
      resolved.ts = 0.0
    }

    if (msg.lon_debug_msg !== undefined) {
      resolved.lon_debug_msg = lon_debug.Resolve(msg.lon_debug_msg)
    }
    else {
      resolved.lon_debug_msg = new lon_debug()
    }

    if (msg.lat_debug_msg !== undefined) {
      resolved.lat_debug_msg = lat_debug.Resolve(msg.lat_debug_msg)
    }
    else {
      resolved.lat_debug_msg = new lat_debug()
    }

    if (msg.mpc_debug_msg !== undefined) {
      resolved.mpc_debug_msg = mpc_debug.Resolve(msg.mpc_debug_msg)
    }
    else {
      resolved.mpc_debug_msg = new mpc_debug()
    }

    return resolved;
    }
};

module.exports = debug;
