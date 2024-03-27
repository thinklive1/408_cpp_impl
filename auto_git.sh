#!/bin/bash
Date=$(date)
git add . 
git commit -m "$Date"
git push
echo "git commit and push succeed!"