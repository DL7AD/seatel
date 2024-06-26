# Seatel

This is a replacement controller (ICU - Integrated Control Unit) for the Seatel 4012 GX Antenna System. While the original ICU
can only track geostationary satellites, this replacement is able to track LEO satellites. It makes use of the original MDE (Motor
Drive Enclosure), the original IMU (inertial measurement unit) and original GPS receiver. It can be accessed with Ethernet or
WiFi (Raspberry PI used as WiFi router) and supplies a web interface and API which can be controlled with an Ethernet driven
satellite tracking program like Gpredict. Since this solution makes no use of the MXP (Media Xchange Point), the antenna can't
track it's own Azimuth, therefore the PCB integrates a magnetometer based on the MPU9250 which can track the earth magnetic field.
Since this board is used for accurate reception, it includes two power feeds with a OCXO/GPS stabilized 10 MHz feed for up to
two external LNA's and downconverters. For external power amplifiers, the board supplies switchable 5V (max. 5A), 24V and 48V.

<img src="https://github.com/DL7AD/seatel/assets/5694705/ab7390b9-cf2e-429b-9e39-52ff04ff3381" height="470" />
<img src="https://github.com/DL7AD/seatel/assets/5694705/78faea67-9972-4dff-94eb-4ea224f8aa96" height="470" />
<img src="https://github.com/DL7AD/seatel/assets/5694705/d21adcf0-5716-4258-be62-a6ccae9e2e50" height="635" />
<img src="https://github.com/DL7AD/seatel/assets/5694705/713eced3-8377-4180-8499-a58c5dcd020d" height="635" />
