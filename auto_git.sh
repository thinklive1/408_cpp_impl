#!/bin/bash

# 获取当前日期作为提交信息
date=$(date +%F)

# 暂存当前目录所有文件
git add . 

# 提交暂存区文件
git commit -m "$date"

# 推送到远程仓库
git push origin main

echo "git commit and push succeed!"