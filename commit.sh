#!/bin/bash
read -p "Commit description: " desc
git status &&\
git add . && \
git add -u && \
git status &&\
git commit -m "$desc" && \
git push origin master
git status &&\
