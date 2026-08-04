# cinteo

## Overview

`cinteo` groups the ROS2 packages that describe, launch and control the Cinteo mobile base in live and simulation modes.

This repository-level README gives a map of the stack. Detailed information about each package can be found in the corresponding package README.

## Packages

| Package | Role |
| --- | --- |
| `cinteo` | Metapackage that groups the Cinteo ROS2 packages. |
| `cinteo_description` | Robot-specific description layer for Cinteo, including configuration files, URDF/Xacro descriptions, meshes and ros2_control descriptions. |
| `cinteo_bringup` | Main integration entry point for generating Cinteo configuration files, URDF descriptions, ros2_control descriptions and launch files. |
| `cinteo_hardware` | Live `ros2_control` hardware plugin for the Cinteo mobile base, built on the generic `1FAS2RWD` hardware abstraction. |

## Usage

In most cases, start with `cinteo_bringup`. It is the user-facing entry point of the stack and the package used by `romea_mobile_base_meta_bringup` when a Cinteo model is selected from a mobile base meta-description.

The Cinteo stack is a robot-specific specialization of `romea_mobile_base`. The mobile base architecture is `1FAS2RWD`; `cinteo_description` provides the concrete geometry and generated descriptions, `cinteo_hardware` provides the live hardware implementation, and `cinteo_bringup` connects these pieces to the generic mobile base launch workflow.

## License

This project is released under the Apache License 2.0. See the `LICENSE` file for details.

## Authors

The `cinteo` project was developed by Jean Laneurit in the context of the TIRREX ANR project.

## Contact

For questions or comments about this project, please contact [Jean Laneurit](mailto:jean.laneurit@inrae.fr).
