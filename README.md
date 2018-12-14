# MATRIX-Lite-JS
 MATRIX Lite JS is a Node.js wrapper that allows users to interface with MATRIX HAL, without having to code in C++.

# Current Roadmap
[] - Led implementation

# Development Setup
Ensure you have a MATRIX device that's flashed with [Raspbian Stretch](https://www.raspberrypi.org/blog/raspbian-stretch/).

## 1. Install MATRIX HAL
Add the MATRIX repository and key.
```bash
curl https://apt.matrix.one/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.matrix.one/raspbian $(lsb_release -sc) main" |sudo tee /etc/apt/sources.list.d/matrixlabs.list
```
Update your repository and packages.
```bash
sudo apt-get update
sudo apt-get upgrade
```
Install the the MATRIX HAL packages.
```
sudo apt-get install matrixio-creator-init libmatrixio-creator-hal libmatrixio-creator-hal-dev
```
Restart your device.
```bash
reboot
```