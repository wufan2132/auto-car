
class PidConf {
 public:
  PidConf()
      : integrator_enable(0),
        integrator_saturation_level(0),
        kp(0),
        ki(0),
        kd(0),
        kaw(0),
        output_saturation_level(0){};

  virtual ~PidConf(){};
  bool integrator_enable;
  double integrator_saturation_level;
  double kp;
  double ki;
  double kd;
  double kaw;
  double output_saturation_level;
};

/**
 * @class PIDController
 * @brief A proportional–integral–derivative controller for speed and steering
 using defualt integral hold
 */
class PIDController {
 public:
  PIDController() {
    kp_ = 0.0;
    ki_ = 0.0;
    kd_ = 0.0;
    kaw_ = 0.0;
    previous_error_ = 0.0;
    previous_output_ = 0.0;
    integral_ = 0.0;
    integrator_saturation_high_ = 0.0;
    integrator_saturation_low_ = 0.0;
    first_hit_ = false;
    integrator_enabled_ = false;
    integrator_hold_ = false;
    integrator_saturation_status_ = 0;
    // Only used for pid_BC_controller and pid_IC_controller
    output_saturation_high_ = 0.0;
    output_saturation_low_ = 0.0;
    output_saturation_status_ = 0;
  }
  /**
   * @brief initialize pid controller
   * @param pid_conf configuration for pid controller
   */
  void Init(const PidConf &pid_conf);

  /**
   * @brief set pid controller coefficients for the proportional,
   * integral, and derivative
   * @param pid_conf configuration for pid controller
   */
  void SetPID(const PidConf &pid_conf);

  /**
   * @brief reset variables for pid controller
   */
  void Reset();

  /**
   * @brief compute control value based on the error
   * @param error error value, the difference between
   * a desired value and a measured value
   * @param dt sampling time interval
   * @return control value based on PID terms
   */
  virtual double Control(const double error, const double dt);

  /**
   * @brief get saturation status
   * @return saturation status
   */
  int IntegratorSaturationStatus() const;

  /**
   * @brief get status that if integrator is hold
   * @return if integrator is hold return true
   */
  bool IntegratorHold() const;

  /**
   * @brief set whether to hold integrator component at its current value.
   * @param hold
   */
  void SetIntegratorHold(bool hold);

 protected:
  double kp_;
  double ki_;
  double kd_;
  double kaw_;
  double previous_error_;
  double previous_output_;
  double integral_;
  double integrator_saturation_high_;
  double integrator_saturation_low_;
  bool first_hit_;
  bool integrator_enabled_;
  bool integrator_hold_;
  int integrator_saturation_status_;
  // Only used for pid_BC_controller and pid_IC_controller
  double output_saturation_high_;
  double output_saturation_low_;
  int output_saturation_status_;
};