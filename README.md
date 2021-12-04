# arduino
my arduino projects

# elegoo uno r3 on raspberry pi
download old versions from https://www.arduino.cc/en/Main/OldSoftwareReleases#1.0.x
eg 1.8.9 ARM32bit! 

untar with
`tar -xf <file>`

move unzipped dir to /opt
`sudo mv arduino-1.8.9 /opt`

complete installation with
`sudo /opt/arduino-1.8.9/install.sh`
 
```
Adding desktop shortcut, menu item and file associations for Arduino IDE...
rm: cannot remove '/usr/local/bin/arduino': No such file or directory
Removing symlink failed. Hope that's OK. If not then rerun as root with sudo.

rm: cannot remove '/usr/local/bin/arduino': No such file or directory
Removing symlink failed. Hope that's OK. If not then rerun as root with sudo.
touch: cannot touch '/root/.config/mimeapps.list': No such file or directory
/usr/bin/xdg-mime: 848: /usr/bin/xdg-mime: cannot create /root/.config/mimeapps.list.new:     Directory nonexistent

done!
```

After that Arduino-Software should be in your PIs programe-menu.
