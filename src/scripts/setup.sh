#!/bin/bash
set -e

echo "==> Installing..."
sudo pacman -S --needed base-devel cmake gcc ncurses lm_sensors git

echo "==> Settings lm_sensors..."
yes | sudo sensors-detect --auto
sudo systemctl enable --now lm_sensors.service || true

echo "==> Finish!"
