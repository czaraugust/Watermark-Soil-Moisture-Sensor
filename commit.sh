#!/bin/bash
read -p "Commit description: " desc
git status &&\
echo "Aperte <ENTER> para ADD"
read '' 
git add . && \
git add -u && \
echo "Aperte <ENTER> para COMMIT"
read '' 
git commit -m "$desc" && \
echo "Aperte <ENTER> para PUSH"
read '' 
git push origin master

