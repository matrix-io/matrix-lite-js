# MATRIX-Lite-JS
 MATRIX Lite JS is a Node.js wrapper that allows users to interface with MATRIX HAL, without having to code in C++.
 
 **Note that this project will eventually become a Node module.**

# Current Implementation Roadmap
- [x] Leds
- [ ] Sensors

# Raspberry Pi Dependencies
Ensure you have a Raspberry Pi, attached with a MATRIX device, that's flashed with [Raspbian Stretch](https://www.raspberrypi.org/blog/raspbian-stretch/).

## 1. Install MATRIX HAL
**Add the MATRIX repository and key.**
```bash
curl https://apt.matrix.one/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.matrix.one/raspbian $(lsb_release -sc) main" |sudo tee /etc/apt/sources.list.d/matrixlabs.list
```
**Update your repository and packages.**
```bash
sudo apt-get update
sudo apt-get upgrade
```
**Install the the MATRIX HAL packages & Git.**
```
sudo apt-get install matrixio-creator-init libmatrixio-creator-hal libmatrixio-creator-hal-dev git
```
**Restart your device.**
```bash
reboot
```

## 2. Install Node.js
Downloads and installs the latest version of Node.js, using nvm
```bash
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.33.11/install.sh | bash
. ~/.bashrc
nvm install node
```
Use the following command to verify that Node.js was properly installed.
```
node -v
```

## 3. Download Project
Download project into any directory
```
git clone https://github.com/matrix-io/matrix-lite-js
cd matrix-lite-js
```

Install all Node.js dependencies
```
npm install
```

Run index.js
```
node.js
```
