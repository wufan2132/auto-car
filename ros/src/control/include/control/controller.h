#include "control/lon_controller.h"

class Controller{
public:
    Controller();
    void ProduceControlCommand(msgs::chassisCommand *cmd);
    void CheckInput(void);
    void SendCmd(msgs::chassisCommand *cmd);
    void OnTimer(void);
private:
    void Init(void);

    msgs::localization localization_;
    msgs::chassis chassis_;
    msgs::trajectory trajectory_;

    LonController lon_controller_;
};