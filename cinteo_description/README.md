# cinteo_description

## 1) Overview

`cinteo_description` provides the robot-specific description layer for the Cinteo mobile base.

It extends `romea_mobile_base_description` with the concrete configuration, URDF/Xacro files, meshes and `ros2_control` descriptions required to instantiate the Cinteo robot.

The Cinteo mobile base uses:

| Configuration file | Mobile base architecture | Command type |
|---|---|---|
| `config/cinteo.yaml` | `1FAS2RWD` | `one_axle_steering` |

This architecture has one front axle steering joint and two rear driving wheels.

## 2) Robot configuration

The `config/` directory contains:

| File | Purpose |
|---|---|
| `cinteo.yaml` | full Cinteo mobile base configuration |
| `teleop.yaml` | default one-axle steering teleoperation configuration |

The robot configuration follows the structure defined by `romea_mobile_base_description` and contains:

* the mobile base architecture (`1FAS2RWD`);
* geometry, wheel dimensions and chassis bounding box;
* front axle steering command and feedback information;
* rear wheel speed command and feedback information;
* inertia and control point;
* link and joint names used in the URDF and `ros2_control` descriptions.

## 3) URDF and ros2_control descriptions

The URDF description is built from:

| Path | Role |
|---|---|
| `urdf/cinteo.urdf.xacro` | main URDF entry point |
| `urdf/cinteo.xacro` | Cinteo mobile base macro |
| `urdf/cinteo.simulation.xacro` | simulator-specific Gazebo or Gazebo Classic plugin insertion |
| `meshes/` | chassis, bridge, arms and wheel meshes |

The Cinteo macro reuses the `base1FASxxx.chassis.xacro` template from `romea_mobile_base_description` and specializes it with Cinteo geometry, link names, joint names and visual meshes.

The `ros2_control` description is built from:

| Path | Role |
|---|---|
| `ros2_control/cinteo.ros2_control.urdf.xacro` | main `ros2_control` entry point |
| `ros2_control/cinteo.ros2_control.xacro` | Cinteo `ros2_control` macro |

Depending on the selected mode, the `ros2_control` description selects:

| Mode | Hardware plugin |
|---|---|
| `live` | `cinteo_hardware/CinteoHardware` |
| `simulation`, `simulation_gazebo_classic` | `romea_mobile_base_gazebo/GazeboSystemInterface1FAS2RWD` |
| `simulation_gazebo` | `romea_mobile_base_gazebo/GazeboSystemInterface1FAS2RWD` |

## 4) Python API

The installed Python module provides helper functions used by `cinteo_bringup` and by the meta-bringup workflow.

| Function | Purpose |
|---|---|
| `get_specifications_path_file()` | returns the Cinteo configuration file path |
| `get_specifications_configuration()` | loads the full robot configuration |
| `get_configuration()` | returns the compact mobile base configuration completed with manufacturer, model and version |
| `generate_configuration_file(configuration, extended)` | serializes the compact configuration |
| `generate_urdf_description(...)` | generates the Cinteo URDF description |
| `generate_ros2_control_description(...)` | generates the Cinteo `ros2_control` description |

Example:

```python
from cinteo_description import get_configuration

configuration = get_configuration()
```

## 5) Relation with other packages

`cinteo_description` is the Cinteo specialization of `romea_mobile_base_description`:

* `romea_mobile_base_description` provides the generic `1FAS2RWD` description and `ros2_control` templates;
* `cinteo_description` provides the Cinteo configuration, meshes and Xacro specialization;
* `cinteo_hardware` provides the live `ros2_control` hardware plugin;
* `cinteo_bringup` uses this package to generate configuration, URDF and `ros2_control` artifacts for live and simulation modes.
