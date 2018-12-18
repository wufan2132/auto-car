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

class mpc_debug {
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
      this.station_reference = null;
      this.station_error = null;
      this.speed_reference = null;
      this.speed_error = null;
      this.acceleration_reference = null;
      this.is_full_stop = null;
      this.station_feedback = null;
      this.speed_feedback = null;
      this.acceleration_cmd_closeloop = null;
      this.acceleration_cmd = null;
      this.acceleration_lookup = null;
      this.speed_lookup = null;
      this.calibration_value = null;
      this.matrix_q_updated1 = null;
      this.matrix_q_updated2 = null;
      this.matrix_q_updated3 = null;
      this.matrix_q_updated4 = null;
      this.matrix_q_updated5 = null;
      this.matrix_q_updated6 = null;
      this.matrix_r_updated1 = null;
      this.matrix_r_updated2 = null;
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
      if (initObj.hasOwnProperty('station_reference')) {
        this.station_reference = initObj.station_reference
      }
      else {
        this.station_reference = 0.0;
      }
      if (initObj.hasOwnProperty('station_error')) {
        this.station_error = initObj.station_error
      }
      else {
        this.station_error = 0.0;
      }
      if (initObj.hasOwnProperty('speed_reference')) {
        this.speed_reference = initObj.speed_reference
      }
      else {
        this.speed_reference = 0.0;
      }
      if (initObj.hasOwnProperty('speed_error')) {
        this.speed_error = initObj.speed_error
      }
      else {
        this.speed_error = 0.0;
      }
      if (initObj.hasOwnProperty('acceleration_reference')) {
        this.acceleration_reference = initObj.acceleration_reference
      }
      else {
        this.acceleration_reference = 0.0;
      }
      if (initObj.hasOwnProperty('is_full_stop')) {
        this.is_full_stop = initObj.is_full_stop
      }
      else {
        this.is_full_stop = false;
      }
      if (initObj.hasOwnProperty('station_feedback')) {
        this.station_feedback = initObj.station_feedback
      }
      else {
        this.station_feedback = 0.0;
      }
      if (initObj.hasOwnProperty('speed_feedback')) {
        this.speed_feedback = initObj.speed_feedback
      }
      else {
        this.speed_feedback = 0.0;
      }
      if (initObj.hasOwnProperty('acceleration_cmd_closeloop')) {
        this.acceleration_cmd_closeloop = initObj.acceleration_cmd_closeloop
      }
      else {
        this.acceleration_cmd_closeloop = 0.0;
      }
      if (initObj.hasOwnProperty('acceleration_cmd')) {
        this.acceleration_cmd = initObj.acceleration_cmd
      }
      else {
        this.acceleration_cmd = 0.0;
      }
      if (initObj.hasOwnProperty('acceleration_lookup')) {
        this.acceleration_lookup = initObj.acceleration_lookup
      }
      else {
        this.acceleration_lookup = 0.0;
      }
      if (initObj.hasOwnProperty('speed_lookup')) {
        this.speed_lookup = initObj.speed_lookup
      }
      else {
        this.speed_lookup = 0.0;
      }
      if (initObj.hasOwnProperty('calibration_value')) {
        this.calibration_value = initObj.calibration_value
      }
      else {
        this.calibration_value = 0.0;
      }
      if (initObj.hasOwnProperty('matrix_q_updated1')) {
        this.matrix_q_updated1 = initObj.matrix_q_updated1
      }
      else {
        this.matrix_q_updated1 = 0.0;
      }
      if (initObj.hasOwnProperty('matrix_q_updated2')) {
        this.matrix_q_updated2 = initObj.matrix_q_updated2
      }
      else {
        this.matrix_q_updated2 = 0.0;
      }
      if (initObj.hasOwnProperty('matrix_q_updated3')) {
        this.matrix_q_updated3 = initObj.matrix_q_updated3
      }
      else {
        this.matrix_q_updated3 = 0.0;
      }
      if (initObj.hasOwnProperty('matrix_q_updated4')) {
        this.matrix_q_updated4 = initObj.matrix_q_updated4
      }
      else {
        this.matrix_q_updated4 = 0.0;
      }
      if (initObj.hasOwnProperty('matrix_q_updated5')) {
        this.matrix_q_updated5 = initObj.matrix_q_updated5
      }
      else {
        this.matrix_q_updated5 = 0.0;
      }
      if (initObj.hasOwnProperty('matrix_q_updated6')) {
        this.matrix_q_updated6 = initObj.matrix_q_updated6
      }
      else {
        this.matrix_q_updated6 = 0.0;
      }
      if (initObj.hasOwnProperty('matrix_r_updated1')) {
        this.matrix_r_updated1 = initObj.matrix_r_updated1
      }
      else {
        this.matrix_r_updated1 = 0.0;
      }
      if (initObj.hasOwnProperty('matrix_r_updated2')) {
        this.matrix_r_updated2 = initObj.matrix_r_updated2
      }
      else {
        this.matrix_r_updated2 = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mpc_debug
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
    // Serialize message field [station_reference]
    bufferOffset = _serializer.float64(obj.station_reference, buffer, bufferOffset);
    // Serialize message field [station_error]
    bufferOffset = _serializer.float64(obj.station_error, buffer, bufferOffset);
    // Serialize message field [speed_reference]
    bufferOffset = _serializer.float64(obj.speed_reference, buffer, bufferOffset);
    // Serialize message field [speed_error]
    bufferOffset = _serializer.float64(obj.speed_error, buffer, bufferOffset);
    // Serialize message field [acceleration_reference]
    bufferOffset = _serializer.float64(obj.acceleration_reference, buffer, bufferOffset);
    // Serialize message field [is_full_stop]
    bufferOffset = _serializer.bool(obj.is_full_stop, buffer, bufferOffset);
    // Serialize message field [station_feedback]
    bufferOffset = _serializer.float64(obj.station_feedback, buffer, bufferOffset);
    // Serialize message field [speed_feedback]
    bufferOffset = _serializer.float64(obj.speed_feedback, buffer, bufferOffset);
    // Serialize message field [acceleration_cmd_closeloop]
    bufferOffset = _serializer.float64(obj.acceleration_cmd_closeloop, buffer, bufferOffset);
    // Serialize message field [acceleration_cmd]
    bufferOffset = _serializer.float64(obj.acceleration_cmd, buffer, bufferOffset);
    // Serialize message field [acceleration_lookup]
    bufferOffset = _serializer.float64(obj.acceleration_lookup, buffer, bufferOffset);
    // Serialize message field [speed_lookup]
    bufferOffset = _serializer.float64(obj.speed_lookup, buffer, bufferOffset);
    // Serialize message field [calibration_value]
    bufferOffset = _serializer.float64(obj.calibration_value, buffer, bufferOffset);
    // Serialize message field [matrix_q_updated1]
    bufferOffset = _serializer.float64(obj.matrix_q_updated1, buffer, bufferOffset);
    // Serialize message field [matrix_q_updated2]
    bufferOffset = _serializer.float64(obj.matrix_q_updated2, buffer, bufferOffset);
    // Serialize message field [matrix_q_updated3]
    bufferOffset = _serializer.float64(obj.matrix_q_updated3, buffer, bufferOffset);
    // Serialize message field [matrix_q_updated4]
    bufferOffset = _serializer.float64(obj.matrix_q_updated4, buffer, bufferOffset);
    // Serialize message field [matrix_q_updated5]
    bufferOffset = _serializer.float64(obj.matrix_q_updated5, buffer, bufferOffset);
    // Serialize message field [matrix_q_updated6]
    bufferOffset = _serializer.float64(obj.matrix_q_updated6, buffer, bufferOffset);
    // Serialize message field [matrix_r_updated1]
    bufferOffset = _serializer.float64(obj.matrix_r_updated1, buffer, bufferOffset);
    // Serialize message field [matrix_r_updated2]
    bufferOffset = _serializer.float64(obj.matrix_r_updated2, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mpc_debug
    let len;
    let data = new mpc_debug(null);
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
    // Deserialize message field [station_reference]
    data.station_reference = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [station_error]
    data.station_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_reference]
    data.speed_reference = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_error]
    data.speed_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [acceleration_reference]
    data.acceleration_reference = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [is_full_stop]
    data.is_full_stop = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [station_feedback]
    data.station_feedback = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_feedback]
    data.speed_feedback = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [acceleration_cmd_closeloop]
    data.acceleration_cmd_closeloop = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [acceleration_cmd]
    data.acceleration_cmd = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [acceleration_lookup]
    data.acceleration_lookup = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_lookup]
    data.speed_lookup = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [calibration_value]
    data.calibration_value = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [matrix_q_updated1]
    data.matrix_q_updated1 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [matrix_q_updated2]
    data.matrix_q_updated2 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [matrix_q_updated3]
    data.matrix_q_updated3 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [matrix_q_updated4]
    data.matrix_q_updated4 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [matrix_q_updated5]
    data.matrix_q_updated5 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [matrix_q_updated6]
    data.matrix_q_updated6 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [matrix_r_updated1]
    data.matrix_r_updated1 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [matrix_r_updated2]
    data.matrix_r_updated2 = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 297;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car_msgs/mpc_debug';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8e149c22ce5f62150360f708ec54ee13';
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
    const resolved = new mpc_debug(null);
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

    if (msg.station_reference !== undefined) {
      resolved.station_reference = msg.station_reference;
    }
    else {
      resolved.station_reference = 0.0
    }

    if (msg.station_error !== undefined) {
      resolved.station_error = msg.station_error;
    }
    else {
      resolved.station_error = 0.0
    }

    if (msg.speed_reference !== undefined) {
      resolved.speed_reference = msg.speed_reference;
    }
    else {
      resolved.speed_reference = 0.0
    }

    if (msg.speed_error !== undefined) {
      resolved.speed_error = msg.speed_error;
    }
    else {
      resolved.speed_error = 0.0
    }

    if (msg.acceleration_reference !== undefined) {
      resolved.acceleration_reference = msg.acceleration_reference;
    }
    else {
      resolved.acceleration_reference = 0.0
    }

    if (msg.is_full_stop !== undefined) {
      resolved.is_full_stop = msg.is_full_stop;
    }
    else {
      resolved.is_full_stop = false
    }

    if (msg.station_feedback !== undefined) {
      resolved.station_feedback = msg.station_feedback;
    }
    else {
      resolved.station_feedback = 0.0
    }

    if (msg.speed_feedback !== undefined) {
      resolved.speed_feedback = msg.speed_feedback;
    }
    else {
      resolved.speed_feedback = 0.0
    }

    if (msg.acceleration_cmd_closeloop !== undefined) {
      resolved.acceleration_cmd_closeloop = msg.acceleration_cmd_closeloop;
    }
    else {
      resolved.acceleration_cmd_closeloop = 0.0
    }

    if (msg.acceleration_cmd !== undefined) {
      resolved.acceleration_cmd = msg.acceleration_cmd;
    }
    else {
      resolved.acceleration_cmd = 0.0
    }

    if (msg.acceleration_lookup !== undefined) {
      resolved.acceleration_lookup = msg.acceleration_lookup;
    }
    else {
      resolved.acceleration_lookup = 0.0
    }

    if (msg.speed_lookup !== undefined) {
      resolved.speed_lookup = msg.speed_lookup;
    }
    else {
      resolved.speed_lookup = 0.0
    }

    if (msg.calibration_value !== undefined) {
      resolved.calibration_value = msg.calibration_value;
    }
    else {
      resolved.calibration_value = 0.0
    }

    if (msg.matrix_q_updated1 !== undefined) {
      resolved.matrix_q_updated1 = msg.matrix_q_updated1;
    }
    else {
      resolved.matrix_q_updated1 = 0.0
    }

    if (msg.matrix_q_updated2 !== undefined) {
      resolved.matrix_q_updated2 = msg.matrix_q_updated2;
    }
    else {
      resolved.matrix_q_updated2 = 0.0
    }

    if (msg.matrix_q_updated3 !== undefined) {
      resolved.matrix_q_updated3 = msg.matrix_q_updated3;
    }
    else {
      resolved.matrix_q_updated3 = 0.0
    }

    if (msg.matrix_q_updated4 !== undefined) {
      resolved.matrix_q_updated4 = msg.matrix_q_updated4;
    }
    else {
      resolved.matrix_q_updated4 = 0.0
    }

    if (msg.matrix_q_updated5 !== undefined) {
      resolved.matrix_q_updated5 = msg.matrix_q_updated5;
    }
    else {
      resolved.matrix_q_updated5 = 0.0
    }

    if (msg.matrix_q_updated6 !== undefined) {
      resolved.matrix_q_updated6 = msg.matrix_q_updated6;
    }
    else {
      resolved.matrix_q_updated6 = 0.0
    }

    if (msg.matrix_r_updated1 !== undefined) {
      resolved.matrix_r_updated1 = msg.matrix_r_updated1;
    }
    else {
      resolved.matrix_r_updated1 = 0.0
    }

    if (msg.matrix_r_updated2 !== undefined) {
      resolved.matrix_r_updated2 = msg.matrix_r_updated2;
    }
    else {
      resolved.matrix_r_updated2 = 0.0
    }

    return resolved;
    }
};

module.exports = mpc_debug;
