#!/bin/bash

# 获取当前日期作为提交信息
Date=$(date)

# 暂存当前目录所有文件
git add . 

# 提交暂存区文件
git commit -m "$Date"

# 推送到远程仓库
git push

echo "git commit and push succeed!"