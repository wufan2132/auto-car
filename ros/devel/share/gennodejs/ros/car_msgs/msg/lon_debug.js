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

class lon_debug {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.station_reference = null;
      this.station_error = null;
      this.station_error_limited = null;
      this.preview_station_error = null;
      this.station_out = null;
      this.speed_reference = null;
      this.speed_error = null;
      this.speed_controller_input_limited = null;
      this.preview_speed_reference = null;
      this.preview_speed_error = null;
      this.speed_out = null;
      this.preview_acceleration_reference = null;
      this.acceleration_cmd_closeloop = null;
      this.acceleration_cmd = null;
      this.acceleration_lookup = null;
      this.speed_lookup = null;
      this.calibration_value = null;
      this.throttle_cmd = null;
      this.brake_cmd = null;
      this.is_full_stop = null;
      this.slope_offset_compensation = null;
      this.current_station = null;
      this.path_remain = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
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
      if (initObj.hasOwnProperty('station_error_limited')) {
        this.station_error_limited = initObj.station_error_limited
      }
      else {
        this.station_error_limited = 0.0;
      }
      if (initObj.hasOwnProperty('preview_station_error')) {
        this.preview_station_error = initObj.preview_station_error
      }
      else {
        this.preview_station_error = 0.0;
      }
      if (initObj.hasOwnProperty('station_out')) {
        this.station_out = initObj.station_out
      }
      else {
        this.station_out = 0.0;
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
      if (initObj.hasOwnProperty('speed_controller_input_limited')) {
        this.speed_controller_input_limited = initObj.speed_controller_input_limited
      }
      else {
        this.speed_controller_input_limited = 0.0;
      }
      if (initObj.hasOwnProperty('preview_speed_reference')) {
        this.preview_speed_reference = initObj.preview_speed_reference
      }
      else {
        this.preview_speed_reference = 0.0;
      }
      if (initObj.hasOwnProperty('preview_speed_error')) {
        this.preview_speed_error = initObj.preview_speed_error
      }
      else {
        this.preview_speed_error = 0.0;
      }
      if (initObj.hasOwnProperty('speed_out')) {
        this.speed_out = initObj.speed_out
      }
      else {
        this.speed_out = 0.0;
      }
      if (initObj.hasOwnProperty('preview_acceleration_reference')) {
        this.preview_acceleration_reference = initObj.preview_acceleration_reference
      }
      else {
        this.preview_acceleration_reference = 0.0;
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
      if (initObj.hasOwnProperty('throttle_cmd')) {
        this.throttle_cmd = initObj.throttle_cmd
      }
      else {
        this.throttle_cmd = 0.0;
      }
      if (initObj.hasOwnProperty('brake_cmd')) {
        this.brake_cmd = initObj.brake_cmd
      }
      else {
        this.brake_cmd = 0.0;
      }
      if (initObj.hasOwnProperty('is_full_stop')) {
        this.is_full_stop = initObj.is_full_stop
      }
      else {
        this.is_full_stop = false;
      }
      if (initObj.hasOwnProperty('slope_offset_compensation')) {
        this.slope_offset_compensation = initObj.slope_offset_compensation
      }
      else {
        this.slope_offset_compensation = 0.0;
      }
      if (initObj.hasOwnProperty('current_station')) {
        this.current_station = initObj.current_station
      }
      else {
        this.current_station = 0.0;
      }
      if (initObj.hasOwnProperty('path_remain')) {
        this.path_remain = initObj.path_remain
      }
      else {
        this.path_remain = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type lon_debug
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [station_reference]
    bufferOffset = _serializer.float64(obj.station_reference, buffer, bufferOffset);
    // Serialize message field [station_error]
    bufferOffset = _serializer.float64(obj.station_error, buffer, bufferOffset);
    // Serialize message field [station_error_limited]
    bufferOffset = _serializer.float64(obj.station_error_limited, buffer, bufferOffset);
    // Serialize message field [preview_station_error]
    bufferOffset = _serializer.float64(obj.preview_station_error, buffer, bufferOffset);
    // Serialize message field [station_out]
    bufferOffset = _serializer.float64(obj.station_out, buffer, bufferOffset);
    // Serialize message field [speed_reference]
    bufferOffset = _serializer.float64(obj.speed_reference, buffer, bufferOffset);
    // Serialize message field [speed_error]
    bufferOffset = _serializer.float64(obj.speed_error, buffer, bufferOffset);
    // Serialize message field [speed_controller_input_limited]
    bufferOffset = _serializer.float64(obj.speed_controller_input_limited, buffer, bufferOffset);
    // Serialize message field [preview_speed_reference]
    bufferOffset = _serializer.float64(obj.preview_speed_reference, buffer, bufferOffset);
    // Serialize message field [preview_speed_error]
    bufferOffset = _serializer.float64(obj.preview_speed_error, buffer, bufferOffset);
    // Serialize message field [speed_out]
    bufferOffset = _serializer.float64(obj.speed_out, buffer, bufferOffset);
    // Serialize message field [preview_acceleration_reference]
    bufferOffset = _serializer.float64(obj.preview_acceleration_reference, buffer, bufferOffset);
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
    // Serialize message field [throttle_cmd]
    bufferOffset = _serializer.float64(obj.throttle_cmd, buffer, bufferOffset);
    // Serialize message field [brake_cmd]
    bufferOffset = _serializer.float64(obj.brake_cmd, buffer, bufferOffset);
    // Serialize message field [is_full_stop]
    bufferOffset = _serializer.bool(obj.is_full_stop, buffer, bufferOffset);
    // Serialize message field [slope_offset_compensation]
    bufferOffset = _serializer.float64(obj.slope_offset_compensation, buffer, bufferOffset);
    // Serialize message field [current_station]
    bufferOffset = _serializer.float64(obj.current_station, buffer, bufferOffset);
    // Serialize message field [path_remain]
    bufferOffset = _serializer.float64(obj.path_remain, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type lon_debug
    let len;
    let data = new lon_debug(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [station_reference]
    data.station_reference = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [station_error]
    data.station_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [station_error_limited]
    data.station_error_limited = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [preview_station_error]
    data.preview_station_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [station_out]
    data.station_out = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_reference]
    data.speed_reference = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_error]
    data.speed_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_controller_input_limited]
    data.speed_controller_input_limited = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [preview_speed_reference]
    data.preview_speed_reference = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [preview_speed_error]
    data.preview_speed_error = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_out]
    data.speed_out = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [preview_acceleration_reference]
    data.preview_acceleration_reference = _deserializer.float64(buffer, bufferOffset);
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
    // Deserialize message field [throttle_cmd]
    data.throttle_cmd = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [brake_cmd]
    data.brake_cmd = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [is_full_stop]
    data.is_full_stop = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [slope_offset_compensation]
    data.slope_offset_compensation = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [current_station]
    data.current_station = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [path_remain]
    data.path_remain = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 177;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car_msgs/lon_debug';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '323d2f9871df4f44858dc872121f8cf2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new lon_debug(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
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

    if (msg.station_error_limited !== undefined) {
      resolved.station_error_limited = msg.station_error_limited;
    }
    else {
      resolved.station_error_limited = 0.0
    }

    if (msg.preview_station_error !== undefined) {
      resolved.preview_station_error = msg.preview_station_error;
    }
    else {
      resolved.preview_station_error = 0.0
    }

    if (msg.station_out !== undefined) {
      resolved.station_out = msg.station_out;
    }
    else {
      resolved.station_out = 0.0
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

    if (msg.speed_controller_input_limited !== undefined) {
      resolved.speed_controller_input_limited = msg.speed_controller_input_limited;
    }
    else {
      resolved.speed_controller_input_limited = 0.0
    }

    if (msg.preview_speed_reference !== undefined) {
      resolved.preview_speed_reference = msg.preview_speed_reference;
    }
    else {
      resolved.preview_speed_reference = 0.0
    }

    if (msg.preview_speed_error !== undefined) {
      resolved.preview_speed_error = msg.preview_speed_error;
    }
    else {
      resolved.preview_speed_error = 0.0
    }

    if (msg.speed_out !== undefined) {
      resolved.speed_out = msg.speed_out;
    }
    else {
      resolved.speed_out = 0.0
    }

    if (msg.preview_acceleration_reference !== undefined) {
      resolved.preview_acceleration_reference = msg.preview_acceleration_reference;
    }
    else {
      resolved.preview_acceleration_reference = 0.0
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

    if (msg.throttle_cmd !== undefined) {
      resolved.throttle_cmd = msg.throttle_cmd;
    }
    else {
      resolved.throttle_cmd = 0.0
    }

    if (msg.brake_cmd !== undefined) {
      resolved.brake_cmd = msg.brake_cmd;
    }
    else {
      resolved.brake_cmd = 0.0
    }

    if (msg.is_full_stop !== undefined) {
      resolved.is_full_stop = msg.is_full_stop;
    }
    else {
      resolved.is_full_stop = false
    }

    if (msg.slope_offset_compensation !== undefined) {
      resolved.slope_offset_compensation = msg.slope_offset_compensation;
    }
    else {
      resolved.slope_offset_compensation = 0.0
    }

    if (msg.current_station !== undefined) {
      resolved.current_station = msg.current_station;
    }
    else {
      resolved.current_station = 0.0
    }

    if (msg.path_remain !== undefined) {
      resolved.path_remain = msg.path_remain;
    }
    else {
      resolved.path_remain = 0.0
    }

    return resolved;
    }
};

module.exports = lon_debug;
