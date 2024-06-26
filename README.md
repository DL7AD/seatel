# Seatel

This is a replacement controller (ICU - Integrated Control Unit) for the Seatel 4012 GX Antenna System. While the original ICU
can only track geostationary satellites, this replacement is able to track LEO satellites. It makes use of the original MDE (Motor
Drive Enclosure), the original IMU (inertial measurement unit) and original GPS receiver. It can be accessed with Ethernet or
WiFi (Raspberry PI used as WiFi router) and supplies a web interface and API which can be controlled with an Ethernet driven
satellite tracking program like Gpredict. Since this solution makes no use of the MXP (Media Xchange Point), the antenna can't
track it's own Azimuth, therefore the PCB integrates a magnetometer based on the MPU9250 which can track the earth magnetic field.
Since this board is used for accurate reception, it includes two power feeds with a OCXO/GPS stabilized 10 MHz feed for up to
two external LNA's and downconverters. For external power amplifiers, the board supplies switchable 5V (max. 5A), 24V and 48V.
