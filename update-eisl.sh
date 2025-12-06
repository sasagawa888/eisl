#!/bin/bash
# Auto-update script for Easy-ISLisp only


DIR="$HOME/eisl"
SERVICE="eisl.service"

if [ ! -d "$DIR" ]; then
  echo "Easy-ISLisp directory not found."
  exit 0
fi

cd "$DIR"

if systemctl list-unit-files | grep -q "$SERVICE"; then
  systemctl stop "$SERVICE"
fi

git stash push -m 
git pull --rebase
make clean
make -j$(nproc)

if systemctl list-unit-files | grep -q "$SERVICE"; then
  systemctl start "$SERVICE"
fi

echo "Easy-ISLisp update finished."