#!/bin/bash
# --------------------------------------------------
# Cluster Auto Update Script
# Stops service, updates project, restarts service
# --------------------------------------------------

# ノードリスト
CHILD_NODES=("node1" "node2" "node3" "node4" "node5" "node6" "node7" "node8")
SERVICE=myservice
PROJECT_DIR=/home/user/project

# アップデートコマンド
UPDATE_CMD="cd $PROJECT_DIR && git pull && make && make install"

# 並列実行
for node in "${CHILD_NODES[@]}"; do
    (
        echo "[$node] Stopping service..."
        ssh user@$node "sudo systemctl stop $SERVICE && sudo systemctl disable $SERVICE"

        echo "[$node] Updating project..."
        ssh user@$node "$UPDATE_CMD"

        echo "[$node] Restarting service..."
        ssh user@$node "sudo systemctl enable $SERVICE && sudo systemctl start $SERVICE"

        echo "[$node] Done."
    ) &
done

# 全ジョブの完了を待つ
wait
echo "All nodes updated and services restarted successfully."