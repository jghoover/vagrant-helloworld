#!/usr/bin/env bash

apt-get update
apt-get install -y apache2 git emacs
if ! [ -L /var/www ]; then
  rm -rf /var/www
  ln -fs /vagrant /var/www
fi
