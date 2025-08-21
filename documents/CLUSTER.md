# Cluster

By using the distributed parallel features of N-Prolog, you can use a Raspberry Pi cluster machine as a parallel Prolog machine. Below is a memo for that.

Running boot.sh at Boot on Raspberry Pi (Network-Ready)

This document explains how to automatically run your boot.sh script at boot time on a Raspberry Pi, ensuring the network is fully up before execution.
Install

1. Prepare the boot.sh Script Place your script in /home/username/nprolog/boot.sh with the following content:

sudo nano /home/username/eisl/boot.sh

```
#!/bin/bash
# Change directory to 'Easy-ISLisp'.
# If this fails (e.g., directory does not exist), exit immediately with status 1.
cd /home/username/eisl || exit 1
# Run the 'eisl' program with the '-n' option.
./eisl -n
```

Make sure the script has execute permission:

```
sudo chmod +x /home/username/eisl/boot.sh
```

2. Create a systemd Service for Network-Ready Boot Execution

Create the systemd service file /etc/systemd/system/eisl.service

sudo nano /etc/systemd/system/eisl.service

```
[Unit]
Description=Run Easy-ISLisp at boot after network is ready
After=network-online.target
Wants=network-online.target

[Service]
ExecStart=/home/username/eisl/boot.sh
WorkingDirectory=/home/username
User=usename
Restart=on-failure

[Install]
WantedBy=multi-user.target
```

```
sudo systemctl enable eisl.service
```

Key points:

- After=network-online.target ensures the script runs after the network is up.

- Wants=network-online.target requests the network to be brought up before starting

# Update child

When upgrading the child machine, please follow the procedure below.

```
sudo systemctl1 stop eisl.service
cd eisl
git pull
sudo make install
```

and reboot PIs

# systemctl
Be sure to run enable; without doing this, automatic startup will not work. stop is used for temporarily stopping the service, for example when upgrading the child machine. The stop state will be cleared upon reboot. status can be used to check the situation when automatic startup is not working properly.

```
sudo systemctl enable eisl.service

sudo systemctl stop eisl.service

sudo systemctl status eisl.service

```