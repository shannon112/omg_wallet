# omg_wallet
offline image wallet
```
add additional boards manager URLs: https://dl.espressif.com/dl/package_esp32_index.json
go to board manager install: esp32
select board: Node32s
select port
download https://github.com/Bodmer/TFT_eSPI zip
add .ZIP library
change TFT_eSPI/User_Setup.h
sudo chown shanlee /dev/ttyUSB0
```
python2
```
cd /usr/bin
sudo ln -s python2.7 python
curl https://bootstrap.pypa.io/pip/2.7/get-pip.py -o get-pip.py
python get-pip.py
sudo apt install python-pip
python -m pip install pyserial
```
