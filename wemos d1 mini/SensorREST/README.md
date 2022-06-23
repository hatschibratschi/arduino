# SensorREST plumber

# Raspberry Pi
## install r

sudo apt-get install r-base -y
sudo apt-get install -y libsodium-dev libcurl4-openssl-dev

then install plumber in R

## nextcloud
### download plot

download plot to file

    wget -O plot.png http://192.168.0.4:5762/plot

### copy plot to nextcloud folder

    sudo cp plot.png /var/www/nextcloud/data/<user>/files/Documents

change user and group for nextcoud to www-data

    sudo chown www-data /var/www/nextcloud/data/<user>/files/Documents/plot.png
    sudo chgrp www-data /var/www/nextcloud/data/<user>/files/Documents/plot.png

scan nextcloud folder to import new pic to nextcloud-library

    sudo -u www-data php /var/www/nextcloud/occ files:scan --path="/<user>/files/Documents"
