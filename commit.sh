#!/bin/bash
read -p "Commit description: " desc
git status &&\
echo "Aperte <ENTER> para ADD"
read -p "$*"
git add . && \
git add -u && \
echo "Aperte <ENTER> para COMMIT"
 read -p "$*"
git commit -m "$desc" && \
echo "Aperte <ENTER> para PUSH"
read -p "$*"
git push origin master

