#!/bin/bash
Date=$(date)
cd ~/408_cpp_impl || exit
find . -depth -name "*.o" -type f -delete 
find . -depth -name "*.exe" -type f -delete 
git add . 
git commit -m "$Date"
git push