// Auto-generated. Do not edit!

// (in-package car_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class lat_debug {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.lateral_error = null;
      this.ref_heading = null;
      this.heading = null;
      this.heading_error = null;
      this.heading_error_rate = null;
      this.lateral_error_rate = null;
      this.curvature = null;
      this.steer_angle = null;
      this.steer_angle_feedforward = null;
      this.steer_angle_lateral_contribution = null;
      this.steer_angle_lateral_rate_contribution = null;
      this.steer_angle_heading_contribution = null;
      this.steer_angle_heading_rate_contribution = null;
      this.steer_angle_feedback = null;
      this.steering_position = null;
      this.ref_speed = null;
      this.steer_angle_limited = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('lateral_error')) {
        this.lateral_error = initObj.lateral_error
      }
      else {
        this.lateral_error = 0.0;
      }
      if (initObj.hasOwnProperty('ref_heading')) {
        this.ref_heading = initObj.ref_heading
      }
      else {
        this.ref_heading = 0.0;
      }
      if (initObj.hasOwnProperty('heading')) {
        this.heading = initObj.heading
      }
      else {
        this.heading = 0.0;
      }
      if (initObj.hasOwnProperty('heading_error')) {
        this.heading_error = initObj.heading_error
      }
      else {
        this.heading_error = 0.0;
      }
      if (initObj.hasOwnProperty('heading_error_rate')) {
        this.heading_error_rate = initObj.heading_error_rate
      }
      else {
        this.heading_error_rate = 0.0;
      }
      if (initObj.hasOwnProperty('lateral_error_rate')) {
        this.lateral_error_rate = initObj.lateral_error_rate
      }
      else {
        this.lateral_error_rate = 0.0;
      }
      if (initObj.hasOwnProperty('curvature')) {
        this.curvature = initObj.curvature
      }
      else {
        this.curvature = 0.0;
      }
      if (initObj.hasOwnProperty('steer_angle')) {
        this.steer_angle = initObj.steer_angle
      }
      else {
        this.steer_angle = 0.0;
      }
      if (initObj.hasOwnProperty('steer_angle_feedforward')) {
        this.steer_angle_feedforward = initObj.steer_angle_feedforward
      }
      else {
        this.steer_angle_feedforward = 0.0;
      }
      if (initObj.hasOwnProperty('steer_angle_lateral_contribution')) {
        this.steer_angle_lateral_contribution = initObj.steer_angle_lateral_contribution
      }
      else {
        this.steer_angle_lateral_contribution = 0.0;
      }
      if (initObj.hasOwnProperty('steer_angle_lateral_rate_contribution')) {
        this.steer_angle_lateral_rate_contribution = initObj.steer_angle_lateral_rate_contribution
      }
      else {
        this.steer_angle_lateral_rate_contribution = 0.0;
      }
      if (initObj.hasOwnProperty('steer_angle_heading_contribution')) {
        this.steer_angle_heading_contribution = initObj.steer_angle_heading_contribution
      }
      else {
        this.steer_angle_heading_contribution = 0.0;
      }
      if (initObj.hasOwnProperty('steer_angle_heading_rate_contribution')) {
        this.steer_angle_heading_rate_contribution = initObj.steer_angle_heading_rate_contribution
      }
      else {
        this.steer_angle_heading_rate_contribution = 0.0;
      }
      if (initObj.hasOwnProperty('steer_angle_feedback')) {
        this.steer_angle_feedback = initObj.steer_angle_feedback
      }
      else {
        this.steer_angle_feedback = 0.0;
      }
      if (initObj.hasOwnProperty('steering_position')) {
        this.steering_position = initObj.steering_position
      }
      else {
        this.steering_position = 0.0;
      }
      if (initObj.hasOwnProperty('ref_speed')) {
        this.ref_speed = initObj.ref_speed
      }
      else {
        this.ref_speed = 0.0;
      }
      if (initObj.hasOwnProperty('steer_angle_limited')) {
        this.steer_angle_limited = initObj.steer_angle_limited
      }
      else {
        this.steer_angle_limited = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type lat_debug
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [lateral_error]
    bufferOffset = _serializer.float64(obj.lateral_error, buffer, bufferOffset);
    // Serialize message field [ref_heading]
    bufferOffset = _serializer.float64(obj.ref_heading, buffer, bufferOffset);
    // Serialize message field [heading]
    bufferOffset = _serializer.float64(obj.heading, buffer, bufferOffset);
    // Serialize message field [heading_error]
    bufferOffset = _serializer.float64(obj.heading_error, buffer, bufferOffset);
    // Serialize message field [heading_error_rate]
    bufferOffset = _serializer.float64(obj.heading_error_rate, buffer, bufferOffset);
    // Serialize message field [lateral_error_rate]
    bufferOffset = _serializer.float64(obj.lateral_error_rate, buffer, bufferOffset);
    // Serialize message field [curvature]
    bufferOffset = _serializer.float64(obj.curvature, buffer, bufferOffset);
    // Serialize message field [steer_angle]
    bufferOffset = _serializer.float64(obj.steer_angle, buffer, bufferOffset);
    // Serialize message field [steer_angle_feedforward]
    bufferOffset = _serializer.float64(obj.steer_angle_feedforward, buffer, bufferOffset);
    // Serialize message field [steer_angle_lateral_contribution]
    bufferOffset = _serializer.float64(obj.steer_angle_lateral_contribution, buffer, bufferOffset);
    // Serialize message field [steer_angle_lateral_rate_contribution]
    bufferOffset = _serializer.float64(obj.steer_angle_lateral_rate_contribution, buffer, bufferOffset);
    // Serialize message field [steer_angle_heading_contribution]
    bufferOffset = _serializer.float64(obj.steer_angle_heading_contribution, buffer, bufferOffset);
    // Serialize message field [steer_angle_heading_rate_contribution]
    bufferOffset = _serializer.float64(obj.steer_angle_heading_rate_contribution, buffer, bufferOffset);
    // Serialize message field [steer_angle_feedback]
    bufferOffset = _serializer.float64(obj.steer_angle_feedback, buffer, bufferOffset);
    // Serialize message field [steering_position]
    bufferOffset = _serializer.float64(obj.steering_position, buffer, bufferOffset);
    // Serialize message field [ref_speed]
    bufferOffset = _serializer.float64(obj.ref_speed, buffer, bufferOffset);
    // Serialize message field [steer_angle_limited]
    bufferOffset = _serializer.float64(obj.steer_angle_limited, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type lat_debug
    let len;
    let data = new lat_debug(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [lateral_error]
    data.lateral_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ref_heading]
    data.ref_heading = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [heading]
    data.heading = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [heading_error]
    data.heading_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [heading_error_rate]
    data.heading_error_rate = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [lateral_error_rate]
    data.lateral_error_rate = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [curvature]
    data.curvature = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_angle]
    data.steer_angle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_angle_feedforward]
    data.steer_angle_feedforward = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_angle_lateral_contribution]
    data.steer_angle_lateral_contribution = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_angle_lateral_rate_contribution]
    data.steer_angle_lateral_rate_contribution = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_angle_heading_contribution]
    data.steer_angle_heading_contribution = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_angle_heading_rate_contribution]
    data.steer_angle_heading_rate_contribution = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_angle_feedback]
    data.steer_angle_feedback = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steering_position]
    data.steering_position = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ref_speed]
    data.ref_speed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_angle_limited]
    data.steer_angle_limited = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 136;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car_msgs/lat_debug';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8df804ed8187912c1b683d311df460c6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new lat_debug(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.lateral_error !== undefined) {
      resolved.lateral_error = msg.lateral_error;
    }
    else {
      resolved.lateral_error = 0.0
    }

    if (msg.ref_heading !== undefined) {
      resolved.ref_heading = msg.ref_heading;
    }
    else {
      resolved.ref_heading = 0.0
    }

    if (msg.heading !== undefined) {
      resolved.heading = msg.heading;
    }
    else {
      resolved.heading = 0.0
    }

    if (msg.heading_error !== undefined) {
      resolved.heading_error = msg.heading_error;
    }
    else {
      resolved.heading_error = 0.0
    }

    if (msg.heading_error_rate !== undefined) {
      resolved.heading_error_rate = msg.heading_error_rate;
    }
    else {
      resolved.heading_error_rate = 0.0
    }

    if (msg.lateral_error_rate !== undefined) {
      resolved.lateral_error_rate = msg.lateral_error_rate;
    }
    else {
      resolved.lateral_error_rate = 0.0
    }

    if (msg.curvature !== undefined) {
      resolved.curvature = msg.curvature;
    }
    else {
      resolved.curvature = 0.0
    }

    if (msg.steer_angle !== undefined) {
      resolved.steer_angle = msg.steer_angle;
    }
    else {
      resolved.steer_angle = 0.0
    }

    if (msg.steer_angle_feedforward !== undefined) {
      resolved.steer_angle_feedforward = msg.steer_angle_feedforward;
    }
    else {
      resolved.steer_angle_feedforward = 0.0
    }

    if (msg.steer_angle_lateral_contribution !== undefined) {
      resolved.steer_angle_lateral_contribution = msg.steer_angle_lateral_contribution;
    }
    else {
      resolved.steer_angle_lateral_contribution = 0.0
    }

    if (msg.steer_angle_lateral_rate_contribution !== undefined) {
      resolved.steer_angle_lateral_rate_contribution = msg.steer_angle_lateral_rate_contribution;
    }
    else {
      resolved.steer_angle_lateral_rate_contribution = 0.0
    }

    if (msg.steer_angle_heading_contribution !== undefined) {
      resolved.steer_angle_heading_contribution = msg.steer_angle_heading_contribution;
    }
    else {
      resolved.steer_angle_heading_contribution = 0.0
    }

    if (msg.steer_angle_heading_rate_contribution !== undefined) {
      resolved.steer_angle_heading_rate_contribution = msg.steer_angle_heading_rate_contribution;
    }
    else {
      resolved.steer_angle_heading_rate_contribution = 0.0
    }

    if (msg.steer_angle_feedback !== undefined) {
      resolved.steer_angle_feedback = msg.steer_angle_feedback;
    }
    else {
      resolved.steer_angle_feedback = 0.0
    }

    if (msg.steering_position !== undefined) {
      resolved.steering_position = msg.steering_position;
    }
    else {
      resolved.steering_position = 0.0
    }

    if (msg.ref_speed !== undefined) {
      resolved.ref_speed = msg.ref_speed;
    }
    else {
      resolved.ref_speed = 0.0
    }

    if (msg.steer_angle_limited !== undefined) {
      resolved.steer_angle_limited = msg.steer_angle_limited;
    }
    else {
      resolved.steer_angle_limited = 0.0
    }

    return resolved;
    }
};

module.exports = lat_debug;
