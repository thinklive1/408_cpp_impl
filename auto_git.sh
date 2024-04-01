#!/bin/bash
Date=$(date)
cd ~/408_cpp_impl || exit
rm *.o && rm *.exe
git add . 
git commit -m "$Date"
git push
echo "git commit and push succeed!"