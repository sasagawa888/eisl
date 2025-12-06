#!/bin/bash
# Auto-update script for Easy-ISLisp only


DIR="$HOME/eisl"
SERVICE="eisl.service"

if [ ! -d "$DIR" ]; then
  echo "Easy-ISLisp directory not found."
  exit 0
fi

cd "$DIR"

if sudo systemctl list-unit-files | grep -q "$SERVICE"; then
  sudo systemctl stop "$SERVICE"
fi

git stash push 
git pull --rebase
make clean
make -j$(nproc)

if sudo systemctl list-unit-files | grep -q "$SERVICE"; then
  sudo systemctl start "$SERVICE"
fi

echo "Easy-ISLisp update finished."