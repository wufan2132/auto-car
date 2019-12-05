**鱼眼相机模型参数
src/prius_description/urdf/prius.urdf

**修改相机安装位置: joint - origin
<link name="front_camera_link">
    <inertial>
      <mass value="1"/>
      <inertia ixx="0.001" ixy="0.0" ixz="0.0" iyy="0.001" iyz="0.0" izz="0.001"/>
    </inertial>
  </link>
  <joint name="front_camera_joint" type="fixed">
    <parent link="chassis"/>
    <child link="front_camera_link"/>
    <origin xyz="0 -1.4 1.4" rpy="0 0 -1.5707"/>
  </joint>

  **修改相机传感器参数: gazebo - distortion
    <gazebo reference="front_camera_link">
    <sensor type="camera" name="front_camera_sensor">
      <update_rate>30.0</update_rate>
      <camera name="front_camera">
        <horizontal_fov>3.0000</horizontal_fov>
        <image>
          <width>1280</width>
          <height>720</height>
          <format>R8G8B8</format>
        </image>
        <clip>
          <near>0.02</near>
          <far>300</far>
        </clip>
        <noise>
          <type>gaussian</type>
          <mean>0.0</mean>
          <stddev>0.007</stddev>
        </noise>
         <distortion>
            <k1>-0.25</k1>
            <k2>0.12</k2>
            <k3>0.0</k3>
            <p1>-0.00028</p1>
            <p2>-0.00005</p2>
            <center>0.5 0.5</center>
        </distortion>
      </camera>
      <plugin name="front_camera_controller" filename="libgazebo_ros_camera.so">
        <alwaysOn>false</alwaysOn>
        <updateRate>0.0</updateRate>
        <cameraName>/prius/front_camera</cameraName>
        <imageTopicName>image_raw</imageTopicName>
        <cameraInfoTopicName>/prius/front_camera_info</cameraInfoTopicName>
        <frameName>camera_link</frameName>
        <hackBaseline>0.07</hackBaseline>
      </plugin>
    </sensor>
  </gazebo>