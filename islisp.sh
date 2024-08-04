#!/bin/bash

# 新しい tmux セッションを作成（もし存在しなければ）
tmux new-session -d -s mylisp

# 最初のペインで edlis を起動
tmux send-keys -t mylisp 'edlis' C-m

# 新しいペインを作成し、eislを起動
#tmux split-window -h
#tmux send-keys -t mylisp 'eisl' C-m

# ペインのサイズを調整（オプション）
#tmux resize-pane -R 10

# セッションを表示
#tmux attach -t mylisp